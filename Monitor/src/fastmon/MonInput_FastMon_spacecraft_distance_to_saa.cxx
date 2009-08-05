// 
// Class for input of quantity FastMon_spacecraft_distance_to_saa for monitoring 
// 
// Created by bregeon on Wed Aug  5 13:14:06 2009 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_distance_to_saa.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_distance_to_saa
#define OUTBRANCH "FastMon_spacecraft_distance_to_saa"
#define LEAF "FastMon_spacecraft_distance_to_saa/D"
#define INBRANCH "spacecraft_distance_to_saa"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Spacecraft distance to the SAA polygon"


// End user defined part 

MonInput_FastMon_spacecraft_distance_to_saa::MonInput_FastMon_spacecraft_distance_to_saa(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_distance_to_saa::~MonInput_FastMon_spacecraft_distance_to_saa(){
}


int MonInput_FastMon_spacecraft_distance_to_saa::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_distance_to_saa::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_distance_to_saa::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_distance_to_saa::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_distance_to_saa::getDescription(){
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

