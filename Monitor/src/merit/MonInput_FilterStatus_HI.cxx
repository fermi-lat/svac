// 
// Class for input of quantity FilterStatus_HI for monitoring 
// 
// Created by dpaneque on Thu Mar 13 05:02:53 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FilterStatus_HI.h"
#include <iostream>

// User defined part 

#define NAME FilterStatus_HI
#define OUTBRANCH "FilterStatus_HI"
#define LEAF "FilterStatus_HI/D"
#define INBRANCH "FilterStatus_HI"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "its 15-31 of the filter status word (17 bits)"


// End user defined part 

MonInput_FilterStatus_HI::MonInput_FilterStatus_HI(){
  m_name=OUTBRANCH;
}
MonInput_FilterStatus_HI::~MonInput_FilterStatus_HI(){
}


int MonInput_FilterStatus_HI::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FilterStatus_HI::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FilterStatus_HI::setValue(TObject* event) {
}
std::string MonInput_FilterStatus_HI::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FilterStatus_HI::getDescription(){
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

