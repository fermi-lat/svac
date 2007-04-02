#ifndef RFun_h
#define RFun_h

#include "TObject.h"
#include "configData/db/TrgConfigDB.h"

class RFun:public TObject{
 public:
  RFun(){};
  static int engine(int i,unsigned key);
  static int enginecounter(int i,unsigned key, int engine);
  static int iden(int i);
 private:
  static TrgConfigDB* m_tcf;
  ClassDef(RFun,1) 
  
};

ClassImp(RFun)
#endif
