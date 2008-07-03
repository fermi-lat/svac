// 
// Class for input of quantity FastMon_SpaceCraft_EarthLimb for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:04:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_SpaceCraft_EarthLimb.h"
#include <iostream>

// User defined part 

#define NAME FastMon_SpaceCraft_EarthLimb
#define OUTBRANCH "FastMon_SpaceCraft_EarthLimb"
#define LEAF "FastMon_SpaceCraft_EarthLimb/D"
#define INBRANCH "spacecraft_earthlimb"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the angle between the LAT Z axis and the Earth limb"


// End user defined part 

MonInput_FastMon_SpaceCraft_EarthLimb::MonInput_FastMon_SpaceCraft_EarthLimb(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_SpaceCraft_EarthLimb::~MonInput_FastMon_SpaceCraft_EarthLimb(){
}


int MonInput_FastMon_SpaceCraft_EarthLimb::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_SpaceCraft_EarthLimb::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_SpaceCraft_EarthLimb::setValue(TObject* event) {
}
std::string MonInput_FastMon_SpaceCraft_EarthLimb::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_SpaceCraft_EarthLimb::getDescription(){
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

