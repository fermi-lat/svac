// 
// Class for input of quantity TriggerEngine for monitoring 
// 
// Created by dpaneque on Mon Oct  8 20:00:57 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TriggerEngine_h
#define MonInput_TriggerEngine_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_TriggerEngine: public MonInputObject{
 public:
  MonInput_TriggerEngine();
  ~MonInput_TriggerEngine();
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

