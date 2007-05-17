// 
// Class for input of quantity glttower for monitoring 
// 
// Created by kocian on Fri Apr 20 23:26:52 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_glttower.h"
#include <iostream>

// User defined part 

#define NAME glttower
#define OUTBRANCH "glttower"
#define LEAF "glttower/F"
#define INBRANCH "GltTower"
#define ACCESSOR GltTower
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Id of tower that triggered for TKR; if more than one, choose the tower with the highest triggered layer (null value: -1)"
#include "../MeritEvent.h"

// End user defined part 

MonInput_glttower::MonInput_glttower(){
  m_name=OUTBRANCH;
}
MonInput_glttower::~MonInput_glttower(){
}


int MonInput_glttower::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_glttower::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_glttower::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_glttower::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_glttower::getDescription(){
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

