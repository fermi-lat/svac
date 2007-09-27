// 
// Class for input of quantity FilterBits for monitoring 
// 
// Created by dpaneque on Thu Sep 27 18:08:37 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FilterBits.h"
#include <iostream>

// User defined part 

#define NAME FilterBits
#define OUTBRANCH "FilterBits"
#define LEAF "FilterBits[32]/O"
#define INBRANCH "m_obfFilterStatus"
// #define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [32] containing the OBF filter bits."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_FilterBits::MonInput_FilterBits(){
  m_name=OUTBRANCH;
}
MonInput_FilterBits::~MonInput_FilterBits(){
}


int MonInput_FilterBits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FilterBits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_FilterBits::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  
  // initialize to -1 (= filter could not be computed for this event)
  for(UShort_t i = 0; i < 32; i++)
    m_val[i]=-1;

  // if event passed any of the filters, the corresponding component of the vector is set to 1, otherwise
  // the component is set to zero. If the filters could not run properly, then the default value (=-1) is left.

  if (de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::GammaFilter) != 0) 
    {// filter was successfully applied
      UInt_t filterbit = de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::GammaFilter)->getStatus32();

      for (int iBit = 0; iBit < 32; iBit++) {
	if ((filterbit >> iBit) & 1) 
	  m_val[iBit] = 1;
	else
	  m_val[iBit] = 0;
      }
    }
}
std::string MonInput_FilterBits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FilterBits::getDescription(){
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

