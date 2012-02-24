// 
// Class for input of quantity AcdGemROI_Tower for monitoring 
// 
// Created by dpaneque on Mon Jun  4 22:59:56 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdGemROI_Tower.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME AcdGemROI_Tower
#define OUTBRANCH "AcdGemROI_Tower"
#define LEAF "AcdGemROI_Tower[16]/O"
#define INBRANCH "m_gem"
// #define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [tower] reporting about the existence (1) or not (0) of a ACD GEM ROI"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdGemROI_Tower::MonInput_AcdGemROI_Tower(){
  m_name=OUTBRANCH;
}
MonInput_AcdGemROI_Tower::~MonInput_AcdGemROI_Tower(){
}


int MonInput_AcdGemROI_Tower::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdGemROI_Tower::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdGemROI_Tower::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  
  const UShort_t ntower = 16;
  for (UShort_t i =0; i<ntower;i++)
    m_val[i] = 0;

  const Gem& gem = de->getGem();

  UShort_t roiVect = gem.getRoiVector();
  for ( UInt_t iRoiIdx(0); iRoiIdx < ntower; iRoiIdx++ ) {
    if ( roiVect & ( 1 << iRoiIdx ) ) m_val[iRoiIdx]++;
  } 


}
std::string MonInput_AcdGemROI_Tower::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdGemROI_Tower::getDescription(){
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

