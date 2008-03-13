// 
// Class for input of quantity AcdCornerDoca for monitoring 
// 
// Created by dpaneque on Wed Mar 12 19:39:40 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdCornerDoca_h
#define MonInput_AcdCornerDoca_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdCornerDoca: public MonInputObject{
 public:
  MonInput_AcdCornerDoca();
  ~MonInput_AcdCornerDoca();
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

