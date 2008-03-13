// 
// Class for input of quantity CalTransRms for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:43:03 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalTransRms.h"
#include <iostream>

// User defined part 

#define NAME CalTransRms
#define OUTBRANCH "CalTransRms"
#define LEAF "CalTransRms/F"
#define INBRANCH "CalTransRms"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "rms of transverse position measurements."


// End user defined part 

MonInput_CalTransRms::MonInput_CalTransRms(){
  m_name=OUTBRANCH;
}
MonInput_CalTransRms::~MonInput_CalTransRms(){
}


int MonInput_CalTransRms::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalTransRms::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalTransRms::setValue(TObject* event) {
}
std::string MonInput_CalTransRms::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalTransRms::getDescription(){
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

