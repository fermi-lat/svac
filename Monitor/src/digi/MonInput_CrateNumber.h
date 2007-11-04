// 
// Class for input of quantity CrateNumber for monitoring 
// 
// Created by dpaneque on Wed Oct 31 01:51:55 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CrateNumber_h
#define MonInput_CrateNumber_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_CrateNumber: public MonInputObject{
 public:
  MonInput_CrateNumber();
  ~MonInput_CrateNumber();
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

