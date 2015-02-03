// 
// Class for input of quantity Acd2RibbonEnergy for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:37:40 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2RibbonEnergy.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2RibbonEnergy
#define OUTBRANCH "Acd2RibbonEnergy"
#define LEAF "Acd2RibbonEnergy/F"
#define INBRANCH "Acd2RibbonEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Total energy deposited in ACD Ribbons"


// End user defined part 

MonInput_Acd2RibbonEnergy::MonInput_Acd2RibbonEnergy(){
  m_name=OUTBRANCH;
}
MonInput_Acd2RibbonEnergy::~MonInput_Acd2RibbonEnergy(){
}


int MonInput_Acd2RibbonEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2RibbonEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2RibbonEnergy::setValue(TObject* event) {
}
std::string MonInput_Acd2RibbonEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2RibbonEnergy::getDescription(){
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

