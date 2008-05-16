// 
// Class for input of quantity fracSat for monitoring 
// 
// Created by dpaneque on Fri May 16 04:57:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_fracSat.h"
#include <iostream>

// User defined part 

#define NAME fracSat
#define OUTBRANCH "fracSat_TowerPlane"
#define LEAF "fracSat_TowerPlane[16][36]/D"
#define INBRANCH "fracSat"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "fracSat"


// End user defined part 

MonInput_fracSat::MonInput_fracSat(){
  m_name=OUTBRANCH;
}
MonInput_fracSat::~MonInput_fracSat(){
}


int MonInput_fracSat::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_fracSat::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_fracSat::setValue(TObject* event) {
}
std::string MonInput_fracSat::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_fracSat::getDescription(){
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

