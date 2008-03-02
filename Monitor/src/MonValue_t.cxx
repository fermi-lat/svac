
#include "MonValue_t.h"
#include "TROOT.h"
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
#include <time.h>
#include <map>

std::vector<double> *MonValue::m_result=new std::vector<double>;
std::vector<double> *MonValue::m_result2=new std::vector<double>;
unsigned int MonValue::m_counter=0;

MonValue::MonValue(const char* name, const char* formula, const char* cut):
  m_cut(cut), m_formula(formula),m_sel(0),m_histdim(0),m_timeprof(0),m_dontcompile(false){

  // Data type set to "Normal", default
  
  m_datatype = "Normal";

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

// Checks the buf size needed for this object. 
// if size smaller than 32M, then it returns 32M,
// which is the recomended value by root. Otherwise, 
// it returns the size of the object

  
Int_t MonValue::GetBufSize(Int_t dim,const char* type)
{
  UInt_t RecomendedBufSize = 32000;
  //std::cout << "dim,type = " << dim << ", " << type << std::endl; 
  std::string thistype(type);
  UChar_t BytesNeeded = 0;
  if(thistype=="b" || thistype=="B" || thistype=="O"){
    BytesNeeded = 1;
  }else if(thistype=="s" || thistype=="S"){
    BytesNeeded = 2;
  }else if(thistype=="I" || thistype=="i" || thistype=="F"){
    BytesNeeded = 4;
  }else if(thistype=="D" || thistype=="L" || thistype=="l"){
    BytesNeeded = 8;
  }else{
    std::cerr<<"No such type "<<type<<std::endl;
    assert(0);
  }
  
  UInt_t TotalBytesNeeded = Int_t(dim*BytesNeeded);
  
  //std::cout << "TotalBytesNeeded = " << TotalBytesNeeded  << std::endl;
  if(TotalBytesNeeded<=RecomendedBufSize)
    return Int_t(RecomendedBufSize);
  else
    return Int_t(TotalBytesNeeded);
}

// If leafname (excluding type) is larger than 64 chars, the 
// function makes an assert(0). Currently root versions 5.16 and lower 
// have a limit of 64 chars for leafnmaes.

Bool_t MonValue::CheckLeafName(const char* leafname)
{
  const UShort_t leafnameMaxlength = 64;
  std::string name(leafname);
  std::string type(strstr(leafname,"/"));
  
  if((name.size()- type.size()) > leafnameMaxlength)
    {
      std::cerr << " MonValue::CheckLeafName: ERROR" << std::endl
		<< " Leaf name " <<  name.c_str() << " is " << (name.size()- type.size()) 
		<< " char long (excluding type). Root only allows leafnames shorter or equal to " 
		<< leafnameMaxlength << std::endl
		<< " Aborting... " << std::endl;
      assert(0);
    }
  return 0;
}


void MonValue::makeProxy(TTree* tree){
  
  bool dooutsideformula = false;
  std::string formula(m_formula);
  std::string outsideformula;

  std::string::size_type formulasize=formula.size();
  std::string::size_type spos(formulasize), spos2(formulasize);

  /*
  std::cout << "Starting proxy for name " <<  m_name.c_str() << std::endl;
  std::cout << "Formula BEFORE all loops subrtraction: " << formula.c_str() << std::endl;
  */

  // Define strings we need to look for inside formula, 
  // and the corresponding line to be written in the proxies. 

  typedef std::map<const char*,const char*> ExecutionMap_t;
  ExecutionMap_t execmap;

  execmap["runonce:"]="std::vector<double> runonceformula="; // exec line to be completed once formula is known
  execmap["foreachtower:"]= "for(int tower=0;tower<16;tower++){";
  execmap["foreachengine:"]= "for(int engine=0;engine<16;engine++){";
  execmap["foreachtkrlayer:"]= "for(int tkrlayer=0;tkrlayer<19;tkrlayer++){";
  execmap["foreachtkrplane:"]= "for(int tkrplane=0;tkrplane<36;tkrplane++){";
  execmap["foreachtkrgtfe:"]= "for(int tkrgtfe=0;tkrgtfe<24;tkrgtfe++){";
  execmap["foreachacdface:"]= "for(int acdface=0;acdface<5;acdface++){";
  execmap["foreachacdrow:"]= "for(int acdrow=0;acdrow<5;acdrow++){";
  execmap["foreachacdcolumn:"]= "for(int acdcolumn=0;acdcolumn<5;acdcolumn++){";
  execmap["foreachacdpmt:"]= "for(int acdpmt=0;acdpmt<2;acdpmt++){";
  execmap["foreachgarc:"]= "for(int garc=0;garc<12;garc++){";
  execmap["foreachgafe:"]= "for(int gafe=0;gafe<18;gafe++){";
  execmap["foreachacdtile:"]= "for(int acdtile=0;acdtile<128;acdtile++){";
  execmap["foreachacdtiledigiid:"]= "for(int acdtiledigiid=0;acdtiledigiid<604;acdtiledigiid++){";
  execmap["foreachcallayer:"]= "for(int callayer=0;callayer<8;callayer++){";
  execmap["foreachcalcolumn:"]= "for(int calcolumn=0;calcolumn<12;calcolumn++){";
  execmap["foreachcalxface:"]= "for(int calxface=0;calxface<2;calxface++){";
  execmap["foreachcalxrange:"]= "for(int calxrange=0;calxrange<4;calxrange++){";
  execmap["foreachpos:"]= "for(int pos=0;pos<3;pos++){";
  execmap["foronetime:"]= "{";



  // find positions of the different execution loops/formula to be done in proxy
  // Execution will be done in the same order they appear in m_formu

  typedef std::map<int,const char*> ExecutionList_t;
  ExecutionList_t formulaloops;

  // search in formula for the strings (keys) defined in execmap fill ExecutionList_t formulaloops;

  for(ExecutionMap_t::const_iterator itr=execmap.begin(); 
      itr!=execmap.end(); itr++){
    spos=formula.find(itr->first);
    if(spos<formulasize)
      formulaloops[spos]=itr->first;
  }
    

  // tmp
  /*
  std::cout << "For name " << std::endl
	    << m_name.c_str() << std::endl
	    << "With formula " << std::endl
	    << formula.c_str() << std::endl;
  std::cout << "Printout of formulaloops map (map dim =" << formulaloops.size() <<")" << std::endl;
  for(ExecutionList_t::const_iterator itr =formulaloops.begin();
      itr!=formulaloops.end();itr++)
    std::cout << itr->first << ", " << itr->second << std::endl;
  */
  // endtmp

  /// here 

  // iterate over components of formulaloops and 
  // 1 - retrieve expression for outsideformula (if any)
  // 2 - screen the original formula against loops and outside formula

  for(ExecutionList_t::const_iterator itr =formulaloops.begin();
      itr!=formulaloops.end();itr++){
    spos=formula.find(itr->second);

      
    // check for stupidity
    if(spos>formulasize){
      std::cout << "ERROR while processing formula " << std::endl
		<< formula.c_str() << std::endl
		<< "from monitoring object " << m_name.c_str() << std::endl 
		<< "spos(=" << spos << ") > formulasize(="<<formulasize<<") for string " << std::endl
		<< itr->second << std::endl
		<< "which is in formulaloops. " 
		<< "This should not happen." << std::endl;
      assert(0);
    }

    std::string thisexec = itr->second;
    if(!thisexec.compare("runonce:")){
      // outside formula is a special case
      dooutsideformula = true;
      spos2=formula.find("#");
      outsideformula=formula.substr(spos+strlen(itr->second),spos2-spos-strlen(itr->second));
      formula.replace(spos,spos2+1,"");
    }
    else
      formula.replace(spos,spos+strlen(itr->second),"");
  }
  
  
  // std::cout << "Formula after all loops subrtraction: " << formula.c_str() << std::endl;

  
  if (!formulaloops.size() &&strstr(m_formula.c_str(),"RFun")==0 && strstr(m_cut.c_str(),"RFun")==0)return;
  bool compile=false;
  if (!m_dontcompile){
    std::ofstream formfile;
    formfile.open((m_sodir+m_name+"_val.C_tmp").c_str());
    formfile<<"std::vector<double> *resultvector;"<<std::endl;
    if(m_histdim==2)formfile<<"std::vector<double> *resultvector2;"<<std::endl;
    formfile <<"unsigned int *counter;"<<std::endl
  	   <<"double "<<m_name+"_val"<<"() {"<<std::endl;
    formfile<<"double val;"<<std::endl;

    // Write loops and/or runonceformula

     for(ExecutionList_t::const_iterator itr =formulaloops.begin();
         itr!=formulaloops.end();itr++){
       ExecutionMap_t::iterator thisexec = execmap.find(itr->second);
       formfile<< thisexec->second;

       // in case the exec is runonce, then we need to also write the outsideformula
       std::string thisexecstring = itr->second;
       if(!thisexecstring.compare("runonce:"))
         formfile<<outsideformula<<";";
       
       formfile<<std::endl;
     }


    //formula 2 is only used for 2-d histograms
    std::string formula2;
    if (m_histdim==2){
      std::string dfo="["+formula+"]";
      // for the parsing replace : by ; so :: does not get interpreted as a separator
      for (unsigned int i=1;i<dfo.size()-1;i++) if(dfo[i]==':'&&dfo[i-1]!=':'&&dfo[i+1]!=':')dfo[i]=';'; 
      std::vector<std::string> tt=parse(dfo,"[",";","]");
      if (tt.size()!=2){
        std::cerr<<"2-d histogram "<<m_name<<" does not have a formula for both dimensions"<<std::endl;
        assert(0);
      }
      formula=tt[0];
      formula2=tt[1];
    }    
   
    formfile <<"val = double("<<formula<<");"<<std::endl
  	   <<"resultvector->push_back(val);"<<std::endl;
    if(m_histdim==2){
      formfile <<"val = double("<<formula2<<");"<<std::endl
  	     <<"resultvector2->push_back(val);"<<std::endl;
    }

    // close all the loops
    UInt_t ncloseloops = formulaloops.size();
    if(dooutsideformula) ncloseloops--;

    for (UInt_t i = 0; i < ncloseloops;i++)
      formfile<<"}"<<std::endl;



    formfile<<"(*counter)++;"<<std::endl;
    formfile<<"return val;"<<std::endl<<"}"<<std::endl;
    formfile.close();


    formfile.open((m_sodir+m_name+"_val.h_tmp").c_str());
    formfile<<"#include \"Monitor/RFun.h\""<<std::endl;
    formfile.close();
    if(access((m_sodir+m_name+"_val.h").c_str(),F_OK)!=0 || 
       compareFiles((m_sodir+m_name+"_val.h").c_str(),(m_sodir+m_name+"_val.h_tmp").c_str())!=0){   
      rename((m_sodir+m_name+"_val.h_tmp").c_str(),(m_sodir+m_name+"_val.h").c_str());
    }else{
      unlink((m_sodir+m_name+"_val.h_tmp").c_str());
    }


    if (m_cut!=""){
      formfile.open((m_sodir+m_name+"_cut.C_tmp").c_str());
      formfile<<"int "<<m_name+"_cut"<<"(){"<<std::endl
  	    <<"return "<<m_cut<<";"<<std::endl<<"}"<<std::endl;
      formfile.close();

      formfile.open((m_sodir+m_name+"_cut.h_tmp").c_str());
      formfile<<"#include \"Monitor/RFun.h\""<<std::endl;
      formfile.close();
      if(access((m_sodir+m_name+"_cut.h").c_str(),F_OK)!=0 || 
      compareFiles((m_sodir+m_name+"_cut.h").c_str(),(m_sodir+m_name+"_cut.h_tmp").c_str())!=0){   
        rename((m_sodir+m_name+"_cut.h_tmp").c_str(),(m_sodir+m_name+"_cut.h").c_str());
      }else{
        unlink((m_sodir+m_name+"_cut.h_tmp").c_str());
      }
    }
    // check if we need to recompile a formula
    // if there was/wasn't a cut before but now there is one we have to compile
    if (m_cut==""){
      if (access((m_sodir+m_name+"_cut.C").c_str(),F_OK)==0){
        compile=true;
        unlink((m_sodir+m_name+"_cut.C").c_str());
      }
    }else{
      if (access((m_sodir+m_name+"_cut.C").c_str(),F_OK)!=0){
        compile=true;
        rename((m_sodir+m_name+"_cut.C_tmp").c_str(),(m_sodir+m_name+"_cut.C").c_str());
       }
    }
    if(access((m_sodir+m_name+"_val.C").c_str(),F_OK)!=0){
      rename((m_sodir+m_name+"_val.C_tmp").c_str(),(m_sodir+m_name+"_val.C").c_str());
      compile=true;
    }else{
      if (compareFiles((m_sodir+m_name+"_val.C").c_str(),(m_sodir+m_name+"_val.C_tmp").c_str())!=0){
      rename((m_sodir+m_name+"_val.C_tmp").c_str(),(m_sodir+m_name+"_val.C").c_str());
      compile=true;
      }else{
        unlink((m_sodir+m_name+"_val.C_tmp").c_str());
      }
    }
    if (m_cut!=""&& !compile){
      if (compareFiles((m_sodir+m_name+"_cut.C").c_str(),(m_sodir+m_name+"_cut.C_tmp").c_str())!=0){
        rename((m_sodir+m_name+"_cut.C_tmp").c_str(),(m_sodir+m_name+"_cut.C").c_str());
        compile=true;
      }else{
        unlink((m_sodir+m_name+"_cut.C_tmp").c_str());
      }
    }
  }
  char rootcommand[128];
  if (compile){
    if(access((m_sodir+m_name+"Selector.h").c_str(),F_OK)==0)unlink((m_sodir+m_name+"Selector.h").c_str());
    if (m_cut!=""){
      tree->MakeProxy((m_sodir+m_name+"Selector").c_str(),(m_sodir+m_name+"_val.C").c_str(),(m_sodir+m_name+"_cut.C").c_str(),"nohist");
    }else{
      tree->MakeProxy((m_sodir+m_name+"Selector").c_str(),(m_sodir+m_name+"_val.C").c_str(),"","nohist");
    }

    // patch for root 5.14
    std::ifstream inf((m_sodir+m_name+"Selector.h").c_str());
    std::ofstream outf((m_sodir+m_name+"Selector.h_tmp").c_str());
    char st[1000];
    inf.getline(st,1000);
    while(strstr(st,"if (fTerminateMethod.IsValid()) fTerminateMethod.Execute(this);")==0){
    //while(strstr(st,"SetTree")==0){
      outf<<st<<std::endl;
      inf.getline(st,1000);
    }
    outf<<st<<std::endl;
    outf<<"   delete fHelper;"<<std::endl;
    outf<<"   fHelper=0;"<<std::endl;
    while(!inf.eof()){
      inf.getline(st,1000);
      outf<<st<<std::endl;
    }
    rename((m_sodir+m_name+"Selector.h_tmp").c_str(),(m_sodir+m_name+"Selector.h").c_str());
    //end patch

    std::cout<<"Compiling formula for "<<m_name<<std::endl;
    sprintf(rootcommand,".L %s.h+O",(m_sodir+m_name+"Selector").c_str());
    gROOT->ProcessLine(rootcommand);
    std::cout << "Done" << std::endl;
  }else{
    if(m_dontcompile)std::cout<<"Option p: Reading old library for "<<m_name<<std::endl;
    else std::cout<<"Formula/cut for "<<m_name<<" has not changed. Using old library"<<std::endl;
    gSystem->Load((m_sodir+m_name+"Selector_h.so").c_str());
    //sprintf(rootcommand,".L %s.h+O",(m_name+"Selector").c_str());
    //gROOT->ProcessLine(rootcommand);
  }
  sprintf(rootcommand,"new %s((TTree*)0x%%x);",(m_name+"Selector").c_str());
  m_sel=(TSelector*)gROOT->ProcessLineFast(Form(rootcommand,tree));
  sprintf(rootcommand,"&((%s*)0x%%x)->resultvector;",(m_name+"Selector").c_str());
  std::vector<double> **fVar1 = (std::vector<double>**)gROOT->ProcessLineFast(Form(rootcommand,m_sel));
  *fVar1=m_result;
  if (m_histdim==2){
    sprintf(rootcommand,"&((%s*)0x%%x)->resultvector2;",(m_name+"Selector").c_str());
    std::vector<double> **fVar2 = (std::vector<double>**)gROOT->ProcessLineFast(Form(rootcommand,m_sel));
    *fVar2=m_result2;
  }
  sprintf(rootcommand,"&((%s*)0x%%x)->counter;",(m_name+"Selector").c_str());
  unsigned int **ct = (unsigned int**)gROOT->ProcessLineFast(Form(rootcommand,m_sel));
  *ct=&m_counter;
  // std::cout << "Done with this proxy" << std::endl;
}
  

void MonValue::increment(TTree* tree){

  // std::cout << "MonValue::increment: Object= " << m_name.c_str() << std::endl;

  struct timespec ts1, ts2;
  clock_gettime(CLOCK_REALTIME, &ts1);
  // Have to reserve space for return values from tree
  Long64_t est;
  unsigned nev;
  TEventList* el=tree->GetEventList();
  if (el==0)nev=tree->GetEntries();
  else nev=el->GetN();
  est=nev*m_dim;
  unsigned iterations=1;
  //tree->SetEstimate(5000000);
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
      if(est<MAXMEM){
	m_result->reserve(est);
	if(m_histdim==2)m_result2->reserve(est);
      }
      else{
	m_result->reserve((unsigned int)MAXMEM+m_dim);//160 MB
	if (m_histdim==2) m_result2->reserve((unsigned int)MAXMEM+m_dim);//160 MB
	iterations=(unsigned int)(est/MAXMEM+1);
      }
    }
  }    
  unsigned evperit=nev/iterations+1;
  //  std::cout<<"Estimate: "<<tree->GetEstimate()<<std::endl;

  for (unsigned it=0;it<iterations;it++){
    if (m_sel==0){
      tree->Draw(m_formula.c_str(),m_cut.c_str(),"goff",evperit,evperit*it);
      if (tree->GetPlayer()->GetVar1()->GetNdata()!=(int)m_dim){
	std::cout<<"The dimension of the formula "<<m_formula<<" ("<<tree->GetPlayer()->GetVar1()->GetNdata()<<")"
		 <<" does not match the definition of variable "<<m_name<<m_dimstring<<" ("<<m_dim<<")"<<std::endl;
	assert(0);
      }
      double *val=tree->GetV1();
      double *val2=tree->GetV2();
      for (int i=0;i<tree->GetSelectedRows();i+=m_dim){
	if (val2){
	  singleincrement(&val[i],&val2[i]);
	}else{
	  singleincrement(&val[i]);
	}
      }
    }else{
      m_result->clear();
      m_result2->clear();
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
      double *val2=&((*m_result2)[0]);
      for (unsigned i=0;i<m_result->size();i+=m_dim){
	if(m_histdim==2)
	  singleincrement(&val[i],&val2[i]);
	else 
	  singleincrement(&val[i]);
      }
    }
  }    
  clock_gettime(CLOCK_REALTIME, &ts2);
  // std::cout<<"Moninputcollection "<<ts1.tv_nsec<<" "<<ts2.tv_nsec<<std::endl;
  unsigned long starttime=ts1.tv_sec*1000000+ts1.tv_nsec/1000;
  unsigned long endtime=ts2.tv_sec*1000000+ts2.tv_nsec/1000;
  //sometimes the clock goes backwards.
  if(endtime>starttime)m_timeprof+=(endtime-starttime);

}

