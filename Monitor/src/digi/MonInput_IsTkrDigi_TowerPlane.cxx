// 
// Class for input of quantity IsTkrDigi_TowerPlane for monitoring 
// 
// Created by dpaneque on Fri Apr 13 18:40:42 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_IsTkrDigi_TowerPlane.h"
#include "digiRootData/GlastAxis.h"
#include "../Geo.h"
#include <iostream>

// User defined part 

#define NAME IsTkrDigi_TowerPlane
#define OUTBRANCH "IsTkrDigi_TowerPlane"
#define LEAF "IsTkrDigi_TowerPlane[16][36]/s"
#define INBRANCH "m_tkrDigiCol"
// #define ACCESSOR Capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector reporting the existence (1) or not (0) of a TkrDigi object for that [tower][plane]"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_IsTkrDigi_TowerPlane::MonInput_IsTkrDigi_TowerPlane(){
  m_name=OUTBRANCH;
}
MonInput_IsTkrDigi_TowerPlane::~MonInput_IsTkrDigi_TowerPlane(){
}


int MonInput_IsTkrDigi_TowerPlane::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_IsTkrDigi_TowerPlane::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_IsTkrDigi_TowerPlane::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  const UShort_t NTower = 16; // should we get that from defined macro with global quantities? 
  const UShort_t NPlane = 36;

  for(UShort_t i = 0; i < NTower; i++){
    for(UShort_t j = 0; j < NPlane;j++)
      m_val[i][j] = 0;
  }

  // let's compute number of hits per tower and plane
  //  Loop over TkrDigiCol object and Fill 2d vector m_val[NTower][NPlane] with number of hits
            
  Int_t TowerId(0),BiLayer(0),View(0),Plane(0);
  
  Int_t nTkrDigis = de->getTkrDigiCol()->GetLast()+1;
  
  for(Int_t i = 0; i < nTkrDigis; i++) {
    const TkrDigi* tkrDigi = de->getTkrDigi(i);
    assert(tkrDigi != 0); 
    
    TowerId= tkrDigi->getTower().id();
    BiLayer = tkrDigi->getBilayer();
    GlastAxis::axis direction = tkrDigi->getView();
    View = (direction == GlastAxis::X) ? 0 : 1;
    Plane= Geo::instance()->getPlane(BiLayer, View);
    
    // There is a TkrDigi object for this tower/plane
    m_val[TowerId][Plane]++;
  }
}

std::string MonInput_IsTkrDigi_TowerPlane::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_IsTkrDigi_TowerPlane::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
// #undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

