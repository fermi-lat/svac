// 
// Class for input of quantity TemBug for monitoring 
// 
// Created by dpaneque on Fri Mar 27 19:50:54 2009 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TemBug.h"
#include <iostream>

// User defined part 

#define NAME TemBug
#define OUTBRANCH "TemBug"
#define LEAF "TemBug/O"
#define INBRANCH "m_summary"
#define ACCESSOR getEventSummaryData().temBug()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "True if there is a Tem Bug, False otherwise"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_TemBug::MonInput_TemBug(){
  m_name=OUTBRANCH;
}
MonInput_TemBug::~MonInput_TemBug(){
}


int MonInput_TemBug::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TemBug::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_TemBug::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_TemBug::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TemBug::getDescription(){
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

