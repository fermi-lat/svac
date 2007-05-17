// 
// Class for input of quantity Gem_elapsed for monitoring 
// 
// Created by kocian on Fri Mar  9 19:50:55 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Gem_elapsed.h"
#include <iostream>

// User defined part 

#define NAME Gem_elapsed
#define OUTBRANCH "Gem_elapsed"
#define LEAF "Gem_elapsed/l"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().scalers().elapsed()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Gem trigger time"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_Gem_elapsed::MonInput_Gem_elapsed(){
  m_name=OUTBRANCH;
}
MonInput_Gem_elapsed::~MonInput_Gem_elapsed(){
}


int MonInput_Gem_elapsed::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Gem_elapsed::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_Gem_elapsed::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_Gem_elapsed::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Gem_elapsed::getDescription(){
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

