// 
// Class for input of quantity FastMon_TkrHits for monitoring 
// 
// Created by dpaneque on Tue Feb 26 05:10:44 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_TkrHits.h"
#include <iostream>

// User defined part 

#define NAME FastMon_TkrHits
#define OUTBRANCH "FastMon_TkrHits"
#define LEAF "FastMon_TkrHits/I"
#define INBRANCH "TkrHits"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Number of strip hits in the tracker (from FastMon)"


// End user defined part 

MonInput_FastMon_TkrHits::MonInput_FastMon_TkrHits(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_TkrHits::~MonInput_FastMon_TkrHits(){
}


int MonInput_FastMon_TkrHits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_TkrHits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_TkrHits::setValue(TObject* event) {
}
std::string MonInput_FastMon_TkrHits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_TkrHits::getDescription(){
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

