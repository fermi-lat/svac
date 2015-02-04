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

  
  /*
  if (acdRecon && numtracks) { 

   
    // map of the acd hits
    std::map<int,const AcdHit*> acdHitMap;
    UInt_t nAcdHit = acdRecon->getHitCol().GetEntriesFast();
    for ( UInt_t iAcdHit(0); iAcdHit < nAcdHit; iAcdHit++ ) {
      const AcdHit* acdHit = (const AcdHit*)(acdRecon->getHitCol().UncheckedAt(iAcdHit));
      assert(acdHit);
      acdHitMap[acdHit->getId().getId()] = acdHit;
    }

    UInt_t nAcdInter = acdRecon->nAcdIntersections();



    for ( UInt_t iAcdInter(0); iAcdInter < nAcdInter; iAcdInter++ ) {
      const AcdTkrIntersection* acdInter = acdRecon->getAcdTkrIntersection(iAcdInter);

      if ( acdInter->getTrackIndex() != 0 ) continue;

      int acdID = acdInter->getTileId().getId() ;
      UShort_t AcdGemID = AcdId::gemIndexFromTile(acdID);

      if(AcdGemID<128){
	if ( acdInter->tileHit() ) { // There is a tile hit associated with this track
	  const AcdHit* acdHit = acdHitMap[ acdInter->getTileId().getId() ];
	  if ( acdHit != 0 ) {
	    Double_t tileWidth = int( acdID / 10 ) == 2 ? 12. : 10.;
	    Double_t pathLength = acdInter->getPathLengthInTile();
	    Double_t angleToPlane = tileWidth / pathLength; 
	    //    Double_t angleToPlane = acdInter->getCosTheta();
	    Double_t mipsA = acdHit->getMips(AcdHit::A) * angleToPlane;
	    Double_t mipsB = acdHit->getMips(AcdHit::B) * angleToPlane;
	    m_val[0][AcdGemID]= Float_t(mipsA);
	    m_val[1][AcdGemID]=Float_t(mipsB);

	    // tmp
	    //  std::cout << "MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::setValue: INFO" 
	    //  << std::endl
	    //  << "iAcdInter = " << iAcdInter << std::endl
	    //  << "ID, AcdGemID,angle,mipsA,mipsB,mipANoAngle, mipBNoAngle,  = " 
	    //  << acdID << ", " 
	    //  << AcdGemID << std::endl
	    //  << angleToPlane << ", " << std::endl
	    //  <<  m_val[0][AcdGemID] << ", " <<  m_val[1][AcdGemID] << std::endl
	    //  << acdHit->getMips(AcdHit::A)<< ", " << acdHit->getMips(AcdHit::B)
	    //  << std::endl;
	    // entmp


	  }
	}
      }
      else{
	if(acdID != 899)// NA values are set to 899
	  {
	    std::cout << "MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile::setValue: WARNING" 
		      << std::endl
		      << " AcdGemID = " <<  AcdGemID << std::endl
		      << " acdHit->getId().getId() = " << acdID
		      << " , which is NOT the conventional NA value (=899)"
		      << std::endl;
	  }
      }
    }
  }
*/
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
