// 
// Class for input of quantity FastMon_spacecraft_longitude for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:31:56 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_longitude.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_longitude
#define OUTBRANCH "FastMon_spacecraft_longitude"
#define LEAF "FastMon_spacecraft_longitude/D"
#define INBRANCH "spacecraft_longitude"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the space craft longitude"


// End user defined part 

MonInput_FastMon_spacecraft_longitude::MonInput_FastMon_spacecraft_longitude(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_longitude::~MonInput_FastMon_spacecraft_longitude(){
}


int MonInput_FastMon_spacecraft_longitude::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_longitude::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_longitude::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_longitude::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_longitude::getDescription(){
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

