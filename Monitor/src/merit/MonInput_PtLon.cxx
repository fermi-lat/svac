// 
// Class for input of quantity PtLon for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:45:24 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PtLon.h"
#include <iostream>

// User defined part 

#define NAME PtLon
#define OUTBRANCH "PtLon"
#define LEAF "PtLon/F"
#define INBRANCH "PtLon"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "PtLon"


// End user defined part 

MonInput_PtLon::MonInput_PtLon(){
  m_name=OUTBRANCH;
}
MonInput_PtLon::~MonInput_PtLon(){
}


int MonInput_PtLon::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PtLon::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_PtLon::setValue(TObject* event) {
}
std::string MonInput_PtLon::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PtLon::getDescription(){
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

