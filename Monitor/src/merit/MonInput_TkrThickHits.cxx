// 
// Class for input of quantity TkrThickHits for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:40:25 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrThickHits.h"
#include <iostream>

// User defined part 

#define NAME TkrThickHits
#define OUTBRANCH "TkrThickHits"
#define LEAF "TkrThickHits/F"
#define INBRANCH "TkrThickHits"
#define ACCESSOR xx
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of clusters in the above cone in the thick-converter layers"


// End user defined part 

MonInput_TkrThickHits::MonInput_TkrThickHits(){
  m_name=OUTBRANCH;
}
MonInput_TkrThickHits::~MonInput_TkrThickHits(){
}


int MonInput_TkrThickHits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrThickHits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrThickHits::setValue(TObject* event) {
}
std::string MonInput_TkrThickHits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrThickHits::getDescription(){
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

