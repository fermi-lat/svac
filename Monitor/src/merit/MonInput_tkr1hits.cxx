// 
// Class for input of quantity tkr1hits for monitoring 
// 
// Created by kocian on Fri Apr 20 20:46:47 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_tkr1hits.h"
#include <iostream>

// User defined part 

#define NAME tkr1hits
#define OUTBRANCH "tkr1hits"
#define LEAF "tkr1hits/F"
#define INBRANCH "Tkr1Hits"
#define ACCESSOR Tkr1Hits
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of hits in track 1"

// End user defined part 

MonInput_tkr1hits::MonInput_tkr1hits(){
  m_name=OUTBRANCH;
}
MonInput_tkr1hits::~MonInput_tkr1hits(){
}


int MonInput_tkr1hits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_tkr1hits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_tkr1hits::setValue(TObject* event) {
}
std::string MonInput_tkr1hits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_tkr1hits::getDescription(){
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

