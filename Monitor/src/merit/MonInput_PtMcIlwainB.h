// 
// Class for input of quantity PtMcIlwainB for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:44:04 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_PtMcIlwainB_h
#define MonInput_PtMcIlwainB_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_PtMcIlwainB: public MonInputObject{
 public:
  MonInput_PtMcIlwainB();
  ~MonInput_PtMcIlwainB();
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

