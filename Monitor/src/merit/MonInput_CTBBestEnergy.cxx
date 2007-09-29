// 
// Class for input of quantity CTBBestEnergy for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:12:23 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBBestEnergy.h"
#include <iostream>

// User defined part 

#define NAME CTBBestEnergy
#define OUTBRANCH "CTBBestEnergy"
#define LEAF "CTBBestEnergy/F"
#define INBRANCH "CTBBestEnergy"
#define ACCESSOR hhh
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Best Estimated energy from among the 4 methods."


// End user defined part 

MonInput_CTBBestEnergy::MonInput_CTBBestEnergy(){
  m_name=OUTBRANCH;
}
MonInput_CTBBestEnergy::~MonInput_CTBBestEnergy(){
}


int MonInput_CTBBestEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBBestEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBBestEnergy::setValue(TObject* event) {
}
std::string MonInput_CTBBestEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBBestEnergy::getDescription(){
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

