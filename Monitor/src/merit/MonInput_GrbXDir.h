// 
// Class for input of quantity GrbXDir for monitoring 
// 
// Created by dpaneque on Thu Jul 17 21:27:49 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_GrbXDir_h
#define MonInput_GrbXDir_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_GrbXDir: public MonInputObject{
 public:
  MonInput_GrbXDir();
  ~MonInput_GrbXDir();
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

