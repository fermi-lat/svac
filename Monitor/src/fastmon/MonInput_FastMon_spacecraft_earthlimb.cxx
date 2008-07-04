// 
// Class for input of quantity FastMon_spacecraft_earthlimb for monitoring 
// 
// Created by bregeon on Fri Jul  4 00:58:27 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_earthlimb.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_earthlimb
#define OUTBRANCH "FastMon_spacecraft_earthlimb"
#define LEAF "FastMon_spacecraft_earthlimb/D"
#define INBRANCH "spacecraft_earthlimb"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the angle between the LAT Z axis and the Earth limb"


// End user defined part 

MonInput_FastMon_spacecraft_earthlimb::MonInput_FastMon_spacecraft_earthlimb(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_earthlimb::~MonInput_FastMon_spacecraft_earthlimb(){
}


int MonInput_FastMon_spacecraft_earthlimb::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_earthlimb::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_earthlimb::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_earthlimb::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_earthlimb::getDescription(){
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

