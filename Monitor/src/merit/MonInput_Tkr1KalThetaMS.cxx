// 
// Class for input of quantity Tkr1KalThetaMS for monitoring 
// 
// Created by dpaneque on Wed Mar 19 03:23:17 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Tkr1KalThetaMS.h"
#include <iostream>

// User defined part 

#define NAME Tkr1KalThetaMS
#define OUTBRANCH "Tkr1KalThetaMS"
#define LEAF "Tkr1KalThetaMS/F"
#define INBRANCH "Tkr1KalThetaMS"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Multiple scattering angle (radians) referenced to first layer. The contributions from all the layers in the track are adjusted for the predicted energy in each layer, and weighted accordingly. So the result is sensitive to the particle type and the chosen energy-loss mechanism."


// End user defined part 

MonInput_Tkr1KalThetaMS::MonInput_Tkr1KalThetaMS(){
  m_name=OUTBRANCH;
}
MonInput_Tkr1KalThetaMS::~MonInput_Tkr1KalThetaMS(){
}


int MonInput_Tkr1KalThetaMS::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Tkr1KalThetaMS::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Tkr1KalThetaMS::setValue(TObject* event) {
}
std::string MonInput_Tkr1KalThetaMS::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Tkr1KalThetaMS::getDescription(){
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

