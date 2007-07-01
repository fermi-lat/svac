// 
// Class for input of quantity condarrcno for monitoring 
// 
// Created by dpaneque on Sun Jul  1 00:37:40 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_condarrcno_h
#define MonInput_condarrcno_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_condarrcno: public MonInputObject{
 public:
  MonInput_condarrcno();
  ~MonInput_condarrcno();
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

