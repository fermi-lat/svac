// 
// Class for input of quantity AcdTkr1ActiveDist for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:34:14 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdTkr1ActiveDist.h"
#include <iostream>

// User defined part 

#define NAME AcdTkr1ActiveDist
#define OUTBRANCH "AcdTkr1ActiveDist"
#define LEAF "AcdTkr1ActiveDist/F"
#define INBRANCH "AcdTkr1ActiveDist"
#define ACCESSOR 3
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Largest active distance from track 1 to the edge of any tile"


// End user defined part 

MonInput_AcdTkr1ActiveDist::MonInput_AcdTkr1ActiveDist(){
  m_name=OUTBRANCH;
}
MonInput_AcdTkr1ActiveDist::~MonInput_AcdTkr1ActiveDist(){
}


int MonInput_AcdTkr1ActiveDist::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdTkr1ActiveDist::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdTkr1ActiveDist::setValue(TObject* event) {
}
std::string MonInput_AcdTkr1ActiveDist::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdTkr1ActiveDist::getDescription(){
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

