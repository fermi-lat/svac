// 
// Class for input of quantity ReconEnergy_TowerCalLayerCalColumn for monitoring 
// 
// Created by dpaneque on Sun Jul 22 23:45:43 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ReconEnergy_TowerCalLayerCalColumn.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME ReconEnergy_TowerCalLayerCalColumn
#define OUTBRANCH "ReconEnergy_TowerCalLayerCalColumn"
#define LEAF "ReconEnergy_TowerCalLayerCalColumn[16][8][12]/F"
#define INBRANCH "m_cal"
// #define ACCESSOR capullo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector[tower][callayer][calcolumn] holding the reconstructed energy for the calorimeter crystal defined by coordinates tower, callayer,calcolumn. The Energy is retrieved by means of CalXtalRecData::getEnergy. If reconstruction was not possible, the value (for that tower,callayer,calcolumn) is set to -1.0."
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_ReconEnergy_TowerCalLayerCalColumn::MonInput_ReconEnergy_TowerCalLayerCalColumn(){
  m_name=OUTBRANCH;
}
MonInput_ReconEnergy_TowerCalLayerCalColumn::~MonInput_ReconEnergy_TowerCalLayerCalColumn(){
}


int MonInput_ReconEnergy_TowerCalLayerCalColumn::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_ReconEnergy_TowerCalLayerCalColumn::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ReconEnergy_TowerCalLayerCalColumn::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
 

  const UShort_t ntower(16),ncallayer(8),ncalcolumn(12);
  for(UShort_t tower = 0; tower<ntower;tower++){
    for(UShort_t callayer=0;callayer<ncallayer;callayer++){
      for(UShort_t calcolumn=0;calcolumn<ncalcolumn;calcolumn++)
	m_val[tower][callayer][calcolumn] = -1.0;
    }
  }

  CalRecon* calRecon = de->getCalRecon();

  if(calRecon) {
    TObjArray* calXtalCol = calRecon->getCalXtalRecCol();
    if(calXtalCol) {
      for(int i = 0; i <= calXtalCol->GetLast(); ++i) {
	if(CalXtalRecData* p = 
	   dynamic_cast<CalXtalRecData*>(calXtalCol->At(i))) {
	  CalXtalId id = p->getPackedId();
	  UShort_t tower = id.getTower();
	  UShort_t layer = id.getLayer();
	  UShort_t column = id.getColumn();
	   if(tower<16 && layer<8 && column<12){
	     if(m_val[tower][layer][column]<0.0)
	       m_val[tower][layer][column] = 0.0;
	     m_val[tower][layer][column] += p->getEnergy();
	   }
	   else{
	    std::cout << "MonInput_ReconEnergy_TowerCalLayerCalColumn::setValue; WARNING" 
		      << std::endl
		      << "Indices tower,layer,column out of range: tower = " << tower
		      << ", layer = " << layer << ", column = " << column << std::endl;
	  }
	}
      }
    }
  }


}
std::string MonInput_ReconEnergy_TowerCalLayerCalColumn::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ReconEnergy_TowerCalLayerCalColumn::getDescription(){
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

