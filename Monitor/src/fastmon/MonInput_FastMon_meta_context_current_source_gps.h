// 
// Class for input of quantity FastMon_meta_context_current_source_gps for monitoring 
// 
// Created by bregeon on Fri May  2 09:26:32 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_meta_context_current_source_gps_h
#define MonInput_FastMon_meta_context_current_source_gps_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_FastMon_meta_context_current_source_gps: public MonInputObject{
 public:
  MonInput_FastMon_meta_context_current_source_gps();
  ~MonInput_FastMon_meta_context_current_source_gps();
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

