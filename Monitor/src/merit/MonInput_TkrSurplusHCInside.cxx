// 
// Class for input of quantity TkrSurplusHCInside for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:36:20 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrSurplusHCInside.h"
#include <iostream>

// User defined part 

#define NAME TkrSurplusHCInside
#define OUTBRANCH "TkrSurplusHCInside"
#define LEAF "TkrSurplusHCInside/F"
#define INBRANCH "TkrSurplusHCInside"
#define ACCESSOR vvv
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of cluster hits in the tracker."


// End user defined part 

MonInput_TkrSurplusHCInside::MonInput_TkrSurplusHCInside(){
  m_name=OUTBRANCH;
}
MonInput_TkrSurplusHCInside::~MonInput_TkrSurplusHCInside(){
}


int MonInput_TkrSurplusHCInside::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrSurplusHCInside::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrSurplusHCInside::setValue(TObject* event) {
}
std::string MonInput_TkrSurplusHCInside::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrSurplusHCInside::getDescription(){
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

