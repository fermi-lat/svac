// 
// Class for input of quantity CondSummary5bits for monitoring 
// 
// Created by dpaneque on Fri Jul 18 19:14:49 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CondSummary5bits_h
#define MonInput_CondSummary5bits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_CondSummary5bits: public MonInputObject{
 public:
  MonInput_CondSummary5bits();
  ~MonInput_CondSummary5bits();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[5];
};

#undef VARTYPE
#endif

