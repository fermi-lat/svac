// 
// Class for input of quantity TOT_FracLowTOT for monitoring 
// 
// Created by dpaneque on Fri May 16 04:54:00 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_FracLowTOT.h"
#include <iostream>

// User defined part 

#define NAME TOT_FracLowTOT
#define OUTBRANCH "TOT_FracLowTOT_TowerPlane"
#define LEAF "TOT_FracLowTOT_TowerPlane[16][36]/D"
#define INBRANCH "TOT_FracLowTOT"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_FracLowTOT"


// End user defined part 

MonInput_TOT_FracLowTOT::MonInput_TOT_FracLowTOT(){
  m_name=OUTBRANCH;
}
MonInput_TOT_FracLowTOT::~MonInput_TOT_FracLowTOT(){
}


int MonInput_TOT_FracLowTOT::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_FracLowTOT::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_FracLowTOT::setValue(TObject* event) {
}
std::string MonInput_TOT_FracLowTOT::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_FracLowTOT::getDescription(){
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

