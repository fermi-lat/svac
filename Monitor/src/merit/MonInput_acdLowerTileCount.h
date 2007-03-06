// 
// Class for input of quantity acdLowerTileCount for monitoring 
// 
// Created by kocian on Tue Mar  6 21:10:00 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_acdLowerTileCount_h
#define MonInput_acdLowerTileCount_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_acdLowerTileCount: public MonInputObject{
 public:
  MonInput_acdLowerTileCount();
  ~MonInput_acdLowerTileCount();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
 private:
  VARTYPE m_val;
};

#undef VARTYPE
#endif

