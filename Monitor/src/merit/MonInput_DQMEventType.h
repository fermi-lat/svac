// 
// Class for input of quantity DQMEventType for monitoring 
// 
// Created by bregeon on Thu Feb  5 15:25:59 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DQMEventType_h
#define MonInput_DQMEventType_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_DQMEventType: public MonInputObject{
 public:
  MonInput_DQMEventType();
  ~MonInput_DQMEventType();
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

