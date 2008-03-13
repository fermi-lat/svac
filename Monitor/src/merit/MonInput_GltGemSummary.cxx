// 
// Class for input of quantity GltGemSummary for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:08:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_GltGemSummary.h"
#include <iostream>

// User defined part 

#define NAME GltGemSummary
#define OUTBRANCH "GltGemSummary"
#define LEAF "GltGemSummary/F"
#define INBRANCH "GltGemSummary"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "For Data, a copy of the GEM condtion summary; for MC, the same as calculated from the trigger (digi) information (null value: -1) "


// End user defined part 

MonInput_GltGemSummary::MonInput_GltGemSummary(){
  m_name=OUTBRANCH;
}
MonInput_GltGemSummary::~MonInput_GltGemSummary(){
}


int MonInput_GltGemSummary::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_GltGemSummary::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_GltGemSummary::setValue(TObject* event) {
}
std::string MonInput_GltGemSummary::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_GltGemSummary::getDescription(){
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

