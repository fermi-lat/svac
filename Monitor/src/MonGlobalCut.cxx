
#include "TROOT.h"
#include "MonGlobalCut.h"
#include "TTree.h"
#include "TSystem.h"
#include "TSelector.h"
#include "TTreeFormula.h"
#include "TEventList.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include "compareFiles.h"


MonGlobalCut::MonGlobalCut(const char* name, const char* cut):m_name(name),m_cut(cut), m_sel(0),m_nUsed(0),m_nFilter(0),m_eventlist(0),m_timeprof(0){
  m_eventlist=new TEventList(m_name.c_str());
}
  
void MonGlobalCut::makeProxy(TTree* tree){
  if (m_cut=="" || strstr(m_cut.c_str(),"RFun")==0)return;
  std::ofstream formfile;
  formfile.open((m_sodir+m_name+"_globalCut_val.C").c_str());
  formfile<<"double "<<m_name+"_globalCut_val"<<"() {"<<std::endl;
  formfile<<"return 0;"<<std::endl<<"}"<<std::endl;
  formfile.close();
  formfile.open((m_sodir+m_name+"_globalCut_cut.C_tmp").c_str());
  formfile<<"TEventList *resultlist;"<<std::endl
	  <<"unsigned int *counter;"<<std::endl;
  formfile<<"int "<<m_name+"_globalCut_cut"<<"(){"<<std::endl;
  formfile  <<"if("<<m_cut<<")resultlist->Enter(*counter);"<<std::endl
	    <<"(*counter)++;"<<std::endl
	    <<"return 0;"<<std::endl<<"}"<<std::endl;
  formfile.close();
  formfile.open((m_sodir+m_name+"_globalCut_cut.h_tmp").c_str());
  formfile<<"#include \"Monitor/RFun.h\""<<std::endl;
  formfile<<"#include \"TEventList.h\""<<std::endl;
  formfile.close();
  if(access((m_sodir+m_name+"_globalCut_cut.h").c_str(),F_OK)!=0 || 
     compareFiles((m_sodir+m_name+"_globalCut_cut.h").c_str(),(m_sodir+m_name+"_globalCut_cut.h_tmp").c_str())!=0){   
    rename((m_sodir+m_name+"_globalCut_cut.h_tmp").c_str(),(m_sodir+m_name+"_globalCut_cut.h").c_str());
  }else{
    unlink((m_sodir+m_name+"_globalCut_cut.h_tmp").c_str());
  }
  // check if we need to recompile 
  bool compile=false;
  // if there was/wasn't a cut before but now there is one we have to compile
  if (access((m_sodir+m_name+"_globalCut_cut.C").c_str(),F_OK)!=0){
    compile=true;
    rename((m_sodir+m_name+"_globalCut_cut.C_tmp").c_str(),(m_sodir+m_name+"_globalCut_cut.C").c_str());
  }
  if (!compile){
    if (compareFiles((m_sodir+m_name+"_globalCut_cut.C").c_str(),(m_sodir+m_name+"_globalCut_cut.C_tmp").c_str())!=0){
      rename((m_sodir+m_name+"_globalCut_cut.C_tmp").c_str(),(m_sodir+m_name+"_globalCut_cut.C").c_str());
      compile=true;
    }else{
      unlink((m_sodir+m_name+"_globalCut_cut.C_tmp").c_str());
    }
  }
  char rootcommand[128];
  if (compile){
    if(access((m_sodir+m_name+"globalCutSelector.h").c_str(),F_OK)==0)unlink((m_sodir+m_name+"globalCutSelector.h").c_str());
    tree->MakeProxy((m_sodir+m_name+"globalCutSelector").c_str(),(m_sodir+m_name+"_globalCut_val.C").c_str(),(m_sodir+m_name+"_globalCut_cut.C").c_str(),"nohist");

    // patch for root 5.14
    std::ifstream inf((m_sodir+m_name+"globalCutSelector.h").c_str());
    std::ofstream outf((m_sodir+m_name+"globalCutSelector.h_tmp").c_str());
    char st[200];
    inf.getline(st,200);
    while(strstr(st,"if (fTerminateMethod.IsValid()) fTerminateMethod.Execute(this);")==0){
//    while(strstr(st,"SetTree")==0){
      outf<<st<<std::endl;
      inf.getline(st,200);
    }
    outf<<st<<std::endl;
    outf<<"   delete fHelper;"<<std::endl;
    outf<<"   fHelper=0;"<<std::endl;
    while(!inf.eof()){
      inf.getline(st,200);
      outf<<st<<std::endl;
    }
    rename((m_sodir+m_name+"globalCutSelector.h_tmp").c_str(),(m_sodir+m_name+"globalCutSelector.h").c_str());
    //end patch

    std::cout<<"Compiling formula for global cut "<<m_name<<std::endl;
    sprintf(rootcommand,".L %s.h+O",(m_sodir+m_name+"globalCutSelector").c_str());
    gROOT->ProcessLine(rootcommand);
  }else{
    std::cout<<"Formula/cut for global cut "<<m_name<<" has not changed. Using old library"<<std::endl;
    gSystem->Load((m_sodir+m_name+"globalCutSelector_h.so").c_str());
    //sprintf(rootcommand,".L %s.h+O",(m_name+"globalCutSelector").c_str());
    //gROOT->ProcessLine(rootcommand);
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
  struct timespec ts1, ts2;
  clock_gettime(CLOCK_REALTIME, &ts1);
  reset();
  m_nUsed=tree->GetEntriesFast()-1;
  tree->SetEventList(0);
  if (m_eventlist)m_eventlist->Clear();
  if(!m_sel){
    tree->Draw((">>"+m_name).c_str(),m_cut.c_str(),"goff",m_nUsed);
    //m_eventlist=(TEventList*)gDirectory->Get("eventsel");
  }else{
    tree->Process(m_sel,"goff",m_nUsed);
  }
  m_nFilter=m_eventlist->GetN();
  tree->SetEventList(m_eventlist);
    clock_gettime(CLOCK_REALTIME, &ts2);
  unsigned long starttime=ts1.tv_sec*1000000+ts1.tv_nsec/1000;
  unsigned long endtime=ts2.tv_sec*1000000+ts2.tv_nsec/1000;
  //sometimes the clock goes backwards.
  if (starttime<endtime) m_timeprof+=(endtime-starttime);
}

void MonGlobalCut::reset(){
  m_eventlist->Clear();
  m_counter=0;
}

float MonGlobalCut::timeProfile(){
  float timeprof=(float)m_timeprof/1e6;
  std::cout<<setiosflags(std::ios::left);
  std::cout<<std::setw(60)<<std::setfill(' ')<<"Global cut"<<": "<<timeprof<<" seconds"<<std::endl;
  return timeprof;
}
 

void MonGlobalCut::setSharedLibDir(std::string sodir){
  m_sodir=sodir;
}
