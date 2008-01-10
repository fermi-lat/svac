// 
// Class for input of quantity AcdGlobalPos_NotMatchedTrack_FacePosXYZ for monitoring 
// 
// Created by dpaneque on Mon Jan  7 17:34:37 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ.h"
#include <iostream>

// User defined part 

#define NAME AcdGlobalPos_NotMatchedTrack_FacePosXYZ
#define OUTBRANCH "AcdGlobalPos_NotMatchedTrack_FacePosXYZ"
#define LEAF "AcdGlobalPos_NotMatchedTrack_FacePosXYZ[7][3]/F"
#define INBRANCH "m_acd"
//#define ACCESSOR ggg
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector [face][posXYZ] containing the position (X,Y,Z) of the intersection of the best track to the ACD tile. Only not matched tracks (tracks without a related ACD hit) are being considered. Vector components which are not used (e.g. index face=1 for a extrapolated track to TOP tile) are set to 10000, which is a non-physical position easily to recognize."
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ(){
  m_name=OUTBRANCH;
}
MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::~MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ(){
}


int MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }


  for(UShort_t j=0;j<5;j++){
    for(UShort_t i=0;i<3;i++)
      m_val[j][i] = 10000;
  }

  
  const AcdRecon* acdRecon = de->getAcdRecon();
  if (acdRecon) { 
    UInt_t nAcdInter = acdRecon->nAcdIntersections();
    for ( UInt_t iAcdInter(0); iAcdInter < nAcdInter; iAcdInter++ ) {
      const AcdTkrIntersection* acdInter = acdRecon->getAcdTkrIntersection(iAcdInter);

      if ( acdInter->getTrackIndex() != 0 ) continue; // only the best track is used

      if ( !acdInter->tileHit() ) { // There is NOT a tile hit associated with this track
	const TVector3& missPos = acdInter->getGlobalPosition();
	UInt_t face = acdInter->getTileId().getFace();
	if(face<7){
	  m_val[face][0] = missPos.X();
	  m_val[face][1] = missPos.Y();
	  m_val[face][2] = missPos.Z();
	}
	else
	  {
	     std::cout << "MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::setValue: ERROR" 
		       << std::endl
		       << "face (="<<face<<") is out of bound [0,5). Aborting..." << std::endl;
	     assert(0);
	  }
	
      }
    }
  }
  
}

std::string MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ::getDescription(){
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

