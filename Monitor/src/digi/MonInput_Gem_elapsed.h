// 
// Class for input of quantity Gem_elapsed for monitoring 
// 
// Created by kocian on Fri Mar  9 19:50:55 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Gem_elapsed_h
#define MonInput_Gem_elapsed_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE ULong64_t 

// end user defined part

class MonInput_Gem_elapsed: public MonInputObject{
 public:
  MonInput_Gem_elapsed();
  ~MonInput_Gem_elapsed();
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

