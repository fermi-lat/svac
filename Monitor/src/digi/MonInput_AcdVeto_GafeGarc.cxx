// 
// Class for input of quantity AcdVeto_GafeGarc for monitoring 
// 
// Created by dpaneque on Sun Jan  6 02:11:06 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdVeto_GafeGarc.h"
#include <iostream>

// User defined part 

#define NAME AcdVeto_GafeGarc
#define OUTBRANCH "AcdVeto_GafeGarc"
#define LEAF "AcdVeto_GafeGarc[18][12]/I"
#define INBRANCH "m_acdDigiCol"
#define ACCESSOR fff
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [gafe][garc] reporting the number of Vetos in electronics coordinates garc and gafe (both pmts A/B are considered)."

#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdVeto_GafeGarc::MonInput_AcdVeto_GafeGarc(){
  m_name=OUTBRANCH;
}
MonInput_AcdVeto_GafeGarc::~MonInput_AcdVeto_GafeGarc(){
}


int MonInput_AcdVeto_GafeGarc::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdVeto_GafeGarc::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdVeto_GafeGarc::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  for(UShort_t garc=0;garc<12;garc++){
    for(UShort_t gafe=0;gafe<18;gafe++)
	m_val[gafe][garc] = 0;
  }

  const TObjArray* acdDigiCol = de->getAcdDigiCol();
  assert(acdDigiCol);

  for(int iDigi = 0; iDigi <= acdDigiCol->GetLast(); ++iDigi) {
    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi);


    UShort_t AcdGemID = AcdId::gemIndexFromTile(acdDigi->getId().getId());
    Bool_t Veto_pmt[2];
    Veto_pmt[0] = acdDigi->getVeto(AcdDigi::A);
    Veto_pmt[1] = acdDigi->getVeto(AcdDigi::B);

    unsigned garcA(0); unsigned gafeA(0);
    unsigned garcB(0); unsigned gafeB(0);

    AcdId::convertToGarcGafe( AcdGemID, AcdDigi::A, garcA, gafeA );
    AcdId::convertToGarcGafe( AcdGemID, AcdDigi::B, garcB, gafeB );


    if ( Veto_pmt[0] && garcA < 12 && gafeA <18) m_val[gafeA][garcA]++;
    if ( Veto_pmt[1] && garcB < 12 && gafeB <18) m_val[gafeB][garcB]++;
  }


}
std::string MonInput_AcdVeto_GafeGarc::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdVeto_GafeGarc::getDescription(){
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

