// 
// Class for input of quantity condarrtkr for monitoring 
// 
// Created by dpaneque on Sun Jul  1 00:36:38 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_condarrtkr_h
#define MonInput_condarrtkr_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_condarrtkr: public MonInputObject{
 public:
  MonInput_condarrtkr();
  ~MonInput_condarrtkr();
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

