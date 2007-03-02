// 
// Class for input of digi quantity nAcd for monitoring 
// 
// Martin Kocian, SLAC, 2/1/07
// Software developed for GLAST
#ifndef MonInput_nAcd_h
#define MonInput_nAcd_h
#include "MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t

// end user defined part

class MonInput_nAcd: public MonInputObject{
 public:
  MonInput_nAcd();
  ~MonInput_nAcd();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  virtual std::string getInputSource();
 private:
  VARTYPE m_val;
};
#undef VARTYPE
#endif
