// 
// Class for input of quantity CTBCalDocaAngle for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:06:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBCalDocaAngle.h"
#include <iostream>

// User defined part 

#define NAME CTBCalDocaAngle
#define OUTBRANCH "CTBCalDocaAngle"
#define LEAF "CTBCalDocaAngle/F"
#define INBRANCH "CTBCalDocaAngle"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "xxxxx"


// End user defined part 

MonInput_CTBCalDocaAngle::MonInput_CTBCalDocaAngle(){
  m_name=OUTBRANCH;
}
MonInput_CTBCalDocaAngle::~MonInput_CTBCalDocaAngle(){
}


int MonInput_CTBCalDocaAngle::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBCalDocaAngle::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBCalDocaAngle::setValue(TObject* event) {
}
std::string MonInput_CTBCalDocaAngle::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBCalDocaAngle::getDescription(){
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

