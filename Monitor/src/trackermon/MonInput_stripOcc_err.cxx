// 
// Class for input of quantity stripOcc_err for monitoring 
// 
// Created by lbaldini on Fri Jan 15 13:01:16 2010 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_stripOcc_err.h"
#include <iostream>

// User defined part 

#define NAME stripOcc_err
#define OUTBRANCH "stripOcc_err"
// Modification by lb starting...
#define LEAF "stripOcc_err_TowerPlane[16][36]/D"
// Modification by lb ended.
#define INBRANCH "stripOcc_err"
#define ACCESSOR NotNeeded
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "Error on the stripOcc variable"


// End user defined part 

MonInput_stripOcc_err::MonInput_stripOcc_err(){
  m_name=OUTBRANCH;
}
MonInput_stripOcc_err::~MonInput_stripOcc_err(){
}


int MonInput_stripOcc_err::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_stripOcc_err::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_stripOcc_err::setValue(TObject* event) {
}
std::string MonInput_stripOcc_err::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_stripOcc_err::getDescription(){
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

