// 
// Class for input of quantity FastMon_spacecraft_orbit_mode for monitoring 
// 
// Created by bregeon on Mon Aug 25 10:01:09 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_orbit_mode.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_orbit_mode
#define OUTBRANCH "FastMon_spacecraft_orbit_mode"
#define LEAF "FastMon_spacecraft_orbit_mode/i"
#define INBRANCH "spacecraft_orbit_mode"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Changes of the spacecraft orbit mode"


// End user defined part 

MonInput_FastMon_spacecraft_orbit_mode::MonInput_FastMon_spacecraft_orbit_mode(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_orbit_mode::~MonInput_FastMon_spacecraft_orbit_mode(){
}


int MonInput_FastMon_spacecraft_orbit_mode::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_orbit_mode::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_orbit_mode::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_orbit_mode::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_orbit_mode::getDescription(){
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

