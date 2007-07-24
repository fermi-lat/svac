// 
// Class for input of quantity ReconEnergy_TowerCalLayerCalColumnCalXFace for monitoring 
// 
// Created by dpaneque on Mon Jul 23 02:25:22 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace_h
#define MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace: public MonInputObject{
 public:
  MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace();
  ~MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12][2];
};

#undef VARTYPE
#endif

