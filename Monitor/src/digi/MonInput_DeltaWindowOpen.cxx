// 
// Class for input of quantity DeltaWindowOpen for monitoring 
// 
// Created by dpaneque on Wed Oct  3 00:33:15 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DeltaWindowOpen.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME DeltaWindowOpen
#define OUTBRANCH "DeltaWindowOpen"
#define LEAF "DeltaWindowOpen/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getDeltaWindowOpenTime()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "GEM Delta window open time counter: Number of 50 ns ticks between the opening of the trigger window between the previous event and this event."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DeltaWindowOpen::MonInput_DeltaWindowOpen(){
  m_name=OUTBRANCH;
}
MonInput_DeltaWindowOpen::~MonInput_DeltaWindowOpen(){
}


int MonInput_DeltaWindowOpen::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DeltaWindowOpen::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DeltaWindowOpen::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_DeltaWindowOpen::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DeltaWindowOpen::getDescription(){
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

