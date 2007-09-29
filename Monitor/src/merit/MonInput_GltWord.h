// 
// Class for input of quantity GltWord for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:03:08 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_GltWord_h
#define MonInput_GltWord_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_GltWord: public MonInputObject{
 public:
  MonInput_GltWord();
  ~MonInput_GltWord();
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

