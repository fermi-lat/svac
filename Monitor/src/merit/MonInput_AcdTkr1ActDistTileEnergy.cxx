// 
// Class for input of quantity AcdTkr1ActDistTileEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:32:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdTkr1ActDistTileEnergy.h"
#include <iostream>

// User defined part 

#define NAME AcdTkr1ActDistTileEnergy
#define OUTBRANCH "AcdTkr1ActDistTileEnergy"
#define LEAF "AcdTkr1ActDistTileEnergy/F"
#define INBRANCH "AcdTkr1ActDistTileEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "The deposited energy in the corresponding hit tile, looped over track 1."


// End user defined part 

MonInput_AcdTkr1ActDistTileEnergy::MonInput_AcdTkr1ActDistTileEnergy(){
  m_name=OUTBRANCH;
}
MonInput_AcdTkr1ActDistTileEnergy::~MonInput_AcdTkr1ActDistTileEnergy(){
}


int MonInput_AcdTkr1ActDistTileEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdTkr1ActDistTileEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdTkr1ActDistTileEnergy::setValue(TObject* event) {
}
std::string MonInput_AcdTkr1ActDistTileEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdTkr1ActDistTileEnergy::getDescription(){
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

