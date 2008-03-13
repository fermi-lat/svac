// 
// Class for input of quantity TkrSurplusHitRatio for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:20:43 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrSurplusHitRatio.h"
#include <iostream>

// User defined part 

#define NAME TkrSurplusHitRatio
#define OUTBRANCH "TkrSurplusHitRatio"
#define LEAF "TkrSurplusHitRatio/F"
#define INBRANCH "TkrSurplusHitRatio"
#define ACCESSOR vv
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Ratio of the number of hits outside the cone to the number inside. See TkrSurplusHitsInside"


// End user defined part 

MonInput_TkrSurplusHitRatio::MonInput_TkrSurplusHitRatio(){
  m_name=OUTBRANCH;
}
MonInput_TkrSurplusHitRatio::~MonInput_TkrSurplusHitRatio(){
}


int MonInput_TkrSurplusHitRatio::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrSurplusHitRatio::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrSurplusHitRatio::setValue(TObject* event) {
}
std::string MonInput_TkrSurplusHitRatio::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrSurplusHitRatio::getDescription(){
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

