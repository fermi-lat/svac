// 
// Class for input of quantity TkrBlankHits for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:41:07 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrBlankHits_h
#define MonInput_TkrBlankHits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrBlankHits: public MonInputObject{
 public:
  MonInput_TkrBlankHits();
  ~MonInput_TkrBlankHits();
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

