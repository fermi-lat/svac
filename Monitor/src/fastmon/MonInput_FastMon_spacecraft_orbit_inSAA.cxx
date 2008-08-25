// 
// Class for input of quantity FastMon_spacecraft_orbit_inSAA for monitoring 
// 
// Created by bregeon on Mon Aug 25 10:01:56 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_orbit_inSAA.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_orbit_inSAA
#define OUTBRANCH "FastMon_spacecraft_orbit_inSAA"
#define LEAF "FastMon_spacecraft_orbit_inSAA/O"
#define INBRANCH "spacecraft_orbit_inSAA"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Changes of the spacecraft orbit in SAA flag"


// End user defined part 

MonInput_FastMon_spacecraft_orbit_inSAA::MonInput_FastMon_spacecraft_orbit_inSAA(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_orbit_inSAA::~MonInput_FastMon_spacecraft_orbit_inSAA(){
}


int MonInput_FastMon_spacecraft_orbit_inSAA::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_orbit_inSAA::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_orbit_inSAA::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_orbit_inSAA::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_orbit_inSAA::getDescription(){
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

