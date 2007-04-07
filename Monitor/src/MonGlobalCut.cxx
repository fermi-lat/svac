
#include "MonGlobalCut.h"
#include "TTree.h"
#include "TSystem.h"
#include "TSelector.h"
#include "TTreeFormula.h"
#include "TEventList.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include "compareFiles.h"


MonGlobalCut::MonGlobalCut(const char* name, const char* cut):m_name(name),m_cut(cut), m_sel(0),m_nUsed(0),m_nFilter(0),m_eventlist(0){
  m_eventlist=new TEventList(m_name.c_str());
}
  
void MonGlobalCut::makeProxy(TTree* tree){
  if (m_cut=="" || strstr(m_cut.c_str(),"RFun")==0)return;
  std::ofstream formfile;
  formfile.open((m_name+"_globalCut_val.C").c_str());
  formfile<<"double "<<m_name+"_globalCut_val"<<"() {"<<std::endl;
  formfile<<"return 0;"<<std::endl<<"}"<<std::endl;
  formfile.close();
  formfile.open((m_name+"_globalCut_cut.C_tmp").c_str());
  formfile<<"TEventList *resultlist;"<<std::endl
	  <<"unsigned int *counter;"<<std::endl;
  formfile<<"int "<<m_name+"_globalCut_cut"<<"(){"<<std::endl;
  formfile  <<"if("<<m_cut<<")resultlist->Enter(*counter);"<<std::endl
	    <<"(*counter)++;"<<std::endl
	    <<"return 0;"<<std::endl<<"}"<<std::endl;
  formfile.close();
  formfile.open((m_name+"_globalCut_cut.h").c_str());
  formfile<<"#include \"../src/RFun.h\""<<std::endl;
  formfile<<"#include \"TEventList.h\""<<std::endl;
  formfile.close();
  // check if we need to recompile 
  bool compile=false;
  // if there was/wasn't a cut before but now there is one we have to compile
  if (access((m_name+"_globalCut_cut.C").c_str(),F_OK)!=0){
    compile=true;
    rename((m_name+"_globalCut_cut.C_tmp").c_str(),(m_name+"_globalCut_cut.C").c_str());
  }
  if (!compile){
    if (compareFiles((m_name+"_globalCut_cut.C").c_str(),(m_name+"_globalCut_cut.C_tmp").c_str())!=0){
      rename((m_name+"_globalCut_cut.C_tmp").c_str(),(m_name+"_globalCut_cut.C").c_str());
      compile=true;
    }else{
      unlink((m_name+"_globalCut_cut.C_tmp").c_str());
    }
  }
  char rootcommand[128];
  if (compile){
    tree->MakeProxy((m_name+"globalCutSelector").c_str(),(m_name+"_globalCut_val.C").c_str(),(m_name+"_globalCut_cut.C").c_str(),"nohist");
    std::cout<<"Compiling formula for global cut "<<m_name<<std::endl;
    sprintf(rootcommand,".L %s.h+O",(m_name+"globalCutSelector").c_str());
    gROOT->ProcessLine(rootcommand);
  }else{
    std::cout<<"Formula/cut for global cut "<<m_name<<" has not changed. Using old library"<<std::endl;
    gSystem->Load((m_name+"globalCutSelector_h.so").c_str());
  }
  sprintf(rootcommand,"new %s((TTree*)0x%%x);",(m_name+"globalCutSelector").c_str());
  m_sel=(TSelector*)gROOT->ProcessLineFast(Form(rootcommand,tree));
  sprintf(rootcommand,"&((%s*)0x%%x)->resultlist;",(m_name+"globalCutSelector").c_str());
  TEventList **fVar1 = (TEventList**)gROOT->ProcessLineFast(Form(rootcommand,m_sel));
  *fVar1=m_eventlist;
  sprintf(rootcommand,"&((%s*)0x%%x)->counter;",(m_name+"globalCutSelector").c_str());
  unsigned int **ct = (unsigned int**)gROOT->ProcessLineFast(Form(rootcommand,m_sel));
  *ct=&m_counter;
}
  

void MonGlobalCut::applyCut(TTree* tree){
  reset();
  m_nUsed=tree->GetEntriesFast()-1;
  tree->SetEventList(0);
  if(!m_sel){
    tree->Draw((">>"+m_name).c_str(),m_cut.c_str(),"goff",m_nUsed);
    //m_eventlist=(TEventList*)gDirectory->Get("eventsel");
  }else{
    tree->Process(m_sel,"goff",m_nUsed);
  }
  m_nFilter=m_eventlist->GetN();
  tree->SetEventList(m_eventlist);
}

void MonGlobalCut::reset(){
  m_eventlist->Clear();
  m_counter=0;
}
