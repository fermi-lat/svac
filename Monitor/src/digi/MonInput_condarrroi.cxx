// 
// Class for input of quantity condarrroi for monitoring 
// 
// Created by dpaneque on Sun Jul  1 00:38:14 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_condarrroi.h"
#include <iostream>

// User defined part 

#define NAME condarrroi
#define OUTBRANCH "condarrroi"
#define LEAF "condarrroi/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getCondArrTime().roi()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Condition arrival times for ROI triggers"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_condarrroi::MonInput_condarrroi(){
  m_name=OUTBRANCH;
}
MonInput_condarrroi::~MonInput_condarrroi(){
}


int MonInput_condarrroi::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_condarrroi::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_condarrroi::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_condarrroi::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_condarrroi::getDescription(){
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

