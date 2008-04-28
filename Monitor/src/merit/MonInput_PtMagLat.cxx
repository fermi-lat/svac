// 
// Class for input of quantity PtMagLat for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:45:47 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PtMagLat.h"
#include <iostream>

// User defined part 

#define NAME PtMagLat
#define OUTBRANCH "PtMagLat"
#define LEAF "PtMagLat/F"
#define INBRANCH "PtMagLat"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "PtMagLat"


// End user defined part 

MonInput_PtMagLat::MonInput_PtMagLat(){
  m_name=OUTBRANCH;
}
MonInput_PtMagLat::~MonInput_PtMagLat(){
}


int MonInput_PtMagLat::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PtMagLat::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_PtMagLat::setValue(TObject* event) {
}
std::string MonInput_PtMagLat::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PtMagLat::getDescription(){
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

