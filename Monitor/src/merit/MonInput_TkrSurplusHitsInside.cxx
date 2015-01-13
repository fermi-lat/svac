// 
// Class for input of quantity TkrSurplusHitsInside for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:19:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrSurplusHitsInside.h"
#include <iostream>

// User defined part 

#define NAME TkrSurplusHitsInside
#define OUTBRANCH "TkrSurplusHitsInside"
#define LEAF "TkrSurplusHitsInside/F"
#define INBRANCH "TkrSurplusHitsInside"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Number of clusters inside an energy- and angle-dependent cone centered on the reconstructed axis of the best track and starting at the head of track 1. Only hits in layers with at least one x and one y cluster in the tower are counted."


// End user defined part 

MonInput_TkrSurplusHitsInside::MonInput_TkrSurplusHitsInside(){
  m_name=OUTBRANCH;
}
MonInput_TkrSurplusHitsInside::~MonInput_TkrSurplusHitsInside(){
}


int MonInput_TkrSurplusHitsInside::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrSurplusHitsInside::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrSurplusHitsInside::setValue(TObject* event) {
}
std::string MonInput_TkrSurplusHitsInside::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrSurplusHitsInside::getDescription(){
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

