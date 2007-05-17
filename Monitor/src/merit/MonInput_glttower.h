// 
// Class for input of quantity glttower for monitoring 
// 
// Created by kocian on Fri Apr 20 23:26:52 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_glttower_h
#define MonInput_glttower_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_glttower: public MonInputObject{
 public:
  MonInput_glttower();
  ~MonInput_glttower();
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

