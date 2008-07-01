// 
// Class for input of quantity OBFStatus for monitoring 
// 
// Created by dpaneque on Wed Sep 26 01:24:44 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_OBFStatus.h"
#include <iostream>

// User defined part 

#define NAME OBFStatus
#define OUTBRANCH "OBFStatus"
#define LEAF "OBFStatus[4]/I"
#define INBRANCH "m_obfFilterStatus"
//#define ACCESSOR Capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [4] containing the status of the following Onboard Filters: Gamma, Mip, Hip, Dgn; which correspond to the vector indices 0,1,2,3, respectively. The status are the following ones: 0=Evt did not pass filter; 1=Evt did pass the filter; -1=Filter could not be computed for this event."
#include "digiRootData/DigiEvent.h"

// End user defined part 

// tmp for debug
  /*
int MonInput_OBFStatus::gfcounter = 0;
int MonInput_OBFStatus::mipfcounter = 0;
int MonInput_OBFStatus::mipgfcounter = 0;
*/
  // end of tmp for debug


// endtmp

MonInput_OBFStatus::MonInput_OBFStatus(){
  m_name=OUTBRANCH;
}
MonInput_OBFStatus::~MonInput_OBFStatus(){
}


int MonInput_OBFStatus::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_OBFStatus::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_OBFStatus::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  // initialize to -1 (= filter could not be computed for this event)
  for(UShort_t i = 0; i < 4; i++)
    m_val[i]=-1;

  // if event passed any of the filters, the corresponding component of the vector is set to 1, otherwise
  // the component is set to zero. If the filters could not run properly, then the default value (=-1) is left.

  // Gamma filter

   if (de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::GammaFilter) != 0) {
     
    UChar_t m_gammaStatus = de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::GammaFilter)->getFiltersb();
    int m_gammaStatusInt = m_gammaStatus>>4;
    if (m_gammaStatusInt==0 || m_gammaStatusInt==6) {
      //it means it passed or was leaked by the gamma-filter
      m_val[0] = 1;
    }
    else
      m_val[0] = 0;
   }


 

  // Mip filter 
  
   if (de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::MipFilter) != 0) {
    UChar_t m_mipStatus = de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::MipFilter)->getFiltersb();
    int m_mipStatusInt = m_mipStatus>>4;
    if (m_mipStatusInt==0 || m_mipStatusInt==6) {
      //it means it passed or was leaked by the MIP-filter
      m_val[1] = 1;
    }
    else
       m_val[1] = 0;
  }

  // Hip filter
  
   if (de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::HipFilter) != 0) {
    UChar_t m_hipStatus = de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::HipFilter)->getFiltersb();
    int m_hipStatusInt = m_hipStatus>>4;
    if (m_hipStatusInt==0 || m_hipStatusInt==6) {
      //it means it passed or was leaked by the HIP-filter
      m_val[2] = 1;
    }
    else
      m_val[2] = 0;
  }


  // Dgn filter
  
   if (de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::DgnFilter) != 0) {
    UChar_t m_dgnStatus = de->getObfFilterStatus().getFilterStatus(ObfFilterStatus::DgnFilter)->getFiltersb();
    int m_dgnStatusInt = m_dgnStatus>>4;
    if (m_dgnStatusInt==0 || m_dgnStatusInt==6) {
      //it means it passed or was leaked by the DGN-filter
       m_val[3] = 1;
    }
    else
      m_val[3] = 0;
  }



 







}
std::string MonInput_OBFStatus::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_OBFStatus::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
//#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

