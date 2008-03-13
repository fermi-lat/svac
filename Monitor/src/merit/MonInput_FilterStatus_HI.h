// 
// Class for input of quantity FilterStatus_HI for monitoring 
// 
// Created by dpaneque on Thu Mar 13 05:02:53 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FilterStatus_HI_h
#define MonInput_FilterStatus_HI_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FilterStatus_HI: public MonInputObject{
 public:
  MonInput_FilterStatus_HI();
  ~MonInput_FilterStatus_HI();
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

