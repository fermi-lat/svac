// 
// Class for input of quantity AcdCornerDoca for monitoring 
// 
// Created by dpaneque on Wed Mar 12 19:39:40 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdCornerDoca.h"
#include <iostream>

// User defined part 

#define NAME AcdCornerDoca
#define OUTBRANCH "AcdCornerDoca"
#define LEAF "AcdCornerDoca/F"
#define INBRANCH "AcdCornerDoca"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Minimum Distance of Closest Approach of best track to the corner side gaps"


// End user defined part 

MonInput_AcdCornerDoca::MonInput_AcdCornerDoca(){
  m_name=OUTBRANCH;
}
MonInput_AcdCornerDoca::~MonInput_AcdCornerDoca(){
}


int MonInput_AcdCornerDoca::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdCornerDoca::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdCornerDoca::setValue(TObject* event) {
}
std::string MonInput_AcdCornerDoca::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdCornerDoca::getDescription(){
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

