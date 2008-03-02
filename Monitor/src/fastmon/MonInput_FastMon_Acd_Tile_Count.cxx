// 
// Class for input of quantity FastMon_Acd_Tile_Count for monitoring 
// 
// Created by bregeon on Thu Feb 28 14:08:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_Acd_Tile_Count.h"
#include <iostream>

// User defined part 

#define NAME FastMon_Acd_Tile_Count
#define OUTBRANCH "FastMon_Acd_Tile_Count"
#define LEAF "FastMon_Acd_Tile_Count/I"
#define INBRANCH "acd_tile_count"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Number of Acd tiles hit per event"


// End user defined part 

MonInput_FastMon_Acd_Tile_Count::MonInput_FastMon_Acd_Tile_Count(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_Acd_Tile_Count::~MonInput_FastMon_Acd_Tile_Count(){
}


int MonInput_FastMon_Acd_Tile_Count::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_Acd_Tile_Count::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_Acd_Tile_Count::setValue(TObject* event) {
}
std::string MonInput_FastMon_Acd_Tile_Count::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_Acd_Tile_Count::getDescription(){
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

