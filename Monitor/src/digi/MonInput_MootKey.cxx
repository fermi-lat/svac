// 
// Class for input of quantity MootKey for monitoring 
// 
// Created by dpaneque on Thu Jul 17 22:33:04 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_MootKey.h"
#include <iostream>

// User defined part 

#define NAME MootKey
#define OUTBRANCH "MootKey"
#define LEAF "MootKey/i"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().mootKey() 
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "The Moot Key"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_MootKey::MonInput_MootKey(){
  m_name=OUTBRANCH;
}
MonInput_MootKey::~MonInput_MootKey(){
}


int MonInput_MootKey::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_MootKey::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_MootKey::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_MootKey::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_MootKey::getDescription(){
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

