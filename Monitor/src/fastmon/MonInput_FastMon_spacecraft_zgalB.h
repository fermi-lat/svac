// 
// Class for input of quantity FastMon_spacecraft_zgalB for monitoring 
// 
// Created by bregeon on Sun Jul 13 03:21:35 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_spacecraft_zgalB_h
#define MonInput_FastMon_spacecraft_zgalB_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_spacecraft_zgalB: public MonInputObject{
 public:
  MonInput_FastMon_spacecraft_zgalB();
  ~MonInput_FastMon_spacecraft_zgalB();
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

