// 
// Class for input of quantity trigEff_err for monitoring 
// 
// Created by dpaneque on Fri May 16 04:56:20 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_trigEff_err.h"
#include <iostream>

// User defined part 

#define NAME trigEff_err
#define OUTBRANCH "trigEff_err_Tower"
#define LEAF "trigEff_err_Tower[16]/D"
#define INBRANCH "trigEff_err"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "trigEff_err"


// End user defined part 

MonInput_trigEff_err::MonInput_trigEff_err(){
  m_name=OUTBRANCH;
}
MonInput_trigEff_err::~MonInput_trigEff_err(){
}


int MonInput_trigEff_err::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_trigEff_err::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_trigEff_err::setValue(TObject* event) {
}
std::string MonInput_trigEff_err::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_trigEff_err::getDescription(){
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

