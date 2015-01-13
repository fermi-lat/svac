// 
// Class for input of quantity AcdTotalEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:13:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdTotalEnergy.h"
#include <iostream>

// User defined part 

#define NAME AcdTotalEnergy
#define OUTBRANCH "AcdTotalEnergy"
#define LEAF "AcdTotalEnergy/F"
#define INBRANCH "AcdTotalEnergy"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Total energy deposited in ACD Tiles"


// End user defined part 

MonInput_AcdTotalEnergy::MonInput_AcdTotalEnergy(){
  m_name=OUTBRANCH;
}
MonInput_AcdTotalEnergy::~MonInput_AcdTotalEnergy(){
}


int MonInput_AcdTotalEnergy::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdTotalEnergy::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdTotalEnergy::setValue(TObject* event) {
}
std::string MonInput_AcdTotalEnergy::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdTotalEnergy::getDescription(){
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

