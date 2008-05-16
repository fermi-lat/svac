// 
// Class for input of quantity TOT_GSigmaError for monitoring 
// 
// Created by dpaneque on Fri May 16 04:53:25 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TOT_GSigmaError_h
#define MonInput_TOT_GSigmaError_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_TOT_GSigmaError: public MonInputObject{
 public:
  MonInput_TOT_GSigmaError();
  ~MonInput_TOT_GSigmaError();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][36];
};

#undef VARTYPE
#endif

