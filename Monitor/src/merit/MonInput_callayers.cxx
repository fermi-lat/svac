// 
// Class for input of quantity callayers for monitoring 
// 
// Created by kocian on Wed May 30 18:47:05 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_callayers.h"
#include <iostream>

// User defined part 

#define NAME callayers
#define OUTBRANCH "callayers"
#define LEAF "callayers[8]/F"
#define INBRANCH "CalELayer*"
#define ACCESSOR asdf
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Cal energy per layer"
#include "../MeritEvent.h"

// End user defined part 

MonInput_callayers::MonInput_callayers(){
  m_name=OUTBRANCH;
}
MonInput_callayers::~MonInput_callayers(){
}


int MonInput_callayers::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_callayers::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_callayers::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
    m_val[0]= de->CalELayer0;
    m_val[1]= de->CalELayer1;
    m_val[2]= de->CalELayer2;
    m_val[3]= de->CalELayer3;
    m_val[4]= de->CalELayer4;
    m_val[5]= de->CalELayer5;
    m_val[6]= de->CalELayer6;
    m_val[7]= de->CalELayer7;
}
std::string MonInput_callayers::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_callayers::getDescription(){
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

