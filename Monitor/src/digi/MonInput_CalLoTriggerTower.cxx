// 
// Class for input of quantity CalLoTriggerTower for monitoring 
// 
// Created by kocian on Fri Apr 20 20:12:05 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalLoTriggerTower.h"
#include <iostream>

// User defined part 

#define NAME CalLoTriggerTower
#define OUTBRANCH "CalLoTriggerTower"
#define LEAF "CalLoTriggerTower[16]/O"
#define INBRANCH "m_gem"
#define ACCESSOR bla
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "GEM CAL low trigger vector"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CalLoTriggerTower::MonInput_CalLoTriggerTower(){
  m_name=OUTBRANCH;
}
MonInput_CalLoTriggerTower::~MonInput_CalLoTriggerTower(){
}


int MonInput_CalLoTriggerTower::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalLoTriggerTower::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CalLoTriggerTower::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  for(UShort_t i = 0; i < 16; i++)
    m_val[i]=0;

  // Get condsummary word and check if there is tkr trigger
  int cond = de->getGem().getConditionSummary();
  if(cond&4)
    {// 3 in a row TKR trigger; update vector with triggers per tower
      int leVector = de->getGem().getCalLeVector();
      for(int i = 0; i < 16; ++i) {
	if( (leVector >> i) & 1 ) ++m_val[i];
      }
    }
  
}
std::string MonInput_CalLoTriggerTower::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalLoTriggerTower::getDescription(){
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

