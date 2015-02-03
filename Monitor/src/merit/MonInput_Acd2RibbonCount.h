// 
// Class for input of quantity Acd2RibbonCount for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:35:09 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Acd2RibbonCount_h
#define MonInput_Acd2RibbonCount_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_Acd2RibbonCount: public MonInputObject{
 public:
  MonInput_Acd2RibbonCount();
  ~MonInput_Acd2RibbonCount();
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

