// 
// Class for input of quantity FastMon_spacecraft_orbit_inSAA for monitoring 
// 
// Created by bregeon on Mon Aug 25 10:01:56 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_spacecraft_orbit_inSAA_h
#define MonInput_FastMon_spacecraft_orbit_inSAA_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_FastMon_spacecraft_orbit_inSAA: public MonInputObject{
 public:
  MonInput_FastMon_spacecraft_orbit_inSAA();
  ~MonInput_FastMon_spacecraft_orbit_inSAA();
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

