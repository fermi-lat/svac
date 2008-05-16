// 
// Class for input of quantity TOT_FitProb for monitoring 
// 
// Created by dpaneque on Fri May 16 04:53:41 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_FitProb.h"
#include <iostream>

// User defined part 

#define NAME TOT_FitProb
#define OUTBRANCH "TOT_FitProb_TowerPlane"
#define LEAF "TOT_FitProb_TowerPlane[16][36]/D"
#define INBRANCH "TOT_FitProb"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_FitProb"


// End user defined part 

MonInput_TOT_FitProb::MonInput_TOT_FitProb(){
  m_name=OUTBRANCH;
}
MonInput_TOT_FitProb::~MonInput_TOT_FitProb(){
}


int MonInput_TOT_FitProb::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_FitProb::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_FitProb::setValue(TObject* event) {
}
std::string MonInput_TOT_FitProb::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_FitProb::getDescription(){
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

