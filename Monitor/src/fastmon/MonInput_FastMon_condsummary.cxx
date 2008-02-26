// 
// Class for input of quantity FastMon_condsummary for monitoring 
// 
// Created by dpaneque on Tue Feb 26 06:01:21 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_condsummary.h"
#include <iostream>

// User defined part 

#define NAME FastMon_condsummary
#define OUTBRANCH "FastMon_condsummary"
#define LEAF "FastMon_condsummary/I"
#define INBRANCH "condsummary"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Condition summary word (from FastMon)"


// End user defined part 

MonInput_FastMon_condsummary::MonInput_FastMon_condsummary(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_condsummary::~MonInput_FastMon_condsummary(){
}


int MonInput_FastMon_condsummary::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_condsummary::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_condsummary::setValue(TObject* event) {
}
std::string MonInput_FastMon_condsummary::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_condsummary::getDescription(){
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

