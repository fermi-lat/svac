// 
// Class for input of quantity layerEff_err for monitoring 
// 
// Created by dpaneque on Fri May 16 04:54:48 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_layerEff_err.h"
#include <iostream>

// User defined part 

#define NAME layerEff_err
#define OUTBRANCH "layerEff_err_TowerPlane"
#define LEAF "layerEff_err_TowerPlane[16][36]/D"
#define INBRANCH "layerEff_err"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "layerEff_err"


// End user defined part 

MonInput_layerEff_err::MonInput_layerEff_err(){
  m_name=OUTBRANCH;
}
MonInput_layerEff_err::~MonInput_layerEff_err(){
}


int MonInput_layerEff_err::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_layerEff_err::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_layerEff_err::setValue(TObject* event) {
}
std::string MonInput_layerEff_err::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_layerEff_err::getDescription(){
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

