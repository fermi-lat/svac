// 
// Class for input of quantity PtSCzenith for monitoring 
// 
// Created by dpaneque on Tue Jul  1 01:21:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_PtSCzenith_h
#define MonInput_PtSCzenith_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_PtSCzenith: public MonInputObject{
 public:
  MonInput_PtSCzenith();
  ~MonInput_PtSCzenith();
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

