#include <string>
#include "GaudiKernel/IAddressCreator.h"
#include "GaudiKernel/IOpaqueAddress.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/IValidity.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/Service.h"
#include "GaudiKernel/SvcFactory.h"
#include "OCIWrapper.h"
#include "OracleDbSvc.h"

static SvcFactory<OracleDbSvc> s_factory;
const ISvcFactory& OracleDbSvcFactory = s_factory;


OracleDbSvc::OracleDbSvc(const std::string&  name, 
			 ISvcLocator*        pSvcLocator )
 : Service(name, pSvcLocator), m_db(0)
{
  // Declare properties here.
  declareProperty("dbName",  m_dbName="");
  declareProperty("userName",  m_userName="");
  declareProperty("passWord",  m_passWord="");
  declareProperty("dateFormat",  m_dateFormat="YYYY-MM-DD HH24:MI");
}

StatusCode OracleDbSvc::queryInterface(const IID& riid, void**ppvIF)
{
  if(IID_IOracleDbSvc == riid) {
    *ppvIF = dynamic_cast<IOracleDbSvc*> (this);
    return StatusCode::SUCCESS;
  }
  else {
    return Service::queryInterface(riid, ppvIF);
  }
}

StatusCode OracleDbSvc::initialize()
{
  StatusCode sc;
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "Initialize()" << endreq;

  sc = setProperties();

  try {
    m_db = new OCIWrapper(m_dbName.c_str(), m_userName.c_str(), 
			  m_passWord.c_str());
  }
  catch (const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }

  return sc;
}

StatusCode OracleDbSvc::finalize( ) 
{
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "          Finalize DbManager " << endreq;
 
  delete m_db;
 
  return StatusCode::SUCCESS;
}
