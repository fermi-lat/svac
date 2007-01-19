//
// Base class
#include "MonEventLooper.h"

//
// stl
#include <iostream>
#include <cstdio>

// ROOT IO
#include "digiRootData/DigiEvent.h"

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
MonEventLooper::MonEventLooper(UInt_t binSize)
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
   m_stripValCol("Top",""),
   m_trigCnt("nEvents"),
   m_filterCnt("nPassed"),
   m_usedCnt("nUsed"){
  m_stripValCol.addVal(m_trigCnt);
  m_stripValCol.addVal(m_filterCnt);
  m_stripValCol.addVal(m_usedCnt);
}


MonEventLooper::~MonEventLooper(){
}


void MonEventLooper::attachTree(TTree& tree) {
  m_tree = &tree;

  tree.Branch("Bin_Index",(void*)(&m_currentBin),"Bin_Index/i");
  tree.Branch("Bin_Start",(void*)(&m_currentStart),"Bin_Start/l");
  tree.Branch("Bin_End",(void*)(&m_currentEnd),"Bin_End/l");
  tree.Branch("Bin_Flags",(void*)(&m_currentFlags),"Bin_Flags/i");

  std::string prefix;
  m_stripValCol.attach(tree,prefix);
}

void MonEventLooper::go(Long64_t numEvents, Long64_t startEvent) {

  // set up the loop
  m_startEvent = startEvent;
  Long64_t nTotal = getTotalEvents();
  m_last = numEvents < 1 ? nTotal : TMath::Min(numEvents+startEvent,nTotal);
  ULong64_t currentTimeStamp(0);

  // Starting message
  std::cout << "Number of events in the chain: " << nTotal << std::endl;
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
    Bool_t ok = readEvent(ievent,filtered,currentTimeStamp);
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
    m_nTrigger++; m_trigCnt++;    
    if ( !filtered ) {
      m_nFilter++; m_filterCnt++;

      // ok, this is the call that actually fills the event data
      useEvent(used);
      if ( used ) {
	m_nUsed++; m_usedCnt++;
      }
    }
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
  m_stripValCol.latchValue();
  m_tree->Fill();
  m_stripValCol.reset();

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

  m_stripValCol.latchValue();
  m_tree->Fill();
  m_stripValCol.reset();

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

