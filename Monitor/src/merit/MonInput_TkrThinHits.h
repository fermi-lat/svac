// 
// Class for input of quantity TkrThinHits for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:39:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrThinHits_h
#define MonInput_TkrThinHits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrThinHits: public MonInputObject{
 public:
  MonInput_TkrThinHits();
  ~MonInput_TkrThinHits();
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

