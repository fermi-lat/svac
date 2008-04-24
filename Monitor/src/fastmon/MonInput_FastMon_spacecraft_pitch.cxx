// 
// Class for input of quantity FastMon_spacecraft_pitch for monitoring 
// 
// Created by bregeon on Thu Apr 24 15:20:28 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_spacecraft_pitch.h"
#include <iostream>

// User defined part 

#define NAME FastMon_spacecraft_pitch
#define OUTBRANCH "FastMon_spacecraft_pitch"
#define LEAF "FastMon_spacecraft_pitch/D"
#define INBRANCH "spacecraft_pitch"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Space craft pitch angle"


// End user defined part 

MonInput_FastMon_spacecraft_pitch::MonInput_FastMon_spacecraft_pitch(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_spacecraft_pitch::~MonInput_FastMon_spacecraft_pitch(){
}


int MonInput_FastMon_spacecraft_pitch::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_spacecraft_pitch::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_spacecraft_pitch::setValue(TObject* event) {
}
std::string MonInput_FastMon_spacecraft_pitch::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_spacecraft_pitch::getDescription(){
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

