// 
// Class for input of quantity FastMon_error_summary for monitoring 
// 
// Created by bregeon on Mon Aug 25 14:46:04 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_error_summary.h"
#include <iostream>

// User defined part 

#define NAME FastMon_error_summary
#define OUTBRANCH "FastMon_error_summary"
#define LEAF "FastMon_error_summary/i"
#define INBRANCH "error_summary"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Error summary bit coded"


// End user defined part 

MonInput_FastMon_error_summary::MonInput_FastMon_error_summary(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_error_summary::~MonInput_FastMon_error_summary(){
}


int MonInput_FastMon_error_summary::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_error_summary::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_error_summary::setValue(TObject* event) {
}
std::string MonInput_FastMon_error_summary::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_error_summary::getDescription(){
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

