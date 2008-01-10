// 
// Class for input of quantity AcdHit_PmtGarcGafe for monitoring 
// 
// Created by dpaneque on Sun Jan  6 01:23:23 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdHit_PmtGarcGafe_h
#define MonInput_AcdHit_PmtGarcGafe_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdHit_PmtGarcGafe: public MonInputObject{
 public:
  MonInput_AcdHit_PmtGarcGafe();
  ~MonInput_AcdHit_PmtGarcGafe();
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

