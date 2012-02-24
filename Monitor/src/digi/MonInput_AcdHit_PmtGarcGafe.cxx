// 
// Class for input of quantity AcdHit_PmtGarcGafe for monitoring 
// 
// Created by dpaneque on Sun Jan  6 01:23:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdHit_PmtGarcGafe.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME AcdHit_PmtGarcGafe
#define OUTBRANCH "AcdHit_PmtGarcGafe"
#define LEAF "AcdHit_PmtGarcGafe[2][12][18]/O"
#define INBRANCH "m_acdDigiCol"
#define ACCESSOR kkk
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [pmt][garc][gafe] reporting the existence (1) or not (0) of a hit in pmt A/B in garc and gafe."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdHit_PmtGarcGafe::MonInput_AcdHit_PmtGarcGafe(){
  m_name=OUTBRANCH;
}
MonInput_AcdHit_PmtGarcGafe::~MonInput_AcdHit_PmtGarcGafe(){
}


int MonInput_AcdHit_PmtGarcGafe::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdHit_PmtGarcGafe::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdHit_PmtGarcGafe::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  for(UShort_t pmt=0;pmt<2;pmt++){
    for(UShort_t garc=0;garc<12;garc++){
      for(UShort_t gafe=0;gafe<18;gafe++)
	m_val[pmt][garc][gafe] = 0;
    }}

  const TObjArray* acdDigiCol = de->getAcdDigiCol();
  assert(acdDigiCol);

  for(int iDigi = 0; iDigi <= acdDigiCol->GetLast(); ++iDigi) {
    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi);


    UShort_t AcdGemID = AcdId::gemIndexFromTile(acdDigi->getId().getId());
    Bool_t Hit_pmt[2];
    
    Hit_pmt[0] = acdDigi->getLowDiscrim(AcdDigi::A);
    Hit_pmt[1] = acdDigi->getLowDiscrim(AcdDigi::B);
    /*
    UShort_t garc_pmt[2],gafe_pmt[2];
    for(UShort_t i = 0; i<2;i++){
      garc_pmt[i] =0;
      gafe_pmt[i] = 0;
    }
    */
    unsigned garcA(0); unsigned gafeA(0);
    unsigned garcB(0); unsigned gafeB(0);

    /*
    AcdId::convertToGarcGafe( AcdGemID, AcdDigi::A, garcA, gafeA );
    AcdId::convertToGarcGafe( AcdGemID, AcdDigi::B, garcB, gafeB );
    */

    AcdId::convertToGarcGafe( acdDigi->getId().getId(), AcdDigi::A, garcA, gafeA );
    AcdId::convertToGarcGafe( acdDigi->getId().getId(), AcdDigi::B, garcB, gafeB );


    if ( Hit_pmt[0] && garcA < 12 && gafeA <18) m_val[0][garcA][gafeA]++;
    if ( Hit_pmt[1] && garcB < 12 && gafeB <18) m_val[1][garcB][gafeB]++;
  }
}

std::string MonInput_AcdHit_PmtGarcGafe::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdHit_PmtGarcGafe::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

