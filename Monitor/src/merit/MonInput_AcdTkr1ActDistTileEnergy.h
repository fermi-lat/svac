// 
// Class for input of quantity AcdTkr1ActDistTileEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:32:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdTkr1ActDistTileEnergy_h
#define MonInput_AcdTkr1ActDistTileEnergy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdTkr1ActDistTileEnergy: public MonInputObject{
 public:
  MonInput_AcdTkr1ActDistTileEnergy();
  ~MonInput_AcdTkr1ActDistTileEnergy();
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

