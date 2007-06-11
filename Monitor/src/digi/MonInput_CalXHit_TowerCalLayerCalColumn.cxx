// 
// Class for input of quantity CalXHit_TowerCalLayerCalColumn for monitoring 
// 
// Created by dpaneque on Mon Jun  4 23:37:34 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalXHit_TowerCalLayerCalColumn.h"
#include <iostream>

// User defined part 

#define NAME CalXHit_TowerCalLayerCalColumn
#define OUTBRANCH "CalXHit_TowerCalLayerCalColumn"
#define LEAF "CalXHit_TowerCalLayerCalColumn[16][8][12]/s"
#define INBRANCH "m_calDigiCol"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector[tower][callayer][calcolumn] reporting about the number of hits in that crystal defined by the coordinates tower,callayer,calcolumn."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CalXHit_TowerCalLayerCalColumn::MonInput_CalXHit_TowerCalLayerCalColumn(){
  m_name=OUTBRANCH;
}
MonInput_CalXHit_TowerCalLayerCalColumn::~MonInput_CalXHit_TowerCalLayerCalColumn(){
}


int MonInput_CalXHit_TowerCalLayerCalColumn::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalXHit_TowerCalLayerCalColumn::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CalXHit_TowerCalLayerCalColumn::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
 

 const UShort_t ntower(16),ncallayer(8),ncalcolumn(12);
 for(UShort_t tower = 0; tower<ntower;tower++){
   for(UShort_t callayer=0;callayer<ncallayer;callayer++){
     for(UShort_t calcolumn=0;calcolumn<ncalcolumn;calcolumn++)
       m_val[tower][callayer][calcolumn] = 0;
   }
 }

 const TClonesArray* calDigiCol = de->getCalDigiCol();
  for(int i = 0; i <= calDigiCol->GetLast(); ++i) {
    CalDigi* p = dynamic_cast<CalDigi*>(calDigiCol->At(i)); 
    assert(p); 
    UShort_t tower = p->getPackedId().getTower();
    UShort_t callayer = p->getPackedId().getLayer();
    UShort_t calcolumn = p->getPackedId().getColumn();
    m_val[tower][callayer][calcolumn]++;
  }
  
      


}
std::string MonInput_CalXHit_TowerCalLayerCalColumn::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalXHit_TowerCalLayerCalColumn::getDescription(){
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

