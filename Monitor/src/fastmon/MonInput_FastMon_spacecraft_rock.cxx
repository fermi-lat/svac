// 
// Class for input of quantity FastMon_spacecraft_rock for monitoring 
// 
// Created by bregeon on Fri Jul  4 00:56:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_rock.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_rock
#define OUTBRANCH "FastMon_spacecraft_rock"
#define LEAF "FastMon_spacecraft_rock/D"
#define INBRANCH "spacecraft_rock"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft rock angle"


// End user defined part 

MonInput_FastMon_spacecraft_rock::MonInput_FastMon_spacecraft_rock(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_rock::~MonInput_FastMon_spacecraft_rock(){
}


int MonInput_FastMon_spacecraft_rock::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_rock::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_rock::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_rock::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_rock::getDescription(){
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

