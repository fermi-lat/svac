// 
// Class for input of quantity FswGamState for monitoring 
// 
// Created by dpaneque on Thu Jul 17 22:24:13 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FswGamState.h"
#include <iostream>

// User defined part 

#define NAME FswGamState
#define OUTBRANCH "FswGamState"
#define LEAF "FswGamState/I"
#define INBRANCH "FswGamState"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "4-bit state word summaryzing the status of the gamma filter"


// End user defined part 

MonInput_FswGamState::MonInput_FswGamState(){
  m_name=OUTBRANCH;
}
MonInput_FswGamState::~MonInput_FswGamState(){
}


int MonInput_FswGamState::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FswGamState::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FswGamState::setValue(TObject* event) {
}
std::string MonInput_FswGamState::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FswGamState::getDescription(){
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

