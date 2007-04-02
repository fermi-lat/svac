#include "configData/db/TrgConfigDB.h"
#include "configData/db/LatcDBImplOld.h"
#include "commonRootData/idents/AcdId.h"
#include "RFun.h"
#include "TTree.h"
#include <iostream>


int main(){
  TrgConfigDB tcf(new LatcDBImplOld);
  unsigned key;
  while(1){
    std::cin>>key;
    tcf.updateKey(key);
    std::cout<<tcf<<std::endl;
  }
  //RFun::setTrgConfig(tcf);
  TTree t;
  int a=22;
  unsigned char foreachtower[16];
  for (int i=0;i<16;i++)foreachtower[i]=i;
  t.Branch("a",&a,"a/I");
  t.Branch("foreachtower",&foreachtower,"foreachtower[16]/b");
  t.SetAlias("tower","Iteration$");
  t.Fill();
  char form[128],cut[128];
  std::cin>>form;
  std::cin>>cut;
  t.Draw(form,cut,"goff");
  double *b=t.GetV1();
  int it=t.GetSelectedRows();
  for (int i=0;i<it;i++){
    std::cout<<b[i]<<std::endl;
  }
  
  
}
