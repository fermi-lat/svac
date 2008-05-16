// 
// Class for input of quantity towerEff_err for monitoring 
// 
// Created by dpaneque on Fri May 16 04:55:34 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_towerEff_err.h"
#include <iostream>

// User defined part 

#define NAME towerEff_err
#define OUTBRANCH "towerEff_err_Tower"
#define LEAF "towerEff_err_Tower[16]/D"
#define INBRANCH "towerEff_err"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "towerEff_err"


// End user defined part 

MonInput_towerEff_err::MonInput_towerEff_err(){
  m_name=OUTBRANCH;
}
MonInput_towerEff_err::~MonInput_towerEff_err(){
}


int MonInput_towerEff_err::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_towerEff_err::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_towerEff_err::setValue(TObject* event) {
}
std::string MonInput_towerEff_err::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_towerEff_err::getDescription(){
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

