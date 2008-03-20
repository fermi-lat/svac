// 
// Class for input of quantity Tkr1KalEne for monitoring 
// 
// Created by dpaneque on Wed Mar 19 03:21:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Tkr1KalEne.h"
#include <iostream>

// User defined part 

#define NAME Tkr1KalEne
#define OUTBRANCH "Tkr1KalEne"
#define LEAF "Tkr1KalEne/F"
#define INBRANCH "Tkr1KalEne"
#define ACCESSOR notneeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Kalman energy of track 1; this is the energy determined from the multiple scattering along the track (goes like 1/E)."


// End user defined part 

MonInput_Tkr1KalEne::MonInput_Tkr1KalEne(){
  m_name=OUTBRANCH;
}
MonInput_Tkr1KalEne::~MonInput_Tkr1KalEne(){
}


int MonInput_Tkr1KalEne::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Tkr1KalEne::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Tkr1KalEne::setValue(TObject* event) {
}
std::string MonInput_Tkr1KalEne::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Tkr1KalEne::getDescription(){
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

