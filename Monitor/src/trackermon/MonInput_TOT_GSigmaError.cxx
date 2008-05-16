// 
// Class for input of quantity TOT_GSigmaError for monitoring 
// 
// Created by dpaneque on Fri May 16 04:53:25 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_GSigmaError.h"
#include <iostream>

// User defined part 

#define NAME TOT_GSigmaError
#define OUTBRANCH "TOT_GSigmaError_TowerPlane"
#define LEAF "TOT_GSigmaError_TowerPlane[16][36]/D"
#define INBRANCH "TOT_GSigmaError"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_GSigmaError"


// End user defined part 

MonInput_TOT_GSigmaError::MonInput_TOT_GSigmaError(){
  m_name=OUTBRANCH;
}
MonInput_TOT_GSigmaError::~MonInput_TOT_GSigmaError(){
}


int MonInput_TOT_GSigmaError::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_GSigmaError::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_GSigmaError::setValue(TObject* event) {
}
std::string MonInput_TOT_GSigmaError::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_GSigmaError::getDescription(){
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

