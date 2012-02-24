// 
// Class for input of digi quantity nAcd for monitoring 
// 
// Martin Kocian, SLAC, 2/1/07
// Software developed for GLAST

#include "MonInput_nAcd.h"
#include <iostream>
#include <cassert>

//user defined part

#define NAME nACD
#define OUTBRANCH "nACD"
#define LEAF "nACD/I"
#define VARTYPE Int_t
#define INBRANCH "m_acd*"
#define ACCESSOR getAcdDigiCol()->GetEntries()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of ACD tiles hit"
#include "digiRootData/DigiEvent.h"

//end user defined part

MonInput_nAcd::MonInput_nAcd(){
  m_name=OUTBRANCH;
}
MonInput_nAcd::~MonInput_nAcd(){
}


int MonInput_nAcd::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_nAcd::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_nAcd::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_nAcd::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_nAcd::getDescription(){
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
