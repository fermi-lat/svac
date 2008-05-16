// 
// Class for input of quantity layerdXY for monitoring 
// 
// Created by dpaneque on Fri May 16 04:56:39 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_layerdXY.h"
#include <iostream>

// User defined part 

#define NAME layerdXY
#define OUTBRANCH "layerdXY_TowerPlane"
#define LEAF "layerdXY_TowerPlane[16][36]/D"
#define INBRANCH "layerdXY"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "layerdXY"


// End user defined part 

MonInput_layerdXY::MonInput_layerdXY(){
  m_name=OUTBRANCH;
}
MonInput_layerdXY::~MonInput_layerdXY(){
}


int MonInput_layerdXY::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_layerdXY::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_layerdXY::setValue(TObject* event) {
}
std::string MonInput_layerdXY::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_layerdXY::getDescription(){
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

