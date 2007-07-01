// 
// Class for input of quantity condarrtkr for monitoring 
// 
// Created by dpaneque on Sun Jul  1 00:36:38 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_condarrtkr.h"
#include <iostream>

// User defined part 

#define NAME condarrtkr
#define OUTBRANCH "condarrtkr"
#define LEAF "condarrtkr/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getCondArrTime().tkr()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Condition arrival time for TKR Triggers"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_condarrtkr::MonInput_condarrtkr(){
  m_name=OUTBRANCH;
}
MonInput_condarrtkr::~MonInput_condarrtkr(){
}


int MonInput_condarrtkr::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_condarrtkr::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_condarrtkr::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_condarrtkr::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_condarrtkr::getDescription(){
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

