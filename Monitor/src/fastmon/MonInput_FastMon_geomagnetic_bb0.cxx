// 
// Class for input of quantity FastMon_geomagnetic_bb0 for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:40:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_geomagnetic_bb0.h"
#include <iostream>

// User defined part 

#define NAME FastMon_geomagnetic_bb0
#define OUTBRANCH "FastMon_geomagnetic_bb0"
#define LEAF "FastMon_geomagnetic_bb0/D"
#define INBRANCH "geomagnetic_bb0"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of BAbs divided by BEquator"


// End user defined part 

MonInput_FastMon_geomagnetic_bb0::MonInput_FastMon_geomagnetic_bb0(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_geomagnetic_bb0::~MonInput_FastMon_geomagnetic_bb0(){
}


int MonInput_FastMon_geomagnetic_bb0::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_geomagnetic_bb0::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_geomagnetic_bb0::setValue(TObject* event) {
}
std::string MonInput_FastMon_geomagnetic_bb0::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_geomagnetic_bb0::getDescription(){
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

