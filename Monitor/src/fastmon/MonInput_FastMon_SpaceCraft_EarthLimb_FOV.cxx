// 
// Class for input of quantity FastMon_SpaceCraft_EarthLimb_FOV for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:04:46 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_SpaceCraft_EarthLimb_FOV.h"
#include <iostream>

// User defined part 

#define NAME FastMon_SpaceCraft_EarthLimb_FOV
#define OUTBRANCH "FastMon_SpaceCraft_EarthLimb_FOV"
#define LEAF "FastMon_SpaceCraft_EarthLimb_FOV/D"
#define INBRANCH "spacecraft_earthlimb_fov"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the arc length of Earth limb in the LAT field of view"


// End user defined part 

MonInput_FastMon_SpaceCraft_EarthLimb_FOV::MonInput_FastMon_SpaceCraft_EarthLimb_FOV(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_SpaceCraft_EarthLimb_FOV::~MonInput_FastMon_SpaceCraft_EarthLimb_FOV(){
}


int MonInput_FastMon_SpaceCraft_EarthLimb_FOV::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_SpaceCraft_EarthLimb_FOV::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_SpaceCraft_EarthLimb_FOV::setValue(TObject* event) {
}
std::string MonInput_FastMon_SpaceCraft_EarthLimb_FOV::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_SpaceCraft_EarthLimb_FOV::getDescription(){
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

