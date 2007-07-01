// 
// Class for input of quantity GemDiscardedDelta for monitoring 
// 
// Created by dpaneque on Sun Jul  1 02:05:05 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DiscardedDelta.h"
#include <iostream>

// User defined part 

#define NAME GemDiscardedDelta
#define OUTBRANCH "DiscardedDelta"
#define LEAF "DiscardedDelta/L"
#define INBRANCH "m_metaEvent"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of GEM discarded events between two successive read out events"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DiscardedDelta::MonInput_DiscardedDelta(){
  m_name=OUTBRANCH;
  firstevt = 1;
  m_previous = 0;
  m_current = 0;
}
MonInput_DiscardedDelta::~MonInput_DiscardedDelta(){
}


int MonInput_DiscardedDelta::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DiscardedDelta::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DiscardedDelta::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  
  m_val = 0;
  m_current = de->getMetaEvent().scalers().discarded();
  if(firstevt){
     m_previous = m_current;
     firstevt = 0;
  }
  else{
    m_val = m_current-m_previous;
    m_previous = m_current;
  }

}
std::string MonInput_DiscardedDelta::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DiscardedDelta::getDescription(){
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

