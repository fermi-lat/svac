// 
// Class for input of quantity CalXHit_TowerCalLayerCalColumn for monitoring 
// 
// Created by dpaneque on Mon Jun  4 23:37:34 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalXHit_TowerCalLayerCalColumn_h
#define MonInput_CalXHit_TowerCalLayerCalColumn_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_CalXHit_TowerCalLayerCalColumn: public MonInputObject{
 public:
  MonInput_CalXHit_TowerCalLayerCalColumn();
  ~MonInput_CalXHit_TowerCalLayerCalColumn();
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

