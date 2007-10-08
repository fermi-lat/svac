// 
// Class for input of quantity DeltaEventTimeManual for monitoring 
// 
// Created by dpaneque on Mon Oct  8 19:35:18 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DeltaEventTimeManual_h
#define MonInput_DeltaEventTimeManual_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_DeltaEventTimeManual: public MonInputObject{
 public:
  MonInput_DeltaEventTimeManual();
  ~MonInput_DeltaEventTimeManual();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  Bool_t firstevt;
  VARTYPE m_previous;
  VARTYPE m_current;
  VARTYPE m_val;
};

#undef VARTYPE
#endif

