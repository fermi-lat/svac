#include <stdio.h>
#include <typeinfo>
#include <cassert>
#include <string>
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/Service.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "idents/TowerId.h"
#include "CalibData/CalibModel.h"
#include "CalibData/Tkr/BadStrips.h"
#include "IOracleDbSvc.h"
#include "OCIWrapper.h"
#include "TkrGeo.h"
#include "CalibrationDescription.h"
#include "TkrIndex.h"
#include "TkrDeadChannel.h"
#include "TkrNoisyChannel.h"
#include "Constants.h"

class OracleDbSvc;

class GetTkrBadStrip;

/**
 *     @class BadVisitor
 *   Minimal class derived from CalibData::BadStripsVisitor to
 *   check out BadStrips visitor interface.
*/
class BadVisitor : public CalibData::BadStripsVisitor {
public:
  BadVisitor(GetTkrBadStrip* get=0) : m_get(get) {}
    
  void setGet(GetTkrBadStrip* get) {m_get = get;}
    
  virtual CalibData::eVisitorRet badTower(unsigned int row, unsigned int col,
					  int badness)
  { return CalibData::USER_DONE; }
    
  virtual CalibData::eVisitorRet badPlane(unsigned int row, unsigned int col, 
					  unsigned int tray, bool top,
					  int badness, bool allBad,
					  const CalibData::StripCol& strips);
private:
  GetTkrBadStrip* m_get;
};


/** 
 *   @class GetTkrBadStrip
 *  Algorithm retrieving TKR dead/hot strips from SAS's calibration database 
 *  and populating I&T's oracle database
*/

class GetTkrBadStrip : public Algorithm {
public:
  GetTkrBadStrip(const std::string& name, ISvcLocator* pSvcLocator); 

  StatusCode initialize();

  StatusCode execute();

  StatusCode finalize();

  friend class BadVisitor;

private:

  StatusCode fillTkrBadStripTable(CalibData::BadStrips* pBad);

  StatusCode fillDescriptionTables();

  IDataProviderSvc* m_pCalibDataSvc;
  IOracleDbSvc* m_pOracleDbSvc;
  
  std::string m_calibFlavor;

  OCIWrapper* m_db;

  CalibrationDescription m_calDes;

  TkrIndex m_tkrIndex;

  TkrDeadChannel m_tkrDeadChannel;
  TkrNoisyChannel m_tkrNoisyChannel;

  /// used in BadVisitor::badPlane to determine whether it is processing dead
  /// or noisy strip
  bool m_procDeadCh; 

  BadVisitor m_visitor;
};


/// Instantiation of a static factory to create instances of this algorithm
static const AlgFactory<GetTkrBadStrip> Factory;
const IAlgFactory& GetTkrBadStripFactory = Factory;


GetTkrBadStrip::GetTkrBadStrip(const std::string&  name, 
                 ISvcLocator*        pSvcLocator )
  : Algorithm(name, pSvcLocator), m_pCalibDataSvc(0), m_pOracleDbSvc(0),
    m_db(0)
{
  // Declare properties here.
  declareProperty("calibFlavor",  m_calibFlavor);

  declareProperty("source",  m_calDes.m_source=Constants::CosmicMuon);
  declareProperty("hardware", m_calDes.m_hardware=Constants::EM2);
  declareProperty("location", m_calDes.m_location=Constants::SlacCleanRoom);
  declareProperty("calibType", m_calDes.m_calibType=Constants::TkrNoisyChannel);
  declareProperty("procLevel", m_calDes.m_procLevel=Constants::Test);
  declareProperty("status", m_calDes.m_status=Constants::Ok);
  declareProperty("validStartTime", m_calDes.m_validStartTime="");
  declareProperty("validEndTime", m_calDes.m_validEndTime="");
  declareProperty("creationTime", m_calDes.m_creationTime="2003-10-11 12:00");
  declareProperty("orbitPosition", m_calDes.m_orbitPos=-1);
  declareProperty("temperature", m_calDes.m_temperature=-9999);
  declareProperty("humidity", m_calDes.m_humidity=-9999);
  declareProperty("dataSize", m_calDes.m_dataSize=-9999);
  declareProperty("creator", m_calDes.m_creator="");
  declareProperty("description", m_calDes.m_description="");
}


StatusCode GetTkrBadStrip::initialize() {
  StatusCode sc;
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "Initialize()" << endreq;

  sc = setProperties();
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not set properties in GetTkrBadStrip" 
	<< endreq;
    return sc;
  }

  sc = service("CalibDataSvc", m_pCalibDataSvc, true);

  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not get OracleDbSvc"
	<< endreq;
    return sc;
  }

  sc = service("OracleDbSvc", m_pOracleDbSvc, true);

  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not get IDataProviderSvc interface of CalibDataSvc" 
	<< endreq;
    return sc;
  }

  m_db = m_pOracleDbSvc->getOracleDb();
  assert(m_db != 0);

  m_calDes.setDb(m_db);
  m_calDes.setOracleTimeFmt(m_pOracleDbSvc->getOracleTimeFmt());
  m_tkrIndex.setDb(m_db);
  m_tkrDeadChannel.setDb(m_db);
  m_tkrNoisyChannel.setDb(m_db);

  try {
    m_calDes.prepareFill();
    m_tkrIndex.prepareFill();
    m_tkrDeadChannel.prepareFill();
    m_tkrNoisyChannel.prepareFill();
  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }

  m_visitor.setGet(this);
  return sc;
}


