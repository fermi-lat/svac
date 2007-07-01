// 
// Class for input of quantity condarrroi for monitoring 
// 
// Created by dpaneque on Sun Jul  1 00:38:14 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_condarrroi_h
#define MonInput_condarrroi_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_condarrroi: public MonInputObject{
 public:
  MonInput_condarrroi();
  ~MonInput_condarrroi();
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

