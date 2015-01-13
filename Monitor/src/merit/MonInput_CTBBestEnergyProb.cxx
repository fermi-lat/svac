// 
// Class for input of quantity CTBBestEnergyProb for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:10:45 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBBestEnergyProb.h"
#include <iostream>

// User defined part 

#define NAME CTBBestEnergyProb
#define OUTBRANCH "CTBBestEnergyProb"
#define LEAF "CTBBestEnergyProb/F"
#define INBRANCH "CTBBestEnergyProb"
#define ACCESSOR bbb
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Energy probability knob. Tunes the energy resolution for the selected method"


// End user defined part 

MonInput_CTBBestEnergyProb::MonInput_CTBBestEnergyProb(){
  m_name=OUTBRANCH;
}
MonInput_CTBBestEnergyProb::~MonInput_CTBBestEnergyProb(){
}


int MonInput_CTBBestEnergyProb::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBBestEnergyProb::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBBestEnergyProb::setValue(TObject* event) {
}
std::string MonInput_CTBBestEnergyProb::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBBestEnergyProb::getDescription(){
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

