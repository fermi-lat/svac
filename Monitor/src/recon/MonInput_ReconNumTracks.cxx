// 
// Class for input of quantity ReconNumTracks for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:03:51 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ReconNumTracks.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME ReconNumTracks
#define OUTBRANCH "ReconNumTracks"
#define LEAF "ReconNumTracks[11]/s"
#define INBRANCH "m_tkr"
// #define ACCESSOR Capullo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector[11] reporting the number of tracks for this event (only component different to zero). This makes easier the computation of rates of events with n [0,10] number of tracks."
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_ReconNumTracks::MonInput_ReconNumTracks(){
  m_name=OUTBRANCH;
}
MonInput_ReconNumTracks::~MonInput_ReconNumTracks(){
}


int MonInput_ReconNumTracks::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_ReconNumTracks::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ReconNumTracks::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  

  for(UInt_t i = 0; i < 11; i++)
    m_val[i] = 0;


  TkrRecon* tkrRecon = de->getTkrRecon();
  UInt_t numtracks(0);
  
  if(tkrRecon) 
    numtracks = tkrRecon->getTrackCol()->GetLast()+1;

  // for now, just fill the first 10 tracks, but don't crash (>10 is allowed in Pass8)
  if(numtracks<=10)
    m_val[numtracks]++;
  
  /* else{
    std::cout << "Retrieved number of tracks = " << numtracks 
	      << " .This is not allowed. Something wrong happened."
	      << std:: endl;
    assert(0);
  }*/`


}
std::string MonInput_ReconNumTracks::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ReconNumTracks::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

