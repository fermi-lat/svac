// 
// Class for input of quantity evtelapsedtime for monitoring 
// 
// Created by kocian on Fri Apr 20 23:38:22 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_evtelapsedtime.h"
#include <iostream>

// User defined part 

#define NAME evtelapsedtime
#define OUTBRANCH "evtelapsedtime"
#define LEAF "evtelapsedtime/F"
#define INBRANCH "EvtElapsedTime"
#define ACCESSOR EvtElapsedTime
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Elapsed time in seconds since t0"

// End user defined part 

MonInput_evtelapsedtime::MonInput_evtelapsedtime(){
  m_name=OUTBRANCH;
}
MonInput_evtelapsedtime::~MonInput_evtelapsedtime(){
}


int MonInput_evtelapsedtime::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_evtelapsedtime::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_evtelapsedtime::setValue(TObject* event) {
}
std::string MonInput_evtelapsedtime::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_evtelapsedtime::getDescription(){
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

