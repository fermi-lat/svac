// 
// Class for input of quantity FastMon_condsummary for monitoring 
// 
// Created by dpaneque on Tue Feb 26 06:01:21 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_condsummary_h
#define MonInput_FastMon_condsummary_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FastMon_condsummary: public MonInputObject{
 public:
  MonInput_FastMon_condsummary();
  ~MonInput_FastMon_condsummary();
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

