// 
// Class for input of quantity Tkr1TwrGap for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:29:50 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Tkr1TwrGap_h
#define MonInput_Tkr1TwrGap_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Tkr1TwrGap: public MonInputObject{
 public:
  MonInput_Tkr1TwrGap();
  ~MonInput_Tkr1TwrGap();
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

