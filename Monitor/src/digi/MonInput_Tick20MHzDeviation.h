// 
// Class for input of quantity Tick20MHzDeviation for monitoring 
// 
// Created by dpaneque on Fri Aug 17 19:07:09 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Tick20MHzDeviation_h
#define MonInput_Tick20MHzDeviation_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_Tick20MHzDeviation: public MonInputObject{
 public:
  MonInput_Tick20MHzDeviation();
  ~MonInput_Tick20MHzDeviation();
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

