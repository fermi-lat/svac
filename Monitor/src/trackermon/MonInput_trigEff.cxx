// 
// Class for input of quantity trigEff for monitoring 
// 
// Created by dpaneque on Fri May 16 04:55:52 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_trigEff.h"
#include <iostream>

// User defined part 

#define NAME trigEff
#define OUTBRANCH "trigEff_Tower"
#define LEAF "trigEff_Tower[16]/D"
#define INBRANCH "trigEff"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "trigEff"


// End user defined part 

MonInput_trigEff::MonInput_trigEff(){
  m_name=OUTBRANCH;
}
MonInput_trigEff::~MonInput_trigEff(){
}


int MonInput_trigEff::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_trigEff::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_trigEff::setValue(TObject* event) {
}
std::string MonInput_trigEff::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_trigEff::getDescription(){
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

