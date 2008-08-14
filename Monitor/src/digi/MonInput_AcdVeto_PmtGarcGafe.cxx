// 
// Class for input of quantity AcdVeto_PmtGarcGafe for monitoring 
// 
// Created by dpaneque on Sun Jan  6 01:24:10 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdVeto_PmtGarcGafe.h"
#include <iostream>

// User defined part 

#define NAME AcdVeto_PmtGarcGafe
#define OUTBRANCH "AcdVeto_PmtGarcGafe"
#define LEAF "AcdVeto_PmtGarcGafe[2][12][18]/O"
#define INBRANCH "m_acdDigiCol"
#define ACCESSOR vvv
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [pmt][garc][gafe] reporting the existence (1) or not (0) of a Veto in pmt A/B in garc and gafe."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdVeto_PmtGarcGafe::MonInput_AcdVeto_PmtGarcGafe(){
  m_name=OUTBRANCH;
}
MonInput_AcdVeto_PmtGarcGafe::~MonInput_AcdVeto_PmtGarcGafe(){
}


int MonInput_AcdVeto_PmtGarcGafe::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdVeto_PmtGarcGafe::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdVeto_PmtGarcGafe::setValue(TObject* event) {
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
    Bool_t Veto_pmt[2];
    Veto_pmt[0] = acdDigi->getVeto(AcdDigi::A);
    Veto_pmt[1] = acdDigi->getVeto(AcdDigi::B);

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

    if ( Veto_pmt[0] && garcA < 12 && gafeA <18) m_val[0][garcA][gafeA]++;
    if ( Veto_pmt[1] && garcB < 12 && gafeB <18) m_val[1][garcB][gafeB]++;
  }



}
std::string MonInput_AcdVeto_PmtGarcGafe::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdVeto_PmtGarcGafe::getDescription(){
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

