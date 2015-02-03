// 
// Class for input of quantity Acd2RibbonCount for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:35:09 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2RibbonCount.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2RibbonCount
#define OUTBRANCH "Acd2RibbonCount"
#define LEAF "Acd2RibbonCount/i"
#define INBRANCH "Acd2RibbonCount"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of ribbons fired"


// End user defined part 

MonInput_Acd2RibbonCount::MonInput_Acd2RibbonCount(){
  m_name=OUTBRANCH;
}
MonInput_Acd2RibbonCount::~MonInput_Acd2RibbonCount(){
}


int MonInput_Acd2RibbonCount::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2RibbonCount::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2RibbonCount::setValue(TObject* event) {
}
std::string MonInput_Acd2RibbonCount::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2RibbonCount::getDescription(){
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

