// 
// Class for input of quantity FastMon_meta_context_open_modechanges for monitoring 
// 
// Created by bregeon on Thu Apr 10 14:16:26 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_meta_context_open_modechanges_h
#define MonInput_FastMon_meta_context_open_modechanges_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_FastMon_meta_context_open_modechanges: public MonInputObject{
 public:
  MonInput_FastMon_meta_context_open_modechanges();
  ~MonInput_FastMon_meta_context_open_modechanges();
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

