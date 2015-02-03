// 
// Class for input of quantity Acd2RibbonActDist for monitoring 
// 
// Created by lbaldini on Tue Feb  3 13:36:48 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Acd2RibbonActDist_h
#define MonInput_Acd2RibbonActDist_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Acd2RibbonActDist: public MonInputObject{
 public:
  MonInput_Acd2RibbonActDist();
  ~MonInput_Acd2RibbonActDist();
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

