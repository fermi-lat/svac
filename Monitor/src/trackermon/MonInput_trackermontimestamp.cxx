// 
// Class for input of quantity trackermontimestamp for monitoring 
// 
// Created by dpaneque on Wed May 14 23:59:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_trackermontimestamp.h"
#include <iostream>

// User defined part 

#define NAME trackermontimestamp
#define OUTBRANCH "trackermontimestamp"
#define LEAF "trackermontimestamp/D"
#define INBRANCH "startTime"
//#define ACCESSOR NotAplicable
#define MONSOURCE TrackerMonEvent
#define INPUTSOURCE "TrackerMonEvent"
#define DESCRIPTION "Variable used as timestamp for TrackerMon jobs. This variable is actually the startTime in input root file."


// End user defined part 

MonInput_trackermontimestamp::MonInput_trackermontimestamp(){
  m_name=OUTBRANCH;
}
MonInput_trackermontimestamp::~MonInput_trackermontimestamp(){
}


int MonInput_trackermontimestamp::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_trackermontimestamp::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_trackermontimestamp::setValue(TObject* event) {
}
std::string MonInput_trackermontimestamp::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_trackermontimestamp::getDescription(){
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

