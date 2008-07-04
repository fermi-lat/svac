// 
// Class for input of quantity FastMon_spacecraft_xdec for monitoring 
// 
// Created by bregeon on Fri Jul  4 00:57:53 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_xdec.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_xdec
#define OUTBRANCH "FastMon_spacecraft_xdec"
#define LEAF "FastMon_spacecraft_xdec/D"
#define INBRANCH "spacecraft_xdec"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft x axis declination"


// End user defined part 

MonInput_FastMon_spacecraft_xdec::MonInput_FastMon_spacecraft_xdec(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_xdec::~MonInput_FastMon_spacecraft_xdec(){
}


int MonInput_FastMon_spacecraft_xdec::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_xdec::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_xdec::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_xdec::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_xdec::getDescription(){
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

