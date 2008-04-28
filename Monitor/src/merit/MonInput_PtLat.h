// 
// Class for input of quantity PtLat for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:44:51 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_PtLat_h
#define MonInput_PtLat_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_PtLat: public MonInputObject{
 public:
  MonInput_PtLat();
  ~MonInput_PtLat();
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