float MonValue::timeProfile(){
  float timeprof=(float)m_timeprof/1e6;
  std::cout<<setiosflags(std::ios::left);
  std::cout<<std::setw(60)<<std::setfill(' ')<<m_name<<": "<<timeprof<<" seconds"<<std::endl;
  return timeprof;
}
  
void MonValue::setSharedLibDir(std::string sodir){
  m_sodir=sodir;
}
void MonValue::setDontCompile(bool dont){
  m_dontcompile=dont;
}
void MonValue::setDataType(std::string type){
  m_datatype = type;
}

std::vector<std::string> MonValue::parse(const std::string str, const std::string beg, const std::string sep, const std::string end){
  std::vector<std::string> retvec;
  unsigned int bpos=str.find(beg);
  if(bpos==(unsigned int)-1)return retvec;
  unsigned int epos=str.rfind(end);
  //unsigned int epos=str.find(end,pos+1);
  if(epos==(unsigned int)-1 || epos<bpos)return retvec;
  if (sep==""){
    retvec.push_back(str.substr(bpos+beg.length(),epos-bpos-beg.length()));
  } else{
    unsigned int mpos=str.find(sep,bpos+1);
    unsigned int len=beg.length();
    while(mpos!=(unsigned int)-1 && mpos<epos){
      retvec.push_back(str.substr(bpos+len,mpos-bpos-len));
      bpos=mpos;
      mpos=str.find(sep,mpos+1);
      len=sep.length();
    }
    retvec.push_back(str.substr(bpos+len,epos-bpos-len));
  }
  return retvec;
}
			    
const std::string MonValue::indexString(int index){
  int ind=index;
  std::vector<std::string>dims=parse(m_dimstring,"[","][","]");
  std::string retstring;
  char tmps[128];
  for (unsigned i=0;i<dims.size();i++){
    int fact=1;
    for (unsigned j=i+1;j<dims.size();j++){
      fact*=atoi(dims[j].c_str());
    }
    sprintf(tmps,"_%d",ind/fact);
    retstring+=tmps;
    ind-=ind/fact*fact;
  }
  return retstring;
}
    
    
    
