// 
// Class for input of quantity L1TTriggerWord5bits for monitoring 
// 
// Created by dpaneque on Fri Jul 18 19:17:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_L1TTriggerWord5bits.h"
#include <iostream>

// User defined part 

#define NAME L1TTriggerWord5bits
#define OUTBRANCH "L1TTriggerWord5bits"
#define LEAF "L1TTriggerWord5bits[5]/O"
#define INBRANCH "m_levelOneTrigger"
#define ACCESSOR bblblblb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [5] reporting the first 5 bits of the L1T Trigger word"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_L1TTriggerWord5bits::MonInput_L1TTriggerWord5bits(){
  m_name=OUTBRANCH;
}
MonInput_L1TTriggerWord5bits::~MonInput_L1TTriggerWord5bits(){
}


int MonInput_L1TTriggerWord5bits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_L1TTriggerWord5bits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_L1TTriggerWord5bits::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  

  for(UShort_t i = 0; i < 5; i++)
    m_val[i]=0;

  // Get condsummary word and check if there is tkr trigger
  UInt_t word = de->getL1T().getTriggerWord(); 

  // fill vector with first 5 bits
  for(int i = 0; i < 5; ++i) {
    if( (word >> i) & 1 ) m_val[i]=1;
  }

}
std::string MonInput_L1TTriggerWord5bits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_L1TTriggerWord5bits::getDescription(){
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

