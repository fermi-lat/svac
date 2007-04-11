// 
// Class for input of quantity configkey1852 for monitoring 
// 
// Created by kocian on Fri Mar 30 18:25:24 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_configkey1852_h
#define MonInput_configkey1852_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_configkey1852: public MonInputObject{
 public:
  MonInput_configkey1852();
  ~MonInput_configkey1852();
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

