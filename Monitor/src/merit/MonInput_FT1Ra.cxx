// 
// Class for input of quantity FT1Ra for monitoring 
// 
// Created by dpaneque on Tue Jul  5 12:00:04 2011 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1Ra.h"
#include <iostream>

// User defined part 

#define NAME FT1Ra
#define OUTBRANCH "FT1Ra"
#define LEAF "FT1Ra/F"
#define INBRANCH "FT1Ra"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Variable FT1Ra from Merit Tuple"


// End user defined part 

MonInput_FT1Ra::MonInput_FT1Ra(){
  m_name=OUTBRANCH;
}
MonInput_FT1Ra::~MonInput_FT1Ra(){
}


int MonInput_FT1Ra::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1Ra::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FT1Ra::setValue(TObject* event) {
}
std::string MonInput_FT1Ra::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1Ra::getDescription(){
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

