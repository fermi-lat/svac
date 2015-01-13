// 
// Class for input of quantity FT1Energy for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:03:40 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1Energy.h"
#include <iostream>

// User defined part 

#define NAME FT1Energy
#define OUTBRANCH "FT1Energy"
#define LEAF "FT1Energy/F"
#define INBRANCH "FT1Energy"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Estimated energy (MeV)."


// End user defined part 

MonInput_FT1Energy::MonInput_FT1Energy(){
  m_name=OUTBRANCH;
}
MonInput_FT1Energy::~MonInput_FT1Energy(){
}


int MonInput_FT1Energy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1Energy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FT1Energy::setValue(TObject* event) {
}
std::string MonInput_FT1Energy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1Energy::getDescription(){
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

