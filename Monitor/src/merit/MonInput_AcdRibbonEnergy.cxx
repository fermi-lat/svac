// 
// Class for input of quantity AcdRibbonEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:13:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdRibbonEnergy.h"
#include <iostream>

// User defined part 

#define NAME AcdRibbonEnergy
#define OUTBRANCH "AcdRibbonEnergy"
#define LEAF "AcdRibbonEnergy/F"
#define INBRANCH "AcdRibbonEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Total energy deposited in ACD Ribbons"


// End user defined part 

MonInput_AcdRibbonEnergy::MonInput_AcdRibbonEnergy(){
  m_name=OUTBRANCH;
}
MonInput_AcdRibbonEnergy::~MonInput_AcdRibbonEnergy(){
}


int MonInput_AcdRibbonEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdRibbonEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdRibbonEnergy::setValue(TObject* event) {
}
std::string MonInput_AcdRibbonEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdRibbonEnergy::getDescription(){
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

