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
#include "CalibData/CalibModel.h"
#include "CalibData/Cal/CalCalibGain.h"
#include "idents/CalXtalId.h"                
#include "IOracleDbSvc.h"
#include "OCIWrapper.h"
#include "CalGeo.h"
#include "CalibrationDescription.h"
#include "CalIndex.h"
#include "CalElecGain.h"
#include "Constants.h"

class OracleDbSvc;

/** 
 *   @class GetCalElecGain
 *  Algorithm retrieving CAL electronic gain (muon peak) data from SAS's 
 *  calibration database and populating I&T's oracle database
*/

class GetCalElecGain : public Algorithm {


public:
  GetCalElecGain(const std::string& name, ISvcLocator* pSvcLocator); 

  StatusCode initialize();

  StatusCode execute();

  StatusCode finalize();

private:

  StatusCode fillCalElecGainTable(CalibData::CalCalibGain* pGain);
 
  StatusCode fillDescriptionTables();

  IDataProviderSvc* m_pCalibDataSvc;
  IOracleDbSvc* m_pOracleDbSvc;
  
  std::string m_calibFlavor;

  OCIWrapper* m_db;

  CalibrationDescription m_calDes;

  CalIndex m_calIndex;

  CalElecGain m_calElecGain;
};


/// Instantiation of a static factory to create instances of this algorithm
static const AlgFactory<GetCalElecGain> Factory;
const IAlgFactory& GetCalElecGainFactory = Factory;


GetCalElecGain::GetCalElecGain(const std::string&  name, 
                 ISvcLocator*        pSvcLocator )
  : Algorithm(name, pSvcLocator), m_pCalibDataSvc(0), m_pOracleDbSvc(0),
    m_db(0)
{
  // Declare properties here.
  declareProperty("calibFlavor",  m_calibFlavor);

  declareProperty("source",  m_calDes.m_source=Constants::CosmicMuon);
  declareProperty("hardware", m_calDes.m_hardware=Constants::EM2);
  declareProperty("location", m_calDes.m_location=Constants::SlacCleanRoom);
  declareProperty("calibType", m_calDes.m_calibType=Constants::CalElecGain);
  declareProperty("procLevel", m_calDes.m_procLevel=Constants::Test);
  declareProperty("status", m_calDes.m_status=Constants::Ok);
  declareProperty("validStartTime", m_calDes.m_validStartTime="");
  declareProperty("validEndTime", m_calDes.m_validEndTime="");
  declareProperty("creationTime", m_calDes.m_creationTime="2003-10-11 12:00");
  declareProperty("software", m_calDes.m_software="calibGenCAL");
  declareProperty("version", m_calDes.m_version="v0");
  declareProperty("dataSize", m_calDes.m_dataSize=-9999);
  declareProperty("creator", m_calDes.m_creator="");
  declareProperty("description", m_calDes.m_description="");
}


StatusCode GetCalElecGain::initialize() {
  StatusCode sc;
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "Initialize()" << endreq;

  sc = setProperties();
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not set properties in GetCalElecGain" 
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
  m_calIndex.setDb(m_db);
  m_calElecGain.setDb(m_db);

  try {
    m_calDes.prepareFill();
    m_calIndex.prepareFill();
    m_calElecGain.prepareFill();
  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }

  return sc;
}


StatusCode GetCalElecGain::execute( ) {

  MsgStream log(msgSvc(), name());

  StatusCode sc;

  std::string fullPath = "/Calib/CAL_ElecGain/";
  fullPath += m_calibFlavor;
  DataObject *pObject;

  m_pCalibDataSvc->retrieveObject(fullPath, pObject);

  CalibData::CalCalibGain* pGain = 0;
  pGain = dynamic_cast<CalibData::CalCalibGain *> (pObject);
  if (!pGain) {
    log << MSG::ERROR << "Dynamic cast to CalCalibGain failed" << endreq;
    return StatusCode::FAILURE;
  }

  sc = fillDescriptionTables();
  if(sc == StatusCode::FAILURE) return sc;

  fillCalElecGainTable(pGain);

  return StatusCode::SUCCESS;
}

StatusCode GetCalElecGain::fillDescriptionTables()
{
  MsgStream log(msgSvc(), name());

  try {
    m_db->getNextSeqNo("Seq_CalDesID", &m_calDes.m_id);
    m_calDes.m_calibType = Constants::CalElecGain;
    m_calDes.fill();

  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }
  return StatusCode::SUCCESS;
}

StatusCode GetCalElecGain::fillCalElecGainTable(CalibData::CalCalibGain* pGain) 
{
  using idents::CalXtalId;
  using CalibData::Gain;

  MsgStream log(msgSvc(), name());


  for(int iTower = 0; iTower != CalGeo::nTower; ++iTower) {
    for(int iLayer = 0; iLayer != CalGeo::nLayer; ++iLayer) {
      for(int iCol = 0; iCol != CalGeo::nCol; ++iCol) {

	try {
	  m_db->getNextSeqNo("Seq_CalIndexID", &(m_calIndex.m_id));
	  m_calIndex.m_calDesId = m_calDes.m_id;
	  m_calIndex.m_calInstId = CalGeo::getCalId(iTower, iLayer, iCol);
	  m_calIndex.fill();
	}
	catch(const OCIException& e) {
	  log << MSG::ERROR << e.what() << endreq;
	  return StatusCode::FAILURE;
	}

	for(int iRange = 0; iRange != CalGeo::nRange; ++iRange) {
	  for(int iFace = 0; iFace != CalGeo::nFace; ++iFace) {

	    CalXtalId id(iTower, iLayer, iCol);

	    CalibData::RangeBase* pRange;
	    if(iFace == 0) {
	      pRange = pGain->getRange(id, iRange, idents::CalXtalId::NEG);
	    }
	    else {
	      pRange = pGain->getRange(id, iRange, idents::CalXtalId::POS);
	    }

	    if(pRange == 0) {
	      log << MSG::INFO << "ElecGain calibration constants for crystal at tower " << iTower << " layer " << iLayer << " col " << iCol << " range " << iRange << " face " << iFace << "don't exist! " << endreq;
	      continue;
	    }

	    CalibData::Gain* gain = dynamic_cast<CalibData::Gain*>(pRange);
	    assert(gain != 0);

	    try {
	      m_db->getNextSeqNo("Seq_CalElectronicGainID", &m_calElecGain.m_id);

	      m_calElecGain.m_calIndexId = m_calIndex.m_id;
	      m_calElecGain.m_face = iFace;
	      m_calElecGain.m_range = iRange;
	      m_calElecGain.m_peak = gain->getGain();
	      m_calElecGain.m_width = gain->getSig();

	      m_calElecGain.fill();
	    }
	    catch(const OCIException& e) {
	      log << MSG::ERROR << e.what() << endreq;
	      return StatusCode::FAILURE;
	    } 

	  }
	}
      }
    }
  }
  return StatusCode::SUCCESS;
}

StatusCode GetCalElecGain::finalize( ) {

  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "          Finalize GetCalElecGain " << endreq;
  
  return StatusCode::SUCCESS;
}

