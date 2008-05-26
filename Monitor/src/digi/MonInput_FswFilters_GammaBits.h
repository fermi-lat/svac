// 
// Class for input of quantity FswFilters_GammaBits for monitoring 
// 
// Created by dpaneque on Sun May 25 23:31:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FswFilters_GammaBits_h
#define MonInput_FswFilters_GammaBits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FswFilters_GammaBits: public MonInputObject{
 public:
  MonInput_FswFilters_GammaBits();
  ~MonInput_FswFilters_GammaBits();
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

