// 
// Class for input of quantity CalEnergyRaw for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:37:58 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalEnergyRaw.h"
#include <iostream>

// User defined part 

#define NAME CalEnergyRaw
#define OUTBRANCH "CalEnergyRaw"
#define LEAF "CalEnergyRaw/F"
#define INBRANCH "CalEnergyRaw"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Measured energy in the calorimeter. No corrections applied."


// End user defined part 

MonInput_CalEnergyRaw::MonInput_CalEnergyRaw(){
  m_name=OUTBRANCH;
}
MonInput_CalEnergyRaw::~MonInput_CalEnergyRaw(){
}


int MonInput_CalEnergyRaw::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalEnergyRaw::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalEnergyRaw::setValue(TObject* event) {
}
std::string MonInput_CalEnergyRaw::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalEnergyRaw::getDescription(){
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

