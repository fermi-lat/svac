// 
// Class for input of quantity TkrThickHits for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:40:25 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrThickHits_h
#define MonInput_TkrThickHits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrThickHits: public MonInputObject{
 public:
  MonInput_TkrThickHits();
  ~MonInput_TkrThickHits();
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

