// 
// Class for input of quantity timestampdouble for monitoring 
// 
// Created by dpaneque on Fri Jul 20 01:17:49 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_timestampdouble_h
#define MonInput_timestampdouble_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_timestampdouble: public MonInputObject{
 public:
  MonInput_timestampdouble();
  ~MonInput_timestampdouble();
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

