// 
// Class for input of quantity WP8BestEnergy for monitoring 
// 
// Created by lbaldini on Tue Feb  3 15:14:15 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_WP8BestEnergy.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME WP8BestEnergy
#define OUTBRANCH "WP8BestEnergy"
#define LEAF "WP8BestEnergy/D"
#define INBRANCH "WP8BestEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Our energy measurement"


// End user defined part 

MonInput_WP8BestEnergy::MonInput_WP8BestEnergy(){
  m_name=OUTBRANCH;
}
MonInput_WP8BestEnergy::~MonInput_WP8BestEnergy(){
}


int MonInput_WP8BestEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_WP8BestEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_WP8BestEnergy::setValue(TObject* event) {
}
std::string MonInput_WP8BestEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_WP8BestEnergy::getDescription(){
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

