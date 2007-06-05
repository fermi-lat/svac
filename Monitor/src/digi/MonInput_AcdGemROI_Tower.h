// 
// Class for input of quantity AcdGemROI_Tower for monitoring 
// 
// Created by dpaneque on Mon Jun  4 22:59:56 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdGemROI_Tower_h
#define MonInput_AcdGemROI_Tower_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdGemROI_Tower: public MonInputObject{
 public:
  MonInput_AcdGemROI_Tower();
  ~MonInput_AcdGemROI_Tower();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16]; 
};

#undef VARTYPE
#endif

