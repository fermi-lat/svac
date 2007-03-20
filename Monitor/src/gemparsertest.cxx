#include "configData/gem/TrgConfig.h"
#include "configData/gem/TrgConfigParser.h"
#include "commonRootData/idents/AcdId.h"
#include "RFun.h"
#include "TTree.h"


int main(){
  TrgConfigParser tp("bcast.xml");
  TrgConfig *tcf=new TrgConfig;
  tp.parse(tcf);
  std::cout<<*tcf->configuration()<<std::endl;
  std::cout<<*tcf->periodicTrigger()<<std::endl;
  std::cout<<*tcf->windowParams()<<std::endl;
  std::cout<<*tcf->lut()<<std::endl;
  for (int i=0;i<16;i++){
    std::cout<<"Engine "<<i<<std::endl;
    std::cout<<*tcf->trgEngine(i)<<std::endl;
  }
  std::cout<<*tcf->disabledChannels()<<std::endl;
  std::cout<<*tcf->roi()<<std::endl;
  std::vector<unsigned long> cv;
  for (int i=0;i<16;i++){
    cv=tcf->lut()->conditionsInEngine(i);
    std::cout<<"Engine "<<i<<std::endl;
    for (unsigned j=0;j<cv.size();j++){
      std::cout<<std::hex<<cv[j]<<" ";
    }
    std::cout<<std::dec<<std::endl;
      
  }
  RFun::setTrgConfig(tcf);
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
