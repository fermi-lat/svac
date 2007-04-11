// 
// Class for input of quantity eventid for monitoring 
// 
// Created by kocian on Tue Mar  6 22:51:00 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_eventid.h"
#include <iostream>

// User defined part 

#define NAME eventid
#define OUTBRANCH "eventid"
#define LEAF "eventid/i"
#define INBRANCH "EvtEventId"
#define ACCESSOR EvtEventId
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "event id"
#include "../MeritEvent.h"

// End user defined part 

MonInput_eventid::MonInput_eventid(){
}
MonInput_eventid::~MonInput_eventid(){
}


int MonInput_eventid::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_eventid::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_eventid::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_eventid::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_eventid::getDescription(){
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

