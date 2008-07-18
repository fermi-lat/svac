// 
// Class for input of quantity GrbZDir for monitoring 
// 
// Created by dpaneque on Thu Jul 17 21:29:13 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_GrbZDir.h"
#include <iostream>

// User defined part 

#define NAME GrbZDir
#define OUTBRANCH "GrbZDir"
#define LEAF "GrbZDir/F"
#define INBRANCH "GrbZDir"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Direction cosine in the Z direction of the best (GRB) track"


// End user defined part 

MonInput_GrbZDir::MonInput_GrbZDir(){
  m_name=OUTBRANCH;
}
MonInput_GrbZDir::~MonInput_GrbZDir(){
}


int MonInput_GrbZDir::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_GrbZDir::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_GrbZDir::setValue(TObject* event) {
}
std::string MonInput_GrbZDir::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_GrbZDir::getDescription(){
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

