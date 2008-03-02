// 
// Class for input of quantity FastMon_spacecraft_altitude for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:34:52 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_altitude.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_altitude
#define OUTBRANCH "FastMon_spacecraft_altitude"
#define LEAF "FastMon_spacecraft_altitude/D"
#define INBRANCH "spacecraft_altitude"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the space craft altitude with respect to the earth surface (km)"


// End user defined part 

MonInput_FastMon_spacecraft_altitude::MonInput_FastMon_spacecraft_altitude(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_altitude::~MonInput_FastMon_spacecraft_altitude(){
}


int MonInput_FastMon_spacecraft_altitude::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_altitude::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_altitude::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_altitude::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_altitude::getDescription(){
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

