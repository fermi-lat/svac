// 
// Class for input of quantity Acd2Tkr1TileActDistEnergy for monitoring 
// 
// Created by maldera on Mon Apr 20 12:50:31 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2Tkr1TileActDistEnergy.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2Tkr1TileActDistEnergy
#define OUTBRANCH "Acd2Tkr1TileActDistEnergy"
#define LEAF "Acd2Tkr1TileActDistEnergy/F"
#define INBRANCH "Acd2Tkr1TileActDistEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Acd2Tkr1TileActDistEnergy"


// End user defined part 

MonInput_Acd2Tkr1TileActDistEnergy::MonInput_Acd2Tkr1TileActDistEnergy(){
  m_name=OUTBRANCH;
}
MonInput_Acd2Tkr1TileActDistEnergy::~MonInput_Acd2Tkr1TileActDistEnergy(){
}


int MonInput_Acd2Tkr1TileActDistEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2Tkr1TileActDistEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2Tkr1TileActDistEnergy::setValue(TObject* event) {
}
std::string MonInput_Acd2Tkr1TileActDistEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2Tkr1TileActDistEnergy::getDescription(){
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

