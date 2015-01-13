// 
// Class for input of quantity CalTrackAngle for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:42:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalTrackAngle.h"
#include <iostream>

// User defined part 

#define NAME CalTrackAngle
#define OUTBRANCH "CalTrackAngle"
#define LEAF "CalTrackAngle/F"
#define INBRANCH "CalTrackAngle"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Angle between 'gamma' direction in the tracker and direction of the CAL 'track'."


// End user defined part 

MonInput_CalTrackAngle::MonInput_CalTrackAngle(){
  m_name=OUTBRANCH;
}
MonInput_CalTrackAngle::~MonInput_CalTrackAngle(){
}


int MonInput_CalTrackAngle::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalTrackAngle::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CalTrackAngle::setValue(TObject* event) {
}
std::string MonInput_CalTrackAngle::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalTrackAngle::getDescription(){
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

