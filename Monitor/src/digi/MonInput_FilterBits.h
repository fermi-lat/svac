// 
// Class for input of quantity FilterBits for monitoring 
// 
// Created by dpaneque on Thu Sep 27 18:08:37 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FilterBits_h
#define MonInput_FilterBits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_FilterBits: public MonInputObject{
 public:
  MonInput_FilterBits();
  ~MonInput_FilterBits();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[32];
};

#undef VARTYPE
#endif

