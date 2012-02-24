// 
// Class for input of quantity filterstatus_hi for monitoring 
// 
// Created by kocian on Fri Apr 20 19:52:10 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_filterstatus_hi.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME filterstatus_hi
#define OUTBRANCH "filterstatus_hi"
#define LEAF "filterstatus_hi/i"
#define INBRANCH "m_obf"
#define ACCESSOR getFilterStatus().getHigh()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Onboard filter status from Gleam"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_filterstatus_hi::MonInput_filterstatus_hi(){
  m_name=OUTBRANCH;
}
MonInput_filterstatus_hi::~MonInput_filterstatus_hi(){
}


int MonInput_filterstatus_hi::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_filterstatus_hi::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_filterstatus_hi::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_filterstatus_hi::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_filterstatus_hi::getDescription(){
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

