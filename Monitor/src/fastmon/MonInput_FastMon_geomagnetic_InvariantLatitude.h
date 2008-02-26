// 
// Class for input of quantity FastMon_geomagnetic_InvariantLatitude for monitoring 
// 
// Created by dpaneque on Tue Feb 26 20:48:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_geomagnetic_InvariantLatitude_h
#define MonInput_FastMon_geomagnetic_InvariantLatitude_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_geomagnetic_InvariantLatitude: public MonInputObject{
 public:
  MonInput_FastMon_geomagnetic_InvariantLatitude();
  ~MonInput_FastMon_geomagnetic_InvariantLatitude();
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

