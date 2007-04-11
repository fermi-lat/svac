
#include "MonValue_t.h"
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

std::vector<double> *MonValue::m_result=new std::vector<double>;
unsigned int MonValue::m_counter=0;

MonValue::MonValue(const char* name, const char* formula, const char* cut):m_cut(cut), m_formula(formula),m_sel(0){
  // split up the name into the name part and the dimension part

  char* dimpos=strchr(name,'[');
  if (dimpos==0){
    m_name=std::string(name);
    m_dim=1;
    m_dimstring="";
  }else{
    char res[128];
    char* dimpos=strchr(name,'[')+1;
    strncpy(res,name,dimpos-name-1);
    res[dimpos-name-1]='\0';
    m_name=std::string(res);
    char* dimstart=dimpos-1;
    char* token=strstr(dimpos,"][");
    int dims=1;
    while (token!=0){
      strncpy (res,dimpos,token-dimpos);
      res[token-dimpos]='\0';
      dims*=atoi(res);
      dimpos=token+2;
      token=strstr(dimpos,"][");
    }
    token=strchr(dimpos,']');
    assert(token);
    strncpy (res,dimpos,token-dimpos);
    res[token-dimpos]='\0';
    dims*=atoi(res);
    strcpy(res,dimstart);
    m_dimstring=std::string(res);
    m_dim=dims;
  }
}
  
void MonValue::makeProxy(TTree* tree){
  bool engineloop=false;
  bool towerloop=false;
  bool tkrlayerloop=false;
  bool dooutsideformula=false;
  std::string formula(m_formula);
  std::string outsideformula;
  unsigned int outsidepos=formula.find("runonce:");
  if(outsidepos!=0xffffffff){
    dooutsideformula=true;
    unsigned int endformula=formula.find("#");
    outsideformula=formula.substr(outsidepos+strlen("runonce:"),endformula-outsidepos-strlen("runonce:"));
    formula.replace(outsidepos,endformula+1,"");
  }
  unsigned int enginepos=formula.find("foreachengine:");
  if(enginepos!=0xffffffff){
    engineloop=true;
    formula.replace(enginepos,enginepos+strlen("foreachengine:"),"");
  }
  unsigned int towerpos=formula.find("foreachtower:");
  if(towerpos!=0xffffffff){
    towerloop=true;
    formula.replace(towerpos,towerpos+strlen("foreachtower:"),"");
  }
  unsigned int tkrlayerpos=formula.find("foreachtkrlayer:");
  if(tkrlayerpos!=0xffffffff){
    tkrlayerloop=true;
    formula.replace(tkrlayerpos,tkrlayerpos+strlen("foreachtkrlayer:"),"");
  }
  if (!engineloop && !towerloop && !tkrlayerloop && !dooutsideformula &&strstr(m_formula.c_str(),"RFun")==0 && strstr(m_cut.c_str(),"RFun")==0)return;

  std::ofstream formfile;
  formfile.open((m_name+"_val.C_tmp").c_str());
  formfile<<"std::vector<double> *resultvector;"<<std::endl
	  <<"unsigned int *counter;"<<std::endl
	  <<"double "<<m_name+"_val"<<"() {"<<std::endl;
  formfile<<"double val;"<<std::endl;
  if(dooutsideformula)formfile<<"std::vector<double> runonceformula="<<outsideformula<<";"<<std::endl;
  if(engineloop)formfile<<"for(int engine=0;engine<16;engine++){"<<std::endl;
  if(towerloop)formfile<<"for(int tower=0;tower<16;tower++){"<<std::endl;
  if(tkrlayerloop)formfile<<"for(int tkrlayer=0;tkrlayer<36;tkrlayer++){"<<std::endl;
  formfile <<"val = "<<formula<<";"<<std::endl
	   <<"resultvector->push_back(val);"<<std::endl;
  if(engineloop||towerloop||tkrlayerloop)formfile<<"}"<<std::endl;
  formfile<<"(*counter)++;"<<std::endl;
  formfile<<"return val;"<<std::endl<<"}"<<std::endl;
  formfile.close();
  formfile.open((m_name+"_val.h").c_str());
  formfile<<"#include \"../src/RFun.h\""<<std::endl;
  formfile.close();
  if (m_cut!=""){
    formfile.open((m_name+"_cut.C_tmp").c_str());
    formfile<<"int "<<m_name+"_cut"<<"(){"<<std::endl
	    <<"return "<<m_cut<<";"<<std::endl<<"}"<<std::endl;
    formfile.close();
    formfile.open((m_name+"_cut.h").c_str());
    formfile<<"#include \"../src/RFun.h\""<<std::endl;
    formfile.close();
  }
  // check if we need to recompile a formula
  bool compile=false;
  // if there was/wasn't a cut before but now there is one we have to compile
  if (m_cut==""){
    if (access((m_name+"_cut.C").c_str(),F_OK)==0){
      compile=true;
      unlink((m_name+"_cut.C").c_str());
    }
  }else{
    if (access((m_name+"_cut.C").c_str(),F_OK)!=0){
      compile=true;
      rename((m_name+"_cut.C_tmp").c_str(),(m_name+"_cut.C").c_str());
     }
  }
  if(access((m_name+"_val.C").c_str(),F_OK)!=0){
    rename((m_name+"_val.C_tmp").c_str(),(m_name+"_val.C").c_str());
    compile=true;
  }else{
    if (compareFiles((m_name+"_val.C").c_str(),(m_name+"_val.C_tmp").c_str())!=0){
    rename((m_name+"_val.C_tmp").c_str(),(m_name+"_val.C").c_str());
    compile=true;
    }else{
      unlink((m_name+"_val.C_tmp").c_str());
    }
  }
  if (m_cut!=""&& !compile){
    if (compareFiles((m_name+"_cut.C").c_str(),(m_name+"_cut.C_tmp").c_str())!=0){
      rename((m_name+"_cut.C_tmp").c_str(),(m_name+"_cut.C").c_str());
      compile=true;
    }else{
      unlink((m_name+"_cut.C_tmp").c_str());
    }
  }
  char rootcommand[128];
  if (compile){
    if (m_cut!=""){
      tree->MakeProxy((m_name+"Selector").c_str(),(m_name+"_val.C").c_str(),(m_name+"_cut.C").c_str(),"nohist");
    }else{
      tree->MakeProxy((m_name+"Selector").c_str(),(m_name+"_val.C").c_str(),"","nohist");
    }
    std::cout<<"Compiling formula for "<<m_name<<std::endl;
    sprintf(rootcommand,".L %s.h+O",(m_name+"Selector").c_str());
    gROOT->ProcessLine(rootcommand);
  }else{
    std::cout<<"Formula/cut for "<<m_name<<" has not changed. Using old library"<<std::endl;
    gSystem->Load((m_name+"Selector_h.so").c_str());
  }
  sprintf(rootcommand,"new %s((TTree*)0x%%x);",(m_name+"Selector").c_str());
  m_sel=(TSelector*)gROOT->ProcessLineFast(Form(rootcommand,tree));
  sprintf(rootcommand,"&((%s*)0x%%x)->resultvector;",(m_name+"Selector").c_str());
  std::vector<double> **fVar1 = (std::vector<double>**)gROOT->ProcessLineFast(Form(rootcommand,m_sel));
  *fVar1=m_result;
  sprintf(rootcommand,"&((%s*)0x%%x)->counter;",(m_name+"Selector").c_str());
  unsigned int **ct = (unsigned int**)gROOT->ProcessLineFast(Form(rootcommand,m_sel));
  *ct=&m_counter;
}
  

