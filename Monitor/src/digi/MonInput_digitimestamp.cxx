// 
// Class for input of quantity digitimestamp for monitoring 
// 
// Created by kocian on Fri Apr 20 18:17:48 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_digitimestamp.h"
#include <iostream>

// User defined part 

#define NAME digitimestamp
#define OUTBRANCH "digitimestamp"
#define LEAF "digitimestamp/D"
#define INBRANCH "m_timeStamp"
#define ACCESSOR  getTimeStamp()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Time stamp from Digi Event"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_digitimestamp::MonInput_digitimestamp(){
  m_name=OUTBRANCH;
}
MonInput_digitimestamp::~MonInput_digitimestamp(){
}


int MonInput_digitimestamp::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_digitimestamp::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_digitimestamp::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_digitimestamp::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_digitimestamp::getDescription(){
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

