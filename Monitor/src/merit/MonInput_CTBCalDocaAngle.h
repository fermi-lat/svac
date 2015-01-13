// 
// Class for input of quantity CTBCalDocaAngle for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:06:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBCalDocaAngle_h
#define MonInput_CTBCalDocaAngle_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CTBCalDocaAngle: public MonInputObject{
 public:
  MonInput_CTBCalDocaAngle();
  ~MonInput_CTBCalDocaAngle();
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

