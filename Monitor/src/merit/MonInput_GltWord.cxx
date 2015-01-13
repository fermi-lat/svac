// 
// Class for input of quantity GltWord for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:03:08 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_GltWord.h"
#include <iostream>

// User defined part 

#define NAME GltWord
#define OUTBRANCH "GltWord"
#define LEAF "GltWord/F"
#define INBRANCH "GltWord"
//#define ACCESSOR capullo
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Trigger word from the event header, based on digi information (null value: -1) The definition of the bits can be found in TriggerBits.h in the enums package."


// End user defined part 

MonInput_GltWord::MonInput_GltWord(){
  m_name=OUTBRANCH;
}
MonInput_GltWord::~MonInput_GltWord(){
}


int MonInput_GltWord::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_GltWord::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_GltWord::setValue(TObject* event) {
}
std::string MonInput_GltWord::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_GltWord::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
// #undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

