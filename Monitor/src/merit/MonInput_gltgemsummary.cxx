// 
// Class for input of quantity gltgemsummary for monitoring 
// 
// Created by kocian on Fri Apr 20 22:06:31 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_gltgemsummary.h"
#include <iostream>

// User defined part 

#define NAME gltgemsummary
#define OUTBRANCH "gltgemsummary"
#define LEAF "gltgemsummary/F"
#define INBRANCH "GltGemSummary"
#define ACCESSOR GltGemSummary
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Glt Gem Summary from Merit"

// End user defined part 

MonInput_gltgemsummary::MonInput_gltgemsummary(){
  m_name=OUTBRANCH;
}
MonInput_gltgemsummary::~MonInput_gltgemsummary(){
}


int MonInput_gltgemsummary::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_gltgemsummary::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_gltgemsummary::setValue(TObject* event) {
}
std::string MonInput_gltgemsummary::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_gltgemsummary::getDescription(){
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

