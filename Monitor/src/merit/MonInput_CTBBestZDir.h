// 
// Class for input of quantity CTBBestZDir for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:06:01 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBBestZDir_h
#define MonInput_CTBBestZDir_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CTBBestZDir: public MonInputObject{
 public:
  MonInput_CTBBestZDir();
  ~MonInput_CTBBestZDir();
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

