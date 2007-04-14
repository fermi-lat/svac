// 
// Class for input of quantity ToT_con1_TowerPlane for monitoring 
// 
// Created by dpaneque on Fri Apr 13 18:42:53 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ToT_con1_TowerPlane_h
#define MonInput_ToT_con1_TowerPlane_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_ToT_con1_TowerPlane: public MonInputObject{
 public:
  MonInput_ToT_con1_TowerPlane();
  ~MonInput_ToT_con1_TowerPlane();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][36]; // ToT counter for controller ZERO of this [tower][plane]
};

#undef VARTYPE
#endif

