// 
// Class for input of quantity AcdPha_PmtB_AcdTile for monitoring 
// 
// Created by dpaneque on Tue Jun  5 01:12:23 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_AcdPha_PmtB_AcdTile.h"
#include <iostream>

// User defined part 

#define NAME AcdPha_PmtB_AcdTile
#define OUTBRANCH "AcdPha_PmtB_AcdTile"
#define LEAF "AcdPha_PmtB_AcdTile[128]/s"
#define INBRANCH "m_acdDigiCol"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [acdtile] reporting about the PHA from PMT B"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_AcdPha_PmtB_AcdTile::MonInput_AcdPha_PmtB_AcdTile(){
  m_name=OUTBRANCH;
}
MonInput_AcdPha_PmtB_AcdTile::~MonInput_AcdPha_PmtB_AcdTile(){
}


int MonInput_AcdPha_PmtB_AcdTile::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_AcdPha_PmtB_AcdTile::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_AcdPha_PmtB_AcdTile::setValue(TObject* event) {
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

    UShort_t AcdGemID = getGemId ( acdDigi->getId().getId() );
    if(acdDigi->getRange(AcdDigi::B) == 0 )
     if(AcdGemID>=0&&AcdGemID<128) m_val[AcdGemID]=acdDigi->getPulseHeight(AcdDigi::B);
   
  }
}



UShort_t MonInput_AcdPha_PmtB_AcdTile::getGemId(UInt_t id) {
  UInt_t face = id / 100;
  UInt_t row = (id % 100 ) / 10;
  UInt_t col = (id % 10 );
  switch ( face ) {
  case 0:  return 64 + 5*row + col;  // top:      64 - 89
  case 1:  return 32 + 5*row + col;  // -x side:  32 - 47
  case 2:  return      5*row + col;  // -y side    0 - 15
  case 3:  return 48 + 5*row + col;  // +x side   48 - 63
  case 4:  return 16 + 5*row + col;  // +y side   16 - 31
  case 5:                                   // x ribbons 96 - 99
    return 96 + col;
  case 6:                                   // y ribbons 100- 103
    return 100 + col;
  }
  return 0xFFFF;
}

std::string MonInput_AcdPha_PmtB_AcdTile::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_AcdPha_PmtB_AcdTile::getDescription(){
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

