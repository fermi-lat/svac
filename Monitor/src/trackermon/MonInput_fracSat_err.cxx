// 
// Class for input of quantity fracSat_err for monitoring 
// 
// Created by lbaldini on Thu Jan 14 18:31:31 2010 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_fracSat_err.h"
#include <iostream>

// User defined part 

#define NAME fracSat_err
#define OUTBRANCH "fracSat_err"
// Modification by lb starting.
#define LEAF "fracSat_err_TowerPlane[16][36]/D"
// Modification by lb ended.
#define INBRANCH "fracSat_err"
#define ACCESSOR NotNeeded
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "Error on the number of saturated Tracker planes"


// End user defined part 

MonInput_fracSat_err::MonInput_fracSat_err(){
  m_name=OUTBRANCH;
}
MonInput_fracSat_err::~MonInput_fracSat_err(){
}


int MonInput_fracSat_err::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_fracSat_err::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_fracSat_err::setValue(TObject* event) {
}
std::string MonInput_fracSat_err::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_fracSat_err::getDescription(){
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

