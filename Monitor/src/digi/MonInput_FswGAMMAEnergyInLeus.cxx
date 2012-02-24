// 
// Class for input of quantity FswGAMMAEnergyInLeus for monitoring 
// 
// Created by dpaneque on Mon Aug 11 16:37:56 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FswGAMMAEnergyInLeus.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME FswGAMMAEnergyInLeus
#define OUTBRANCH "FswGAMMAEnergyInLeus"
#define LEAF "FswGAMMAEnergyInLeus[2]/F"
#define INBRANCH "m_metaEvent"
#define ACCESSOR bbb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vecrtor [2] reporting Fsw Gamma energy in Leus (vector index 0) and the validity of such energy (vector index 1). If it is valid, the value is set to zero, otherwise 1."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_FswGAMMAEnergyInLeus::MonInput_FswGAMMAEnergyInLeus(){
  m_name=OUTBRANCH;
}
MonInput_FswGAMMAEnergyInLeus::~MonInput_FswGAMMAEnergyInLeus(){
}


int MonInput_FswGAMMAEnergyInLeus::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FswGAMMAEnergyInLeus::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_FswGAMMAEnergyInLeus::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

   // initialize to -1 (= filter could not be computed for this event)
  for(UShort_t i = 0; i < 2; i++)
    m_val[i]=-1.0; 

  // if event passed any of the filters, the corresponding component of the vector is set to 1, otherwise
  // the component is set to zero. If the filters could not run properly, then the default value (=-1) is left.

  // Gamma filter
 
  const LpaGammaFilter *gam = de->getGammaFilter();
  if(gam){
    if (gam->has()) {
      m_val[0] = gam->getEnergyInLeus();
      if(gam->getEnergyValid()) 
	m_val[1]= 1;
      else
	m_val[1]= 0;
    }
  }


}
std::string MonInput_FswGAMMAEnergyInLeus::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FswGAMMAEnergyInLeus::getDescription(){
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

