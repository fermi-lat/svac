// 
// Class for input of quantity MeritObfGamStatus for monitoring 
// 
// Created by dpaneque on Thu May 29 04:12:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_MeritObfGamStatus_h
#define MonInput_MeritObfGamStatus_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_MeritObfGamStatus: public MonInputObject{
 public:
  MonInput_MeritObfGamStatus();
  ~MonInput_MeritObfGamStatus();
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

