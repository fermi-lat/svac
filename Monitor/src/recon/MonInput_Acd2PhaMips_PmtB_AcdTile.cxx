// 
// Class for input of quantity Acd2PhaMips_PmtB_AcdTile for monitoring 
// 
// Created by dpaneque on Wed Sep 26 03:52:14 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Acd2PhaMips_PmtB_AcdTile.h"
#include "commonRootData/idents/AcdId.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2PhaMips_PmtB_AcdTile
#define OUTBRANCH "Acd2PhaMips_PmtB_AcdTile"
#define LEAF "Acd2PhaMips_PmtB_AcdTile[128]/F"
#define INBRANCH "m_acdV2"
//#define ACCESSOR capullo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector [acdtile] reporting about the PHA in Mips for PMT A"
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_Acd2PhaMips_PmtB_AcdTile::MonInput_Acd2PhaMips_PmtB_AcdTile(){
  m_name=OUTBRANCH;
}
MonInput_Acd2PhaMips_PmtB_AcdTile::~MonInput_Acd2PhaMips_PmtB_AcdTile(){
}


int MonInput_Acd2PhaMips_PmtB_AcdTile::setOutputBranch(TTree* tree) {
  TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
  return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2PhaMips_PmtB_AcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_Acd2PhaMips_PmtB_AcdTile::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  const UShort_t nacdtile(128);
  for(UShort_t i=0;i<nacdtile;i++)
    m_val[i] = 0;


  const AcdReconV2* acdRecon = de->getAcdReconV2();
  if (acdRecon) {
    UInt_t nAcdHit = acdRecon->getHitCol().GetEntriesFast();
    for ( UInt_t iAcdHit(0); iAcdHit < nAcdHit; iAcdHit++ ) {
      const AcdHit* acdHit = (const AcdHit*)(acdRecon->getHitCol().UncheckedAt(iAcdHit));
      assert(acdHit);
      const AcdId& acdId = acdHit->getId();
      int acdID = acdId.getId();
      
      UShort_t AcdGemID = AcdId::gemIndexFromTile(acdID);
      if(AcdGemID<128) m_val[AcdGemID]= acdHit->getMips(AcdHit::B);
      else{
	if(acdID != 899)// NA values are set to 899
	  {
	    std::cout << "MonInput_Acd2PhaMips_PmtB_AcdTile::setValue: WARNING" << std::endl
		      << " AcdGemID = " <<  AcdGemID << std::endl
		      << " acdHit->getId().getId() = " << acdID
		      << " , which is NOT the conventional NA value (=899)"
		      << std::endl;
	  }
      }
    }
  }

}


std::string MonInput_Acd2PhaMips_PmtB_AcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2PhaMips_PmtB_AcdTile::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
// #undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION
