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

  static unsigned getconsecutiveplaneshit(const UShort_t invector[36]);
  static bool isempty(bool invector[16], unsigned towerid);
  static void getemptytowers(bool invector[16], bool outvector[16]);
  static std::vector<double> testfun();
 private:
  static TrgConfigDB* m_tcf;
  
};

#endif
