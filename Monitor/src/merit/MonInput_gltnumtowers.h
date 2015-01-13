// 
// Class for input of quantity gltnumtowers for monitoring 
// 
// Created by kocian on Fri Apr 20 23:27:36 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_gltnumtowers_h
#define MonInput_gltnumtowers_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_gltnumtowers: public MonInputObject{
 public:
  MonInput_gltnumtowers();
  ~MonInput_gltnumtowers();
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

