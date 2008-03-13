// 
// Class for input of quantity CTBGAM for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:05:58 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBGAM_h
#define MonInput_CTBGAM_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CTBGAM: public MonInputObject{
 public:
  MonInput_CTBGAM();
  ~MonInput_CTBGAM();
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

