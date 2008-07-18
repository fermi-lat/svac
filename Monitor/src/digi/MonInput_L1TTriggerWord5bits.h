// 
// Class for input of quantity L1TTriggerWord5bits for monitoring 
// 
// Created by dpaneque on Fri Jul 18 19:17:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_L1TTriggerWord5bits_h
#define MonInput_L1TTriggerWord5bits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_L1TTriggerWord5bits: public MonInputObject{
 public:
  MonInput_L1TTriggerWord5bits();
  ~MonInput_L1TTriggerWord5bits();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[5];
};

#undef VARTYPE
#endif

