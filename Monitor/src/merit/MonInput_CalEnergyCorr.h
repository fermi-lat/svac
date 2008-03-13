// 
// Class for input of quantity CalEnergyCorr for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:38:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalEnergyCorr_h
#define MonInput_CalEnergyCorr_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalEnergyCorr: public MonInputObject{
 public:
  MonInput_CalEnergyCorr();
  ~MonInput_CalEnergyCorr();
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

