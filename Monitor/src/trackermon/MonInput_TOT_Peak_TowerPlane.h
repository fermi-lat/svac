// 
// Class for input of quantity TOT_Peak_TowerPlane for monitoring 
// 
// Created by dpaneque on Fri May 16 01:24:02 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TOT_Peak_TowerPlane_h
#define MonInput_TOT_Peak_TowerPlane_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_TOT_Peak_TowerPlane: public MonInputObject{
 public:
  MonInput_TOT_Peak_TowerPlane();
  ~MonInput_TOT_Peak_TowerPlane();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][36];
};

#undef VARTYPE
#endif

