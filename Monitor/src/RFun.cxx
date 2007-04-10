#include "RFun.h"
#include "configData/db/LatcDBImplOld.h"


int RFun::engine(int i,unsigned key){
  m_tcf->updateKey(key);
  return m_tcf->lut()->engineNumber(i);
}
int RFun::enginecounter(int i,unsigned key,int engine){
  m_tcf->updateKey(key);
  int eng= m_tcf->lut()->engineNumber(i);
  if (eng==engine)return 1;
  else return 0;
}
int RFun::iden(int i ){
  return i;
}

std::vector<double> RFun::testfun(){
  std::vector<double> retvec;
  for (int i=0;i<16;i++)retvec.push_back((double)i);
  return retvec;
}
  
TrgConfigDB* RFun::m_tcf=new TrgConfigDB(new LatcDBImplOld);


