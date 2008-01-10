// 
// Class for input of quantity AcdVeto_PmtGarcGafe for monitoring 
// 
// Created by dpaneque on Sun Jan  6 01:24:10 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdVeto_PmtGarcGafe_h
#define MonInput_AcdVeto_PmtGarcGafe_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdVeto_PmtGarcGafe: public MonInputObject{
 public:
  MonInput_AcdVeto_PmtGarcGafe();
  ~MonInput_AcdVeto_PmtGarcGafe();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[2][12][18];
};

#undef VARTYPE
#endif

