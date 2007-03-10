// 
// Class for input of quantity calxtalene for monitoring 
// 
// Created by kocian on Fri Mar  9 20:38:36 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_calxtalene.h"
#include <iostream>

// User defined part 

#define NAME calxtalene
#define OUTBRANCH "calxtalene"
#define LEAF "calxtalene[16][8][12][2]/F"
#define INBRANCH "CalXtalEne"
#define ACCESSOR CalXtalEne
#define MONSOURCE SvacEvent
#define INPUTSOURCE "SvacEvent"
#include "../SvacEvent.h"

// End user defined part 

MonInput_calxtalene::MonInput_calxtalene(){
}
MonInput_calxtalene::~MonInput_calxtalene(){
}


int MonInput_calxtalene::setOutputBranch(TTree* tree) {
  m_tree=tree;
  m_firstevent=true;
  return 0;
}
void MonInput_calxtalene::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_calxtalene::setValue(TObject* event) {
  if (!m_firstevent)return;
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  assert(m_tree);
  TBranch* bErr= m_tree->Branch(OUTBRANCH,de->ACCESSOR,LEAF);
  m_firstevent=false;
}
std::string MonInput_calxtalene::getInputSource(){
  return INPUTSOURCE;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE

