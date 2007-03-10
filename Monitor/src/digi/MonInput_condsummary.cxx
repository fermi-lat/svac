// 
// Class for input of quantity condsummary for monitoring 
// 
// Created by kocian on Fri Mar  9 22:53:38 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_condsummary.h"
#include <iostream>

// User defined part 

#define NAME condsummary
#define OUTBRANCH "condsummary"
#define LEAF "condsummary/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getConditionSummary()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_condsummary::MonInput_condsummary(){
}
MonInput_condsummary::~MonInput_condsummary(){
}


int MonInput_condsummary::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_condsummary::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_condsummary::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_condsummary::getInputSource(){
  return INPUTSOURCE;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE

