// 
// Class for input of quantity tkrnumtracks for monitoring 
// 
// Created by kocian on Fri Apr 20 20:44:19 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_tkrnumtracks_h
#define MonInput_tkrnumtracks_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_tkrnumtracks: public MonInputObject{
 public:
  MonInput_tkrnumtracks();
  ~MonInput_tkrnumtracks();
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

