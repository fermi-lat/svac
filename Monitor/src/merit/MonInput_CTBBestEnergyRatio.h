// 
// Class for input of quantity CTBBestEnergyRatio for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:13:23 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBBestEnergyRatio_h
#define MonInput_CTBBestEnergyRatio_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_CTBBestEnergyRatio: public MonInputObject{
 public:
  MonInput_CTBBestEnergyRatio();
  ~MonInput_CTBBestEnergyRatio();
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

