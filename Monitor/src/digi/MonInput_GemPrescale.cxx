// 
// Class for input of quantity GemPrescale for monitoring 
// 
// Created by dpaneque on Sat May 24 21:46:05 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_GemPrescale.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME GemPrescale
#define OUTBRANCH "GemPrescale"
#define LEAF "GemPrescale/i"
#define INBRANCH "m_levelOneTrigger"
#define ACCESSOR getL1T().getGemPrescale()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "blblbl"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_GemPrescale::MonInput_GemPrescale(){
  m_name=OUTBRANCH;
}
MonInput_GemPrescale::~MonInput_GemPrescale(){
}


int MonInput_GemPrescale::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_GemPrescale::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_GemPrescale::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_GemPrescale::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_GemPrescale::getDescription(){
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

