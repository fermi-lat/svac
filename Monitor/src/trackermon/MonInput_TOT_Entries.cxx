// 
// Class for input of quantity TOT_Entries for monitoring 
// 
// Created by dpaneque on Fri May 16 04:52:24 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TOT_Entries.h"
#include <iostream>

// User defined part 

#define NAME TOT_Entries
#define OUTBRANCH "TOT_Entries_TowerPlane"
#define LEAF "TOT_Entries_TowerPlane[16][36]/D"
#define INBRANCH "TOT_Entries"
#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "TOT_Entries"


// End user defined part 

MonInput_TOT_Entries::MonInput_TOT_Entries(){
  m_name=OUTBRANCH;
}
MonInput_TOT_Entries::~MonInput_TOT_Entries(){
}


int MonInput_TOT_Entries::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TOT_Entries::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TOT_Entries::setValue(TObject* event) {
}
std::string MonInput_TOT_Entries::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TOT_Entries::getDescription(){
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

