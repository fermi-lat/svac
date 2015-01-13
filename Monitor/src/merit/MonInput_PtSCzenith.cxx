// 
// Class for input of quantity PtSCzenith for monitoring 
// 
// Created by dpaneque on Tue Jul  1 01:21:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PtSCzenith.h"
#include <iostream>

// User defined part 

#define NAME PtSCzenith
#define OUTBRANCH "PtSCzenith"
#define LEAF "PtSCzenith/F"
#define INBRANCH "PtSCzenith"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "current angle between zenith and S/C z-axis (in degrees)"


// End user defined part 

MonInput_PtSCzenith::MonInput_PtSCzenith(){
  m_name=OUTBRANCH;
}
MonInput_PtSCzenith::~MonInput_PtSCzenith(){
}


int MonInput_PtSCzenith::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PtSCzenith::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_PtSCzenith::setValue(TObject* event) {
}
std::string MonInput_PtSCzenith::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PtSCzenith::getDescription(){
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

