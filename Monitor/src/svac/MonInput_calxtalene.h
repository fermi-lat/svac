// 
// Class for input of quantity calxtalene for monitoring 
// 
// Created by kocian on Fri Mar  9 20:38:36 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_calxtalene_h
#define MonInput_calxtalene_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part
#define VARTYPE Float_t 

// end user defined part

class MonInput_calxtalene: public MonInputObject{
 public:
  MonInput_calxtalene();
  ~MonInput_calxtalene();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12][2];
};
#undef VARTYPE
#endif

