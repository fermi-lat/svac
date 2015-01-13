// 
// Class for input of quantity CalMipNum for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:37:17 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalMipNum_h
#define MonInput_CalMipNum_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalMipNum: public MonInputObject{
 public:
  MonInput_CalMipNum();
  ~MonInput_CalMipNum();
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

