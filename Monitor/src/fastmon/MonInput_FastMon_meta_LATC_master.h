// 
// Class for input of quantity FastMon_meta_LATC_master for monitoring 
// 
// Created by bregeon on Sat May 17 12:23:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_meta_LATC_master_h
#define MonInput_FastMon_meta_LATC_master_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_FastMon_meta_LATC_master: public MonInputObject{
 public:
  MonInput_FastMon_meta_LATC_master();
  ~MonInput_FastMon_meta_LATC_master();
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

