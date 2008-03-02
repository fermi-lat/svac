// 
// Class for input of quantity FastMon_spacecraft_latitude for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:28:10 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_latitude.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_latitude
#define OUTBRANCH "FastMon_spacecraft_latitude"
#define LEAF "FastMon_spacecraft_latitude/D"
#define INBRANCH "spacecraft_latitude"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the space craft latitude"


// End user defined part 

MonInput_FastMon_spacecraft_latitude::MonInput_FastMon_spacecraft_latitude(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_latitude::~MonInput_FastMon_spacecraft_latitude(){
}


int MonInput_FastMon_spacecraft_latitude::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_latitude::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_latitude::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_latitude::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_latitude::getDescription(){
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

