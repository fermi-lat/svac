// 
// Class for input of quantity DeltaEventTime for monitoring 
// 
// Created by dpaneque on Wed Oct  3 00:27:24 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DeltaEventTime_h
#define MonInput_DeltaEventTime_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_DeltaEventTime: public MonInputObject{
 public:
  MonInput_DeltaEventTime();
  ~MonInput_DeltaEventTime();
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

