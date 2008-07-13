// 
// Class for input of quantity FastMon_spacecraft_zgalB for monitoring 
// 
// Created by bregeon on Sun Jul 13 03:21:35 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_zgalB.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_zgalB
#define OUTBRANCH "FastMon_spacecraft_zgalB"
#define LEAF "FastMon_spacecraft_zgalB/D"
#define INBRANCH "spacecraft_zgalB"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft z axis galactic B coordinate"


// End user defined part 

MonInput_FastMon_spacecraft_zgalB::MonInput_FastMon_spacecraft_zgalB(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_zgalB::~MonInput_FastMon_spacecraft_zgalB(){
}


int MonInput_FastMon_spacecraft_zgalB::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_zgalB::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_zgalB::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_zgalB::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_zgalB::getDescription(){
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

