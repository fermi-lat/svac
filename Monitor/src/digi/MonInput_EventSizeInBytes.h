// 
// Class for input of quantity EventSizeInBytes for monitoring 
// 
// Created by dpaneque on Tue Jul  1 02:33:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_EventSizeInBytes_h
#define MonInput_EventSizeInBytes_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE ULong_t 

// end user defined part

class MonInput_EventSizeInBytes: public MonInputObject{
 public:
  MonInput_EventSizeInBytes();
  ~MonInput_EventSizeInBytes();
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

