// 
// Class for input of quantity FastMon_meta_context_open_mode for monitoring 
// 
// Created by bregeon on Wed Apr  9 10:04:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_meta_context_open_mode_h
#define MonInput_FastMon_meta_context_open_mode_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t

// end user defined part

class MonInput_FastMon_meta_context_open_mode: public MonInputObject{
 public:
  MonInput_FastMon_meta_context_open_mode();
  ~MonInput_FastMon_meta_context_open_mode();
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

