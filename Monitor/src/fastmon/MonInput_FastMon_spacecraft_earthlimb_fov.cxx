// 
// Class for input of quantity FastMon_spacecraft_earthlimb_fov for monitoring 
// 
// Created by bregeon on Fri Jul  4 00:58:47 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_earthlimb_fov.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_earthlimb_fov
#define OUTBRANCH "FastMon_spacecraft_earthlimb_fov"
#define LEAF "FastMon_spacecraft_earthlimb_fov/D"
#define INBRANCH "spacecraft_earthlimb_fov"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the arc length of Earth limb in the LAT field of view"


// End user defined part 

MonInput_FastMon_spacecraft_earthlimb_fov::MonInput_FastMon_spacecraft_earthlimb_fov(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_earthlimb_fov::~MonInput_FastMon_spacecraft_earthlimb_fov(){
}


int MonInput_FastMon_spacecraft_earthlimb_fov::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_earthlimb_fov::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_earthlimb_fov::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_earthlimb_fov::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_earthlimb_fov::getDescription(){
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

