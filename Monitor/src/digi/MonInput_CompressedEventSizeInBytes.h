// 
// Class for input of quantity CompressedEventSizeInBytes for monitoring 
// 
// Created by dpaneque on Mon Aug 11 18:04:30 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CompressedEventSizeInBytes_h
#define MonInput_CompressedEventSizeInBytes_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_CompressedEventSizeInBytes: public MonInputObject{
 public:
  MonInput_CompressedEventSizeInBytes();
  ~MonInput_CompressedEventSizeInBytes();
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

