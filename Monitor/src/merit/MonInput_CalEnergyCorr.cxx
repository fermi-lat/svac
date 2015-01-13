// 
// Class for input of quantity CalEnergyCorr for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:38:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalEnergyCorr.h"
#include <iostream>

// User defined part 

#define NAME CalEnergyCorr
#define OUTBRANCH "CalEnergyCorr"
#define LEAF "CalEnergyCorr/F"
#define INBRANCH "CalEnergyCorr"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Measured energy in the calorimeter after applying corrections."


// End user defined part 

MonInput_CalEnergyCorr::MonInput_CalEnergyCorr(){
  m_name=OUTBRANCH;
}
MonInput_CalEnergyCorr::~MonInput_CalEnergyCorr(){
}


int MonInput_CalEnergyCorr::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalEnergyCorr::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalEnergyCorr::setValue(TObject* event) {
}
std::string MonInput_CalEnergyCorr::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalEnergyCorr::getDescription(){
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

