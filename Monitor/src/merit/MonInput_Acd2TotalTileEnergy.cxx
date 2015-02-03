// 
// Class for input of quantity Acd2TotalTileEnergy for monitoring 
// 
// Created by lbaldini on Tue Feb  3 14:27:00 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2TotalTileEnergy.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2TotalTileEnergy
#define OUTBRANCH "Acd2TotalTileEnergy"
#define LEAF "Acd2TotalTileEnergy/F"
#define INBRANCH "Acd2TotalTileEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Total energy in the ACD tiles"


// End user defined part 

MonInput_Acd2TotalTileEnergy::MonInput_Acd2TotalTileEnergy(){
  m_name=OUTBRANCH;
}
MonInput_Acd2TotalTileEnergy::~MonInput_Acd2TotalTileEnergy(){
}


int MonInput_Acd2TotalTileEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2TotalTileEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2TotalTileEnergy::setValue(TObject* event) {
}
std::string MonInput_Acd2TotalTileEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2TotalTileEnergy::getDescription(){
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

