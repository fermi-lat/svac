// 
// Class for input of quantity GemPrescale for monitoring 
// 
// Created by dpaneque on Sat May 24 21:46:05 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_GemPrescale_h
#define MonInput_GemPrescale_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_GemPrescale: public MonInputObject{
 public:
  MonInput_GemPrescale();
  ~MonInput_GemPrescale();
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

