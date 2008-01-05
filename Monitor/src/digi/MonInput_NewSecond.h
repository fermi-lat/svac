// 
// Class for input of quantity NewSecond for monitoring 
// 
// Created by dpaneque on Tue Dec 18 04:51:28 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_NewSecond_h
#define MonInput_NewSecond_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_NewSecond: public MonInputObject{
 public:
  MonInput_NewSecond();
  ~MonInput_NewSecond();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  bool firstevt;
  UInt_t m_previoustime;
  UInt_t m_currenttime;
  VARTYPE m_val;
};

#undef VARTYPE
#endif

