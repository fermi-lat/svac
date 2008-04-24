// 
// Class for input of quantity FastMon_spacecraft_zra for monitoring 
// 
// Created by bregeon on Thu Apr 24 15:00:35 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_zra.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_zra
#define OUTBRANCH "FastMon_spacecraft_zra"
#define LEAF "FastMon_spacecraft_zra/D"
#define INBRANCH "spacecraft_zra"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Space craft z axis right ascension"


// End user defined part 

MonInput_FastMon_spacecraft_zra::MonInput_FastMon_spacecraft_zra(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_zra::~MonInput_FastMon_spacecraft_zra(){
}


int MonInput_FastMon_spacecraft_zra::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_zra::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_zra::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_zra::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_zra::getDescription(){
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

