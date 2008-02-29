// 
// Class for input of quantity FastMon_geomagnetic_cutoff for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:38:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_geomagnetic_cutoff.h"
#include <iostream>

// User defined part 

#define NAME FastMon_geomagnetic_cutoff
#define OUTBRANCH "FastMon_geomagnetic_cutoff"
#define LEAF "geomagnetic_cutoff/D"
#define INBRANCH "geomagnetic_cutoff"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Rigidity cutoff in GeV from approximation DipoleMoment/(McIlwain L)**2 "


// End user defined part 

MonInput_FastMon_geomagnetic_cutoff::MonInput_FastMon_geomagnetic_cutoff(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_geomagnetic_cutoff::~MonInput_FastMon_geomagnetic_cutoff(){
}


int MonInput_FastMon_geomagnetic_cutoff::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_geomagnetic_cutoff::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_geomagnetic_cutoff::setValue(TObject* event) {
}
std::string MonInput_FastMon_geomagnetic_cutoff::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_geomagnetic_cutoff::getDescription(){
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