void MonValue::increment(TTree* tree){
  // Have to reserve space for return values from tree
  Long64_t est;
  unsigned nev;
  TEventList* el=tree->GetEventList();
  if (el==0)nev=tree->GetEntries();
  else nev=el->GetN();
  est=nev*m_dim;
  unsigned iterations=1;
  // if there is too much data we have to iterate so we don't run out of memory
  // no proxy case:
  if (m_sel==0){
    if (est>tree->GetEstimate()){
      if(est<MAXMEM)tree->SetEstimate(est);
      else{
	tree->SetEstimate((long long int)MAXMEM+m_dim);//160 MB
	iterations=(unsigned int)(est/MAXMEM+1);
      }
    }
    // proxy case
  }else{
    if (est>m_result->capacity()){
      if(est<MAXMEM)m_result->reserve(est);
      else{
	m_result->reserve((unsigned int)MAXMEM+m_dim);//160 MB
	iterations=(unsigned int)(est/MAXMEM+1);
      }
    }
  }    
  unsigned evperit=nev/iterations+1;
  for (unsigned it=0;it<iterations;it++){
    if (m_sel==0){
      tree->Draw(m_formula.c_str(),m_cut.c_str(),"goff",evperit,evperit*it);
      if (tree->GetPlayer()->GetVar1()->GetNdata()!=(int)m_dim){
	std::cout<<"The dimension of the formula "<<m_formula<<" ("<<tree->GetPlayer()->GetVar1()->GetNdata()<<")"
		 <<" does not match the definition of variable "<<m_name<<m_dimstring<<" ("<<m_dim<<")"<<std::endl;
	assert(0);
      }
      double *val=tree->GetV1();
      for (int i=0;i<tree->GetSelectedRows();i+=m_dim){
	singleincrement(&val[i]);
      }
    }else{
      m_result->clear();
      m_counter=0;
      tree->Process(m_sel,"goff",evperit,evperit*it);
      unsigned int fdim=0;
      if (m_counter>0)fdim=(unsigned int)((double)m_result->size()/double(m_counter));
      if (m_counter>0&&fdim!=m_dim){
	std::cout<<"The dimension of the formula "<<m_formula<<" ("<<fdim<<")"
		 <<" does not match the definition of variable "<<m_name<<m_dimstring<<" ("<<m_dim<<")"<<std::endl;
	assert(0);
      }
      double *val=&((*m_result)[0]);
      for (unsigned i=0;i<m_result->size();i+=m_dim){
	singleincrement(&val[i]);
      }
    }
  }    
}
