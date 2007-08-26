// 
// Class for input of quantity ReconEnergy_TowerCalLayerCalColumn for monitoring 
// 
// Created by dpaneque on Sun Jul 22 23:45:43 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ReconEnergy_TowerCalLayerCalColumn_h
#define MonInput_ReconEnergy_TowerCalLayerCalColumn_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_ReconEnergy_TowerCalLayerCalColumn: public MonInputObject{
 public:
  MonInput_ReconEnergy_TowerCalLayerCalColumn();
  ~MonInput_ReconEnergy_TowerCalLayerCalColumn();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12];
};

#undef VARTYPE
#endif

