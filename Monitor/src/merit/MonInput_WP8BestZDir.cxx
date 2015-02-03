// 
// Class for input of quantity WP8BestZDir for monitoring 
// 
// Created by lbaldini on Tue Feb  3 15:16:41 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_WP8BestZDir.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME WP8BestZDir
#define OUTBRANCH "WP8BestZDir"
#define LEAF "WP8BestZDir/D"
#define INBRANCH "WP8BestZDir"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Our best ZDir estimate"


// End user defined part 

MonInput_WP8BestZDir::MonInput_WP8BestZDir(){
  m_name=OUTBRANCH;
}
MonInput_WP8BestZDir::~MonInput_WP8BestZDir(){
}


int MonInput_WP8BestZDir::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_WP8BestZDir::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_WP8BestZDir::setValue(TObject* event) {
}
std::string MonInput_WP8BestZDir::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_WP8BestZDir::getDescription(){
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

