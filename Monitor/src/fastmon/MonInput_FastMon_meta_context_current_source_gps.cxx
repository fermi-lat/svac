// 
// Class for input of quantity FastMon_meta_context_current_source_gps for monitoring 
// 
// Created by bregeon on Fri May  2 09:26:32 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_meta_context_current_source_gps.h"
#include <iostream>

// User defined part 

#define NAME FastMon_meta_context_current_source_gps
#define OUTBRANCH "FastMon_meta_context_current_source_gps"
#define LEAF "FastMon_meta_context_current_source_gps/O"
#define INBRANCH "meta_context_current_source_gps"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "This quantity is true when the source GPS is locked."


// End user defined part 

MonInput_FastMon_meta_context_current_source_gps::MonInput_FastMon_meta_context_current_source_gps(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_meta_context_current_source_gps::~MonInput_FastMon_meta_context_current_source_gps(){
}


int MonInput_FastMon_meta_context_current_source_gps::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_meta_context_current_source_gps::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_meta_context_current_source_gps::setValue(TObject* event) {
}
std::string MonInput_FastMon_meta_context_current_source_gps::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_meta_context_current_source_gps::getDescription(){
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

