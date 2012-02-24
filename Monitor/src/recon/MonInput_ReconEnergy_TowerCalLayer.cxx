// 
// Class for input of quantity ReconEnergy_TowerCalLayer for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:40:27 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ReconEnergy_TowerCalLayer.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME ReconEnergy_TowerCalLayer
#define OUTBRANCH "ReconEnergy_TowerCalLayer"
#define LEAF "ReconEnergy_TowerCalLayer[16][8]/D"
#define INBRANCH "m_cal"
#define ACCESSOR capullo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector[tower][callayer] holding the reconstructed energy for the calorimeter layer defined by coordinates tower, callayer. The Energy is retrieved by means of CalXtalRecData::getEnergy. If reconstruction was not possible, the value (for that tower,callayer) is set to -1.0."
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_ReconEnergy_TowerCalLayer::MonInput_ReconEnergy_TowerCalLayer(){
  m_name=OUTBRANCH;
}
MonInput_ReconEnergy_TowerCalLayer::~MonInput_ReconEnergy_TowerCalLayer(){
}


int MonInput_ReconEnergy_TowerCalLayer::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_ReconEnergy_TowerCalLayer::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ReconEnergy_TowerCalLayer::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  

  const UShort_t ntower(16),ncallayer(8);
  for(UShort_t tower = 0; tower<ntower;tower++){
    for(UShort_t callayer=0;callayer<ncallayer;callayer++)
      m_val[tower][callayer] = -1.0;
  }

  CalRecon* calRecon = de->getCalRecon();

  if(calRecon) {
    TObjArray* calXtalCol = calRecon->getCalXtalRecCol();
    if(calXtalCol) {
      for(int i = 0; i <= calXtalCol->GetLast(); ++i) {
	if(CalXtalRecData* p = 
	   dynamic_cast<CalXtalRecData*>(calXtalCol->At(i))) {
	  CalXtalId id = p->getPackedId();
	  int tower = id.getTower();
	  int layer = id.getLayer();
	  if(tower<16 && layer<8){
	    if(m_val[tower][layer]<0.0)
	      m_val[tower][layer] = 0.0;
	    m_val[tower][layer] += p->getEnergy();
	  }
	  else{
	    std::cout << "MonInput_ReconEnergy_TowerCalLayer::setValue; WARNING" 
		      << std::endl
		      << "Indices tower,layer out of range: tower = " << tower
		      << ", layer = " << layer << std::endl;
	  }
	  	    
	}
      }
    }
  }

}

std::string MonInput_ReconEnergy_TowerCalLayer::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ReconEnergy_TowerCalLayer::getDescription(){
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

