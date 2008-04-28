// 
// Class for input of quantity PtMcIlwainL for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:44:28 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_PtMcIlwainL_h
#define MonInput_PtMcIlwainL_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_PtMcIlwainL: public MonInputObject{
 public:
  MonInput_PtMcIlwainL();
  ~MonInput_PtMcIlwainL();
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

