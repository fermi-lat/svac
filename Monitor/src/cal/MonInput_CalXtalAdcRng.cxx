// 
// Class for input of quantity CalXtalAdcRng for monitoring 
// 
// Created by dpaneque on Mon Aug 11 04:41:33 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalXtalAdcRng.h"
#include <iostream>

// User defined part 

#define NAME CalXtalAdcRng
#define OUTBRANCH "CalXtalAdcRng"
#define LEAF "CalXtalAdcRng[16][8][12][2]/I"
#define INBRANCH "CalXtalAdcRng[16][8][12][2]"
#define ACCESSOR NotApplicable
#define MONSOURCE CalEvent
#define INPUTSOURCE "CalEvent"
#define DESCRIPTION "Vector [tower][callayer][calcolumn][xface] reporting the best range used for the xtal log and face defined by the coordinates  tower, callayer, calcolumn, xface."


// End user defined part 

MonInput_CalXtalAdcRng::MonInput_CalXtalAdcRng(){
  m_name=OUTBRANCH;
}
MonInput_CalXtalAdcRng::~MonInput_CalXtalAdcRng(){
}


int MonInput_CalXtalAdcRng::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalXtalAdcRng::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,m_val);
}
void MonInput_CalXtalAdcRng::setValue(TObject* event) {
}
std::string MonInput_CalXtalAdcRng::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalXtalAdcRng::getDescription(){
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

