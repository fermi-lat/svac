// 
// Class for input of quantity FastMon_spacecraft_zdec for monitoring 
// 
// Created by bregeon on Thu Apr 24 15:01:17 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_zdec.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_zdec
#define OUTBRANCH "FastMon_spacecraft_zdec"
#define LEAF "FastMon_spacecraft_zdec/D"
#define INBRANCH "spacecraft_zdec"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Space craft z axis declination"


// End user defined part 

MonInput_FastMon_spacecraft_zdec::MonInput_FastMon_spacecraft_zdec(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_zdec::~MonInput_FastMon_spacecraft_zdec(){
}


int MonInput_FastMon_spacecraft_zdec::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_zdec::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_zdec::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_zdec::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_zdec::getDescription(){
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

