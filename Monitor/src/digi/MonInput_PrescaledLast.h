// 
// Class for input of quantity PrescaledLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:45:05 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_PrescaledLast_h
#define MonInput_PrescaledLast_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE ULong64_t 

// end user defined part

class MonInput_PrescaledLast: public MonInputObject{
 public:
  MonInput_PrescaledLast();
  ~MonInput_PrescaledLast();
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

