// 
// Class for input of quantity TriggerEngine for monitoring 
// 
// Created by dpaneque on Mon Oct  8 20:00:57 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TriggerEngine.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME TriggerEngine
#define OUTBRANCH "TriggerEngine"
#define LEAF "TriggerEngine[16]/s"
#define INBRANCH "m_levelOneTrigger"
#define ACCESSOR getL1T().getGemEngine()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "DigiEvent->getL1T().getGemEngine()"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_TriggerEngine::MonInput_TriggerEngine(){
  m_name=OUTBRANCH;
}
MonInput_TriggerEngine::~MonInput_TriggerEngine(){
}


int MonInput_TriggerEngine::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TriggerEngine::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_TriggerEngine::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  for(UShort_t i = 0; i < 16; i++)
    m_val[i] = 0;
  
  Int_t engine = de->getL1T().getGemEngine();
  
  if(engine < 0 || engine > 16){
    std::cout << " MonInput_TriggerEngine::setValue:ERROR" << std::endl
	      << "Problem with the value of engine " << std::endl
	      << "de->getL1T().getGemEngine() = " << engine << std::endl;
    assert(0);
  }
  
  m_val[engine] = 1;
}
std::string MonInput_TriggerEngine::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TriggerEngine::getDescription(){
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

