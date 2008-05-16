// 
// Class for input of quantity trigEff for monitoring 
// 
// Created by dpaneque on Fri May 16 04:55:52 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_trigEff_h
#define MonInput_trigEff_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_trigEff: public MonInputObject{
 public:
  MonInput_trigEff();
  ~MonInput_trigEff();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16];
};

#undef VARTYPE
#endif

