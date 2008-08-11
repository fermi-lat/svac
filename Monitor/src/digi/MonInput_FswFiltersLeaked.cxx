// 
// Class for input of quantity FswFiltersLeaked for monitoring 
// 
// Created by dpaneque on Mon Aug 11 16:24:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FswFiltersLeaked.h"
#include <iostream>

// User defined part 

#define NAME FswFiltersLeaked
#define OUTBRANCH "FswFiltersLeaked"
#define LEAF "FswFiltersLeaked[5]/I"
#define INBRANCH "m_metaEvent"
#define ACCESSOR bbb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [5] containing the status of the following Flight Sowftware Onboard Filters that were LEAKED: Gamma, Mip, Hip, DGN, PassThru; which correspond to the vector indices 0,1,2,3,4 respectively. The status are the following ones: 0=Evt was not leaked; 1=Evt leaked this filter; -1=Filter could not be computed for this event."
#include "digiRootData/DigiEvent.h"


// End user defined part 

MonInput_FswFiltersLeaked::MonInput_FswFiltersLeaked(){
  m_name=OUTBRANCH;
}
MonInput_FswFiltersLeaked::~MonInput_FswFiltersLeaked(){
}


int MonInput_FswFiltersLeaked::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FswFiltersLeaked::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_FswFiltersLeaked::setValue(TObject* event) {
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
    if(gam->leaked())
      m_val[0] = 1;
    else
      m_val[0] = 0; // It did NOT passed
  }
  
   // Mip filter
  const LpaMipFilter *mip = de->getMipFilter(); 
  if(mip){
    if(mip->leaked())
      m_val[1] = 1;
    else
      m_val[1] = 0; // It did NOT passed
  }

   // HIp filter
  const LpaHipFilter *hip = de->getHipFilter();
  if(hip){
    if(hip->leaked())
      m_val[2] = 1;
    else
      m_val[2] = 0; // It did NOT passed
  }

   // DGN filter
  const LpaDgnFilter *dgn = de->getDgnFilter();
  if(dgn){
    if(dgn->leaked())
      m_val[3] = 1;
    else
      m_val[3] = 0; // It did NOT passed
  }

  const LpaHandler& thislpahandler=de->getLpaHandler();
  const LpaPassthruFilter* pass = thislpahandler.getPassthruFilter();

  if(pass){
    if(1)//pass->passed())
      m_val[4] = 1;
    else
      m_val[4] = 0;
  }


}
std::string MonInput_FswFiltersLeaked::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FswFiltersLeaked::getDescription(){
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

