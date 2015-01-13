// 
// Class for input of quantity GrbYDir for monitoring 
// 
// Created by dpaneque on Thu Jul 17 21:28:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_GrbYDir.h"
#include <iostream>

// User defined part 

#define NAME GrbYDir
#define OUTBRANCH "GrbYDir"
#define LEAF "GrbYDir/F"
#define INBRANCH "GrbYDir"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Direction cosine in Y direction of the best (GRB) track"


// End user defined part 

MonInput_GrbYDir::MonInput_GrbYDir(){
  m_name=OUTBRANCH;
}
MonInput_GrbYDir::~MonInput_GrbYDir(){
}


int MonInput_GrbYDir::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_GrbYDir::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_GrbYDir::setValue(TObject* event) {
}
std::string MonInput_GrbYDir::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_GrbYDir::getDescription(){
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

