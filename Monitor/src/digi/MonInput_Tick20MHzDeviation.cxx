// 
// Class for input of quantity Tick20MHzDeviation for monitoring 
// 
// Created by dpaneque on Fri Aug 17 19:07:09 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Tick20MHzDeviation.h"
#include <iostream>

// User defined part 

#define NAME Tick20MHzDeviation
#define OUTBRANCH "Tick20MHzDeviation"
#define LEAF "Tick20MHzDeviation/I"
#define INBRANCH "m_metaEvent"
//#define ACCESSOR 
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of ticks between successive 1-PPS - Deviation from 20 MHz"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_Tick20MHzDeviation::MonInput_Tick20MHzDeviation(){
  m_name=OUTBRANCH;
}
MonInput_Tick20MHzDeviation::~MonInput_Tick20MHzDeviation(){
}


int MonInput_Tick20MHzDeviation::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Tick20MHzDeviation::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_Tick20MHzDeviation::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->getMetaEvent().time().current().timeHack().ticks()-de->getMetaEvent().time().previous().timeHack().ticks();

  Int_t RollOverInt = 33554432;  
  if (m_val < 0) {
    m_val += RollOverInt;
  }
  m_val = 20000000-m_val; // we only want the deviations with respect to the 20MHz ticks

}
std::string MonInput_Tick20MHzDeviation::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Tick20MHzDeviation::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
//#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

