// 
// Class for input of quantity Mfilterstatus_hi for monitoring 
// 
// Created by kocian on Sat Apr 21 00:03:41 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Mfilterstatus_hi.h"
#include <iostream>

// User defined part 

#define NAME Mfilterstatus_hi
#define OUTBRANCH "Mfilterstatus_hi"
#define LEAF "Mfilterstatus_hi/D"
#define INBRANCH "FilterStatus_HI"
#define ACCESSOR FilterStatus_HI
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "bits 15-31 of the filter status word (17 bits)"

// End user defined part 

MonInput_Mfilterstatus_hi::MonInput_Mfilterstatus_hi(){
  m_name=OUTBRANCH;
}
MonInput_Mfilterstatus_hi::~MonInput_Mfilterstatus_hi(){
}


int MonInput_Mfilterstatus_hi::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Mfilterstatus_hi::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Mfilterstatus_hi::setValue(TObject* event) {
}
std::string MonInput_Mfilterstatus_hi::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Mfilterstatus_hi::getDescription(){
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

