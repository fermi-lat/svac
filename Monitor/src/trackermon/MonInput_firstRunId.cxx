// 
// Class for input of quantity firstRunId for monitoring 
// 
// Created by dpaneque on Thu May 15 00:06:09 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_firstRunId.h"
#include <iostream>

// User defined part 

#define NAME firstRunId
#define OUTBRANCH "firstRunId"
#define LEAF "firstRunId/i"
#define INBRANCH "firstRunId"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "firstRunId"


// End user defined part 

MonInput_firstRunId::MonInput_firstRunId(){
  m_name=OUTBRANCH;
}
MonInput_firstRunId::~MonInput_firstRunId(){
}


int MonInput_firstRunId::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_firstRunId::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_firstRunId::setValue(TObject* event) {
}
std::string MonInput_firstRunId::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_firstRunId::getDescription(){
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

