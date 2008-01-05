// 
// Class for input of quantity DatagramInfo for monitoring 
// 
// Created by dpaneque on Mon Dec 17 21:08:27 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DatagramInfo.h"
#include <iostream>

// User defined part 

#define NAME DatagramInfo
#define OUTBRANCH "DatagramInfo"
#define LEAF "DatagramInfo[2]/I"
#define INBRANCH "m_metaEvent"
#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector[2] containing the crate number (first component; 0=Epu0, 1=Epu1, 2=Epu2, 3=Siu0, 4=Siu1) and the datagram number (second component; m_digiEvent->getMetaEvent().datagram().datagrams())."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DatagramInfo::MonInput_DatagramInfo(){
  m_name=OUTBRANCH;
}
MonInput_DatagramInfo::~MonInput_DatagramInfo(){
}


int MonInput_DatagramInfo::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DatagramInfo::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DatagramInfo::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  for(UInt_t i=0;i<2;i++)
    m_val[i] = -1;


   int CpuNumber = de->getMetaEvent().datagram().crate(); 
   if (CpuNumber>-1 && CpuNumber<5) {
     if(CpuNumber ==  enums::Lsf::Epu0) 
       m_val[0] = 0;
     if(CpuNumber ==  enums::Lsf::Epu1)
       m_val[0] = 1;
     if(CpuNumber ==  enums::Lsf::Epu2) 
       m_val[0] = 2;
     if(CpuNumber ==  enums::Lsf::Siu0)
       m_val[0] = 3;
     if(CpuNumber ==  enums::Lsf::Siu1)
       m_val[0] = 3;

     m_val[1] = de->getMetaEvent().datagram().datagrams();
   }
   else
     {
       std::cerr<<"MonInput_DatagramInfo::setValue(): ERROR" << std::endl
		<<"de->getMetaEvent().datagram().crate() out of bounds [0,4]" << std::endl;
       assert(0);
     }

}
std::string MonInput_DatagramInfo::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DatagramInfo::getDescription(){
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

