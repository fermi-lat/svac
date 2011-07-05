// 
// Class for input of quantity FT1Dec for monitoring 
// 
// Created by dpaneque on Tue Jul  5 12:01:02 2011 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1Dec.h"
#include <iostream>

// User defined part 

#define NAME FT1Dec
#define OUTBRANCH "FT1Dec"
#define LEAF "FT1Dec/F"
#define INBRANCH "FT1Dec"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Variable FT1Dec from the Merit Tuple"


// End user defined part 

MonInput_FT1Dec::MonInput_FT1Dec(){
  m_name=OUTBRANCH;
}
MonInput_FT1Dec::~MonInput_FT1Dec(){
}


int MonInput_FT1Dec::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1Dec::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FT1Dec::setValue(TObject* event) {
}
std::string MonInput_FT1Dec::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1Dec::getDescription(){
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

