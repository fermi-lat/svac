//$Header$
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
#include "CalibData/Cal/CalCalibPed.h"
#include "idents/CalXtalId.h"                // shouldn't be necessary
#include "IOracleDbSvc.h"
#include "OCIWrapper.h"
#include "CalGeo.h"
#include "CalibrationDescription.h"
#include "CalIndex.h"
#include "CalPedestal.h"
#include "Constants.h"

class OracleDbSvc;

/**
   @file GetCalPedestal.cxx
   Simple algorithm to test functioning of "the other" TDS, Cal pedestals data
*/



  /** 
   @class GetCalPedestal

   Algorithm exemplifying retrieval and use of Calorimeter pedestal calibration
*/

class GetCalPedestal : public Algorithm {


public:
  GetCalPedestal(const std::string& name, ISvcLocator* pSvcLocator); 

  StatusCode initialize();

  StatusCode execute();

  StatusCode finalize();

private:

  StatusCode fillCalPedsTable(CalibData::CalCalibPed* pPeds);
 
  StatusCode fillDescriptionTables();

  IDataProviderSvc* m_pCalibDataSvc;
  IOracleDbSvc* m_pOracleDbSvc;
  
  std::string m_calibFlavor;

  OCIWrapper* m_db;

  CalibrationDescription m_calDes;

  CalIndex m_calIndex;

  CalPedestal m_calPedestal;
};


/// Instantiation of a static factory to create instances of this algorithm
static const AlgFactory<GetCalPedestal> Factory;
const IAlgFactory& GetCalPedestalFactory = Factory;


GetCalPedestal::GetCalPedestal(const std::string&  name, 
                 ISvcLocator*        pSvcLocator )
  : Algorithm(name, pSvcLocator), m_pCalibDataSvc(0), m_pOracleDbSvc(0),
    m_db(0)
{
  // Declare properties here.
  declareProperty("calibFlavor",  m_calibFlavor);

  declareProperty("source",  m_calDes.m_source=Constants::CosmicMuon);
  declareProperty("hardware", m_calDes.m_hardware=Constants::EM2);
  declareProperty("location", m_calDes.m_location=Constants::SlacCleanRoom);
  declareProperty("calibType", m_calDes.m_calibType=Constants::CalPedestal);
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


StatusCode GetCalPedestal::initialize() {
  StatusCode sc;
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "Initialize()" << endreq;

  sc = setProperties();
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not set properties in GetCalPedestal" 
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
  m_calPedestal.setDb(m_db);

  try {
    m_calDes.prepareFill();
    m_calIndex.prepareFill();
    m_calPedestal.prepareFill();
  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }

  return sc;
}


StatusCode GetCalPedestal::execute( ) {

  MsgStream log(msgSvc(), name());

  StatusCode sc;

  std::string fullPath = "/Calib/CAL_Ped/";
  fullPath += m_calibFlavor;
  DataObject *pObject;

  m_pCalibDataSvc->retrieveObject(fullPath, pObject);

  CalibData::CalCalibPed* pPeds = 0;
  pPeds = dynamic_cast<CalibData::CalCalibPed *> (pObject);
  if (!pPeds) {
    log << MSG::ERROR << "Dynamic cast to CalCalibPed failed" << endreq;
    return StatusCode::FAILURE;
  }

  m_db = m_pOracleDbSvc->getOracleDb();
  assert(m_db != 0);

  sc = fillDescriptionTables();
  if(sc == StatusCode::FAILURE) return sc;

  fillCalPedsTable(pPeds);

  return StatusCode::SUCCESS;
}

StatusCode GetCalPedestal::fillDescriptionTables()
{
  MsgStream log(msgSvc(), name());

  try {
    m_db->getNextSeqNo("Seq_CalDesID", &m_calDes.m_id);
    m_calDes.m_calibType = Constants::CalPedestal;
    m_calDes.fill();

  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }
  return StatusCode::SUCCESS;
}

StatusCode GetCalPedestal::fillCalPedsTable(CalibData::CalCalibPed* pPeds) 
{
  using idents::CalXtalId;
  using CalibData::Ped;

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
	      pRange = pPeds->getRange(id, iRange, idents::CalXtalId::NEG);
	    }
	    else {
	      pRange = pPeds->getRange(id, iRange, idents::CalXtalId::POS);
	    }

	    if(pRange == 0) {
	      log << MSG::INFO << "Pedestal calibration constants for crystal at tower " << iTower << " layer " << iLayer << " col " << iCol << " range " << iRange << " face " << iFace << "don't exist! " << endreq;
	      continue;
	    }

	    CalibData::Ped* ped = dynamic_cast<CalibData::Ped*>(pRange);
	    assert(ped != 0);

	    try {
	      m_db->getNextSeqNo("Seq_CalPedestalID", &m_calPedestal.m_id);

	      m_calPedestal.m_calIndexId = m_calIndex.m_id;
	      m_calPedestal.m_face = iFace;
	      m_calPedestal.m_range = iRange;
	      m_calPedestal.m_peak = ped->getAvr();
	      m_calPedestal.m_width = ped->getSig();

	      m_calPedestal.fill();
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

StatusCode GetCalPedestal::finalize( ) {

  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "          Finalize GetCalPedestal " << endreq;
  
  return StatusCode::SUCCESS;
}

