// 
// Class for input of quantity Acd2CornerDoca for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:11:20 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2CornerDoca.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2CornerDoca
#define OUTBRANCH "Acd2CornerDoca"
#define LEAF "Acd2CornerDoca/F"
#define INBRANCH "Acd2CornerDoca"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Minimum Distance of Closest Approach of best track to the corner side gaps"


// End user defined part 

MonInput_Acd2CornerDoca::MonInput_Acd2CornerDoca(){
  m_name=OUTBRANCH;
}
MonInput_Acd2CornerDoca::~MonInput_Acd2CornerDoca(){
}


int MonInput_Acd2CornerDoca::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2CornerDoca::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2CornerDoca::setValue(TObject* event) {
}
std::string MonInput_Acd2CornerDoca::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2CornerDoca::getDescription(){
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

