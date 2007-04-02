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
  
TrgConfigDB* RFun::m_tcf=new TrgConfigDB(new LatcDBImplOld);


