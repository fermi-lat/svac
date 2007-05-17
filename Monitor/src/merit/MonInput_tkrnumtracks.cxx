// 
// Class for input of quantity tkrnumtracks for monitoring 
// 
// Created by kocian on Fri Apr 20 20:44:19 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_tkrnumtracks.h"
#include <iostream>

// User defined part 

#define NAME tkrnumtracks
#define OUTBRANCH "tkrnumtracks"
#define LEAF "tkrnumtracks/F"
#define INBRANCH "TkrNumTracks"
#define ACCESSOR TkrNumTracks
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of tracks"
#include "../MeritEvent.h"

// End user defined part 

MonInput_tkrnumtracks::MonInput_tkrnumtracks(){
  m_name=OUTBRANCH;
}
MonInput_tkrnumtracks::~MonInput_tkrnumtracks(){
}


int MonInput_tkrnumtracks::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_tkrnumtracks::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_tkrnumtracks::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_tkrnumtracks::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_tkrnumtracks::getDescription(){
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

