// 
// Class for input of quantity gltnumtowers for monitoring 
// 
// Created by kocian on Fri Apr 20 23:27:36 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_gltnumtowers.h"
#include <iostream>

// User defined part 

#define NAME gltnumtowers
#define OUTBRANCH "gltnumtowers"
#define LEAF "gltnumtowers/F"
#define INBRANCH "GltNumTowers"
#define ACCESSOR GltNumTowers
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of towers with TKR trigger (crossing)"
#include "../MeritEvent.h"

// End user defined part 

MonInput_gltnumtowers::MonInput_gltnumtowers(){
  m_name=OUTBRANCH;
}
MonInput_gltnumtowers::~MonInput_gltnumtowers(){
}


int MonInput_gltnumtowers::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_gltnumtowers::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_gltnumtowers::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_gltnumtowers::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_gltnumtowers::getDescription(){
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

