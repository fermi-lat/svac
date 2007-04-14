// 
// Class for input of quantity IsTkrDigi_TowerPlane for monitoring 
// 
// Created by dpaneque on Fri Apr 13 18:40:42 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_IsTkrDigi_TowerPlane_h
#define MonInput_IsTkrDigi_TowerPlane_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_IsTkrDigi_TowerPlane: public MonInputObject{
 public:
  MonInput_IsTkrDigi_TowerPlane();
  ~MonInput_IsTkrDigi_TowerPlane();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][36];  // 1 for existence of TkrDigi for this [tower][plane]; 0 otherwise
};

#undef VARTYPE
#endif

