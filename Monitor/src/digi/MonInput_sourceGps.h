// 
// Class for input of quantity sourceGps for monitoring 
// 
// Created by dpaneque on Thu Apr 24 23:26:12 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_sourceGps_h
#define MonInput_sourceGps_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_sourceGps: public MonInputObject{
 public:
  MonInput_sourceGps();
  ~MonInput_sourceGps();
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

