// 
// Class for input of quantity GrbXDir for monitoring 
// 
// Created by dpaneque on Thu Jul 17 21:27:49 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_GrbXDir.h"
#include <iostream>

// User defined part 

#define NAME GrbXDir
#define OUTBRANCH "GrbXDir"
#define LEAF "GrbXDir/F"
#define INBRANCH "GrbXDir"
#define ACCESSOR NotAplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Direction cosines of best (GRB) track"


// End user defined part 

MonInput_GrbXDir::MonInput_GrbXDir(){
  m_name=OUTBRANCH;
}
MonInput_GrbXDir::~MonInput_GrbXDir(){
}


int MonInput_GrbXDir::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_GrbXDir::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_GrbXDir::setValue(TObject* event) {
}
std::string MonInput_GrbXDir::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_GrbXDir::getDescription(){
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

