// 
// Class for input of quantity MeritObfGamStatus for monitoring 
// 
// Created by dpaneque on Thu May 29 04:12:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_MeritObfGamStatus.h"
#include <iostream>

// User defined part 

#define NAME MeritObfGamStatus
#define OUTBRANCH "MeritObfGamStatus"
#define LEAF "MeritObfGamStatus/D"
#define INBRANCH "ObfGamStatus"
#define ACCESSOR NotAplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "The 32 bit status word output from the Gamma Filter (retrieved from Merit file)"


// End user defined part 

MonInput_MeritObfGamStatus::MonInput_MeritObfGamStatus(){
  m_name=OUTBRANCH;
}
MonInput_MeritObfGamStatus::~MonInput_MeritObfGamStatus(){
}


int MonInput_MeritObfGamStatus::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_MeritObfGamStatus::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_MeritObfGamStatus::setValue(TObject* event) {
}
std::string MonInput_MeritObfGamStatus::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_MeritObfGamStatus::getDescription(){
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

