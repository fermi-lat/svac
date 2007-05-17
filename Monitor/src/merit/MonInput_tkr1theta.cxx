// 
// Class for input of quantity tkr1theta for monitoring 
// 
// Created by kocian on Fri Apr 20 20:46:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_tkr1theta.h"
#include <iostream>

// User defined part 

#define NAME tkr1theta
#define OUTBRANCH "tkr1theta"
#define LEAF "tkr1theta/F"
#define INBRANCH "Tkr1Theta"
#define ACCESSOR Tkr1Theta
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Theta of track 1"
#include "../MeritEvent.h"

// End user defined part 

MonInput_tkr1theta::MonInput_tkr1theta(){
  m_name=OUTBRANCH;
}
MonInput_tkr1theta::~MonInput_tkr1theta(){
}


int MonInput_tkr1theta::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_tkr1theta::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_tkr1theta::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_tkr1theta::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_tkr1theta::getDescription(){
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

