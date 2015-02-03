// 
// Class for input of quantity Acd2TileCount for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:34:07 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2TileCount.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2TileCount
#define OUTBRANCH "Acd2TileCount"
#define LEAF "Acd2TileCount/i"
#define INBRANCH "Acd2TileCount"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of tiles fired"


// End user defined part 

MonInput_Acd2TileCount::MonInput_Acd2TileCount(){
  m_name=OUTBRANCH;
}
MonInput_Acd2TileCount::~MonInput_Acd2TileCount(){
}


int MonInput_Acd2TileCount::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2TileCount::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2TileCount::setValue(TObject* event) {
}
std::string MonInput_Acd2TileCount::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2TileCount::getDescription(){
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

