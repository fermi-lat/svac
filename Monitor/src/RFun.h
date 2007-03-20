#ifndef RFun_h
#define RFun_h

#include "TObject.h"
#include "configData/gem/TrgConfig.h"

class RFun:public TObject{
 public:
  RFun(){};
  static int engine(int i);
  static void setTrgConfig(TrgConfig* tcf);
 private:
  static TrgConfig* m_tcf;
  ClassDef(RFun,1) 
  
};

ClassImp(RFun)
#endif
