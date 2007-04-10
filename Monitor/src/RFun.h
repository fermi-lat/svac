#ifndef RFun_h
#define RFun_h

#include "configData/db/TrgConfigDB.h"
#include <vector>

class RFun{
 public:
  RFun(){};
  static int engine(int i,unsigned key);
  static int enginecounter(int i,unsigned key, int engine);
  static int iden(int i);
  static std::vector<double> testfun();
 private:
  static TrgConfigDB* m_tcf;
  
};

#endif
