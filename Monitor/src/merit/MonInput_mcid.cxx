// 
// Class for input of quantity mcid for monitoring 
// 
// Created by kocian on Fri Jun  1 21:41:01 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_mcid.h"
#include <iostream>

// User defined part 

#define NAME mcid
#define OUTBRANCH "mcid"
#define LEAF "mcid/F"
#define INBRANCH "McId"
#define ACCESSOR McId
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Monte Carlo id "

// End user defined part 

MonInput_mcid::MonInput_mcid(){
  m_name=OUTBRANCH;
}
MonInput_mcid::~MonInput_mcid(){
}


int MonInput_mcid::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_mcid::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_mcid::setValue(TObject* event) {
}
std::string MonInput_mcid::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_mcid::getDescription(){
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

