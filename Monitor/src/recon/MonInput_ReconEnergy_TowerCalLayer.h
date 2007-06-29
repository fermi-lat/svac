// 
// Class for input of quantity ReconEnergy_TowerCalLayer for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:40:27 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ReconEnergy_TowerCalLayer_h
#define MonInput_ReconEnergy_TowerCalLayer_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_ReconEnergy_TowerCalLayer: public MonInputObject{
 public:
  MonInput_ReconEnergy_TowerCalLayer();
  ~MonInput_ReconEnergy_TowerCalLayer();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8];
};

#undef VARTYPE
#endif

