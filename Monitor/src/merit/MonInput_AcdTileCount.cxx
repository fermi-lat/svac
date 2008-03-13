// 
// Class for input of quantity AcdTileCount for monitoring 
// 
// Created by dpaneque on Wed Mar 12 18:57:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdTileCount.h"
#include <iostream>

// User defined part 

#define NAME AcdTileCount
#define OUTBRANCH "AcdTileCount"
#define LEAF "AcdTileCount/i"
#define INBRANCH "AcdTileCount"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of tiles fired"


// End user defined part 

MonInput_AcdTileCount::MonInput_AcdTileCount(){
  m_name=OUTBRANCH;
}
MonInput_AcdTileCount::~MonInput_AcdTileCount(){
}


int MonInput_AcdTileCount::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdTileCount::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdTileCount::setValue(TObject* event) {
}
std::string MonInput_AcdTileCount::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdTileCount::getDescription(){
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

