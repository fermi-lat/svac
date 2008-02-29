// 
// Class for input of quantity FastMon_CalLogEndRangeHit for monitoring 
// 
// Created by bregeon on Fri Feb 29 14:20:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_CalLogEndRangeHit.h"
#include <iostream>

// User defined part 

#define NAME FastMon_CalLogEndRangeHit
#define OUTBRANCH "FastMon_CalLogEndRangeHit"
#define LEAF "CalLogEndRangeHit[16][8][12][2][4]/O"
#define INBRANCH "CalLogEndRangeHit"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Number of hits in each Cal log end for each range"


// End user defined part 

MonInput_FastMon_CalLogEndRangeHit::MonInput_FastMon_CalLogEndRangeHit(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_CalLogEndRangeHit::~MonInput_FastMon_CalLogEndRangeHit(){
}


int MonInput_FastMon_CalLogEndRangeHit::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_CalLogEndRangeHit::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_CalLogEndRangeHit::setValue(TObject* event) {
}
std::string MonInput_FastMon_CalLogEndRangeHit::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_CalLogEndRangeHit::getDescription(){
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

