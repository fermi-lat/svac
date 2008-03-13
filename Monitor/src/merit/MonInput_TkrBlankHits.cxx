// 
// Class for input of quantity TkrBlankHits for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:41:07 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrBlankHits.h"
#include <iostream>

// User defined part 

#define NAME TkrBlankHits
#define OUTBRANCH "TkrBlankHits"
#define LEAF "TkrBlankHits/F"
#define INBRANCH "TkrBlankHits"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of clusters in the above cone in the no-converter layers"


// End user defined part 

MonInput_TkrBlankHits::MonInput_TkrBlankHits(){
  m_name=OUTBRANCH;
}
MonInput_TkrBlankHits::~MonInput_TkrBlankHits(){
}


int MonInput_TkrBlankHits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrBlankHits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrBlankHits::setValue(TObject* event) {
}
std::string MonInput_TkrBlankHits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrBlankHits::getDescription(){
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

