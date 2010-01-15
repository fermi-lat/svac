// 
// Class for input of quantity layerOcc_err for monitoring 
// 
// Created by lbaldini on Fri Jan 15 11:25:13 2010 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_layerOcc_err.h"
#include <iostream>

// User defined part 

#define NAME layerOcc_err
#define OUTBRANCH "layerOcc_err"
// Modification by lb starting...
#define LEAF "layerOcc_err_TowerPlane[16][36]/D"
// Modification by lb ended.
#define INBRANCH "layerOcc_err"
#define ACCESSOR NotNeeded
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "Error on the layerOcc variable"


// End user defined part 

MonInput_layerOcc_err::MonInput_layerOcc_err(){
  m_name=OUTBRANCH;
}
MonInput_layerOcc_err::~MonInput_layerOcc_err(){
}


int MonInput_layerOcc_err::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_layerOcc_err::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_layerOcc_err::setValue(TObject* event) {
}
std::string MonInput_layerOcc_err::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_layerOcc_err::getDescription(){
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

