// 
// Class for input of quantity WP8CTBestEnergyProb for monitoring 
// 
// Created by lbaldini on Tue Feb  3 15:15:12 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_WP8CTBestEnergyProb_h
#define MonInput_WP8CTBestEnergyProb_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_WP8CTBestEnergyProb: public MonInputObject{
 public:
  MonInput_WP8CTBestEnergyProb();
  ~MonInput_WP8CTBestEnergyProb();
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

