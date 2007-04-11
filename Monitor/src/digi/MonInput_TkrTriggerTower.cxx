// 
// Class for input of quantity TkrTriggerTower for monitoring 
// 
// Created by dpaneque on Fri Apr  6 01:40:01 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrTriggerTower.h"
#include <iostream>

// User defined part 

#define NAME TkrTriggerTower
#define OUTBRANCH "TkrTriggerTower"
#define LEAF "TkrTriggerTower[16]/O"
#define INBRANCH "m_gem"
//#define ACCESSOR Capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_TkrTriggerTower::MonInput_TkrTriggerTower(){
}
MonInput_TkrTriggerTower::~MonInput_TkrTriggerTower(){
}


int MonInput_TkrTriggerTower::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrTriggerTower::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_TkrTriggerTower::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  for(UShort_t i = 0; i < 16; i++)
    m_val[i]=0;

  // Get condsummary word and check if there is tkr trigger
  int cond = de->getGem().getConditionSummary();
  if(cond&2)
    {// 3 in a row TKR trigger; update vector with triggers per tower
      int tkrVector = de->getGem().getTkrVector();
      for(int i = 0; i < 16; ++i) {
      if( (tkrVector >> i) & 1 ) ++m_val[i];
      }
    }
}
std::string MonInput_TkrTriggerTower::getInputSource(){
  return INPUTSOURCE;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
//#undef ACCESSOR
#undef MONSOURCE

