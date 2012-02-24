// 
// Class for input of quantity EventSizeInBytes for monitoring 
// 
// Created by dpaneque on Tue Jul  1 02:33:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_EventSizeInBytes.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME EventSizeInBytes
#define OUTBRANCH "EventSizeInBytes"
#define LEAF "EventSizeInBytes/i"
#define INBRANCH "m_summary"
#define ACCESSOR getEventSummaryData().eventSizeInBytes()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Size of the evt in Bytes (before compression)"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_EventSizeInBytes::MonInput_EventSizeInBytes(){
  m_name=OUTBRANCH;
}
MonInput_EventSizeInBytes::~MonInput_EventSizeInBytes(){
}


int MonInput_EventSizeInBytes::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_EventSizeInBytes::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_EventSizeInBytes::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_EventSizeInBytes::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_EventSizeInBytes::getDescription(){
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

