//$Header$
#include <stdio.h>
#include <typeinfo>
#include <cassert>
#include <string>
#include <vector>
#include "TROOT.h"
#include "TRandom.h"
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
#include "ToString.h"
#include "TkrGeo.h"
#include "CalibrationDescription.h"
#include "TkrIndex.h"
#include "TkrTot.h"
#include "Constants.h"

using std::cout;
using std::endl;

class OracleDbSvc;

/**
   @file RandomFillTot.cxx
   Simple algorithm to test functioning of "the other" TDS, Cal pedestals data
*/



  /** 
   @class RandomFillTot

   Algorithm exemplifying retrieval and use of Calorimeter pedestal calibration
*/

class RandomFillTot : public Algorithm {

public:

  RandomFillTot(const std::string& name, ISvcLocator* pSvcLocator); 

  ~RandomFillTot();

  StatusCode initialize();

  StatusCode execute();

  StatusCode finalize();

private:

  // return a string representing random time between (2003-01-01 and 
  // 20030-12-30), string format is (yyyy-mm-dd hh:mi)
  std::string randomTime() const;

  // generate random number between 0 and max-1, including two ends
  int randomInt(int max) const
    {
      int temp = int(gRandom->Rndm()*max);
      if(temp == max) return max-1;
      else return temp;
    }

  //generate random number between 0 and max, excluding two ends
  double randomDB(double max) const { return (max*gRandom->Rndm()); }

  //generate random number between min and max, excluding two ends
  double randomDB(double min, double max) const
    {
      double rnd = gRandom->Rndm();
      return (min + rnd * (max - min));
    }

  // random fill a vector, vector item can not be duplicated
  template<class X> void randomFillVector(std::vector<X>& v, size_t size,
					  X min, X max);

  IOracleDbSvc* m_pOracleDbSvc;

  OCIWrapper* m_db;
  
  CalibrationDescription m_calDes;

  TkrIndex m_tkrIndex;

  TkrTot m_tkrTot;
};

/// Instantiation of a static factory to create instances of this algorithm
static const AlgFactory<RandomFillTot> Factory;
const IAlgFactory& RandomFillTotFactory = Factory;


RandomFillTot::RandomFillTot(const std::string&  name, 
                 ISvcLocator*        pSvcLocator )
  : Algorithm(name, pSvcLocator), m_pOracleDbSvc(0), m_db(0)
{

  // Declare properties here.
  declareProperty("source",  m_calDes.m_source=0);
  declareProperty("hardware", m_calDes.m_hardware=2);
  declareProperty("location", m_calDes.m_location=0);
  declareProperty("calibType", m_calDes.m_calibType=4);
  declareProperty("procLevel", m_calDes.m_procLevel=0);
  declareProperty("status", m_calDes.m_status=0);
  declareProperty("validStartTime", m_calDes.m_validStartTime="2003-10-11 12:00");
  declareProperty("validEndTime", m_calDes.m_validEndTime="2003-10-11 12:00");
  declareProperty("runStartTime", m_calDes.m_runStartTime="2003-10-11 12:00");
  declareProperty("runEndTime", m_calDes.m_runEndTime="2003-10-11 12:00");
  declareProperty("creationTime", m_calDes.m_creationTime="2003-10-11 12:00");
  declareProperty("software", m_calDes.m_software="calibGenTKR");
  declareProperty("version", m_calDes.m_version="v0");
  declareProperty("dataSize", m_calDes.m_dataSize=-9999);
  declareProperty("creator", m_calDes.m_creator="");
  declareProperty("description", m_calDes.m_description="");

  if(gROOT == 0) {
    static TROOT g_root("root", "root oracle interface");
  }
  gRandom->SetSeed(1);
}

RandomFillTot::~RandomFillTot()
{
}

StatusCode RandomFillTot::initialize() {
  StatusCode sc;
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "Initialize()" << endreq;

  sc = setProperties();
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not set properties in RandomFillTot" 
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
  m_tkrTot.setDb(m_db);

  try {
    m_calDes.prepareFill();
    m_tkrIndex.prepareFill();
    m_tkrTot.prepareFill();
  }
  catch(const OCIException& e) {
    log << MSG::ERROR << e.what() << endreq;
    return StatusCode::FAILURE;
  }

  return sc;
}


