// 
// Class for input of quantity ntkrdigis for monitoring 
// 
// Created by kocian on Mon Apr 23 17:13:41 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ntkrdigis.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME ntkrdigis
#define OUTBRANCH "ntkrdigis"
#define LEAF "ntkrdigis/I"
#define INBRANCH "m_tkrDigiCol"
#define ACCESSOR  getTkrDigiCol()->GetEntries()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of TKR digis"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_ntkrdigis::MonInput_ntkrdigis(){
  m_name=OUTBRANCH;
}
MonInput_ntkrdigis::~MonInput_ntkrdigis(){
}


int MonInput_ntkrdigis::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_ntkrdigis::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ntkrdigis::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_ntkrdigis::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ntkrdigis::getDescription(){
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

