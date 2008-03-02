// 
// Class for input of quantity FastMon_Cal_Tower_Count for monitoring 
// 
// Created by bregeon on Thu Feb 28 14:18:58 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FastMon_Cal_Tower_Count.h"
#include <iostream>

// User defined part 

#define NAME FastMon_Cal_Tower_Count
#define OUTBRANCH "FastMon_Cal_Tower_Count"
#define LEAF "FastMon_Cal_Tower_Count/I"
#define INBRANCH "CalTowerCount"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Number of Cal module with at least one CDE hit"


// End user defined part 

MonInput_FastMon_Cal_Tower_Count::MonInput_FastMon_Cal_Tower_Count(){
  m_name=OUTBRANCH;
}
MonInput_FastMon_Cal_Tower_Count::~MonInput_FastMon_Cal_Tower_Count(){
}


int MonInput_FastMon_Cal_Tower_Count::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FastMon_Cal_Tower_Count::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FastMon_Cal_Tower_Count::setValue(TObject* event) {
}
std::string MonInput_FastMon_Cal_Tower_Count::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FastMon_Cal_Tower_Count::getDescription(){
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

