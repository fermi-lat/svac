// 
// Class for input of quantity FastMon_spacecraft_roll for monitoring 
// 
// Created by bregeon on Thu Apr 24 15:21:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_roll.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_roll
#define OUTBRANCH "FastMon_spacecraft_roll"
#define LEAF "FastMon_spacecraft_roll/D"
#define INBRANCH "spacecraft_roll"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Space craft roll angle"


// End user defined part 

MonInput_FastMon_spacecraft_roll::MonInput_FastMon_spacecraft_roll(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_roll::~MonInput_FastMon_spacecraft_roll(){
}


int MonInput_FastMon_spacecraft_roll::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_roll::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_roll::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_roll::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_roll::getDescription(){
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

