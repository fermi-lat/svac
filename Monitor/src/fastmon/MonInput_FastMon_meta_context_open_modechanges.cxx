// 
// Class for input of quantity FastMon_meta_context_open_modechanges for monitoring 
// 
// Created by bregeon on Thu Apr 10 14:16:26 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_meta_context_open_modechanges.h"
#include <iostream>

// User defined part 

#define NAME FastMon_meta_context_open_modechanges
#define OUTBRANCH "FastMon_meta_context_open_modechanges"
#define LEAF "FastMon_meta_context_open_modechanges/i"
#define INBRANCH "meta_context_open_modechanges"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the LAT mode changes as read from the datagram open mode"


// End user defined part 

MonInput_FastMon_meta_context_open_modechanges::MonInput_FastMon_meta_context_open_modechanges(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_meta_context_open_modechanges::~MonInput_FastMon_meta_context_open_modechanges(){
}


int MonInput_FastMon_meta_context_open_modechanges::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_meta_context_open_modechanges::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_meta_context_open_modechanges::setValue(TObject* event) {
}
std::string MonInput_FastMon_meta_context_open_modechanges::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_meta_context_open_modechanges::getDescription(){
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

