#include "RFun.h"

void RFun::setTrgConfig(TrgConfig* tcf){
  m_tcf=tcf;
}

int RFun::engine(int i){
  return m_tcf->lut()->engineNumber(i);
}
  
TrgConfig* RFun::m_tcf;


