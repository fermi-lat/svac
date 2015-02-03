// 
// Class for input of quantity WP8BestZDir for monitoring 
// 
// Created by lbaldini on Tue Feb  3 15:16:41 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_WP8BestZDir_h
#define MonInput_WP8BestZDir_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_WP8BestZDir: public MonInputObject{
 public:
  MonInput_WP8BestZDir();
  ~MonInput_WP8BestZDir();
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

