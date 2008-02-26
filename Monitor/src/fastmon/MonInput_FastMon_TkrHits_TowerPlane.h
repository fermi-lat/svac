// 
// Class for input of quantity FastMon_TkrHits_TowerPlane for monitoring 
// 
// Created by dpaneque on Tue Feb 26 05:59:16 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_TkrHits_TowerPlane_h
#define MonInput_FastMon_TkrHits_TowerPlane_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FastMon_TkrHits_TowerPlane: public MonInputObject{
 public:
  MonInput_FastMon_TkrHits_TowerPlane();
  ~MonInput_FastMon_TkrHits_TowerPlane();
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

