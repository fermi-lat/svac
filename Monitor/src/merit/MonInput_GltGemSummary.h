// 
// Class for input of quantity GltGemSummary for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:08:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_GltGemSummary_h
#define MonInput_GltGemSummary_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_GltGemSummary: public MonInputObject{
 public:
  MonInput_GltGemSummary();
  ~MonInput_GltGemSummary();
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

