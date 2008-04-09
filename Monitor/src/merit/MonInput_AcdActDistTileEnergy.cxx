// 
// Class for input of quantity AcdActDistTileEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:14:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdActDistTileEnergy.h"
#include <iostream>

// User defined part 

#define NAME AcdActDistTileEnergy
#define OUTBRANCH "AcdActDistTileEnergy"
#define LEAF "AcdActDistTileEnergy/F"
#define INBRANCH "AcdActDistTileEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "The deposited energy in the corresponding hit tile, looped over all tracks."


// End user defined part 

MonInput_AcdActDistTileEnergy::MonInput_AcdActDistTileEnergy(){
  m_name=OUTBRANCH;
}
MonInput_AcdActDistTileEnergy::~MonInput_AcdActDistTileEnergy(){
}


int MonInput_AcdActDistTileEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdActDistTileEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdActDistTileEnergy::setValue(TObject* event) {
}
std::string MonInput_AcdActDistTileEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdActDistTileEnergy::getDescription(){
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

