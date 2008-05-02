// 
// Class for input of quantity FastMon_new_second for monitoring 
// 
// Created by bregeon on Fri May  2 09:24:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_new_second.h"
#include <iostream>

// User defined part 

#define NAME FastMon_new_second
#define OUTBRANCH "FastMon_new_second"
#define LEAF "FastMon_new_second/O"
#define INBRANCH "new_second"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "This quantity is true when the second just changed."


// End user defined part 

MonInput_FastMon_new_second::MonInput_FastMon_new_second(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_new_second::~MonInput_FastMon_new_second(){
}


int MonInput_FastMon_new_second::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_new_second::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_new_second::setValue(TObject* event) {
}
std::string MonInput_FastMon_new_second::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_new_second::getDescription(){
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

