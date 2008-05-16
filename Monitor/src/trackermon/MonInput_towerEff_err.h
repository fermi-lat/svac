// 
// Class for input of quantity towerEff_err for monitoring 
// 
// Created by dpaneque on Fri May 16 04:55:34 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_towerEff_err_h
#define MonInput_towerEff_err_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_towerEff_err: public MonInputObject{
 public:
  MonInput_towerEff_err();
  ~MonInput_towerEff_err();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16];
};

#undef VARTYPE
#endif

