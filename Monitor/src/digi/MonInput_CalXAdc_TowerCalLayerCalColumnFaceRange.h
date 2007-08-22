// 
// Class for input of quantity CalXAdc_TowerCalLayerCalColumnFaceRange for monitoring 
// 
// Created by dpaneque on Fri Aug 17 22:14:39 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange_h
#define MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Short_t 

// end user defined part

class MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange: public MonInputObject{
 public:
  MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange();
  ~MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12][2][4];
};

#undef VARTYPE
#endif

