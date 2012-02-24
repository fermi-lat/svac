// 
// Class for input of quantity DiscardedLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:43:54 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DiscardedLast.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME DiscardedLast
#define OUTBRANCH "DiscardedLast"
#define LEAF "DiscardedLast/l"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().scalers().discarded()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of events discarded because they arrived in deadtime"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DiscardedLast::MonInput_DiscardedLast(){
  m_name=OUTBRANCH;
}
MonInput_DiscardedLast::~MonInput_DiscardedLast(){
}


int MonInput_DiscardedLast::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DiscardedLast::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DiscardedLast::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_DiscardedLast::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DiscardedLast::getDescription(){
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

