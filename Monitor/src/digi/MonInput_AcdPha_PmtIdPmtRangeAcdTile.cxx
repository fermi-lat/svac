// 
// Class for input of quantity AcdPha_PmtIdPmtRangeAcdTile for monitoring 
// 
// Created by dpaneque on Sun Jan  6 22:42:24 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdPha_PmtIdPmtRangeAcdTile.h"
#include <iostream>

// User defined part 

#define NAME AcdPha_PmtIdPmtRangeAcdTile
#define OUTBRANCH "AcdPha_PmtIdPmtRangeAcdTile"
#define LEAF "AcdPha_PmtIdPmtRangeAcdTile[2][2][128]/I"
#define INBRANCH "m_acdDigiCol"
//#define ACCESSOR ll
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [pmtid][pmtrange][acdtile] reporting about the PHA in pmtid (A/B) and pmtrange. If pmtid with pmtrange from acdtile was not used, the value set in the vector is -1."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdPha_PmtIdPmtRangeAcdTile::MonInput_AcdPha_PmtIdPmtRangeAcdTile(){
  m_name=OUTBRANCH;
}
MonInput_AcdPha_PmtIdPmtRangeAcdTile::~MonInput_AcdPha_PmtIdPmtRangeAcdTile(){
}


int MonInput_AcdPha_PmtIdPmtRangeAcdTile::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdPha_PmtIdPmtRangeAcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdPha_PmtIdPmtRangeAcdTile::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  const UShort_t nacdtile(128);
  for(UShort_t id=0;id<2;id++){
    for(UShort_t range=0;range<2;range++){
      for(UShort_t i=0;i<nacdtile;i++)
	m_val[id][range][i] = -1;
    }}

  const TObjArray* acdDigiCol = de->getAcdDigiCol();
  assert(acdDigiCol);

  for(int iDigi = 0; iDigi <= acdDigiCol->GetLast(); ++iDigi) {
    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi);


    UShort_t AcdGemID = AcdId::gemIndexFromTile(acdDigi->getId().getId());
    if(AcdGemID<128){
      // pmt A
      if(acdDigi->getRange(AcdDigi::A) == 0 )// low range
	m_val[0][0][AcdGemID]=acdDigi->getPulseHeight(AcdDigi::A);
      else  // high range
	m_val[0][1][AcdGemID]=acdDigi->getPulseHeight(AcdDigi::A);
      
      // pmt B
      if(acdDigi->getRange(AcdDigi::B) == 0 )// low range
	m_val[1][0][AcdGemID]=acdDigi->getPulseHeight(AcdDigi::B);
      else  // high range
	m_val[1][1][AcdGemID]=acdDigi->getPulseHeight(AcdDigi::B);
    }
    else{
      if(acdDigi->getId().getId() != 899)// NA values are set to 899
	{
	  std::cout << "MonInput_AcdPha_PmtA_AcdTile::setValue: WARNING" << std::endl
		    << " AcdGemID = " <<  AcdGemID << std::endl
		    << " acdDigi->getId().getId() = " << acdDigi->getId().getId()
		    << " , which is NOT the conventional NA value (=899)"
		    << std::endl;
	}
    }
  }
}

std::string MonInput_AcdPha_PmtIdPmtRangeAcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdPha_PmtIdPmtRangeAcdTile::getDescription(){
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

