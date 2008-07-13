// 
// Class for input of quantity FastMon_spacecraft_zgalL for monitoring 
// 
// Created by bregeon on Sun Jul 13 03:20:52 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_spacecraft_zgalL_h
#define MonInput_FastMon_spacecraft_zgalL_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_spacecraft_zgalL: public MonInputObject{
 public:
  MonInput_FastMon_spacecraft_zgalL();
  ~MonInput_FastMon_spacecraft_zgalL();
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

