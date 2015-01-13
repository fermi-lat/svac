// 
// Class for input of quantity TkrThinHits for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:39:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrThinHits.h"
#include <iostream>

// User defined part 

#define NAME TkrThinHits
#define OUTBRANCH "TkrThinHits"
#define LEAF "TkrThinHits/F"
#define INBRANCH "TkrThinHits"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of clusters in the above cone in the thin-converter layers"


// End user defined part 

MonInput_TkrThinHits::MonInput_TkrThinHits(){
  m_name=OUTBRANCH;
}
MonInput_TkrThinHits::~MonInput_TkrThinHits(){
}


int MonInput_TkrThinHits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrThinHits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrThinHits::setValue(TObject* event) {
}
std::string MonInput_TkrThinHits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrThinHits::getDescription(){
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

