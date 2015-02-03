// 
// Class for input of quantity Acd2CR1ActiveDist for monitoring 
// 
// Created by lbaldini on Tue Feb  3 14:17:43 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2CR1ActiveDist.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2CR1ActiveDist
#define OUTBRANCH "Acd2CR1ActiveDist"
#define LEAF "Acd2CR1ActiveDist/F"
#define INBRANCH "Acd2CR1ActiveDist"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Acd2CR1ActiveDist"


// End user defined part 

MonInput_Acd2CR1ActiveDist::MonInput_Acd2CR1ActiveDist(){
  m_name=OUTBRANCH;
}
MonInput_Acd2CR1ActiveDist::~MonInput_Acd2CR1ActiveDist(){
}


int MonInput_Acd2CR1ActiveDist::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2CR1ActiveDist::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2CR1ActiveDist::setValue(TObject* event) {
}
std::string MonInput_Acd2CR1ActiveDist::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2CR1ActiveDist::getDescription(){
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

