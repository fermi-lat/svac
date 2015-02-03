// 
// Class for input of quantity Acd2CR1ActDistTileEnergy for monitoring 
// 
// Created by lbaldini on Tue Feb  3 14:18:07 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2CR1ActDistTileEnergy.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2CR1ActDistTileEnergy
#define OUTBRANCH "Acd2CR1ActDistTileEnergy"
#define LEAF "Acd2CR1ActDistTileEnergy/F"
#define INBRANCH "Acd2CR1ActDistTileEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Acd2CR1ActDistTileEnergy"


// End user defined part 

MonInput_Acd2CR1ActDistTileEnergy::MonInput_Acd2CR1ActDistTileEnergy(){
  m_name=OUTBRANCH;
}
MonInput_Acd2CR1ActDistTileEnergy::~MonInput_Acd2CR1ActDistTileEnergy(){
}


int MonInput_Acd2CR1ActDistTileEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2CR1ActDistTileEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2CR1ActDistTileEnergy::setValue(TObject* event) {
}
std::string MonInput_Acd2CR1ActDistTileEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2CR1ActDistTileEnergy::getDescription(){
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

