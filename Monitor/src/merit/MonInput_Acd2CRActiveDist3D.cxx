// 
// Class for input of quantity Acd2CRActiveDist3D for monitoring 
// 
// Created by lbaldini on Tue Feb  3 14:17:20 2015 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2CRActiveDist3D.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2CRActiveDist3D
#define OUTBRANCH "Acd2CRActiveDist3D"
#define LEAF "Acd2CRActiveDist3D/F"
#define INBRANCH "Acd2CRActiveDist3D"
#define ACCESSOR NotNeeded
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Acd2CRActiveDist3D"


// End user defined part 

MonInput_Acd2CRActiveDist3D::MonInput_Acd2CRActiveDist3D(){
  m_name=OUTBRANCH;
}
MonInput_Acd2CRActiveDist3D::~MonInput_Acd2CRActiveDist3D(){
}


int MonInput_Acd2CRActiveDist3D::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2CRActiveDist3D::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Acd2CRActiveDist3D::setValue(TObject* event) {
}
std::string MonInput_Acd2CRActiveDist3D::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2CRActiveDist3D::getDescription(){
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

