// 
// Class for input of quantity CTBBestZDir for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:06:01 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBBestZDir.h"
#include <iostream>

// User defined part 

#define NAME CTBBestZDir
#define OUTBRANCH "CTBBestZDir"
#define LEAF "CTBBestZDir/F"
#define INBRANCH "CTBBestZDir"
#define ACCESSOR 
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Best direction in the Z axis, chosen from vertex and track-1 Solutions."


// End user defined part 

MonInput_CTBBestZDir::MonInput_CTBBestZDir(){
  m_name=OUTBRANCH;
}
MonInput_CTBBestZDir::~MonInput_CTBBestZDir(){
}


int MonInput_CTBBestZDir::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBBestZDir::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBBestZDir::setValue(TObject* event) {
}
std::string MonInput_CTBBestZDir::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBBestZDir::getDescription(){
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

