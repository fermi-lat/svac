// 
// Class for input of quantity condarrcalhi for monitoring 
// 
// Created by kocian on Thu May 31 23:00:27 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_condarrcalhi_h
#define MonInput_condarrcalhi_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_condarrcalhi: public MonInputObject{
 public:
  MonInput_condarrcalhi();
  ~MonInput_condarrcalhi();
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

