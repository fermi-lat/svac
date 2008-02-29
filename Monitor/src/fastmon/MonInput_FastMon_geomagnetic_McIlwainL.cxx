// 
// Class for input of quantity FastMon_geomagnetic_McIlwainL for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:41:53 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_geomagnetic_McIlwainL.h"
#include <iostream>

// User defined part 

#define NAME FastMon_geomagnetic_McIlwainL
#define OUTBRANCH "FastMon_geomagnetic_McIlwainL"
#define LEAF "geomagnetic_McIlwainL/D"
#define INBRANCH "geomagnetic_McIlwainL"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the McIlwain L parameter"


// End user defined part 

MonInput_FastMon_geomagnetic_McIlwainL::MonInput_FastMon_geomagnetic_McIlwainL(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_geomagnetic_McIlwainL::~MonInput_FastMon_geomagnetic_McIlwainL(){
}


int MonInput_FastMon_geomagnetic_McIlwainL::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_geomagnetic_McIlwainL::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_geomagnetic_McIlwainL::setValue(TObject* event) {
}
std::string MonInput_FastMon_geomagnetic_McIlwainL::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_geomagnetic_McIlwainL::getDescription(){
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

