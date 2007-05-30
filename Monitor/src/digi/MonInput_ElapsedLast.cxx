// 
// Class for input of quantity ElapsedLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:46:29 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ElapsedLast.h"
#include <iostream>

// User defined part 

#define NAME ElapsedLast
#define OUTBRANCH "ElapsedLast"
#define LEAF "ElapsedLast/l"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().scalers().elapsed()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Total elapsed time since the start the run in 50 ns ticks"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_ElapsedLast::MonInput_ElapsedLast(){
}
MonInput_ElapsedLast::~MonInput_ElapsedLast(){
}


int MonInput_ElapsedLast::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_ElapsedLast::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ElapsedLast::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_ElapsedLast::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ElapsedLast::getDescription(){
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

