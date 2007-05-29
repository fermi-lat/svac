// 
// Class for input of quantity numvetotiles for monitoring 
// 
// Created by kocian on Mon May 28 00:10:38 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_numvetotiles.h"
#include <iostream>

// User defined part 

#define NAME numvetotiles
#define OUTBRANCH "numvetotiles"
#define LEAF "numvetotiles/s"
#define INBRANCH "m_gem"
#define ACCESSOR bla
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of asserted veto tiles in GEM vector"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_numvetotiles::MonInput_numvetotiles(){
  m_name=OUTBRANCH;
}
MonInput_numvetotiles::~MonInput_numvetotiles(){
}


int MonInput_numvetotiles::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_numvetotiles::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_numvetotiles::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  const GemTileList& tl=de->getGem().getTileList();
  UShort_t xzm=tl.getXzm();
  UShort_t yzm=tl.getYzm();
  UShort_t xzp=tl.getXzp();
  UShort_t yzp=tl.getYzp();
  UInt_t xy=tl.getXy();
  UShort_t rbn=tl.getRbn();
  m_val=0;
  for (int i=0;i<8;i++){
    if(xzm&(1<<i))m_val++;
    if(xzp&(1<<i))m_val++;
    if(yzm&(1<<i))m_val++;
    if(yzp&(1<<i))m_val++;
    if(xy&(1<<i))m_val++;
    if(rbn&(1<<i))m_val++;
  }
  m_val=0;
  for (int i=8;i<16;i++){
    if(xzm&(1<<i))m_val++;
    if(xzp&(1<<i))m_val++;
    if(yzm&(1<<i))m_val++;
    if(yzp&(1<<i))m_val++;
    if(xy&(1<<i))m_val++;
  }
  for (int i=16;i<25;i++){
    if(xy&(1<<i))m_val++;
  }
    
}
std::string MonInput_numvetotiles::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_numvetotiles::getDescription(){
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

