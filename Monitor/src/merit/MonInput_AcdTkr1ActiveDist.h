// 
// Class for input of quantity AcdTkr1ActiveDist for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:34:14 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdTkr1ActiveDist_h
#define MonInput_AcdTkr1ActiveDist_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdTkr1ActiveDist: public MonInputObject{
 public:
  MonInput_AcdTkr1ActiveDist();
  ~MonInput_AcdTkr1ActiveDist();
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

