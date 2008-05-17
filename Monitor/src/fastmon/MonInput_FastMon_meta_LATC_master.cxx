// 
// Class for input of quantity FastMon_meta_LATC_master for monitoring 
// 
// Created by bregeon on Sat May 17 12:23:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_meta_LATC_master.h"
#include <iostream>

// User defined part 

#define NAME FastMon_meta_LATC_master
#define OUTBRANCH "FastMon_meta_LATC_master"
#define LEAF "FastMon_meta_LATC_master/i"
#define INBRANCH "meta_LATC_master"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Last value of the LATC Master key, within the time bin"


// End user defined part 

MonInput_FastMon_meta_LATC_master::MonInput_FastMon_meta_LATC_master(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_meta_LATC_master::~MonInput_FastMon_meta_LATC_master(){
}


int MonInput_FastMon_meta_LATC_master::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_meta_LATC_master::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_meta_LATC_master::setValue(TObject* event) {
}
std::string MonInput_FastMon_meta_LATC_master::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_meta_LATC_master::getDescription(){
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

