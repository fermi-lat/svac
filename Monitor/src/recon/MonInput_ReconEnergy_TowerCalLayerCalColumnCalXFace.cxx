// 
// Class for input of quantity ReconEnergy_TowerCalLayerCalColumnCalXFace for monitoring 
// 
// Created by dpaneque on Mon Jul 23 02:25:22 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace.h"
#include <iostream>

// User defined part 

#define NAME ReconEnergy_TowerCalLayerCalColumnCalXFace
#define OUTBRANCH "ReconEnergy_TowerCalLayerCalColumnCalXFace"
#define LEAF "ReconEnergy_TowerCalLayerCalColumnCalXFace[16][8][12][2]/D"
#define INBRANCH "m_cal"
// #define ACCESSOR capullo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector[tower][callayer][calcolumn][calxface] holding the reconstructed energy for the calorimeter crystal diode defined by coordinates tower, callayer,calcolumn,calxface. The Energy is retrieved by means of CalXtalRecData::getEnergy. If reconstruction was not possible, the value (for that tower,callayer,calcolumn,calxface) is set to -1.0."
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace::MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace(){
  m_name=OUTBRANCH;
}
MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace::~MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace(){
}


int MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  

  const UShort_t ntower(16),ncallayer(8),ncalcolumn(12), ncalxface(2);
  for(UShort_t tower = 0; tower<ntower;tower++){
    for(UShort_t callayer=0;callayer<ncallayer;callayer++){
      for(UShort_t calcolumn=0;calcolumn<ncalcolumn;calcolumn++){
	for(UShort_t calxface=0;calxface<ncalxface;calxface++)
	  m_val[tower][callayer][calcolumn][calxface] = -1.0;
      }
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
	  UShort_t xface = id.getFace();
	  
	  if(tower<16 && layer<8 && column<12 && xface<2){
	  if(m_val[tower][layer][column][xface]<0.0)
	    m_val[tower][layer][column][xface] = 0.0;
	  m_val[tower][layer][column][xface] += p->getEnergy();
	  }
	  else{
	    std::cout << "MonInput_ReconEnergy_TowerCalLayerCalColumn::setValue; WARNING" 
		      << std::endl
		      << "Indices tower,layer,column,xface out of range: tower = " << tower
		      << ", layer = " << layer << ", column = " << column 
		      << ", xface = " << xface << std::endl;
	  }

	}
      }
    }
  }







}
std::string MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace::getDescription(){
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

