// 
// Class for input of quantity layerOcc for monitoring 
// 
// Created by dpaneque on Fri May 16 04:57:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_layerOcc.h"
#include <iostream>

// User defined part 

#define NAME layerOcc
#define OUTBRANCH "layerOcc_TowerPlane"
#define LEAF "layerOcc_TowerPlane[16][36]/D"
#define INBRANCH "layerOcc"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "layerOcc"


// End user defined part 

MonInput_layerOcc::MonInput_layerOcc(){
  m_name=OUTBRANCH;
}
MonInput_layerOcc::~MonInput_layerOcc(){
}


int MonInput_layerOcc::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_layerOcc::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_layerOcc::setValue(TObject* event) {
}
std::string MonInput_layerOcc::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_layerOcc::getDescription(){
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

