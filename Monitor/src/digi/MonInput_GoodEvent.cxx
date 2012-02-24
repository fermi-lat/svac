// 
// Class for input of quantity GoodEvent for monitoring 
// 
// Created by bregeon on Tue Jan 12 15:14:48 2010 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_GoodEvent.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME GoodEvent
#define OUTBRANCH "GoodEvent"
#define LEAF "GoodEvent/O"
#define INBRANCH "m_summary"
#define ACCESSOR getEventSummaryData().goodEvent()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Flag events without any error"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_GoodEvent::MonInput_GoodEvent(){
  m_name=OUTBRANCH;
}
MonInput_GoodEvent::~MonInput_GoodEvent(){
}


int MonInput_GoodEvent::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_GoodEvent::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_GoodEvent::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_GoodEvent::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_GoodEvent::getDescription(){
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

