// 
// Class for input of quantity AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ for monitoring 
// 
// Created by dpaneque on Mon Jan  7 18:35:28 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ
#define OUTBRANCH "AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ"
#define LEAF "AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ[2][7][3]/F"
#define INBRANCH "m_acd"
//#define ACCESSOR oo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector [matched][face][posXYZ] containing the position (X,Y,Z) of the intersection of the best track extrapolated to the ACD tile. The index matched indicates whther the track has an associated hit (matched=1) or not (matched=0), the index face indicates TOP (face=0), -X (face=1), -Y (face=2), +X (face=3) -X (face=4), X oriented ribbon (face=5) and Y oriented ribbon (face=6). Vector components which are not used (e.g. index matched=1 for a non-matched extrapolated track) are set to 10000, which is a non-physical position easily to recognize."
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ(){
  m_name=OUTBRANCH;
}
MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::~MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ(){
}


int MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue(TObject* event) {
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

  
  const AcdRecon* acdRecon = de->getAcdRecon();
  if (acdRecon) { 
    UInt_t nAcdInter = acdRecon->nAcdIntersections();
    for ( UInt_t iAcdInter(0); iAcdInter < nAcdInter; iAcdInter++ ) {
      const AcdTkrIntersection* acdInter = acdRecon->getAcdTkrIntersection(iAcdInter);

      if ( acdInter->getTrackIndex() != 0 ) continue; // only the best track is used

      const TVector3& missPos = acdInter->getGlobalPosition();
      UInt_t face = acdInter->getTileId().getFace();
      if(face>6){
	std::cout << "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: ERROR" 
		  << std::endl
		  << "face (="<<face<<") is out of bound [0,7)." << std::endl;
	assert(0);
	//continue;
      }

      // tmp
      /*
      if(face==0)
	{
	  std::cout << "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: DEBUG INFO"
		    << std::endl
		    << "TOP: X,Y,Z = " 
		    << missPos.X() << ", " << missPos.Y() << ", " << missPos.Z() << ", " << std::endl;
	}

      if(face==1)
	{
	  std::cout << "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: DEBUG INFO"
		    << std::endl
		    << "Minus X: X,Y,Z = " 
		    << missPos.X() << ", " << missPos.Y() << ", " << missPos.Z() << ", " << std::endl;
	}

       if(face==3)
	{
	  std::cout << "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: DEBUG INFO"
		    << std::endl
		    << "Plus X: X,Y,Z = " 
		    << missPos.X() << ", " << missPos.Y() << ", " << missPos.Z() << ", " << std::endl;
	}



      if(face==5)
	{
	  std::cout << "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: DEBUG INFO"
		    << std::endl
		    TBro b		    << "X Oriented Ribbon: X,Y,Z = " 
		    << missPos.X() << ", " << missPos.Y() << ", " << missPos.Z() << ", " << std::endl;
	}

      if(face==6)
	{
	  std::cout << "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: DEBUG INFO"
		    << std::endl
		    << "Y Oriented Ribbon: X,Y,Z = " 
		    << missPos.X() << ", " << missPos.Y() << ", " << missPos.Z() << ", " << std::endl;
	}
      */
      // endtmp


      if (acdInter->tileHit() ) { // There is a tile hit associated with this track
	m_val[1][face][0] = missPos.X();
	m_val[1][face][1] = missPos.Y();
	m_val[1][face][2] = missPos.Z();
      }
      else{ // no tile hit associated with this track
	m_val[0][face][0] = missPos.X();
	m_val[0][face][1] = missPos.Y();
	m_val[0][face][2] = missPos.Z();

	// tmp
	/*
      if(face==5)
	{
	  sillycounter++;
	  std::cout << "MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::setValue: DEBUG INFO"
		    << std::endl
		    << "Not matched X oriented ribbon, event number " << sillycounter+1 << std::endl << "X,Y,Z = "
		    << missPos.X() << ", " << missPos.Y() << ", " << missPos.Z() << ", " << std::endl;
	  
	}
	*/
      // endtmp

      }
    }
  }
}

std::string MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::getDescription(){
  return DESCRIPTION;
}


// int MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ::sillycounter = 0;

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
//#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

