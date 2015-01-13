// 
// Class for input of quantity TkrNumTracks for monitoring 
// 
// Created by dpaneque on Fri Sep 12 00:06:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrNumTracks_h
#define MonInput_TkrNumTracks_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrNumTracks: public MonInputObject{
 public:
  MonInput_TkrNumTracks();
  ~MonInput_TkrNumTracks();
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

