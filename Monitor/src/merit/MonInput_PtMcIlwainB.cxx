// 
// Class for input of quantity PtMcIlwainB for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:44:04 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PtMcIlwainB.h"
#include <iostream>

// User defined part 

#define NAME PtMcIlwainB
#define OUTBRANCH "PtMcIlwainB"
#define LEAF "PtMcIlwainB/F"
#define INBRANCH "PtMcIlwainB"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "PtMcIlwainB"


// End user defined part 

MonInput_PtMcIlwainB::MonInput_PtMcIlwainB(){
  m_name=OUTBRANCH;
}
MonInput_PtMcIlwainB::~MonInput_PtMcIlwainB(){
}


int MonInput_PtMcIlwainB::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PtMcIlwainB::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_PtMcIlwainB::setValue(TObject* event) {
}
std::string MonInput_PtMcIlwainB::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PtMcIlwainB::getDescription(){
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

