// 
// Class for input of quantity AcdGemCNO_GARC for monitoring 
// 
// Created by dpaneque on Mon Jun  4 23:09:49 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdGemCNO_GARC.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME AcdGemCNO_GARC
#define OUTBRANCH "AcdGemCNO_GARC"
#define LEAF "AcdGemCNO_GARC[12]/O"
#define INBRANCH "m_gem"
#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [GARC] reporting about the existence (1) or not (0) of a ACD CNO trigger"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdGemCNO_GARC::MonInput_AcdGemCNO_GARC(){
  m_name=OUTBRANCH;
}
MonInput_AcdGemCNO_GARC::~MonInput_AcdGemCNO_GARC(){
}


int MonInput_AcdGemCNO_GARC::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdGemCNO_GARC::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdGemCNO_GARC::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  
  const UShort_t ngarc = 12;
  for (UShort_t i = 0; i < ngarc;i++)
    m_val[i] = 0;

  const Gem& gem = de->getGem();

  UShort_t cnoVect = gem.getCnoVector();
  for ( UInt_t iCnoIdx(0); iCnoIdx < ngarc; iCnoIdx++ ) {
    if ( cnoVect & ( 1 << iCnoIdx ) ) m_val[iCnoIdx]++;
  } 

}
std::string MonInput_AcdGemCNO_GARC::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdGemCNO_GARC::getDescription(){
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

