// 
// Class for input of quantity FT1Theta for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:04:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1Theta.h"
#include <iostream>

// User defined part 

#define NAME FT1Theta
#define OUTBRANCH "FT1Theta"
#define LEAF "FT1Theta/F"
#define INBRANCH "FT1Theta"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Reconstructed Theta angle (in deg) with respect to the instrument coordinate system"


// End user defined part 

MonInput_FT1Theta::MonInput_FT1Theta(){
  m_name=OUTBRANCH;
}
MonInput_FT1Theta::~MonInput_FT1Theta(){
}


int MonInput_FT1Theta::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1Theta::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FT1Theta::setValue(TObject* event) {
}
std::string MonInput_FT1Theta::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1Theta::getDescription(){
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

