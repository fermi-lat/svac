// 
// Class for input of quantity CrateNumber for monitoring 
// 
// Created by dpaneque on Wed Oct 31 01:51:55 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CrateNumber.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME CrateNumber
#define OUTBRANCH "CrateNumber"
#define LEAF "CrateNumber/I"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().datagram().crate()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Crate number; source from which this datagram comes from."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CrateNumber::MonInput_CrateNumber(){
  m_name=OUTBRANCH;
}
MonInput_CrateNumber::~MonInput_CrateNumber(){
}


int MonInput_CrateNumber::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CrateNumber::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CrateNumber::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_CrateNumber::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CrateNumber::getDescription(){
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

