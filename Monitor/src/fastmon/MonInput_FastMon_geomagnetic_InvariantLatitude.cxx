// 
// Class for input of quantity FastMon_geomagnetic_InvariantLatitude for monitoring 
// 
// Created by dpaneque on Tue Feb 26 20:48:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_geomagnetic_InvariantLatitude.h"
#include <iostream>

// User defined part 

#define NAME FastMon_geomagnetic_InvariantLatitude
#define OUTBRANCH "FastMon_geomagnetic_InvariantLatitude"
#define LEAF "FastMon_geomagnetic_InvariantLatitude/D"
#define INBRANCH "geomagnetic_InvariantLatitude"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Geomagnetic invariant latitude"


// End user defined part 

MonInput_FastMon_geomagnetic_InvariantLatitude::MonInput_FastMon_geomagnetic_InvariantLatitude(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_geomagnetic_InvariantLatitude::~MonInput_FastMon_geomagnetic_InvariantLatitude(){
}


int MonInput_FastMon_geomagnetic_InvariantLatitude::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_geomagnetic_InvariantLatitude::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_geomagnetic_InvariantLatitude::setValue(TObject* event) {
}
std::string MonInput_FastMon_geomagnetic_InvariantLatitude::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_geomagnetic_InvariantLatitude::getDescription(){
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

