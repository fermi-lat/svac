// 
// Class for input of quantity CTBGAM for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:05:58 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBGAM.h"
#include <iostream>

// User defined part 

#define NAME CTBGAM
#define OUTBRANCH "CTBGAM"
#define LEAF "CTBGAM/F"
#define INBRANCH "CTBGAM"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "xxx"


// End user defined part 

MonInput_CTBGAM::MonInput_CTBGAM(){
  m_name=OUTBRANCH;
}
MonInput_CTBGAM::~MonInput_CTBGAM(){
}


int MonInput_CTBGAM::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBGAM::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBGAM::setValue(TObject* event) {
}
std::string MonInput_CTBGAM::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBGAM::getDescription(){
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

