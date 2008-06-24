// 
// Class for input of quantity CurrentTimeToneMissing for monitoring 
// 
// Created by dpaneque on Tue Jun 24 01:15:42 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CurrentTimeToneMissing.h"
#include <iostream>

// User defined part 

#define NAME CurrentTimeToneMissing
#define OUTBRANCH "CurrentTimeToneMissing"
#define LEAF "CurrentTimeToneMissing/O"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().time().current().incomplete()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "1 if time tone from current evt is not complete. Zero otherwise"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CurrentTimeToneMissing::MonInput_CurrentTimeToneMissing(){
  m_name=OUTBRANCH;
}
MonInput_CurrentTimeToneMissing::~MonInput_CurrentTimeToneMissing(){
}


int MonInput_CurrentTimeToneMissing::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CurrentTimeToneMissing::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CurrentTimeToneMissing::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_CurrentTimeToneMissing::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CurrentTimeToneMissing::getDescription(){
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

