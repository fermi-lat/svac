// 
// Class for input of quantity calxtalmaxene for monitoring 
// 
// Created by kocian on Fri Apr 20 20:47:47 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_calxtalmaxene.h"
#include <iostream>

// User defined part 

#define NAME calxtalmaxene
#define OUTBRANCH "calxtalmaxene"
#define LEAF "calxtalmaxene/F"
#define INBRANCH "CalXtalMaxEne"
#define ACCESSOR CalXtalMaxEne
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Energy of crystal with highest energy"

// End user defined part 

MonInput_calxtalmaxene::MonInput_calxtalmaxene(){
  m_name=OUTBRANCH;
}
MonInput_calxtalmaxene::~MonInput_calxtalmaxene(){
}


int MonInput_calxtalmaxene::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_calxtalmaxene::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_calxtalmaxene::setValue(TObject* event) {
}
std::string MonInput_calxtalmaxene::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_calxtalmaxene::getDescription(){
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

