// 
// Class for input of quantity lastRunId for monitoring 
// 
// Created by dpaneque on Thu May 15 00:06:53 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_lastRunId.h"
#include <iostream>

// User defined part 

#define NAME lastRunId
#define OUTBRANCH "lastRunId"
#define LEAF "lastRunId/i"
#define INBRANCH "lastRunId"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "lastRunId"


// End user defined part 

MonInput_lastRunId::MonInput_lastRunId(){
  m_name=OUTBRANCH;
}
MonInput_lastRunId::~MonInput_lastRunId(){
}


int MonInput_lastRunId::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_lastRunId::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_lastRunId::setValue(TObject* event) {
}
std::string MonInput_lastRunId::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_lastRunId::getDescription(){
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

