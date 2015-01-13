// 
// Class for input of quantity AcdActDistTileEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:14:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdActDistTileEnergy_h
#define MonInput_AcdActDistTileEnergy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdActDistTileEnergy: public MonInputObject{
 public:
  MonInput_AcdActDistTileEnergy();
  ~MonInput_AcdActDistTileEnergy();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val;
};

#undef VARTYPE
#endif

