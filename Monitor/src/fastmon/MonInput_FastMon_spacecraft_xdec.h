// 
// Class for input of quantity FastMon_spacecraft_xdec for monitoring 
// 
// Created by bregeon on Fri Jul  4 00:57:53 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_spacecraft_xdec_h
#define MonInput_FastMon_spacecraft_xdec_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_spacecraft_xdec: public MonInputObject{
 public:
  MonInput_FastMon_spacecraft_xdec();
  ~MonInput_FastMon_spacecraft_xdec();
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

