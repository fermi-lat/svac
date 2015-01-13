// 
// Class for input of quantity PtMcIlwainL for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:44:28 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PtMcIlwainL.h"
#include <iostream>

// User defined part 

#define NAME PtMcIlwainL
#define OUTBRANCH "PtMcIlwainL"
#define LEAF "PtMcIlwainL/F"
#define INBRANCH "PtMcIlwainL"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "PtMcIlwainL"


// End user defined part 

MonInput_PtMcIlwainL::MonInput_PtMcIlwainL(){
  m_name=OUTBRANCH;
}
MonInput_PtMcIlwainL::~MonInput_PtMcIlwainL(){
}


int MonInput_PtMcIlwainL::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PtMcIlwainL::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_PtMcIlwainL::setValue(TObject* event) {
}
std::string MonInput_PtMcIlwainL::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PtMcIlwainL::getDescription(){
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

