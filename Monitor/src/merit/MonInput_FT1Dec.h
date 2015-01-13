// 
// Class for input of quantity FT1Dec for monitoring 
// 
// Created by dpaneque on Tue Jul  5 12:01:02 2011 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FT1Dec_h
#define MonInput_FT1Dec_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_FT1Dec: public MonInputObject{
 public:
  MonInput_FT1Dec();
  ~MonInput_FT1Dec();
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