StatusCode RandomFillTot::execute( ) {

  MsgStream log(msgSvc(), name());

  for(int i = 0; i != 2; ++i) {

    std::cout << "input " << i << "th set of calibration constants" << std::endl;

    m_calDes.m_location = Constants::SlacCleanRoom;
    m_calDes.m_source = Constants::ChargeInj;
    m_calDes.m_validStartTime = "2002-01-01 03:03";
    m_calDes.m_validEndTime = "2002-12-31 05:05";
    m_calDes.m_runStartTime = randomTime().c_str();
    m_calDes.m_runEndTime = randomTime().c_str();
    m_calDes.m_creationTime = randomTime().c_str();
    m_calDes.m_software = "random";
    m_calDes.m_version = "";
    m_calDes.m_hardware = Constants::EM2;
    m_calDes.m_procLevel = randomInt(4);
    m_calDes.m_status = randomInt(3);
    m_calDes.m_dataSize = randomInt(1000);
    m_calDes.m_creator = "Xin Chen";
    m_calDes.m_description = "test data";

    try {
      // randomly fill Tkr tot table
      m_db->getNextSeqNo("Seq_CalDesID", &(m_calDes.m_id));
      m_calDes.m_calibType = Constants::TkrTot;
      m_calDes.fill();

      for(int iTower = 0; iTower != TkrGeo::nTower; ++iTower) {

	cout << "Filling tower " << iTower << endl;

	for(int iTray = 0; iTray != TkrGeo::nTray; ++iTray) {
	  for(int iPos = 0; iPos != TkrGeo::nPos; ++iPos) {

	    if( (iTray == 0 && iPos == TkrGeo::bot) ||
		(iTray == TkrGeo::nTray-1 && iPos == TkrGeo::top) ) continue;

	    m_db->getNextSeqNo("Seq_TkrIndexID", &(m_tkrIndex.m_id));
	    m_tkrIndex.m_calDesId = m_calDes.m_id;
	    m_tkrIndex.m_tkrInstId = TkrGeo::getTkrId(iTower, iTray, iPos);
	    m_tkrIndex.fill();

	    m_tkrTot.m_tkrIndexId = m_tkrIndex.m_id;

	    for(int iStrip = 0; iStrip != TkrGeo::nStripsPerLayer; ++iStrip) {
	      m_tkrTot.m_p0 = randomDB(1);
	      m_tkrTot.m_p1 = randomDB(1);
	      m_tkrTot.m_p2 = randomDB(1);
	      m_tkrTot.m_chi2 = randomDB(10);
	      m_tkrTot.m_strip = iStrip;
	      m_tkrTot.fill();
	    }
	  }
	}
      }
    }
    catch(const OCIException& e) {
      log << MSG::ERROR << e.what() << endreq;
      return StatusCode::FAILURE;
    }
  }

  return StatusCode::SUCCESS;
}


StatusCode RandomFillTot::finalize( ) 
{
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "          Finalize RandomFillTot " << endreq;
  
  return StatusCode::SUCCESS;
}

std::string RandomFillTot::randomTime() const
{
  // feb may have 27 days
  static int max = 12 * 27 * 24 * 60;
  int t = randomInt(max);

  int month = t / (27 * 24 * 60);
  int date = (t - month * 27 * 24 * 60) / (24 * 60);
  int hour = (t - month * 27 * 24 * 60 - date * 24 * 60) / 60;
  int min = t - month * 27 * 24 * 60 - date * 24 * 60 
    - hour * 60;

  std::string time("2003");

  // there are no 0 for month or date
  ++date, ++month;

  if(month <  10) time = time + "-0" + ToString(month);
  else time = time + "-" + ToString(month);

  if(date <  10) time = time + "-0" + ToString(date);
  else time = time + "-" + ToString(date);

  time += ' ';

  if(hour <  10) time = time + "0" + ToString(hour) + ':';
  else time = time + ToString(hour) + ':';

  if(min <  10) time = time + "0" + ToString(min);
  else time = time + ToString(min);

  return time;
}

template<class X> void RandomFillTot::randomFillVector(std::vector<X>& v, 
						    size_t size,
						    X min, X max)
{
  for(; ;) {
    if(v.size() == size) break;

    X temp = (X) randomDB(min, max);

    // check whether temp already exists in the vector
    if(find(v.begin(), v.end(), temp) != v.end()) continue;

    v.push_back(temp);
  }
}
