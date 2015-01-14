// 
// Class for input of quantity CTBBestEnergy for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:12:23 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBBestEnergy_h
#define MonInput_CTBBestEnergy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_CTBBestEnergy: public MonInputObject{
 public:
  MonInput_CTBBestEnergy();
  ~MonInput_CTBBestEnergy();
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

