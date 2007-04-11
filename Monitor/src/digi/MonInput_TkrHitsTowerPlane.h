// 
// Class for input of quantity ConsecutiveTkrHitsTower for monitoring 
// 
// Created by dpaneque on Fri Apr  6 01:40:59 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrHitsTowerPlane_h
#define MonInput_TkrHitsTowerPlane_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_TkrHitsTowerPlane: public MonInputObject{
 public:
  MonInput_TkrHitsTowerPlane();
  ~MonInput_TkrHitsTowerPlane();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][36]; // number of hits per tower and plane
};

#undef VARTYPE
#endif

