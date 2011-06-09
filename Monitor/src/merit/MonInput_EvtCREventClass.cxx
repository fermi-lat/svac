// 
// Class for input of quantity EvtCREventClass for monitoring 
// 
// Created by dpaneque on Wed Jun  8 17:02:20 2011 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_EvtCREventClass.h"
#include <iostream>

// User defined part 

#define NAME EvtCREventClass
#define OUTBRANCH "EvtCREventClass"
#define LEAF "EvtCREventClass/i"
#define INBRANCH "EvtCREventClass"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Parameter EvtCREventClass from merit file"


// End user defined part 

MonInput_EvtCREventClass::MonInput_EvtCREventClass(){
  m_name=OUTBRANCH;
}
MonInput_EvtCREventClass::~MonInput_EvtCREventClass(){
}


int MonInput_EvtCREventClass::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_EvtCREventClass::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_EvtCREventClass::setValue(TObject* event) {
}
std::string MonInput_EvtCREventClass::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_EvtCREventClass::getDescription(){
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

