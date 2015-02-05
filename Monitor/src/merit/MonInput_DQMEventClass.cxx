// 
// Class for input of quantity DQMEventClass for monitoring 
// 
// Created by bregeon on Thu Feb  5 15:25:16 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DQMEventClass.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME DQMEventClass
#define OUTBRANCH "DQMEventClass"
#define LEAF "DQMEventClass/i"
#define INBRANCH "DQMEventClass"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Event Class Bit map (FT1EventClass)"


// End user defined part 

MonInput_DQMEventClass::MonInput_DQMEventClass(){
  m_name=OUTBRANCH;
}
MonInput_DQMEventClass::~MonInput_DQMEventClass(){
}


int MonInput_DQMEventClass::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DQMEventClass::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_DQMEventClass::setValue(TObject* event) {
}
std::string MonInput_DQMEventClass::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DQMEventClass::getDescription(){
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

