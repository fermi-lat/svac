// 
// Class for input of quantity AcdPha_PmtB_AcdTile for monitoring 
// 
// Created by dpaneque on Tue Jun  5 01:12:23 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdPha_PmtB_AcdTile.h"
#include "commonRootData/idents/AcdId.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME AcdPha_PmtB_AcdTile
#define OUTBRANCH "AcdPha_PmtB_AcdTile"
#define LEAF "AcdPha_PmtB_AcdTile[128]/I"
#define INBRANCH "m_acdDigiCol"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [acdtile] reporting about the PHA in PMT B. If PMT A from acdtile was not used, the value set in the vector is -1. Only the LOW PMT range is used. If HIGH range was used, the value is set to -1."

#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdPha_PmtB_AcdTile::MonInput_AcdPha_PmtB_AcdTile(){
  m_name=OUTBRANCH;
}
MonInput_AcdPha_PmtB_AcdTile::~MonInput_AcdPha_PmtB_AcdTile(){
}


int MonInput_AcdPha_PmtB_AcdTile::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdPha_PmtB_AcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdPha_PmtB_AcdTile::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

const UShort_t nacdtile(128);
  for(UShort_t i=0;i<nacdtile;i++)
    m_val[i] = -1;

  const TObjArray* acdDigiCol = de->getAcdDigiCol();
  assert(acdDigiCol);

  for(int iDigi = 0; iDigi <= acdDigiCol->GetLast(); ++iDigi) {
    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi);

    UShort_t AcdGemID = AcdId::gemIndexFromTile(acdDigi->getId().getId());

    if(acdDigi->getRange(AcdDigi::B) == 0 ){
      if(AcdGemID<128) m_val[AcdGemID]=acdDigi->getPulseHeight(AcdDigi::B);
      else{
      if(acdDigi->getId().getId() != 899)// NA values are set to 899
	{
	  std::cout << "MonInput_AcdPha_PmtB_AcdTile::setValue: WARNING" << std::endl
		    << " AcdGemID = " <<  AcdGemID << std::endl
		    << " acdDigi->getId().getId() = " << acdDigi->getId().getId()
		    << " , which is NOT the conventional NA value (=899)"
		    << std::endl;
	}
      }
      
    }
  }
}


std::string MonInput_AcdPha_PmtB_AcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdPha_PmtB_AcdTile::getDescription(){
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

