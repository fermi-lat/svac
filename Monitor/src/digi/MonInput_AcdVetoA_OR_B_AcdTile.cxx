// 
// Class for input of quantity AcdVetoA_OR_B_AcdTile for monitoring 
// 
// Created by dpaneque on Wed Oct 31 19:29:40 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdVetoA_OR_B_AcdTile.h"
#include <iostream>

// User defined part 

#define NAME AcdVetoA_OR_B_AcdTile
#define OUTBRANCH "AcdVetoA_OR_B_AcdTile"
#define LEAF "AcdVetoA_OR_B_AcdTile[128]/O"
#define INBRANCH "m_acdDigiCol"
// #define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector[AcdTile] reporting the existence (1) or not (0) of a Veto from PMT A OR PMT B in acdtile"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdVetoA_OR_B_AcdTile::MonInput_AcdVetoA_OR_B_AcdTile(){
  m_name=OUTBRANCH;
}
MonInput_AcdVetoA_OR_B_AcdTile::~MonInput_AcdVetoA_OR_B_AcdTile(){
}


int MonInput_AcdVetoA_OR_B_AcdTile::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdVetoA_OR_B_AcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdVetoA_OR_B_AcdTile::setValue(TObject* event) {
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
    if(acdDigi->getVeto(AcdDigi::A) || acdDigi->getVeto(AcdDigi::B)){
      if(AcdGemID<128) m_val[AcdGemID]++;
      else{
	if(acdDigi->getId().getId() != 899)// NA values are set to 899
	  {
	    std::cout << " MonInput_AcdVetoA_OR_B_AcdTile::setValue: WARNING" << std::endl
		      << " AcdGemID = " <<  AcdGemID << std::endl
		      << " acdDigi->getId().getId() = " << acdDigi->getId().getId()
		      << " , which is NOT the conventional NA value (=899)"
		      << std::endl;
	  }
      }
    }
  }
}

std::string MonInput_AcdVetoA_OR_B_AcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdVetoA_OR_B_AcdTile::getDescription(){
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

