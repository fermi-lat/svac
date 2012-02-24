// 
// Class for input of quantity condarrcallo for monitoring 
// 
// Created by kocian on Thu May 31 22:59:44 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_condarrcallo.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME condarrcallo
#define OUTBRANCH "condarrcallo"
#define LEAF "condarrcallo/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getCondArrTime().calLE()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Condition arrival time for CAL-LO"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_condarrcallo::MonInput_condarrcallo(){
  m_name=OUTBRANCH;
}
MonInput_condarrcallo::~MonInput_condarrcallo(){
}


int MonInput_condarrcallo::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_condarrcallo::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_condarrcallo::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_condarrcallo::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_condarrcallo::getDescription(){
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

