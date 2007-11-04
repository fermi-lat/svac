// 
// Class for input of quantity AcdSingleVeto for monitoring 
// 
// Created by dpaneque on Wed Oct 31 22:39:07 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdSingleVeto.h"
#include <iostream>

// User defined part 

#define NAME AcdSingleVeto
#define OUTBRANCH "AcdSingleVeto"
#define LEAF "AcdSingleVeto[128]/O"
#define INBRANCH "m_acdDigiCol"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [AcdTile] reporting about the existence (1) or not (0) of an ACD single PMT Veto; that is (VetoA && !VetoB) || (!VetoA && VetoB)."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdSingleVeto::MonInput_AcdSingleVeto(){
  m_name=OUTBRANCH;
}
MonInput_AcdSingleVeto::~MonInput_AcdSingleVeto(){
}


int MonInput_AcdSingleVeto::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdSingleVeto::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdSingleVeto::setValue(TObject* event) {
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
    Bool_t VetoA = acdDigi->getVeto(AcdDigi::A);
    Bool_t VetoB = acdDigi->getVeto(AcdDigi::B);

    if(AcdGemID<128 && ((VetoA && !VetoB) || (!VetoA && VetoB)))
      m_val[AcdGemID]++; // single hit for this tile
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
std::string MonInput_AcdSingleVeto::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdSingleVeto::getDescription(){
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

