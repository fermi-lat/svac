// 
// Class for input of quantity AcdRibbonActDist for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:11:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdRibbonActDist_h
#define MonInput_AcdRibbonActDist_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdRibbonActDist: public MonInputObject{
 public:
  MonInput_AcdRibbonActDist();
  ~MonInput_AcdRibbonActDist();
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

