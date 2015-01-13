// 
// Class for input of quantity CalCsIRLn for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:39:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalCsIRLn.h"
#include <iostream>

// User defined part 

#define NAME CalCsIRLn
#define OUTBRANCH "CalCsIRLn"
#define LEAF "CalCsIRLn/F"
#define INBRANCH "CalCsIRLn"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Total radiation lengths in crystals, integrated along the event axis (line connecting the first hit in the tracker to the CAL energy centroid)."


// End user defined part 

MonInput_CalCsIRLn::MonInput_CalCsIRLn(){
  m_name=OUTBRANCH;
}
MonInput_CalCsIRLn::~MonInput_CalCsIRLn(){
}


int MonInput_CalCsIRLn::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalCsIRLn::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalCsIRLn::setValue(TObject* event) {
}
std::string MonInput_CalCsIRLn::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalCsIRLn::getDescription(){
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

