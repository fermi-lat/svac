// 
// Class for input of quantity FastMon_evt_data_transfer_id for monitoring 
// 
// Created by bregeon on Sat May 17 12:29:02 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_evt_data_transfer_id.h"
#include <iostream>

// User defined part 

#define NAME FastMon_evt_data_transfer_id
#define OUTBRANCH "FastMon_evt_data_transfer_id"
#define LEAF "FastMon_evt_data_transfer_id/i"
#define INBRANCH "evt_data_transfer_id"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Last data transfer id, within the time bin"


// End user defined part 

MonInput_FastMon_evt_data_transfer_id::MonInput_FastMon_evt_data_transfer_id(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_evt_data_transfer_id::~MonInput_FastMon_evt_data_transfer_id(){
}


int MonInput_FastMon_evt_data_transfer_id::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_evt_data_transfer_id::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_evt_data_transfer_id::setValue(TObject* event) {
}
std::string MonInput_FastMon_evt_data_transfer_id::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_evt_data_transfer_id::getDescription(){
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

