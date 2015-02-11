// 
// Class for input of quantity Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile for monitoring 
// 
// Edited by hand by Luca Baldini based on the old file.
//
#include "MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile
#define OUTBRANCH "Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile"
#define LEAF "Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile[2][128]/F"
#define INBRANCH "m_acdV2"
//#define ACCESSOR vvv
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector [pmt][acdtile] containing the PhA in Mips corrected for incoming angle for pmt (A/B) and extrapolated acdtile. Obviously, only AcdHits related to extrapolated tracks are taken into account. If the PMT A/B of acdtile was not used, the vector component is set to -1."
#include "reconRootData/ReconEvent.h"
#include "reconRootData/AcdReconV2.h"
#include "reconRootData/AcdAssoc.h"
#include "reconRootData/AcdTkrHitPocaV2.h"


// End user defined part 

MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile(){
  m_name=OUTBRANCH;
}
MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::~MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile(){
}


int MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::setOutputBranch(TTree* tree) {
  TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
  return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchStatus("m_tkr",1); // to retrieve the number of tracks
}
void MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  const UShort_t nacdtile(128);
  const UShort_t pmt(2);
  UInt_t numtracks(0);
  
  for(UShort_t j=0;j<pmt;j++){
    for(UShort_t i=0;i<nacdtile;i++)
      m_val[j][i] = -1.0;
  }

  TkrRecon* tkrRecon = de->getTkrRecon();
  if(tkrRecon) 
    numtracks = tkrRecon->getTrackCol()->GetLast()+1;
  
  const AcdReconV2* acdRecon = de->getAcdReconV2();
  
  // tmp
  /*
    std::cout << "MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::setValue: INFO" 
    << std::endl
    << "numtracks= " << numtracks << std::endl
    << "numacdhits= " << acdRecon->nAcdHit() << std::endl;
  */
  // entmp


  if (acdRecon && numtracks) {
    const TClonesArray& assocs = acdRecon->getTkrAssocCol();
    UInt_t nTkrAssoc = assocs.GetSize();
    for ( UInt_t iAssoc(0); iAssoc < nTkrAssoc; iAssoc++ ) {
      const AcdAssoc* anAssoc = dynamic_cast<const AcdAssoc*>(assocs[iAssoc]);
      if ( anAssoc == 0 ) continue; // maybe warn? 
      if ( anAssoc->getTrackIndex() != 0 ) continue;  //  only the best track is used
      if ( ! anAssoc->getUpward() ) continue; // only up-going intersctions
      
      UInt_t nHitPoca = anAssoc->nAcdHitPoca();
      for ( UInt_t iHitPoca(0); iHitPoca < nHitPoca; iHitPoca++ ) {
	const AcdTkrHitPocaV2* aHitPoca = anAssoc->getHitPoca(iHitPoca);
	if ( aHitPoca == 0 ) continue; // maybe warn? 
	if ( !aHitPoca->hasHit() ) continue; // no hit
	Int_t acdID = aHitPoca->getId().getId() ;
	UShort_t AcdGemID = AcdId::gemIndexFromTile(acdID);
	Float_t tilePath = int( acdID / 10 ) == 2 ? 12. : 10.;  // width of the tile
	tilePath /= aHitPoca->getCosTheta(); // incidence angle secant-correction
	Float_t mipsA = aHitPoca->mipsPmtA() / tilePath;
	Float_t mipsB = aHitPoca->mipsPmtB() / tilePath;
	m_val[0][AcdGemID]=mipsA;
	m_val[1][AcdGemID]=mipsB;
      }
    }
  }
}
 

std::string MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::getDescription(){
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
