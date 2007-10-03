// 
// Class for input of quantity AcdGemVeto_AcdTile for monitoring 
// 
// Created by dpaneque on Mon Jun  4 22:34:02 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdGemVeto_AcdTile.h"
#include <iostream>

// User defined part 

#define NAME AcdGemVeto_AcdTile
#define OUTBRANCH "AcdGemVeto_AcdTile"
#define LEAF "AcdGemVeto_AcdTile[128]/O"
#define INBRANCH "m_gem"
// #define ACCESSOR Capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [AcdTile] reporting about the existence (1) or not (0) of a ACD GEM Veto"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdGemVeto_AcdTile::MonInput_AcdGemVeto_AcdTile(){
  m_name=OUTBRANCH;
}
MonInput_AcdGemVeto_AcdTile::~MonInput_AcdGemVeto_AcdTile(){
}


int MonInput_AcdGemVeto_AcdTile::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdGemVeto_AcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdGemVeto_AcdTile::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  const UShort_t n_acdtiles = 128;
  // initialize vector for this event
  for(UShort_t i = 0; i < n_acdtiles; i++)
    m_val[i] = 0;

  const Gem& gem = de->getGem();
  const GemTileList& gemTL = gem.getTileList();
  for ( UInt_t iGemIdx(0); iGemIdx < 16; iGemIdx++ ) {
    // unfold the contribuions into a single vector
    if ( gemTL.getXzm() & ( 1 << iGemIdx ) )     m_val[iGemIdx]++;
    if ( gemTL.getXzp() & ( 1 << iGemIdx ) )     m_val[iGemIdx+16]++;
    if ( gemTL.getYzm() & ( 1 << iGemIdx ) )     m_val[iGemIdx+32]++;
    if ( gemTL.getYzp() & ( 1 << iGemIdx ) )     m_val[iGemIdx+48]++;
    if ( gemTL.getXy() & ( 1 << iGemIdx ) )      m_val[iGemIdx+64]++;
    if ( gemTL.getXy() & ( 1 << (16+iGemIdx) ) ) m_val[iGemIdx+80]++;
    if ( gemTL.getRbn() & ( 1 << iGemIdx ) )     m_val[iGemIdx+96]++;
    if ( gemTL.getNa() & ( 1 << iGemIdx ) )      m_val[iGemIdx+112]++;
  }  

    



}
std::string MonInput_AcdGemVeto_AcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdGemVeto_AcdTile::getDescription(){
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

