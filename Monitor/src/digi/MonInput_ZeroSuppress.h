// 
// Class for input of quantity ZeroSuppress for monitoring 
// 
// Created by dpaneque on Thu Jan 24 19:13:42 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ZeroSuppress_h
#define MonInput_ZeroSuppress_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_ZeroSuppress: public MonInputObject{
 public:
  MonInput_ZeroSuppress();
  ~MonInput_ZeroSuppress();
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

