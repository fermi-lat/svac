// 
// Class for input of quantity AcdRibbonCount for monitoring 
// 
// Created by dpaneque on Wed Mar 12 18:57:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdRibbonCount.h"
#include <iostream>

// User defined part 

#define NAME AcdRibbonCount
#define OUTBRANCH "AcdRibbonCount"
#define LEAF "AcdRibbonCount/i"
#define INBRANCH "AcdRibbonCount"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of ribbons fired"


// End user defined part 

MonInput_AcdRibbonCount::MonInput_AcdRibbonCount(){
  m_name=OUTBRANCH;
}
MonInput_AcdRibbonCount::~MonInput_AcdRibbonCount(){
}


int MonInput_AcdRibbonCount::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdRibbonCount::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdRibbonCount::setValue(TObject* event) {
}
std::string MonInput_AcdRibbonCount::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdRibbonCount::getDescription(){
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

