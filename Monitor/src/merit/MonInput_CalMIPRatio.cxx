// 
// Class for input of quantity CalMIPRatio for monitoring 
// 
// Created by dpaneque on Fri Sep 12 00:39:02 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalMIPRatio.h"
#include <iostream>

// User defined part 

#define NAME CalMIPRatio
#define OUTBRANCH "CalMIPRatio"
#define LEAF "CalMIPRatio/F"
#define INBRANCH "CalMIPRatio"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Ratio of measured energy to that expected from a minimum-ionizing particle"


// End user defined part 

MonInput_CalMIPRatio::MonInput_CalMIPRatio(){
  m_name=OUTBRANCH;
}
MonInput_CalMIPRatio::~MonInput_CalMIPRatio(){
}


int MonInput_CalMIPRatio::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalMIPRatio::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalMIPRatio::setValue(TObject* event) {
}
std::string MonInput_CalMIPRatio::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalMIPRatio::getDescription(){
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

