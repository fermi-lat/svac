// 
// Class for input of quantity WP8CTBestEnergyProb for monitoring 
// 
// Created by lbaldini on Tue Feb  3 15:15:12 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_WP8CTBestEnergyProb.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME WP8CTBestEnergyProb
#define OUTBRANCH "WP8CTBestEnergyProb"
#define LEAF "WP8CTBestEnergyProb/F"
#define INBRANCH "WP8CTBestEnergyProb"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Event by event estimator of the energy reconstruction quality"


// End user defined part 

MonInput_WP8CTBestEnergyProb::MonInput_WP8CTBestEnergyProb(){
  m_name=OUTBRANCH;
}
MonInput_WP8CTBestEnergyProb::~MonInput_WP8CTBestEnergyProb(){
}


int MonInput_WP8CTBestEnergyProb::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_WP8CTBestEnergyProb::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_WP8CTBestEnergyProb::setValue(TObject* event) {
}
std::string MonInput_WP8CTBestEnergyProb::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_WP8CTBestEnergyProb::getDescription(){
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

