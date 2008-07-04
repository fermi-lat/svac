// 
// Class for input of quantity FastMon_spacecraft_xra for monitoring 
// 
// Created by bregeon on Fri Jul  4 00:57:25 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_spacecraft_xra_h
#define MonInput_FastMon_spacecraft_xra_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_spacecraft_xra: public MonInputObject{
 public:
  MonInput_FastMon_spacecraft_xra();
  ~MonInput_FastMon_spacecraft_xra();
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

