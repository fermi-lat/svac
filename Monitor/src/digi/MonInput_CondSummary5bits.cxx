// 
// Class for input of quantity CondSummary5bits for monitoring 
// 
// Created by dpaneque on Fri Jul 18 19:14:49 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CondSummary5bits.h"
#include <iostream>

// User defined part 

#define NAME CondSummary5bits
#define OUTBRANCH "CondSummary5bits"
#define LEAF "CondSummary5bits[5]/O"
#define INBRANCH "m_gem"
#define ACCESSOR bbb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [5] containing the 5 first bits of the condsummary word for this event"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CondSummary5bits::MonInput_CondSummary5bits(){
  m_name=OUTBRANCH;
}
MonInput_CondSummary5bits::~MonInput_CondSummary5bits(){
}


int MonInput_CondSummary5bits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CondSummary5bits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CondSummary5bits::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
 
  for(UShort_t i = 0; i < 5; i++)
    m_val[i]=0;

  // Get condsummary word and check if there is tkr trigger
  int cond = de->getGem().getConditionSummary();

  // fill vector with first 5 bits
  for(int i = 0; i < 5; ++i) {
    if( (cond >> i) & 1 ) m_val[i]=1;
  }

}
std::string MonInput_CondSummary5bits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CondSummary5bits::getDescription(){
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

