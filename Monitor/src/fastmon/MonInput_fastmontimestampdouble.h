// 
// Class for input of quantity fastmontimestampdouble for monitoring 
// 
// Created by dpaneque on Tue Feb 26 05:19:54 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_fastmontimestampdouble_h
#define MonInput_fastmontimestampdouble_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_fastmontimestampdouble: public MonInputObject{
 public:
  MonInput_fastmontimestampdouble();
  ~MonInput_fastmontimestampdouble();
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

