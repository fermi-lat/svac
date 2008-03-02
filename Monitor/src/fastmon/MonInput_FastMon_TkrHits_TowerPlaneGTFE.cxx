// 
// Class for input of quantity FastMon_TkrHits_TowerPlaneGTFE for monitoring 
// 
// Created by bregeon on Thu Feb 28 14:49:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_TkrHits_TowerPlaneGTFE.h"
#include <iostream>

// User defined part 

#define NAME FastMon_TkrHits_TowerPlaneGTFE
#define OUTBRANCH "FastMon_TkrHits_TowerPlaneGTFE"
#define LEAF "FastMon_TkrHits_TowerPlaneGTFE[16][36][24]/I"
#define INBRANCH "TkrHitsGTFE"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Vector with the number of Tkr hits per tower, plane, GTFE"


// End user defined part 

MonInput_FastMon_TkrHits_TowerPlaneGTFE::MonInput_FastMon_TkrHits_TowerPlaneGTFE(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_TkrHits_TowerPlaneGTFE::~MonInput_FastMon_TkrHits_TowerPlaneGTFE(){
}


int MonInput_FastMon_TkrHits_TowerPlaneGTFE::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_TkrHits_TowerPlaneGTFE::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_TkrHits_TowerPlaneGTFE::setValue(TObject* event) {
}
std::string MonInput_FastMon_TkrHits_TowerPlaneGTFE::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_TkrHits_TowerPlaneGTFE::getDescription(){
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

