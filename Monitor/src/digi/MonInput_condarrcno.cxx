// 
// Class for input of quantity condarrcno for monitoring 
// 
// Created by dpaneque on Sun Jul  1 00:37:40 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_condarrcno.h"
#include <iostream>

// User defined part 

#define NAME condarrcno
#define OUTBRANCH "condarrcno"
#define LEAF "condarrcno/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getCondArrTime().cno()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Condition arrival times for CNO triggers"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_condarrcno::MonInput_condarrcno(){
  m_name=OUTBRANCH;
}
MonInput_condarrcno::~MonInput_condarrcno(){
}


int MonInput_condarrcno::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_condarrcno::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_condarrcno::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_condarrcno::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_condarrcno::getDescription(){
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

