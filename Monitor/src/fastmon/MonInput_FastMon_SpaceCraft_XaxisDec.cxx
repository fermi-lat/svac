// 
// Class for input of quantity FastMon_SpaceCraft_XaxisDec for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:03:42 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_SpaceCraft_XaxisDec.h"
#include <iostream>

// User defined part 

#define NAME FastMon_SpaceCraft_XaxisDec
#define OUTBRANCH "FastMon_SpaceCraft_XaxisDec"
#define LEAF "FastMon_SpaceCraft_XaxisDec/D"
#define INBRANCH "spacecraft_xdec"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Mean value of the spacecraft x axis declination"


// End user defined part 

MonInput_FastMon_SpaceCraft_XaxisDec::MonInput_FastMon_SpaceCraft_XaxisDec(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_SpaceCraft_XaxisDec::~MonInput_FastMon_SpaceCraft_XaxisDec(){
}


int MonInput_FastMon_SpaceCraft_XaxisDec::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_SpaceCraft_XaxisDec::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_SpaceCraft_XaxisDec::setValue(TObject* event) {
}
std::string MonInput_FastMon_SpaceCraft_XaxisDec::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_SpaceCraft_XaxisDec::getDescription(){
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

