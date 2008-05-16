// 
// Class for input of quantity TOT_LWidthError for monitoring 
// 
// Created by dpaneque on Fri May 16 04:53:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_LWidthError.h"
#include <iostream>

// User defined part 

#define NAME TOT_LWidthError
#define OUTBRANCH "TOT_LWidthError_TowerPlane"
#define LEAF "TOT_LWidthError_TowerPlane[16][36]/D"
#define INBRANCH "TOT_LWidthError"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_LWidthError"


// End user defined part 

MonInput_TOT_LWidthError::MonInput_TOT_LWidthError(){
  m_name=OUTBRANCH;
}
MonInput_TOT_LWidthError::~MonInput_TOT_LWidthError(){
}


int MonInput_TOT_LWidthError::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_LWidthError::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_LWidthError::setValue(TObject* event) {
}
std::string MonInput_TOT_LWidthError::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_LWidthError::getDescription(){
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

