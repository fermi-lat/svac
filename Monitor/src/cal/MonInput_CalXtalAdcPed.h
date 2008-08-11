// 
// Class for input of quantity CalXtalAdcPed for monitoring 
// 
// Created by dpaneque on Mon Aug 11 04:39:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalXtalAdcPed_h
#define MonInput_CalXtalAdcPed_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalXtalAdcPed: public MonInputObject{
 public:
  MonInput_CalXtalAdcPed();
  ~MonInput_CalXtalAdcPed();
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

