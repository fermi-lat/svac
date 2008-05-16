// 
// Class for input of quantity TOT_GSigma for monitoring 
// 
// Created by dpaneque on Fri May 16 04:52:01 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_GSigma.h"
#include <iostream>

// User defined part 

#define NAME TOT_GSigma
#define OUTBRANCH "TOT_GSigma_TowerPlane"
#define LEAF "TOT_GSigma_TowerPlane[16][36]/D"
#define INBRANCH "TOT_GSigma"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_GSigma"


// End user defined part 

MonInput_TOT_GSigma::MonInput_TOT_GSigma(){
  m_name=OUTBRANCH;
}
MonInput_TOT_GSigma::~MonInput_TOT_GSigma(){
}


int MonInput_TOT_GSigma::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_GSigma::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_GSigma::setValue(TObject* event) {
}
std::string MonInput_TOT_GSigma::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_GSigma::getDescription(){
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

