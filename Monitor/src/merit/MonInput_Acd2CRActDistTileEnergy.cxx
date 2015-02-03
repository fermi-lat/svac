// 
// Class for input of quantity Acd2CRActDistTileEnergy for monitoring 
// 
// Created by lbaldini on Tue Feb  3 14:38:41 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2CRActDistTileEnergy.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2CRActDistTileEnergy
#define OUTBRANCH "Acd2CRActDistTileEnergy"
#define LEAF "Acd2CRActDistTileEnergy/F"
#define INBRANCH "Acd2CRActDistTileEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Acd2CRActDistTileEnergy"


// End user defined part 

MonInput_Acd2CRActDistTileEnergy::MonInput_Acd2CRActDistTileEnergy(){
  m_name=OUTBRANCH;
}
MonInput_Acd2CRActDistTileEnergy::~MonInput_Acd2CRActDistTileEnergy(){
}


int MonInput_Acd2CRActDistTileEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2CRActDistTileEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2CRActDistTileEnergy::setValue(TObject* event) {
}
std::string MonInput_Acd2CRActDistTileEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2CRActDistTileEnergy::getDescription(){
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

