// 
// Class for input of quantity PtLat for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:44:51 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PtLat.h"
#include <iostream>

// User defined part 

#define NAME PtLat
#define OUTBRANCH "PtLat"
#define LEAF "PtLat/F"
#define INBRANCH "PtLat"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "PtLat"


// End user defined part 

MonInput_PtLat::MonInput_PtLat(){
  m_name=OUTBRANCH;
}
MonInput_PtLat::~MonInput_PtLat(){
}


int MonInput_PtLat::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PtLat::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_PtLat::setValue(TObject* event) {
}
std::string MonInput_PtLat::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PtLat::getDescription(){
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

