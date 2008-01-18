//
// Base class
#include "MonEventLooper_t.h"
#include "MonValueImpls_t.h"
//
// stl
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <vector>

// ROOT IO
#include "digiRootData/DigiEvent.h"
#include "TEventList.h"

//
//
void MonEventLooper::printTime(ostream& os, Double_t timestamp) {
  
  // Time from Mission elapsed time to Unix time and then from PDT to GMT:
  static const int METtoGMT = 978307200 + 25200;
  ULong64_t time = int(timestamp) + METtoGMT;
  UInt_t itime = (UInt_t)(time);
  os << ctime((time_t*) (&itime))<<"(The date printout is only relevant if the timestamp happens to be in seconds elapsed from Mission start)"; 
}


//
//
MonEventLooper::MonEventLooper(UInt_t binSize, MonValue* colprim, MonValue* colsec, std::vector<MonInputCollection*> incol, MonGlobalCut* eventcut, std::string timestampvar)
  :m_binSize(binSize),
   m_timeStamp(0.0),
   m_currentStart(0),
   m_currentEnd(0),
   m_currentFlags(0),
   m_sec_first(0),
   m_sec_last(0),
   m_timeinterval(0.0),
   m_timestamp_firstevt_inbin(0.0),
   m_timestamp_lastevt_inbin(0.0),
   m_startEvent(0),
   m_last(0),
   m_nFilter(0),
   m_nUsed(0),
   m_evtcounter(0),
   m_intreefile(0),
   m_tree(0),
   m_intree(0),
   m_sectree(0),
   m_stripValCol(colprim),
   m_secstripValCol(colsec),
   m_incol(incol),
   m_globalCut(eventcut),
   m_timestampvar(timestampvar),
   m_intreetfilename("File4IntermediateTree.root"),
   m_sodir("./")
{


   // attach input chains
  // for_each(m_incol.begin(), m_incol.end(), mem_fun(&MonInputCollection::attachChain));

  // tmp
  for(std::vector<MonInputCollection*>::iterator it=m_incol.begin(); it!=m_incol.end();it++){
    (*it)->attachChain();
  }
    // endtmp


  //create and populate intermediate tree
  m_intree = new TTree("Internal","Used to create output");
  for(std::vector<MonInputCollection*>::iterator it=m_incol.begin(); it!=m_incol.end();it++){
    (*it)->populateTableTree(m_intree);
  }



  

  // make proxies for formulas if needed
  colprim->makeProxy(m_intree);
  // create global cut object
  m_globalCut->makeProxy(m_intree);
  m_intree->SetEventList(m_globalCut->eventList());
  // retrieve timestamp
  const char* lstr=m_intree->GetBranch(m_timestampvar.c_str())->GetTitle();
  assert(lstr);
  char ty=lstr[strlen(lstr)-1];
  switch(ty){
  case 'S': 
    m_currentTimestamp=new Timestamp_Short_t((Short_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  case 's': 
    m_currentTimestamp=new Timestamp_UShort_t((UShort_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  case 'I': 
    m_currentTimestamp=new Timestamp_Int_t((Int_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  case 'i': 
    m_currentTimestamp=new Timestamp_UInt_t((UInt_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  case 'F': 
    m_currentTimestamp=new Timestamp_Float_t((Float_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  case 'D': 
    m_currentTimestamp=new Timestamp_Double_t((Double_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  case 'L': 
    m_currentTimestamp=new Timestamp_Long64_t((Long64_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  case 'l': 
    m_currentTimestamp=new Timestamp_ULong64_t((ULong64_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress()));
    break;
  default:
    std::cout<<"Problem with timestamp type. Exiting"<<std::endl;
    assert(0);
  }

  //create output tree
  m_tree = new TTree("Time","Time binned data");
  //create output tree
  attachTree();
  // colsec combines output from the primary variables
  m_sectree=new TTree("sectree","Primary input");
  std::string prefix;
  m_stripValCol->attach(*m_sectree,prefix);
  colsec->makeProxy(m_sectree);

  // Set max root file size to 500 GB:

 

  Long64_t maxTreeSize = 5000000000000;
  m_intree->SetMaxTreeSize(maxTreeSize);
  m_intree->SetMaxVirtualSize(maxTreeSize);
  m_sectree->SetMaxTreeSize(maxTreeSize);
  m_tree->SetMaxTreeSize(maxTreeSize);

  // tmp
  /*
  // Get infor from tree
  std::cout << "MonEventLooper::MonEventLooper: DEBUG INFO: AFTER" << std::endl
	    << "m_intree->GetMaxVirtualSize() = " << m_intree->GetMaxVirtualSize() << std::endl
	    << "m_intree->GetMaxTreeSize() = " << m_intree->GetMaxTreeSize() << std::endl;
	    
  */
  // endtmp

  

  // obj to hold the time interval of the specific bin
  // m_timeintervalobj = new TimeInterval();
}


MonEventLooper::~MonEventLooper(){
  //delete m_timeintervalobj;
  
}
void MonEventLooper::init() {

  // CREATE TFile where the intermediate tree will reside (info written to disk).
  // Writing is necessary if info from intermediate tree, for a time bin, is close to 2 GB
  // which gets into 3 GB (limit on a on a IA32 linux for single process) with another 
  // root stuff, producing a SEG FAULT. 

  // By default, the intermediate tree will be written. The user can 
  // however set m_intreeToDisk to zero (from command line) to speed up (25%) the processing speed
  // of those jobs requiring few memory (say less than 1.5 GB).

  if(m_intreeToDisk){
    createtfile4intree(m_sodir,m_intreetfilename);
  }
  else{
    std::cout << "MonEventLooper::init(), WARNING" << std::endl
	      << "Intermediate TTree will NOT be written to disk. Thus it will a memory-resident TTree."
	      << std::endl
	      << "This will make the process faster. But note that it will make the process crash if "
	      << "the overall memory used when filling the TTree is larger than 3GB." << std::endl;

  }
}


void MonEventLooper::createtfile4intree(std::string dir, std::string filename){

  std::string completename = dir;
  completename+=filename;
  
  // tmnp
  /*
  std::cout << "MonEventLooper::createtfile4intree: filename= " <<  completename.c_str() 
	    << std::endl;
  */
  /// endtmp

  TDirectory* currentdir = gDirectory;
  m_intreefile = new TFile (completename.c_str(), "RECREATE");
  m_intree->SetDirectory(gDirectory);
  currentdir->cd();
}

void MonEventLooper::attachTree() {

  m_tree->Branch("Bin_Index",(void*)(&m_currentBin),"Bin_Index/i");
  m_tree->Branch("Bin_Start",(void*)(&m_currentStart),"Bin_Start/l");
  m_tree->Branch("Bin_End",(void*)(&m_currentEnd),"Bin_End/l");
  m_tree->Branch("Bin_Flags",(void*)(&m_currentFlags),"Bin_Flags/i");
  m_tree->Branch("nEvents",(void*)(&m_nUsed),"nEvents/i");
  m_tree->Branch("nPassed",(void*)(&m_nFilter),"nPassed/i");

  m_tree->Branch("TrueTimeInterval",(void*)(&m_timeinterval),"TrueTimeInterval/D");
  m_tree->Branch("TimeStampFirstEvt",(void*)(&m_timestamp_firstevt_inbin),"TimeStampFirstEvt/D");
  m_tree->Branch("TimeStampLastEvt",(void*)(&m_timestamp_lastevt_inbin),"TimeStampLastEvt/D");


  std::string prefix;
  m_stripValCol->attach(*m_tree,prefix);
  m_secstripValCol->attach(*m_tree,prefix);
}


void MonEventLooper::go(Long64_t numEvents, Long64_t startEvent) {

  // set up the loop
  m_startEvent = startEvent;
  m_last = numEvents;

  // Starting message
  std::cout << "Number of events used: " << m_last-startEvent << std::endl;
  std::cout << "Starting at event: " << startEvent << std::endl;
  
  // 
  init();

  UInt_t unsaved(0);
  Double_t currentTimeStamp(0.0);

  // Event loop
  for (Int_t ievent= startEvent; ievent!=m_last; ievent++ ) {
    //if(ievent%1000==0)std::cout<<"Event: "<<ievent<<std::endl;

    m_evtcounter++;
    /*
    std::cout << " MonEventLooper::go: DEBUG INFO" << std::endl
	      << " Evt number = " <<  m_evtcounter << std::endl;
    */

    // call sub-class to read the event
    Bool_t ok = readEvent(ievent);
    if ( !ok ) {
      std::cerr << "Failed to read event " << ievent << " aborting" << std::endl;
      break;
    }    
    currentTimeStamp=m_currentTimestamp->value();

    // initialize stuff on first event
    if ( ievent == startEvent ) {
      firstEvent(currentTimeStamp);
    } 

    if(!unsaved){
      // first event of this bin
      m_timestamp_firstevt_inbin = currentTimeStamp;
    }
     
    // check for time-bin edge
    if ( currentTimeStamp >= m_currentEnd ) {
	// time-stamp outside of bin, jump to next bin
	// This latches and store all the values
      switchBins();
      unsaved = 0;
    } else {
      m_timestamp_lastevt_inbin = currentTimeStamp;
      unsaved++;
    }
    
    // switch the timestamp
    logEvent(ievent,currentTimeStamp);

    // increment trigger count, filter count
    // this is only done after the bin-switch
    // since useEvent() hasn't been called
    // the last bin doesn't include data from this event
    // so that stats shouldn't either
    m_nTrigger++;
    //filterEvent(filtered);
    //if ( !filtered ) {
    //  m_nFilter++;

      // ok, this is the call that actually fills the event data
      //useEvent(used);
      //if ( used ) {
	//m_nUsed++;
      //}
    //  }
  }
  
  // flush out any remaining events
  if ( unsaved > 0 ) lastEvent(currentTimeStamp);

}


// First event with timestamp with double precision
void MonEventLooper::firstEvent(Double_t timeStampdouble)  {
  ULong64_t timeStamp = ULong64_t(timeStampdouble);
  ULong64_t rem = timeStamp % m_binSize;
  m_currentBin = 0;
  m_currentStart = timeStamp - rem;

  m_currentEnd = m_currentStart + m_binSize;
  m_currentFlags = 3;
  m_sec_first = timeStampdouble;
  TimeInterval::m_interval=m_currentEnd-m_sec_first;
  
  /*
  std::cout << "Time interval; first event, " << std::endl
	    << "m_currentEnd, m_sec_first, m_interval, " <<std::endl
	    << setprecision(20) 
	    << m_currentEnd << ", " <<  m_sec_first << ", " << TimeInterval::m_interval << std::endl;
  */


  printTime(std::cout,timeStampdouble);
  std::cout << std::endl;
}



void MonEventLooper::switchBins() {

  m_timeinterval = TimeInterval::m_interval;
  
  // tmp
  /*
  std::cout << "Info concerning time intervals for bin " << m_currentBin << std::endl
	    << setprecision(20) 
	    << "m_timeinterval = " << m_timeinterval << std::endl
	    << "m_timestamp_firstevt_inbin = " << m_timestamp_firstevt_inbin << std::endl
	    << "m_timestamp_lastevt_inbin = " << m_timestamp_lastevt_inbin << std::endl;
  */
  // endtmp

  
  m_currentFlags -= 1;
  filterEvent();
  stripVals()->increment(m_intree);
  m_stripValCol->latchValue();
  m_sectree->Reset();
  m_sectree->Fill();
  m_secstripValCol->increment(m_sectree);
  m_secstripValCol->latchValue();
  m_tree->Fill();
  m_stripValCol->reset();
  m_secstripValCol->reset();
  m_intree->SetEventList(0);
  m_intree->GetEntry(m_nUsed);
  m_intree->Reset();
  m_intree->Fill();
  
  
  
  m_currentBin++;
  m_currentStart += m_binSize;
  m_currentEnd += m_binSize;
  m_currentFlags = 1;

  TimeInterval::m_interval=m_binSize;
 
  while(m_currentTimestamp->value()>=m_currentEnd){
    m_nUsed=0;
    m_nFilter=0;
    m_timeinterval = 0.0;
    m_timestamp_firstevt_inbin = 0.0;
    m_timestamp_lastevt_inbin = 0.0;
    m_tree->Fill();
    m_currentBin++;
    m_currentStart += m_binSize;
    m_currentEnd += m_binSize;
  }

  // Time from Mission elapsed time to Unix time and then from PDT to GMT:
  if ( (m_currentBin % 10) == 0 ) { 
    std::cout << 'x' << ' ';
    printTime(std::cout,m_timeStamp);
    std::cout << std::endl;
  }
  else { std::cout << '.' << std::flush; }

  if(m_intreeToDisk){
    // Recreating TFile for intermediate TTree to release unsed memory from disk
    createtfile4intree(m_sodir,m_intreetfilename);
  }
}



// Called after on the last event of the event loop
// This timestamp is given with double precision
void MonEventLooper::lastEvent(Double_t timeStampdouble) {

  // kludge: double the last event because the last event does not get used.

  
  m_timestamp_lastevt_inbin = timeStampdouble;
  if (m_currentBin>0) TimeInterval::m_interval=timeStampdouble-m_currentStart;
  else TimeInterval::m_interval=timeStampdouble-m_timestamp_firstevt_inbin;
  m_timeinterval =  TimeInterval::m_interval;


  // tmp
  /*
  std::cout << "Info concerning time intervals for bin " << m_currentBin << std::endl
	    << setprecision(20) 
	    << "m_timeinterval = " << m_timeinterval << std::endl
	    << "m_timestamp_firstevt_inbin = " << m_timestamp_firstevt_inbin << std::endl
	    << "m_timestamp_lastevt_inbin = " << m_timestamp_lastevt_inbin << std::endl;
  */
  // endtmp

 
  m_intree->Fill();

  filterEvent();
  stripVals()->increment(m_intree);
  m_stripValCol->latchValue();
  m_sectree->Reset();
  m_sectree->Fill();
  m_secstripValCol->increment(m_sectree);
  m_secstripValCol->latchValue();
  m_tree->Fill();
  m_stripValCol->reset();
  m_intree->Reset();

  m_sec_last = timeStampdouble;
  printTime(std::cout,m_timeStamp);
  std::cout << std::endl << std::endl;

  // Delete all contents from Tfile 

  std::string deletefile = "rm -rf ";
  deletefile +=m_sodir;
  deletefile +=m_intreetfilename;
  
  if(system(deletefile.c_str())){
    std::cout << "" << std::endl
	      << "PRoblems deleting file used to store intermediate ttree: " << std::endl
	      << "Command failed: " << deletefile.c_str() << std::endl;

  }
    
}



//
// Called every event
// this timestamp is given with double precision 
void MonEventLooper::logEvent(Long64_t /* ievent */, Double_t timeStampdouble ) {

  ULong64_t timeStamp = ULong64_t(timeStampdouble);
  if ( timeStamp < ULong64_t(m_timeStamp) ) {
    m_currentFlags += 4;
  }
  m_timeStamp = timeStampdouble;
}

bool MonEventLooper::readEvent(Long64_t ievent){
  for(std::vector<MonInputCollection*>::iterator it=m_incol.begin(); it!=m_incol.end();it++){
    (*it)->readEventProf(ievent);
    // (*it)->readEvent(ievent);
  }

  m_intree->Fill();
  
  //tmp
  /*
  if(m_evtcounter%1000==0){
    std::cout << "MonEventLooper::readEvent:DEBUG INFO" <<std::endl
	      << "Event number " << m_evtcounter <<": " 
	      << "m_intree->GetBranch(CalXAdc_TowerCalLayerCalColumnFaceRange)->GetTotalSize() = " 
	      << m_intree->GetBranch("CalXAdc_TowerCalLayerCalColumnFaceRange")->GetTotalSize() << std::endl;
  }
  */
  // endtmp

  return kTRUE;
}


void MonEventLooper::filterEvent(){
  m_globalCut->applyCut(m_intree);
  m_nFilter=m_globalCut->nFilter();
  m_nUsed=m_globalCut->nUsed();
}

