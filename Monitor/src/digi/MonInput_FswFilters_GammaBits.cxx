// 
// Class for input of quantity FswFilters_GammaBits for monitoring 
// 
// Created by dpaneque on Sun May 25 23:31:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FswFilters_GammaBits.h"
#include <iostream>

// User defined part 

#define NAME FswFilters_GammaBits
#define OUTBRANCH "FswFilters_GammaBits"
#define LEAF "FswFilters_GammaBits[32]/I"
#define INBRANCH "XXXX" Replace with real name
#define ACCESSOR NotAplicable
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "bb"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_FswFilters_GammaBits::MonInput_FswFilters_GammaBits(){
  m_name=OUTBRANCH;
}
MonInput_FswFilters_GammaBits::~MonInput_FswFilters_GammaBits(){
}


int MonInput_FswFilters_GammaBits::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FswFilters_GammaBits::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_FswFilters_GammaBits::setValue(TObject* event) {
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

  // Real filter status bits:
 
  const LpaGammaFilter* gamma = (LpaGammaFilter*)de->getLpaHandler()->getHandler(enums::Lsf::GAMMA);
  if (gamma) {
    UInt_t filterbit = = gamma->getStatus();
    // gamma_statusword is your 32-bit word
    for (int iBit = 0; iBit < 32; iBit++) {
      if ((filterbit >> iBit) & 1) 
	m_val[iBit] = 1;
      else
	m_val[iBit] = 0;
    }
  }
  
}

std::string MonInput_FswFilters_GammaBits::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FswFilters_GammaBits::getDescription(){
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

