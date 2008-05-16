// 
// Class for input of quantity stripOcc for monitoring 
// 
// Created by dpaneque on Fri May 16 04:57:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_stripOcc.h"
#include <iostream>

// User defined part 

#define NAME stripOcc
#define OUTBRANCH "stripOcc_TowerPlane"
#define LEAF "stripOcc_TowerPlane[16][36]/D"
#define INBRANCH "stripOcc"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "stripOcc"


// End user defined part 

MonInput_stripOcc::MonInput_stripOcc(){
  m_name=OUTBRANCH;
}
MonInput_stripOcc::~MonInput_stripOcc(){
}


int MonInput_stripOcc::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_stripOcc::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_stripOcc::setValue(TObject* event) {
}
std::string MonInput_stripOcc::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_stripOcc::getDescription(){
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

