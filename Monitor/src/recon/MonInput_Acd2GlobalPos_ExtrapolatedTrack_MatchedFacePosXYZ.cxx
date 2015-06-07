// 
// Class for input of quantity Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ for monitoring 
// 
// Edited by hand by Luca Baldini based on a old file.
//
#include "MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ
#define OUTBRANCH "Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ"
#define LEAF "Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ[2][7][3]/F"
#define INBRANCH "m_acdV2"
//#define ACCESSOR oo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector [matched][face][posXYZ] containing the position (X,Y,Z) of the intersection of the best track extrapolated to the ACD tile. The index matched indicates whther the track has an associated hit (matched=1) or not (matched=0), the index face indicates TOP (face=0), -X (face=1), -Y (face=2), +X (face=3) -X (face=4), X oriented ribbon (face=5) and Y oriented ribbon (face=6). Vector components which are not used (e.g. index matched=1 for a non-matched extrapolated track) are set to 10000, which is a non-physical position easily to recognize."
#include "reconRootData/ReconEvent.h"
#include "reconRootData/AcdReconV2.h"
#include "reconRootData/AcdAssoc.h"
#include "reconRootData/AcdTkrHitPocaV2.h"


// End user defined part 

MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ(){
  m_name=OUTBRANCH;
}
MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::~MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ(){
}


int MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setOutputBranch(TTree* tree) {
  TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
  return bErr != 0 ? 0 : 1;
}
void MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  
  for(UShort_t k=0;k<2;k++){
    for(UShort_t j=0;j<7;j++){
      for(UShort_t i=0;i<3;i++)
	m_val[k][j][i] = 10000;
    }}

  const AcdReconV2* acdRecon = de->getAcdReconV2();

  if (acdRecon) { 
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
	if ( aHitPoca->getDoca() < 0 ) continue; // missed element
	UInt_t face = aHitPoca->getId().getFace();
	const TVector3& missPos = face <= 4 ? aHitPoca->getGlobalPosition() : aHitPoca->getPoca() - aHitPoca->getPocaVector();
	if(face>6){
	  std::cout << "MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: ERROR" 
		    << std::endl
		    << "face (="<<face<<") is out of bound [0,7)." << std::endl;
	  assert(0);
	  //continue;
	}
	if ( aHitPoca->hasHit() ) { // There is a tile hit associated with this track
	  m_val[1][face][0] = missPos.X();
	  m_val[1][face][1] = missPos.Y();
	  m_val[1][face][2] = missPos.Z();
	}
	else{ // no tile hit associated with this track
	  m_val[0][face][0] = missPos.X();
	  m_val[0][face][1] = missPos.Y();
	  m_val[0][face][2] = missPos.Z();
	}
      }
    }
  }
}

std::string MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::getDescription(){
  return DESCRIPTION;
}


// int MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::sillycounter = 0;

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
//#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION
