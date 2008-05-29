// 
// Class for input of quantity CTBParticleType for monitoring 
// 
// Created by dpaneque on Thu May 29 04:19:18 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CTBParticleType.h"
#include <iostream>

// User defined part 

#define NAME CTBParticleType
#define OUTBRANCH "CTBParticleType"
#define LEAF "CTBParticleType/F"
#define INBRANCH "CTBParticleType"
#define ACCESSOR NotAplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Particle type determination; 1 = e+/e-, 2 = proton, 3 = alpha, and 4 = heavy ion"


// End user defined part 

MonInput_CTBParticleType::MonInput_CTBParticleType(){
  m_name=OUTBRANCH;
}
MonInput_CTBParticleType::~MonInput_CTBParticleType(){
}


int MonInput_CTBParticleType::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CTBParticleType::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_CTBParticleType::setValue(TObject* event) {
}
std::string MonInput_CTBParticleType::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CTBParticleType::getDescription(){
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

