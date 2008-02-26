// 
// Class for input of quantity FastMon_TkrHits_TowerPlane for monitoring 
// 
// Created by dpaneque on Tue Feb 26 05:59:16 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_TkrHits_TowerPlane.h"
#include <iostream>

// User defined part 

#define NAME FastMon_TkrHits_TowerPlane
#define OUTBRANCH "FastMon_TkrHits_TowerPlane"
#define LEAF "FastMon_TkrHits_TowerPlane[16][36]/I"
#define INBRANCH "TkrHitsTowerPlane"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Vector [tower][plane] reporting the number of strip hits for this tower and plane (from FastMon)"


// End user defined part 

MonInput_FastMon_TkrHits_TowerPlane::MonInput_FastMon_TkrHits_TowerPlane(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_TkrHits_TowerPlane::~MonInput_FastMon_TkrHits_TowerPlane(){
}


int MonInput_FastMon_TkrHits_TowerPlane::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_TkrHits_TowerPlane::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,m_val);
}
void MonInput_FastMon_TkrHits_TowerPlane::setValue(TObject* event) {
}
std::string MonInput_FastMon_TkrHits_TowerPlane::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_TkrHits_TowerPlane::getDescription(){
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

