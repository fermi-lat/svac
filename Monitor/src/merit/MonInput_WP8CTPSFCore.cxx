// 
// Class for input of quantity WP8CTPSFCore for monitoring 
// 
// Created by lbaldini on Tue Feb  3 15:16:11 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_WP8CTPSFCore.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME WP8CTPSFCore
#define OUTBRANCH "WP8CTPSFCore"
#define LEAF "WP8CTPSFCore/D"
#define INBRANCH "WP8CTPSFCore"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Event by event estimator of the direction reconstruction quality"


// End user defined part 

MonInput_WP8CTPSFCore::MonInput_WP8CTPSFCore(){
  m_name=OUTBRANCH;
}
MonInput_WP8CTPSFCore::~MonInput_WP8CTPSFCore(){
}


int MonInput_WP8CTPSFCore::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_WP8CTPSFCore::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_WP8CTPSFCore::setValue(TObject* event) {
}
std::string MonInput_WP8CTPSFCore::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_WP8CTPSFCore::getDescription(){
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

