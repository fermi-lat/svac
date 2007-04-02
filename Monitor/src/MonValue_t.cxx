
#include "MonValue_t.h"
#include "TTree.h"
#include "TTreeFormula.h"
#include "TEventList.h"
#include <iostream>
#include <string.h>

MonValue::MonValue(const char* name, const char* formula, const char* cut):m_cut(cut), m_formula(formula){
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
  if (est>tree->GetEstimate()){
    if(est<MAXMEM)tree->SetEstimate(est);
    else{
      tree->SetEstimate(MAXMEM+m_dim);//160 MB
      iterations=est/MAXMEM+1;
    }
  }
  unsigned evperit=nev/iterations+1;
  for (unsigned it=0;it<iterations;it++){
    tree->Draw(m_formula.c_str(),m_cut.c_str(),"goff",evperit,evperit*it);
    if (tree->GetPlayer()->GetVar1()->GetNdata()==m_dim){}
    else if (tree->GetVar1()->GetNdata()==18&&strstr(m_cut.c_str(),"foreachtower")&& m_dim==16){}
    else if (tree->GetVar1()->GetNdata()==18&&strstr(m_cut.c_str(),"foreachengine")&& m_dim==16){}
    else if (tree->GetVar1()->GetNdata()==18&&strstr(m_cut.c_str(),"foreachcallayer")&& m_dim==8){}
    else if (tree->GetVar1()->GetNdata()==18&&strstr(m_cut.c_str(),"foreachcalcolumn")&& m_dim==12){}
    else{
      std::cout<<"The dimension of the formula "<<m_formula<<" ("<<tree->GetPlayer()->GetVar1()->GetNdata()<<")"
	     <<" does not match the definition of variable "<<m_name<<m_dimstring<<" ("<<m_dim<<")"<<std::endl;
      assert(0);
    }
    double *val=tree->GetV1();
    for (int i=0;i<tree->GetSelectedRows();i+=m_dim){
      singleincrement(&val[i]);
    }
  }
}
