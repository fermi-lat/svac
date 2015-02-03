// 
// Class for input of quantity Acd2CR1ActDistTileEnergy for monitoring 
// 
// Created by lbaldini on Tue Feb  3 14:18:07 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Acd2CR1ActDistTileEnergy_h
#define MonInput_Acd2CR1ActDistTileEnergy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Acd2CR1ActDistTileEnergy: public MonInputObject{
 public:
  MonInput_Acd2CR1ActDistTileEnergy();
  ~MonInput_Acd2CR1ActDistTileEnergy();
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

