// 
// Class for input of quantity AcdSingleHit for monitoring 
// 
// Created by dpaneque on Wed Oct 31 22:24:42 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdSingleHit.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME AcdSingleHit
#define OUTBRANCH "AcdSingleHit"
#define LEAF "AcdSingleHit[128]/O"
#define INBRANCH "m_acdDigiCol"
//#define ACCESSOR bb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [AcdTile] reporting about the existence (1) or not (0) of an ACD hit with Single PMT hit; that is (PMTA && !PMTB) || (!PMTA && PMTB)."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdSingleHit::MonInput_AcdSingleHit(){
  m_name=OUTBRANCH;
}
MonInput_AcdSingleHit::~MonInput_AcdSingleHit(){
}


int MonInput_AcdSingleHit::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdSingleHit::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdSingleHit::setValue(TObject* event) {
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
    Bool_t hitPmtA = acdDigi->getLowDiscrim(AcdDigi::A);
    Bool_t hitPmtB = acdDigi->getLowDiscrim(AcdDigi::B);

    if((hitPmtA && !hitPmtB) || (!hitPmtA && hitPmtB)){
      if(AcdGemID<128)
	m_val[AcdGemID]++; // single hit for this tile
      else{
	if(acdDigi->getId().getId() != 899)// NA values are set to 899
	  {
	    std::cout << "MonInput_AcdSingleHit::setValue: WARNING" << std::endl
		      << " AcdGemID = " <<  AcdGemID << std::endl
		      << " acdDigi->getId().getId() = " << acdDigi->getId().getId()
		      << " , which is NOT the conventional NA value (=899)"
		      << std::endl;
	  }
      }
    }
  }
}


std::string MonInput_AcdSingleHit::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdSingleHit::getDescription(){
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

