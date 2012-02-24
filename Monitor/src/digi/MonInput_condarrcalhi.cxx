// 
// Class for input of quantity condarrcalhi for monitoring 
// 
// Created by kocian on Thu May 31 23:00:27 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_condarrcalhi.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME condarrcalhi
#define OUTBRANCH "condarrcalhi"
#define LEAF "condarrcalhi/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getCondArrTime().calHE()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Condition arrival time for CAL-HI"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_condarrcalhi::MonInput_condarrcalhi(){
  m_name=OUTBRANCH;
}
MonInput_condarrcalhi::~MonInput_condarrcalhi(){
}


int MonInput_condarrcalhi::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_condarrcalhi::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_condarrcalhi::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_condarrcalhi::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_condarrcalhi::getDescription(){
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

