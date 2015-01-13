// 
// Class for input of quantity GrbZDir for monitoring 
// 
// Created by dpaneque on Thu Jul 17 21:29:13 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_GrbZDir_h
#define MonInput_GrbZDir_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_GrbZDir: public MonInputObject{
 public:
  MonInput_GrbZDir();
  ~MonInput_GrbZDir();
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

