// 
// Class for input of quantity FastMon_SpaceCraft_XaxisRA for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:03:16 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_SpaceCraft_XaxisRA.h"
#include <iostream>

// User defined part 

#define NAME FastMon_SpaceCraft_XaxisRA
#define OUTBRANCH "FastMon_SpaceCraft_XaxisRA"
#define LEAF "FastMon_SpaceCraft_XaxisRA/D"
#define INBRANCH "spacecraft_xra"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft x axis right ascension"


// End user defined part 

MonInput_FastMon_SpaceCraft_XaxisRA::MonInput_FastMon_SpaceCraft_XaxisRA(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_SpaceCraft_XaxisRA::~MonInput_FastMon_SpaceCraft_XaxisRA(){
}


int MonInput_FastMon_SpaceCraft_XaxisRA::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_SpaceCraft_XaxisRA::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_SpaceCraft_XaxisRA::setValue(TObject* event) {
}
std::string MonInput_FastMon_SpaceCraft_XaxisRA::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_SpaceCraft_XaxisRA::getDescription(){
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

