// 
// Class for input of quantity Acd2Tkr1TileActDist for monitoring 
// 
// Created by maldera on Mon Apr 20 13:15:04 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2Tkr1TileActDist.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2Tkr1TileActDist
#define OUTBRANCH "Acd2Tkr1TileActDist"
#define LEAF "Acd2Tkr1TileActDist/F"
#define INBRANCH "Acd2Tkr1TileActDist"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Acd2Tkr1TileActDist"


// End user defined part 

MonInput_Acd2Tkr1TileActDist::MonInput_Acd2Tkr1TileActDist(){
  m_name=OUTBRANCH;
}
MonInput_Acd2Tkr1TileActDist::~MonInput_Acd2Tkr1TileActDist(){
}


int MonInput_Acd2Tkr1TileActDist::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2Tkr1TileActDist::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2Tkr1TileActDist::setValue(TObject* event) {
}
std::string MonInput_Acd2Tkr1TileActDist::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2Tkr1TileActDist::getDescription(){
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

