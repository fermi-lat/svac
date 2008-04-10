// 
// Class for input of quantity FastMon_meta_context_open_mode for monitoring 
// 
// Created by bregeon on Wed Apr  9 10:04:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_meta_context_open_mode.h"
#include <iostream>

// User defined part 

#define NAME FastMon_meta_context_open_mode
#define OUTBRANCH "FastMon_meta_context_open_mode"
#define LEAF "FastMon_meta_context_open_mode/s"
#define INBRANCH "meta_context_open_mode"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "LAT mode as read from the datagram open mode"


// End user defined part 

MonInput_FastMon_meta_context_open_mode::MonInput_FastMon_meta_context_open_mode(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_meta_context_open_mode::~MonInput_FastMon_meta_context_open_mode(){
}


int MonInput_FastMon_meta_context_open_mode::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_meta_context_open_mode::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_meta_context_open_mode::setValue(TObject* event) {
}
std::string MonInput_FastMon_meta_context_open_mode::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_meta_context_open_mode::getDescription(){
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

