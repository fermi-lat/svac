// 
// Class for input of quantity DGNGemPrescale for monitoring 
// 
// Created by dpaneque on Sat May 24 21:47:37 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DGNGemPrescale_h
#define MonInput_DGNGemPrescale_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_DGNGemPrescale: public MonInputObject{
 public:
  MonInput_DGNGemPrescale();
  ~MonInput_DGNGemPrescale();
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

