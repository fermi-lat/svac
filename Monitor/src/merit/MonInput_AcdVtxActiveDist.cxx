// 
// Class for input of quantity AcdVtxActiveDist for monitoring 
// 
// Created by dpaneque on Wed Mar 12 21:15:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdVtxActiveDist.h"
#include <iostream>

// User defined part 

#define NAME AcdVtxActiveDist
#define OUTBRANCH "AcdVtxActiveDist"
#define LEAF "AcdVtxActiveDist/F"
#define INBRANCH "AcdVtxActiveDist"
#define ACCESSOR cc
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Largest active distance from vertex extrapolation to the edge of any tile"


// End user defined part 

MonInput_AcdVtxActiveDist::MonInput_AcdVtxActiveDist(){
  m_name=OUTBRANCH;
}
MonInput_AcdVtxActiveDist::~MonInput_AcdVtxActiveDist(){
}


int MonInput_AcdVtxActiveDist::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdVtxActiveDist::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdVtxActiveDist::setValue(TObject* event) {
}
std::string MonInput_AcdVtxActiveDist::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdVtxActiveDist::getDescription(){
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

