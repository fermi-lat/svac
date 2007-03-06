// 
// Class for input of quantity eventid for monitoring 
// 
// Created by kocian on Tue Mar  6 22:51:00 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_eventid_h
#define MonInput_eventid_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_eventid: public MonInputObject{
 public:
  MonInput_eventid();
  ~MonInput_eventid();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
 private:
  VARTYPE m_val;
};

#undef VARTYPE
#endif

