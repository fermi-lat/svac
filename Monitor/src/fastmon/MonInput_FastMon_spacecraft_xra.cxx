// 
// Class for input of quantity FastMon_spacecraft_xra for monitoring 
// 
// Created by bregeon on Fri Jul  4 00:57:25 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_xra.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_xra
#define OUTBRANCH "FastMon_spacecraft_xra"
#define LEAF "FastMon_spacecraft_xra/D"
#define INBRANCH "spacecraft_xra"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft x axis right ascension"


// End user defined part 

MonInput_FastMon_spacecraft_xra::MonInput_FastMon_spacecraft_xra(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_xra::~MonInput_FastMon_spacecraft_xra(){
}


int MonInput_FastMon_spacecraft_xra::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_xra::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_xra::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_xra::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_xra::getDescription(){
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

