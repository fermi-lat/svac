// 
// Class for input of quantity CTBBestEnergyRatio for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:13:23 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBBestEnergyRatio.h"
#include <iostream>

// User defined part 

#define NAME CTBBestEnergyRatio
#define OUTBRANCH "CTBBestEnergyRatio"
#define LEAF "CTBBestEnergyRatio/F"
#define INBRANCH "CTBBestEnergyRatio"
#define ACCESSOR vvvv
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Definition currently not available .... FIX ME !!"


// End user defined part 

MonInput_CTBBestEnergyRatio::MonInput_CTBBestEnergyRatio(){
  m_name=OUTBRANCH;
}
MonInput_CTBBestEnergyRatio::~MonInput_CTBBestEnergyRatio(){
}


int MonInput_CTBBestEnergyRatio::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBBestEnergyRatio::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBBestEnergyRatio::setValue(TObject* event) {
}
std::string MonInput_CTBBestEnergyRatio::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBBestEnergyRatio::getDescription(){
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

