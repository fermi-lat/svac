// 
// Class for input of quantity Sequence for monitoring 
// 
// Created by dpaneque on Wed Sep 26 22:12:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Sequence.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Sequence
#define OUTBRANCH "Sequence"
#define LEAF "Sequence/L"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().scalers().sequence()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Sequence number of this event within the run"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_Sequence::MonInput_Sequence(){
  m_name=OUTBRANCH;
}
MonInput_Sequence::~MonInput_Sequence(){
}


int MonInput_Sequence::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Sequence::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_Sequence::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_Sequence::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Sequence::getDescription(){
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

