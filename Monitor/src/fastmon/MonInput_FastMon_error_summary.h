// 
// Class for input of quantity FastMon_error_summary for monitoring 
// 
// Created by bregeon on Mon Aug 25 14:46:04 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_error_summary_h
#define MonInput_FastMon_error_summary_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_FastMon_error_summary: public MonInputObject{
 public:
  MonInput_FastMon_error_summary();
  ~MonInput_FastMon_error_summary();
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

