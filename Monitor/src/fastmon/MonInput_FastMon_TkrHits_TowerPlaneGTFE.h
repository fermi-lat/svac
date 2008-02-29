// 
// Class for input of quantity FastMon_TkrHits_TowerPlaneGTFE for monitoring 
// 
// Created by bregeon on Thu Feb 28 14:49:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_TkrHits_TowerPlaneGTFE_h
#define MonInput_FastMon_TkrHits_TowerPlaneGTFE_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FastMon_TkrHits_TowerPlaneGTFE: public MonInputObject{
 public:
  MonInput_FastMon_TkrHits_TowerPlaneGTFE();
  ~MonInput_FastMon_TkrHits_TowerPlaneGTFE();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][36][24];
};

#undef VARTYPE
#endif

