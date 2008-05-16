// 
// Class for input of quantity trackermontimestamp for monitoring 
// 
// Created by dpaneque on Wed May 14 23:59:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_trackermontimestamp_h
#define MonInput_trackermontimestamp_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_trackermontimestamp: public MonInputObject{
 public:
  MonInput_trackermontimestamp();
  ~MonInput_trackermontimestamp();
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

