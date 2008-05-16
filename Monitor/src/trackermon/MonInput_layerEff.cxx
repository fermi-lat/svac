// 
// Class for input of quantity layerEff for monitoring 
// 
// Created by dpaneque on Fri May 16 04:54:21 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_layerEff.h"
#include <iostream>

// User defined part 

#define NAME layerEff
#define OUTBRANCH "layerEff_TowerPlane"
#define LEAF "layerEff_TowerPlane[16][36]/D"
#define INBRANCH "layerEff"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "layerEff"


// End user defined part 

MonInput_layerEff::MonInput_layerEff(){
  m_name=OUTBRANCH;
}
MonInput_layerEff::~MonInput_layerEff(){
}


int MonInput_layerEff::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_layerEff::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_layerEff::setValue(TObject* event) {
}
std::string MonInput_layerEff::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_layerEff::getDescription(){
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

