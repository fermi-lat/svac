// 
// Class for input of quantity CTBCORE for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:11:28 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBCORE.h"
#include <iostream>

// User defined part 

#define NAME CTBCORE
#define OUTBRANCH "CTBCORE"
#define LEAF "CTBCORE/F"
#define INBRANCH "CTBCORE"
#define ACCESSOR ccc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Image probability knob. Tunes the image resolution."


// End user defined part 

MonInput_CTBCORE::MonInput_CTBCORE(){
  m_name=OUTBRANCH;
}
MonInput_CTBCORE::~MonInput_CTBCORE(){
}


int MonInput_CTBCORE::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBCORE::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBCORE::setValue(TObject* event) {
}
std::string MonInput_CTBCORE::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBCORE::getDescription(){
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

