// 
// Class for input of quantity FastMon_evt_data_transfer_id for monitoring 
// 
// Created by bregeon on Sat May 17 12:29:02 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_evt_data_transfer_id_h
#define MonInput_FastMon_evt_data_transfer_id_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_FastMon_evt_data_transfer_id: public MonInputObject{
 public:
  MonInput_FastMon_evt_data_transfer_id();
  ~MonInput_FastMon_evt_data_transfer_id();
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

