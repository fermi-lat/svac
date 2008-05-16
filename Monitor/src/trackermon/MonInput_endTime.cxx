// 
// Class for input of quantity endTime for monitoring 
// 
// Created by dpaneque on Thu May 15 05:07:35 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_endTime.h"
#include <iostream>

// User defined part 

#define NAME endTime
#define OUTBRANCH "endTime"
#define LEAF "endTime/D"
#define INBRANCH "endTime"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "Time of the last event in the run"


// End user defined part 

MonInput_endTime::MonInput_endTime(){
  m_name=OUTBRANCH;
}
MonInput_endTime::~MonInput_endTime(){
}


int MonInput_endTime::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_endTime::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_endTime::setValue(TObject* event) {
}
std::string MonInput_endTime::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_endTime::getDescription(){
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

