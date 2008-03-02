// 
// Class for input of quantity FastMon_geomagnetic_InvariantLambda for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:08:45 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_geomagnetic_InvariantLambda.h"
#include <iostream>

// User defined part 

#define NAME FastMon_geomagnetic_InvariantLambda
#define OUTBRANCH "FastMon_geomagnetic_InvariantLambda"
#define LEAF "FastMon_geomagnetic_InvariantLambda/D"
#define INBRANCH "geomagnetic_InvariantLambda"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Geomagnetic Invariant Lambda (only valid for BB0<10)"


// End user defined part 

MonInput_FastMon_geomagnetic_InvariantLambda::MonInput_FastMon_geomagnetic_InvariantLambda(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_geomagnetic_InvariantLambda::~MonInput_FastMon_geomagnetic_InvariantLambda(){
}


int MonInput_FastMon_geomagnetic_InvariantLambda::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_geomagnetic_InvariantLambda::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_geomagnetic_InvariantLambda::setValue(TObject* event) {
}
std::string MonInput_FastMon_geomagnetic_InvariantLambda::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_geomagnetic_InvariantLambda::getDescription(){
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

