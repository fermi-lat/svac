// 
// Class for input of quantity LivetimeLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:39:12 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_LivetimeLast.h"
#include <iostream>

// User defined part 

#define NAME LivetimeLast
#define OUTBRANCH "LivetimeLast"
#define LEAF "LivetimeLast/l"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().scalers().livetime()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Elapsed livetime since the start of the run in 50 ns ticks"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_LivetimeLast::MonInput_LivetimeLast(){
}
MonInput_LivetimeLast::~MonInput_LivetimeLast(){
}


int MonInput_LivetimeLast::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_LivetimeLast::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_LivetimeLast::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_LivetimeLast::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_LivetimeLast::getDescription(){
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

