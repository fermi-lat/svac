// 
// Class for input of quantity FastMon_SpaceCraft_RockAngle for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:02:47 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_SpaceCraft_RockAngle.h"
#include <iostream>

// User defined part 

#define NAME FastMon_SpaceCraft_RockAngle
#define OUTBRANCH "FastMon_SpaceCraft_RockAngle"
#define LEAF "FastMon_SpaceCraft_RockAngle/D"
#define INBRANCH "spacecraft_rock"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft rock angle"


// End user defined part 

MonInput_FastMon_SpaceCraft_RockAngle::MonInput_FastMon_SpaceCraft_RockAngle(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_SpaceCraft_RockAngle::~MonInput_FastMon_SpaceCraft_RockAngle(){
}


int MonInput_FastMon_SpaceCraft_RockAngle::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_SpaceCraft_RockAngle::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_SpaceCraft_RockAngle::setValue(TObject* event) {
}
std::string MonInput_FastMon_SpaceCraft_RockAngle::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_SpaceCraft_RockAngle::getDescription(){
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

