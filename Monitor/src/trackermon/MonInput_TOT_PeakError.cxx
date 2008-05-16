// 
// Class for input of quantity TOT_PeakError for monitoring 
// 
// Created by dpaneque on Fri May 16 04:52:48 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_PeakError.h"
#include <iostream>

// User defined part 

#define NAME TOT_PeakError
#define OUTBRANCH "TOT_PeakError_TowerPlane"
#define LEAF "TOT_PeakError_TowerPlane[16][36]/D"
#define INBRANCH "TOT_PeakError"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_PeakError"


// End user defined part 

MonInput_TOT_PeakError::MonInput_TOT_PeakError(){
  m_name=OUTBRANCH;
}
MonInput_TOT_PeakError::~MonInput_TOT_PeakError(){
}


int MonInput_TOT_PeakError::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_PeakError::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_PeakError::setValue(TObject* event) {
}
std::string MonInput_TOT_PeakError::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_PeakError::getDescription(){
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