StatusCode GetTkrBadStrip::execute( ) {

  MsgStream log(msgSvc(), name());

  StatusCode sc;

  // process dead channel
  m_procDeadCh = true;
  std::string fullPath = "/Calib/TKR_DeadChan/";
  fullPath += m_calibFlavor;
  DataObject *pObject;

  m_pCalibDataSvc->retrieveObject(fullPath, pObject);

  CalibData::BadStrips* pDead = 0;
  pDead = dynamic_cast<CalibData::BadStrips *> (pObject);
  if (!pDead) {
    log << MSG::ERROR << "Dynamic cast to BadStrips failed" << endreq;
    return StatusCode::FAILURE;
  }

  sc = fillDescriptionTables();
  if(sc == StatusCode::FAILURE) return sc;

  sc = fillTkrBadStripTable(pDead);
  if(sc == StatusCode::FAILURE) return sc;

  // process noisy channel
  m_procDeadCh = false;
  fullPath = "/Calib/TKR_HotChan/";
  fullPath += m_calibFlavor;

  m_pCalibDataSvc->retrieveObject(fullPath, pObject);

  CalibData::BadStrips* pHot = dynamic_cast<CalibData::BadStrips *> (pObject);
  if (!pHot) {
    log << MSG::ERROR << "Dynamic cast to BadStrips failed" << endreq;
    return StatusCode::FAILURE;
  }

  sc = fillDescriptionTables();
  if(sc == StatusCode::FAILURE) return sc;

  sc = fillTkrBadStripTable(pHot);
  if(sc == StatusCode::FAILURE) return sc;

  return StatusCode::SUCCESS;
}

StatusCode GetTkrBadStrip::fillDescriptionTables()
{
  MsgStream log(msgSvc(), name());

  try {
    m_db->getNextSeqNo("Seq_CalDesID", &m_calDes.m_id);
    if(m_procDeadCh) {
      m_calDes.m_calibType = Constants::TkrDeadChannel;
    }
    else {
      m_calDes.m_calibType = Constants::TkrNoisyChannel;
    }

    m_calDes.fill();

  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }
  return StatusCode::SUCCESS;
}

StatusCode GetTkrBadStrip::fillTkrBadStripTable(CalibData::BadStrips* pBad)
{
  MsgStream log(msgSvc(), name());

  try {  
    pBad->traverse(&m_visitor);
  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }

  return StatusCode::SUCCESS;
}

StatusCode GetTkrBadStrip::finalize( ) {

  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "          Finalize GetTkrBadStrip " << endreq;
  
  return StatusCode::SUCCESS;
}

CalibData::eVisitorRet BadVisitor::badPlane(unsigned int row, 
                                            unsigned int col, 
                                            unsigned int tray, bool top,
                                            int badness, bool allBad,
                                            const CalibData::StripCol& strips)
{
  idents::TowerId towerId(row, col);

  m_get->m_db->getNextSeqNo("Seq_TkrIndexID", &(m_get->m_tkrIndex.m_id));
  m_get->m_tkrIndex.m_calDesId = m_get->m_calDes.m_id;
  m_get->m_tkrIndex.m_tkrInstId = TkrGeo::getTkrId(towerId.id(), tray, top);
  m_get->m_tkrIndex.fill();

  CalibData::StripCol::const_iterator end = strips.end();
  for(CalibData::StripCol::const_iterator itr = strips.begin(); 
      itr != end; ++itr) {

    if(m_get->m_procDeadCh) {
      m_get->m_db->getNextSeqNo("Seq_TkrDeadChID", 
				&(m_get->m_tkrDeadChannel.m_id));
      m_get->m_tkrDeadChannel.m_tkrIndexId = m_get->m_tkrIndex.m_id;
      m_get->m_tkrDeadChannel.m_strip = *itr;
      m_get->m_tkrDeadChannel.fill();
    }
    else  {
      m_get->m_db->getNextSeqNo("Seq_TkrNoisyChID", 
				&(m_get->m_tkrNoisyChannel.m_id));
      m_get->m_tkrNoisyChannel.m_tkrIndexId = m_get->m_tkrIndex.m_id;
      m_get->m_tkrNoisyChannel.m_strip = *itr;
      m_get->m_tkrNoisyChannel.fill();
    }
  }

  return CalibData::CONT;
}
