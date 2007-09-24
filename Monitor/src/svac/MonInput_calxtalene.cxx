// 
// Class for input of quantity calxtalene for monitoring 
// 
// Created by kocian on Fri Mar  9 20:38:36 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_calxtalene.h"
#include <iostream>

// User defined part 

#define NAME calxtalene
#define OUTBRANCH "calxtalene"
#define LEAF "calxtalene[16][8][12][2]/F"
#define INBRANCH "CalXtalEne"
#define ACCESSOR CalXtalEne
#define MONSOURCE SvacEvent
#define INPUTSOURCE "SvacEvent"
#define DESCRIPTION "crystal energy"

// End user defined part 

MonInput_calxtalene::MonInput_calxtalene(){
  m_name=OUTBRANCH;
}
MonInput_calxtalene::~MonInput_calxtalene(){
}


int MonInput_calxtalene::setOutputBranch(TTree* tree) {
  TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
  return bErr != 0 ? 0 : 1;
}
void MonInput_calxtalene::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,m_val);
}
void MonInput_calxtalene::setValue(TObject* event) {
}
std::string MonInput_calxtalene::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_calxtalene::getDescription(){
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

