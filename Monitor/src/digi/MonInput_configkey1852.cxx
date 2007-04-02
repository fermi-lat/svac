// 
// Class for input of quantity configkey1852 for monitoring 
// 
// Created by kocian on Fri Mar 30 18:25:24 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_configkey1852.h"
#include <iostream>

// User defined part 

#define NAME configkey1852
#define OUTBRANCH "configkey1852"
#define LEAF "configkey1852/i"
#define INBRANCH "m_metaEvent"
#define ACCESSOR 
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_configkey1852::MonInput_configkey1852(){
}
MonInput_configkey1852::~MonInput_configkey1852(){
}


int MonInput_configkey1852::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_configkey1852::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_configkey1852::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= 1852;
}
std::string MonInput_configkey1852::getInputSource(){
  return INPUTSOURCE;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE

