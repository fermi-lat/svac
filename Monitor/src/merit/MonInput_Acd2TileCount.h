// 
// Class for input of quantity Acd2TileCount for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:34:07 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Acd2TileCount_h
#define MonInput_Acd2TileCount_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_Acd2TileCount: public MonInputObject{
 public:
  MonInput_Acd2TileCount();
  ~MonInput_Acd2TileCount();
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

