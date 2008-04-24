// 
// Class for input of quantity FastMon_spacecraft_yaw for monitoring 
// 
// Created by bregeon on Thu Apr 24 15:21:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_spacecraft_yaw_h
#define MonInput_FastMon_spacecraft_yaw_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_spacecraft_yaw: public MonInputObject{
 public:
  MonInput_FastMon_spacecraft_yaw();
  ~MonInput_FastMon_spacecraft_yaw();
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

