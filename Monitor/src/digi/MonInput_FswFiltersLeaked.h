// 
// Class for input of quantity FswFiltersLeaked for monitoring 
// 
// Created by dpaneque on Mon Aug 11 16:24:57 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FswFiltersLeaked_h
#define MonInput_FswFiltersLeaked_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FswFiltersLeaked: public MonInputObject{
 public:
  MonInput_FswFiltersLeaked();
  ~MonInput_FswFiltersLeaked();
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

