// 
// Class for input of quantity endTime for monitoring 
// 
// Created by dpaneque on Thu May 15 05:07:35 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_endTime_h
#define MonInput_endTime_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_endTime: public MonInputObject{
 public:
  MonInput_endTime();
  ~MonInput_endTime();
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

