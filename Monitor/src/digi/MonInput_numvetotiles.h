// 
// Class for input of quantity numvetotiles for monitoring 
// 
// Created by kocian on Mon May 28 00:10:38 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_numvetotiles_h
#define MonInput_numvetotiles_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_numvetotiles: public MonInputObject{
 public:
  MonInput_numvetotiles();
  ~MonInput_numvetotiles();
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

