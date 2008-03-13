// 
// Class for input of quantity Tkr1TwrGap for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:29:50 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Tkr1TwrGap.h"
#include <iostream>

// User defined part 

#define NAME Tkr1TwrGap
#define OUTBRANCH "Tkr1TwrGap"
#define LEAF "Tkr1TwrGap/F"
#define INBRANCH "Tkr1TwrGap"
#define ACCESSOR vvv
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Length of track in nominal intertower gap, currently set to 18 mm. Can be a small as zero if track exits through bottom of tracker, and as large as the intertower gap, if track crosses to adjacent tower."


// End user defined part 

MonInput_Tkr1TwrGap::MonInput_Tkr1TwrGap(){
  m_name=OUTBRANCH;
}
MonInput_Tkr1TwrGap::~MonInput_Tkr1TwrGap(){
}


int MonInput_Tkr1TwrGap::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Tkr1TwrGap::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Tkr1TwrGap::setValue(TObject* event) {
}
std::string MonInput_Tkr1TwrGap::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Tkr1TwrGap::getDescription(){
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

