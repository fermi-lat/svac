// 
// Class for input of quantity CalTwrEdgeCntr for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:41:09 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalTwrEdgeCntr.h"
#include <iostream>

// User defined part 

#define NAME CalTwrEdgeCntr
#define OUTBRANCH "CalTwrEdgeCntr"
#define LEAF "CalTwrEdgeCntr/F"
#define INBRANCH "CalTwrEdgeCntr"
#define ACCESSOR xx
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Distance of the energy centroid from the nearest tower boundary."


// End user defined part 

MonInput_CalTwrEdgeCntr::MonInput_CalTwrEdgeCntr(){
  m_name=OUTBRANCH;
}
MonInput_CalTwrEdgeCntr::~MonInput_CalTwrEdgeCntr(){
}


int MonInput_CalTwrEdgeCntr::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalTwrEdgeCntr::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalTwrEdgeCntr::setValue(TObject* event) {
}
std::string MonInput_CalTwrEdgeCntr::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalTwrEdgeCntr::getDescription(){
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

