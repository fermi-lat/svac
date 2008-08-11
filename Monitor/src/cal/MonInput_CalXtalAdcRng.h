// 
// Class for input of quantity CalXtalAdcRng for monitoring 
// 
// Created by dpaneque on Mon Aug 11 04:41:33 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalXtalAdcRng_h
#define MonInput_CalXtalAdcRng_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_CalXtalAdcRng: public MonInputObject{
 public:
  MonInput_CalXtalAdcRng();
  ~MonInput_CalXtalAdcRng();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12][2];
};

#undef VARTYPE
#endif

