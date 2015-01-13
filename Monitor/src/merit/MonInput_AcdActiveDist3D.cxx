// 
// Class for input of quantity AcdActiveDist3D for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:09:28 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdActiveDist3D.h"
#include <iostream>

// User defined part 

#define NAME AcdActiveDist3D
#define OUTBRANCH "AcdActiveDist3D"
#define LEAF "AcdActiveDist3D/F"
#define INBRANCH "AcdActiveDist3D"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Largest active distance of any track to the edge of any tile"


// End user defined part 

MonInput_AcdActiveDist3D::MonInput_AcdActiveDist3D(){
  m_name=OUTBRANCH;
}
MonInput_AcdActiveDist3D::~MonInput_AcdActiveDist3D(){
}


int MonInput_AcdActiveDist3D::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdActiveDist3D::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_AcdActiveDist3D::setValue(TObject* event) {
}
std::string MonInput_AcdActiveDist3D::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdActiveDist3D::getDescription(){
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

