// 
// Class for input of quantity CurrentTimeToneMissing for monitoring 
// 
// Created by dpaneque on Tue Jun 24 01:15:42 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CurrentTimeToneMissing_h
#define MonInput_CurrentTimeToneMissing_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_CurrentTimeToneMissing: public MonInputObject{
 public:
  MonInput_CurrentTimeToneMissing();
  ~MonInput_CurrentTimeToneMissing();
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

