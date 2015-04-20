// 
// Class for input of quantity Acd2TileActDistEnergy for monitoring 
// 
// Created by maldera on Mon Apr 20 12:13:49 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2TileActDistEnergy.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2TileActDistEnergy
#define OUTBRANCH "Acd2TileActDistEnergy"
#define LEAF "Acd2TileActDistEnergy/F"
#define INBRANCH "Acd2TileActDistEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Acd2TileActDistEnergy"


// End user defined part 

MonInput_Acd2TileActDistEnergy::MonInput_Acd2TileActDistEnergy(){
  m_name=OUTBRANCH;
}
MonInput_Acd2TileActDistEnergy::~MonInput_Acd2TileActDistEnergy(){
}


int MonInput_Acd2TileActDistEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2TileActDistEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2TileActDistEnergy::setValue(TObject* event) {
}
std::string MonInput_Acd2TileActDistEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2TileActDistEnergy::getDescription(){
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

