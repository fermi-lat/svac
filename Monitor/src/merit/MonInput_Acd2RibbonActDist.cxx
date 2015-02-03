// 
// Class for input of quantity Acd2RibbonActDist for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:36:48 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2RibbonActDist.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2RibbonActDist
#define OUTBRANCH "Acd2RibbonActDist"
#define LEAF "Acd2RibbonActDist/F"
#define INBRANCH "Acd2RibbonActDist"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Largest active distance to any ribbon (considered as a straight line of no thickness)"


// End user defined part 

MonInput_Acd2RibbonActDist::MonInput_Acd2RibbonActDist(){
  m_name=OUTBRANCH;
}
MonInput_Acd2RibbonActDist::~MonInput_Acd2RibbonActDist(){
}


int MonInput_Acd2RibbonActDist::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2RibbonActDist::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2RibbonActDist::setValue(TObject* event) {
}
std::string MonInput_Acd2RibbonActDist::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2RibbonActDist::getDescription(){
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

