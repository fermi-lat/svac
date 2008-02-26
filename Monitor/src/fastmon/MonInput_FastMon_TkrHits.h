// 
// Class for input of quantity FastMon_TkrHits for monitoring 
// 
// Created by dpaneque on Tue Feb 26 05:10:44 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_TkrHits_h
#define MonInput_FastMon_TkrHits_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FastMon_TkrHits: public MonInputObject{
 public:
  MonInput_FastMon_TkrHits();
  ~MonInput_FastMon_TkrHits();
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

