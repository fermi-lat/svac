// 
// Class for input of quantity TkrNumTracks for monitoring 
// 
// Created by dpaneque on Fri Sep 12 00:06:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrNumTracks.h"
#include <iostream>

// User defined part 

#define NAME TkrNumTracks
#define OUTBRANCH "TkrNumTracks"
#define LEAF "TkrNumTracks/F"
#define INBRANCH "TkrNumTracks"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of tracks found (Maximum is set by TkrRecon, currently 10)"


// End user defined part 

MonInput_TkrNumTracks::MonInput_TkrNumTracks(){
  m_name=OUTBRANCH;
}
MonInput_TkrNumTracks::~MonInput_TkrNumTracks(){
}


int MonInput_TkrNumTracks::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrNumTracks::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrNumTracks::setValue(TObject* event) {
}
std::string MonInput_TkrNumTracks::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrNumTracks::getDescription(){
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

