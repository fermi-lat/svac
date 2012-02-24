// 
// Class for input of quantity timestamp for monitoring 
// 
// Created by kocian on Tue Feb 27 23:48:45 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_timestamp.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME timestamp
#define OUTBRANCH "timestamp"
#define LEAF "timestamp/i"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().time().current().timeSecs()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Time stamp (seconds since start of mission)"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_timestamp::MonInput_timestamp(){
  m_name=OUTBRANCH;
}
MonInput_timestamp::~MonInput_timestamp(){
}


int MonInput_timestamp::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_timestamp::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_timestamp::setValue(TObject* event) {
  DigiEvent* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_timestamp::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_timestamp::getDescription(){
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

