// 
// Class for input of quantity FswFilters for monitoring 
// 
// Created by dpaneque on Sat May 24 21:39:00 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FswFilters_h
#define MonInput_FswFilters_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FswFilters: public MonInputObject{
 public:
  MonInput_FswFilters();
  ~MonInput_FswFilters();
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

