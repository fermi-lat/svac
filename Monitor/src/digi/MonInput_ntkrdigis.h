// 
// Class for input of quantity ntkrdigis for monitoring 
// 
// Created by kocian on Mon Apr 23 17:13:41 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ntkrdigis_h
#define MonInput_ntkrdigis_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_ntkrdigis: public MonInputObject{
 public:
  MonInput_ntkrdigis();
  ~MonInput_ntkrdigis();
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

