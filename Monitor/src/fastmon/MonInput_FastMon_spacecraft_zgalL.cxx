// 
// Class for input of quantity FastMon_spacecraft_zgalL for monitoring 
// 
// Created by bregeon on Sun Jul 13 03:20:52 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_zgalL.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_zgalL
#define OUTBRANCH "FastMon_spacecraft_zgalL"
#define LEAF "FastMon_spacecraft_zgalL/D"
#define INBRANCH "spacecraft_zgalL"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft z axis galactic L coordinate"


// End user defined part 

MonInput_FastMon_spacecraft_zgalL::MonInput_FastMon_spacecraft_zgalL(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_zgalL::~MonInput_FastMon_spacecraft_zgalL(){
}


int MonInput_FastMon_spacecraft_zgalL::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_zgalL::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_zgalL::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_zgalL::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_zgalL::getDescription(){
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

