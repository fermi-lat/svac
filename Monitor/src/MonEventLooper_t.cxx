//
// Base class
#include "MonEventLooper_t.h"

//
// stl
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

// ROOT IO
#include "digiRootData/DigiEvent.h"
#include "TTreeResult.h"
#include "TTreeRow.h"

//
//
void MonEventLooper::printTime(ostream& os, ULong64_t timestamp) {
  
  // Time from Mission elapsed time to Unix time and then from PDT to GMT:
  static const int METtoGMT = 978307200 + 25200;
  ULong64_t time = timestamp + METtoGMT;
  UInt_t itime = (UInt_t)(time);
  os << ctime((time_t*) (&itime)); 
}

//
//
MonEventLooper::MonEventLooper(UInt_t binSize, MonValue* col, std::vector<MonInputCollection*> incol, std::string eventcut, std::string timestampvar)
  :m_binSize(binSize),
   m_timeStamp(0),
   m_currentStart(0),
   m_currentEnd(0),
   m_currentFlags(0),
   m_sec_first(0),
   m_sec_last(0),
   m_startEvent(0),
   m_last(0),
   m_nFilter(0),
   m_nUsed(0),
   m_tree(0),
   m_intree(0),
   m_stripValCol(col),
   m_incol(incol),
   m_eventcut(eventcut),
   m_timestampvar(timestampvar),
   m_currentTimeStamp(0){

  // attach input chains
  for_each(m_incol.begin(), m_incol.end(), mem_fun(&MonInputCollection::attachChain));
  //create and populate intermediate tree
  m_intree = new TTree("Internal","Used to create output");
  for(std::vector<MonInputCollection*>::iterator it=m_incol.begin(); it!=m_incol.end();it++){
    (*it)->populateTableTree(m_intree);
  }
  m_currentTimeStamp=(UInt_t*)(m_intree->GetBranch(m_timestampvar.c_str())->GetAddress());
  
  //create output tree
  m_tree = new TTree("Time","Time binned data");
  //create output tree
  attachTree();
}


MonEventLooper::~MonEventLooper(){
}
void MonEventLooper::init() {

}

void MonEventLooper::attachTree() {

  m_tree->Branch("Bin_Index",(void*)(&m_currentBin),"Bin_Index/i");
  m_tree->Branch("Bin_Start",(void*)(&m_currentStart),"Bin_Start/l");
  m_tree->Branch("Bin_End",(void*)(&m_currentEnd),"Bin_End/l");
  m_tree->Branch("Bin_Flags",(void*)(&m_currentFlags),"Bin_Flags/i");
  m_tree->Branch("nEvents",(void*)(&m_nUsed),"nEvents/i");
  m_tree->Branch("nPassed",(void*)(&m_nFilter),"nPassed/i");

  std::string prefix;
  m_stripValCol->attach(*m_tree,prefix);
}


void MonEventLooper::go(Long64_t numEvents, Long64_t startEvent) {

  // set up the loop
  m_startEvent = startEvent;
  m_last = numEvents;
  UInt_t& currentTimeStamp=*m_currentTimeStamp;

  // Starting message
  std::cout << "Number of events used: " << m_last-startEvent << std::endl;
  std::cout << "Starting at event: " << startEvent << std::endl;
  
  // 
  init();

  UInt_t unsaved(0);

  // Event loop
  for (Int_t ievent= startEvent; ievent!=m_last; ievent++ ) {

    // Flags for later
    Bool_t filtered(kFALSE);
    Bool_t used(kFALSE);

    // call sub-class to read the event
    Bool_t ok = readEvent(ievent);
    if ( !ok ) {
      std::cerr << "Failed to read event " << ievent << " aborting" << std::endl;
      break;
    }    
    // initialize stuff on first event
    if ( ievent == startEvent ) {
      firstEvent(currentTimeStamp);
    } 

    // check for time-bin edge
    if ( currentTimeStamp >= m_currentEnd ) {
	// time-stamp outside of bin, jump to next bin
	// This latches and store all the values
      switchBins();
      unsaved = 0;
    } else {
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

void MonEventLooper::firstEvent(ULong64_t timeStamp)  {
  ULong64_t rem = timeStamp % m_binSize;
  m_currentBin = 0;
  m_currentStart = timeStamp - rem;
  m_currentEnd = m_currentStart + m_binSize;
  m_currentFlags = 3;
  m_sec_first = timeStamp;
  printTime(std::cout,timeStamp);
  std::cout << std::endl;
}

void MonEventLooper::switchBins() {

  m_currentFlags -= 1;
  stripVals()->increment(m_intree);
  m_stripValCol->latchValue();
  m_nUsed=m_intree->GetEntriesFast()-1;
  filterEvent();
  m_tree->Fill();
  m_stripValCol->reset();
  m_intree->GetEntry(m_nUsed);
  m_intree->Reset();
  m_intree->Fill();

  m_currentBin++;
  m_currentStart += m_binSize;
  m_currentEnd += m_binSize;
  m_currentFlags = 1;

  // Time from Mission elapsed time to Unix time and then from PDT to GMT:
  if ( (m_currentBin % 10) == 0 ) { 
    std::cout << 'x' << ' ';
    printTime(std::cout,m_timeStamp);
    std::cout << std::endl;
  }
  else { std::cout << '.' << std::flush; }
}

//
// Called after on the last event of the event loop
void MonEventLooper::lastEvent(ULong64_t timeStamp) {

  // kludge: double the last event because the last event does not get used.
  m_intree->Fill();
  stripVals()->increment(m_intree);
  m_stripValCol->latchValue();
  m_nUsed=m_intree->GetEntriesFast()-1;
  filterEvent();
  m_tree->Fill();
  m_stripValCol->reset();
  m_intree->Reset();

  m_sec_last = timeStamp;
  printTime(std::cout,m_timeStamp);
  std::cout << std::endl << std::endl;
}

//
// Called every event
void MonEventLooper::logEvent(Long64_t /* ievent */, ULong64_t timeStamp ) {
  if ( timeStamp < m_timeStamp ) {
    m_currentFlags += 4;
  }
  m_timeStamp = timeStamp;
}

bool MonEventLooper::readEvent(Long64_t ievent){
  for(std::vector<MonInputCollection*>::iterator it=m_incol.begin(); it!=m_incol.end();it++){
    (*it)->readEvent(ievent);
  }
  m_intree->Fill();
  return kTRUE;
}

void MonEventLooper::filterEvent(){
  TTreeResult* res;
  res=(TTreeResult*)m_intree->Query("1",m_eventcut.c_str(),"",m_intree->GetEntriesFast()-1);
  if (res){
    m_nFilter=res->GetRowCount();
    delete res;
  }else{
    m_nFilter=0;
  }  
}

