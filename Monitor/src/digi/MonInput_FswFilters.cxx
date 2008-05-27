// 
// Class for input of quantity FswFilters for monitoring 
// 
// Created by dpaneque on Sat May 24 21:39:00 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FswFilters.h"
#include <iostream>

// User defined part 

#define NAME FswFilters
#define OUTBRANCH "FswFilters"
#define LEAF "FswFilters[5]/I"
#define INBRANCH "m_metaEvent"
#define ACCESSOR NotAplicable
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [5] containing the status of the following Flight Sowftware Onboard Filters: Gamma, Mip, Hip, DGN, PassThru; which correspond to the vector indices 0,1,2,3,4 respectively. The status are the following ones: 0=Evt did not pass filter; 1=Evt did pass the filter; -1=Filter could not be computed for this event."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_FswFilters::MonInput_FswFilters(){
  m_name=OUTBRANCH;
}
MonInput_FswFilters::~MonInput_FswFilters(){
}


int MonInput_FswFilters::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FswFilters::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_FswFilters::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  // initialize to -1 (= filter could not be computed for this event)
  for(UShort_t i = 0; i < 5; i++)
    m_val[i]=-1; 

  // if event passed any of the filters, the corresponding component of the vector is set to 1, otherwise
  // the component is set to zero. If the filters could not run properly, then the default value (=-1) is left.

  // Gamma filter
 
  const LpaGammaFilter *gam = de->getGammaFilter();
  if(gam){
    if(gam->passed())
      m_val[0] = 1;
    else
      m_val[0] = 0; // It did NOT passed
  }
  
   // Mip filter
  const LpaMipFilter *mip = de->getMipFilter(); 
  if(mip){
    if(mip->passed())
      m_val[1] = 1;
    else
      m_val[1] = 0; // It did NOT passed
  }

   // HIp filter
  const LpaHipFilter *hip = de->getHipFilter();
  if(hip){
    if(hip->passed())
      m_val[2] = 1;
    else
      m_val[2] = 0; // It did NOT passed
  }

   // DGN filter
  const LpaDgnFilter *dgn = de->getDgnFilter();
  if(dgn){
    if(dgn->passed())
      m_val[3] = 1;
    else
      m_val[3] = 0; // It did NOT passed
  }
 
  const LpaPassthruFilter *pass = de->getPassthruFilter();
  if(pass){
    if(pass->passed())
      m_val[4] = 1;
    else
      m_val[4] = 0;
  }

 

}

std::string MonInput_FswFilters::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FswFilters::getDescription(){
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

