// 
// Class for input of quantity acdLowerTileCount for monitoring 
// 
// Created by kocian on Tue Mar  6 21:10:00 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_acdLowerTileCount.h"
#include <iostream>

// User defined part 

#define NAME acdLowerTileCount
#define OUTBRANCH "acdLowerTileCount"
#define LEAF "acdLowerTileCount/F"
#define INBRANCH "CTBAcdLowerTileCount"
#define ACCESSOR CTBAcdLowerTileCount
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Count of lower ACD tiles"
#include "../MeritEvent.h"

// End user defined part 

MonInput_acdLowerTileCount::MonInput_acdLowerTileCount(){
}
MonInput_acdLowerTileCount::~MonInput_acdLowerTileCount(){
}


int MonInput_acdLowerTileCount::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_acdLowerTileCount::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_acdLowerTileCount::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_acdLowerTileCount::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_acdLowerTileCount::getDescription(){
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

