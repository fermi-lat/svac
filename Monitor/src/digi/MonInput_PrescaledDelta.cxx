// 
// Class for input of quantity PrescaledDelta for monitoring 
// 
// Created by dpaneque on Fri Sep 28 18:41:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PrescaledDelta.h"
#include <iostream>

// User defined part 

#define NAME PrescaledDelta
#define OUTBRANCH "PrescaledDelta"
#define LEAF "PrescaledDelta/L"
#define INBRANCH "m_metaEvent"
#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of GEM prescaled events between two successive read out events."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_PrescaledDelta::MonInput_PrescaledDelta(){
  m_name=OUTBRANCH;
  firstevt = 1;
  m_previous = 0;
  m_current = 0;
}
MonInput_PrescaledDelta::~MonInput_PrescaledDelta(){
}


int MonInput_PrescaledDelta::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PrescaledDelta::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_PrescaledDelta::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val = 0;
  m_current = de->getMetaEvent().scalers().prescaled();
  if(firstevt){
     m_previous = m_current;
     firstevt = 0;
  }
  else{
    m_val = m_current-m_previous;
    m_previous = m_current;
  }

}
std::string MonInput_PrescaledDelta::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PrescaledDelta::getDescription(){
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

