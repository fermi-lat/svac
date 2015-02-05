// 
// Class for input of quantity DQMEventType for monitoring 
// 
// Created by bregeon on Thu Feb  5 15:25:59 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DQMEventType.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME DQMEventType
#define OUTBRANCH "DQMEventType"
#define LEAF "DQMEventType/i"
#define INBRANCH "DQMEventType"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Event type (FT1EventType)"


// End user defined part 

MonInput_DQMEventType::MonInput_DQMEventType(){
  m_name=OUTBRANCH;
}
MonInput_DQMEventType::~MonInput_DQMEventType(){
}


int MonInput_DQMEventType::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DQMEventType::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_DQMEventType::setValue(TObject* event) {
}
std::string MonInput_DQMEventType::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DQMEventType::getDescription(){
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

