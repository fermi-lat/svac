// 
// Class for input of quantity FT1EarthAzimuth for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:11:46 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1EarthAzimuth.h"
#include <iostream>

// User defined part 

#define NAME FT1EarthAzimuth
#define OUTBRANCH "FT1EarthAzimuth"
#define LEAF "FT1EarthAzimuth/F"
#define INBRANCH "FT1EarthAzimuth"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Reconstructed azimuth angle (in deg) with respect to the local zenith angle."


// End user defined part 

MonInput_FT1EarthAzimuth::MonInput_FT1EarthAzimuth(){
  m_name=OUTBRANCH;
}
MonInput_FT1EarthAzimuth::~MonInput_FT1EarthAzimuth(){
}


int MonInput_FT1EarthAzimuth::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1EarthAzimuth::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_FT1EarthAzimuth::setValue(TObject* event) {
}
std::string MonInput_FT1EarthAzimuth::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1EarthAzimuth::getDescription(){
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

