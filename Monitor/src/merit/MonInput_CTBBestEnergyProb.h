// 
// Class for input of quantity CTBBestEnergyProb for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:10:45 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBBestEnergyProb_h
#define MonInput_CTBBestEnergyProb_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CTBBestEnergyProb: public MonInputObject{
 public:
  MonInput_CTBBestEnergyProb();
  ~MonInput_CTBBestEnergyProb();
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

