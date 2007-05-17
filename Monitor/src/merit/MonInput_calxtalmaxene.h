// 
// Class for input of quantity calxtalmaxene for monitoring 
// 
// Created by kocian on Fri Apr 20 20:47:47 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_calxtalmaxene_h
#define MonInput_calxtalmaxene_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_calxtalmaxene: public MonInputObject{
 public:
  MonInput_calxtalmaxene();
  ~MonInput_calxtalmaxene();
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

