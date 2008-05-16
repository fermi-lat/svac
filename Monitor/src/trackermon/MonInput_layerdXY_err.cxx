// 
// Class for input of quantity layerdXY_err for monitoring 
// 
// Created by dpaneque on Fri May 16 04:56:58 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_layerdXY_err.h"
#include <iostream>

// User defined part 

#define NAME layerdXY_err
#define OUTBRANCH "layerdXY_err_TowerPlane"
#define LEAF "layerdXY_err_TowerPlane[16][36]/D"
#define INBRANCH "layerdXY_err"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "layerdXY_err"


// End user defined part 

MonInput_layerdXY_err::MonInput_layerdXY_err(){
  m_name=OUTBRANCH;
}
MonInput_layerdXY_err::~MonInput_layerdXY_err(){
}


int MonInput_layerdXY_err::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_layerdXY_err::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_layerdXY_err::setValue(TObject* event) {
}
std::string MonInput_layerdXY_err::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_layerdXY_err::getDescription(){
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

