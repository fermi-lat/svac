// 
// Class for input of quantity TOT_LWidth for monitoring 
// 
// Created by dpaneque on Fri May 16 04:51:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_LWidth.h"
#include <iostream>

// User defined part 

#define NAME TOT_LWidth
#define OUTBRANCH "TOT_LWidth_TowerPlane"
#define LEAF "TOT_LWidth_TowerPlane[16][36]/D"
#define INBRANCH "TOT_LWidth"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_LWidth"


// End user defined part 

MonInput_TOT_LWidth::MonInput_TOT_LWidth(){
  m_name=OUTBRANCH;
}
MonInput_TOT_LWidth::~MonInput_TOT_LWidth(){
}


int MonInput_TOT_LWidth::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_LWidth::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_LWidth::setValue(TObject* event) {
}
std::string MonInput_TOT_LWidth::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_LWidth::getDescription(){
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

