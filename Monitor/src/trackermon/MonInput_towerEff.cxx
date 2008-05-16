// 
// Class for input of quantity towerEff for monitoring 
// 
// Created by dpaneque on Fri May 16 04:55:16 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_towerEff.h"
#include <iostream>

// User defined part 

#define NAME towerEff
#define OUTBRANCH "towerEff_Tower"
#define LEAF "towerEff_Tower[16]/D"
#define INBRANCH "towerEff"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "towerEff"


// End user defined part 

MonInput_towerEff::MonInput_towerEff(){
  m_name=OUTBRANCH;
}
MonInput_towerEff::~MonInput_towerEff(){
}


int MonInput_towerEff::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_towerEff::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_towerEff::setValue(TObject* event) {
}
std::string MonInput_towerEff::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_towerEff::getDescription(){
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

