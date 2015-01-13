// 
// Class for input of quantity TkrTwrEdge for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:29:00 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrTwrEdge_h
#define MonInput_TkrTwrEdge_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrTwrEdge: public MonInputObject{
 public:
  MonInput_TkrTwrEdge();
  ~MonInput_TkrTwrEdge();
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

