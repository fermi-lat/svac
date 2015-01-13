// 
// Class for input of quantity mcid for monitoring 
// 
// Created by kocian on Fri Jun  1 21:41:01 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_mcid_h
#define MonInput_mcid_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_mcid: public MonInputObject{
 public:
  MonInput_mcid();
  ~MonInput_mcid();
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

