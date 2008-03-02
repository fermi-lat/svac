// 
// Class for input of quantity FastMon_geomagnetic_InvariantRadius for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:19:50 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_geomagnetic_InvariantRadius.h"
#include <iostream>

// User defined part 

#define NAME FastMon_geomagnetic_InvariantRadius
#define OUTBRANCH "FastMon_geomagnetic_InvariantRadius"
#define LEAF "FastMon_geomagnetic_InvariantRadius/D"
#define INBRANCH "geomagnetic_InvariantRadius"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the geomagnetic invariant radius (only valid for BB0<10)"


// End user defined part 

MonInput_FastMon_geomagnetic_InvariantRadius::MonInput_FastMon_geomagnetic_InvariantRadius(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_geomagnetic_InvariantRadius::~MonInput_FastMon_geomagnetic_InvariantRadius(){
}


int MonInput_FastMon_geomagnetic_InvariantRadius::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_geomagnetic_InvariantRadius::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_geomagnetic_InvariantRadius::setValue(TObject* event) {
}
std::string MonInput_FastMon_geomagnetic_InvariantRadius::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_geomagnetic_InvariantRadius::getDescription(){
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

