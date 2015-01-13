// 
// Class for input of quantity EvtEventId for monitoring 
// 
// Created by dpaneque on Tue Apr 22 03:56:45 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_EvtEventId.h"
#include <iostream>

// User defined part 

#define NAME EvtEventId
#define OUTBRANCH "EvtEventId"
#define LEAF "EvtEventId/i"
#define INBRANCH "EvtEventId"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Sequence number of event in the run (as generated)"


// End user defined part 

MonInput_EvtEventId::MonInput_EvtEventId(){
  m_name=OUTBRANCH;
}
MonInput_EvtEventId::~MonInput_EvtEventId(){
}


int MonInput_EvtEventId::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_EvtEventId::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_EvtEventId::setValue(TObject* event) {
}
std::string MonInput_EvtEventId::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_EvtEventId::getDescription(){
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

