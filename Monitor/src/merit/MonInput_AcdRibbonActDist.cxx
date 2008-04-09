// 
// Class for input of quantity AcdRibbonActDist for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:11:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdRibbonActDist.h"
#include <iostream>

// User defined part 

#define NAME AcdRibbonActDist
#define OUTBRANCH "AcdRibbonActDist"
#define LEAF "AcdRibbonActDist/F"
#define INBRANCH "AcdRibbonActDist"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Largest active distance to any ribbon (considered as a straight line of no thickness)"


// End user defined part 

MonInput_AcdRibbonActDist::MonInput_AcdRibbonActDist(){
  m_name=OUTBRANCH;
}
MonInput_AcdRibbonActDist::~MonInput_AcdRibbonActDist(){
}


int MonInput_AcdRibbonActDist::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdRibbonActDist::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdRibbonActDist::setValue(TObject* event) {
}
std::string MonInput_AcdRibbonActDist::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdRibbonActDist::getDescription(){
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

