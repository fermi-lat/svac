// 
// Class for input of quantity CalMipNum for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:37:17 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalMipNum.h"
#include <iostream>

// User defined part 

#define NAME CalMipNum
#define OUTBRANCH "CalMipNum"
#define LEAF "CalMipNum/F"
#define INBRANCH "CalMipNum"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Total number of found mip-like tracks in the Cal"


// End user defined part 

MonInput_CalMipNum::MonInput_CalMipNum(){
  m_name=OUTBRANCH;
}
MonInput_CalMipNum::~MonInput_CalMipNum(){
}


int MonInput_CalMipNum::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalMipNum::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalMipNum::setValue(TObject* event) {
}
std::string MonInput_CalMipNum::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalMipNum::getDescription(){
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

