// 
// Class for input of quantity PtLon for monitoring 
// 
// Created by dpaneque on Fri Apr 18 02:45:24 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_PtLon_h
#define MonInput_PtLon_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_PtLon: public MonInputObject{
 public:
  MonInput_PtLon();
  ~MonInput_PtLon();
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

