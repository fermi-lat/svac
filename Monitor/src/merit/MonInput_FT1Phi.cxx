// 
// Class for input of quantity FT1Phi for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:05:06 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1Phi.h"
#include <iostream>

// User defined part 

#define NAME FT1Phi
#define OUTBRANCH "FT1Phi"
#define LEAF "FT1Phi/F"
#define INBRANCH "FT1Phi"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Reconstructed Phi angle (in deg) with respect to the instrument coordinate system."


// End user defined part 

MonInput_FT1Phi::MonInput_FT1Phi(){
  m_name=OUTBRANCH;
}
MonInput_FT1Phi::~MonInput_FT1Phi(){
}


int MonInput_FT1Phi::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1Phi::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FT1Phi::setValue(TObject* event) {
}
std::string MonInput_FT1Phi::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1Phi::getDescription(){
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

