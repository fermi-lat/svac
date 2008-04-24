// 
// Class for input of quantity FastMon_spacecraft_roll for monitoring 
// 
// Created by bregeon on Thu Apr 24 15:21:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_spacecraft_roll_h
#define MonInput_FastMon_spacecraft_roll_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_spacecraft_roll: public MonInputObject{
 public:
  MonInput_FastMon_spacecraft_roll();
  ~MonInput_FastMon_spacecraft_roll();
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

