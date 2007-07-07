// 
// Class for input of quantity AcdHit_AcdTile for monitoring 
// 
// Created by dpaneque on Tue Jun  5 00:25:53 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdHit_AcdTile.h"
#include "commonRootData/idents/AcdId.h"
#include <iostream>

// User defined part 

#define NAME AcdHit_AcdTile
#define OUTBRANCH "AcdHit_AcdTile"
#define LEAF "AcdHit_AcdTile[128]/O"
#define INBRANCH "m_acdDigiCol"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [AcdTile] reporting about the existence (1) or not (0) of a ACD hit"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdHit_AcdTile::MonInput_AcdHit_AcdTile(){
  m_name=OUTBRANCH;
}
MonInput_AcdHit_AcdTile::~MonInput_AcdHit_AcdTile(){
}


int MonInput_AcdHit_AcdTile::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdHit_AcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdHit_AcdTile::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  
  const UShort_t nacdtile(128);
  for(UShort_t i=0;i<nacdtile;i++)
    m_val[i] = 0;

  const TObjArray* acdDigiCol = de->getAcdDigiCol();
  assert(acdDigiCol);

  for(int iDigi = 0; iDigi <= acdDigiCol->GetLast(); ++iDigi) {
    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi);

    UShort_t AcdGemID = AcdId::gemIndexFromTile(acdDigi->getId().getId());
    if(AcdGemID>=0&&AcdGemID<128)m_val[AcdGemID]++;
    else{
      if(acdDigi->getId().getId() != 899)// NA values are set to 899
	{
	  std::cout << "MonInput_AcdHit_AcdTile::setValue: WARNING" << std::endl
		    << " AcdGemID = " <<  AcdGemID << std::endl
		    << " acdDigi->getId().getId() = " << acdDigi->getId().getId()
		    << " , which is NOT the conventional NA value (=899)"
		    << std::endl;
	}
    }
  }
}


std::string MonInput_AcdHit_AcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdHit_AcdTile::getDescription(){
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

