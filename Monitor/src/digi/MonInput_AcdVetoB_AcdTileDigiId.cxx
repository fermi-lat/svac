// 
// Class for input of quantity AcdVetoB_AcdTileDigiId for monitoring 
// 
// Created by dpaneque on Sat Mar  1 23:00:10 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdVetoB_AcdTileDigiId.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME AcdVetoB_AcdTileDigiId
#define OUTBRANCH "AcdVetoB_AcdTileDigiId"
#define LEAF "AcdVetoB_AcdTileDigiId[604]/O"
#define INBRANCH "m_acdDigiCol"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector[AcdTileDigiId] reporting the existence (1) or not (0) of a Veto from PMT B in acdtile (Digi Id)"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdVetoB_AcdTileDigiId::MonInput_AcdVetoB_AcdTileDigiId(){
  m_name=OUTBRANCH;
}
MonInput_AcdVetoB_AcdTileDigiId::~MonInput_AcdVetoB_AcdTileDigiId(){
}


int MonInput_AcdVetoB_AcdTileDigiId::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdVetoB_AcdTileDigiId::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdVetoB_AcdTileDigiId::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
   const UShort_t nacdtile(604);
  for(UShort_t i=0;i<nacdtile;i++)
    m_val[i] = 0;

  const TObjArray* acdDigiCol = de->getAcdDigiCol();
  assert(acdDigiCol);

  for(int iDigi = 0; iDigi <= acdDigiCol->GetLast(); ++iDigi) {
    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi);

    UShort_t AcdDigiID = acdDigi->getId().getId();
    if(acdDigi->getVeto(AcdDigi::B)){
      if(AcdDigiID<604) m_val[AcdDigiID]++;
      else{
	if(acdDigi->getId().getId() != 899)// NA values are set to 899
	  {
	    std::cout << " MonInput_AcdVetoA_AcdTileDigiId::setValue: WARNING" << std::endl
		      << " AcdDigiID = " <<  AcdDigiID << std::endl
		      << " acdDigi->getId().getId() = " << acdDigi->getId().getId()
		      << " , which is NOT the conventional NA value (=899)"
		      << std::endl;
	  }
      }
    }
  }
}

std::string MonInput_AcdVetoB_AcdTileDigiId::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdVetoB_AcdTileDigiId::getDescription(){
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

