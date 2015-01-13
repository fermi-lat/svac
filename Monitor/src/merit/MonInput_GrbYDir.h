// 
// Class for input of quantity GrbYDir for monitoring 
// 
// Created by dpaneque on Thu Jul 17 21:28:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_GrbYDir_h
#define MonInput_GrbYDir_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_GrbYDir: public MonInputObject{
 public:
  MonInput_GrbYDir();
  ~MonInput_GrbYDir();
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

