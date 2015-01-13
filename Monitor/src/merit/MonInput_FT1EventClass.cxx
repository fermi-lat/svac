// 
// Class for input of quantity FT1EventClass for monitoring 
// 
// Created by lbaldini on Tue Jan 13 15:31:52 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1EventClass.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME FT1EventClass
#define OUTBRANCH "FT1EventClass"
#define LEAF "FT1EventClass/I"
#define INBRANCH "FT1EventClass"
#define ACCESSOR 
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Event class"


// End user defined part 

MonInput_FT1EventClass::MonInput_FT1EventClass(){
  m_name=OUTBRANCH;
}
MonInput_FT1EventClass::~MonInput_FT1EventClass(){
}


int MonInput_FT1EventClass::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1EventClass::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FT1EventClass::setValue(TObject* event) {
}
std::string MonInput_FT1EventClass::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1EventClass::getDescription(){
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

