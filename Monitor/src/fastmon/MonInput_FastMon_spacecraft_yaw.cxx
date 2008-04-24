// 
// Class for input of quantity FastMon_spacecraft_yaw for monitoring 
// 
// Created by bregeon on Thu Apr 24 15:21:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_yaw.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_yaw
#define OUTBRANCH "FastMon_spacecraft_yaw"
#define LEAF "FastMon_spacecraft_yaw/D"
#define INBRANCH "spacecraft_yaw"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Spacecraft yaw angle"


// End user defined part 

MonInput_FastMon_spacecraft_yaw::MonInput_FastMon_spacecraft_yaw(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_yaw::~MonInput_FastMon_spacecraft_yaw(){
}


int MonInput_FastMon_spacecraft_yaw::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_yaw::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_yaw::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_yaw::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_yaw::getDescription(){
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

