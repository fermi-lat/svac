// Header file
#include "MonValueImpls_t.h"
#include "Monitor/RFun.h"

// To attach to trees
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string.h>
#include <math.h> // needed to use functions isnan and isinf
#include <cassert>

const ULong64_t MonCounterDiff::s_maxVal64(0xFFFFFFFFFFFFFFFF);
const Float_t MonMinMax::s_huge(1.e20);

// Standard c'tor
MonCounter::MonCounter(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula,cut){
    m_current = new ULong64_t[m_dim];
    m_val = new ULong64_t[m_dim];
    reset();
  }

  // D'tor, no-op
MonCounter::~MonCounter(){
    delete [] m_current;
    delete [] m_val;
  }
  
  // Reset just nulls the values
void MonCounter::reset() {
    for (unsigned i=0;i<m_dim;i++){
      m_current[i] = 0;
      m_val[i] = 0;
    }
  }
void MonCounter::latchValue() {
    for (unsigned i=0;i<m_dim;i++){
      m_val[i] = m_current[i];
    }
  }

// Attach a MonCounter node to a TTree (unsigned int)
int MonCounter::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + "Counter_" + name();
  
  std::string leafType = fullName + m_dimstring + "/l";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "l");
  CheckLeafName(leafType.c_str());

  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str(),BufSize);
  return b != 0 ? 1 : -1;
}
  // += addition operator
void MonCounter::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonCounter::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_current[i] += (ULong64_t)val[i];
  }
}



// Standard c'tor
MonSecondListDouble::MonSecondListDouble(const char* name, const char* formula, const char* cut) 
  :MonValue(name,formula,cut){
  m_val = new Double_t[m_dim];
  reset();
}

  // D'tor, no-op
MonSecondListDouble::~MonSecondListDouble(){
  delete [] m_val;
}
  
  // Reset just nulls the values
void MonSecondListDouble::reset() {
    for (unsigned i=0;i<m_dim;i++)
      m_val[i] = 0;
}

void MonSecondListDouble::latchValue() {}

// Attach a MonSecondListDouble node to a TTree (unsigned int)
int MonSecondListDouble::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName;
   if(!IsTrackerMonJob)
    fullName = prefix + "OutD_" + name();
  else
    fullName = prefix + name();

  std::string leafType = fullName + m_dimstring + "/D";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "D");
  CheckLeafName(leafType.c_str());

  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str(),BufSize);
  return b != 0 ? 1 : -1;
}
  // value of m_val object is set
void MonSecondListDouble::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonSecondListDouble::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_val[i] = (Double_t)val[i];
  }
}



// Standard c'tor
MonSecondListFloat::MonSecondListFloat(const char* name, const char* formula, const char* cut) 
  :MonValue(name,formula,cut){
  m_val = new Float_t[m_dim];
  reset();
}

  // D'tor, no-op
MonSecondListFloat::~MonSecondListFloat(){
  delete [] m_val;
}
  
  // Reset just nulls the values
void MonSecondListFloat::reset() {
    for (unsigned i=0;i<m_dim;i++)
      m_val[i] = 0.0;
}

void MonSecondListFloat::latchValue() {}

// Attach a MonSecondListFloat node to a TTree (unsigned int)
int MonSecondListFloat::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName;
  if(!IsTrackerMonJob)
    fullName = prefix + "OutF_" + name();
  else
    fullName = prefix + name();
  std::string leafType = fullName + m_dimstring + "/F";
  
  Int_t BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafType.c_str());

  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str(),BufSize);
  return b != 0 ? 1 : -1;
}
  // value of m_val object is set
void MonSecondListFloat::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonSecondListFloat::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_val[i] = (Float_t)val[i];
  }
}

// Standard c'tor
MonSecondListULong64::MonSecondListULong64(const char* name, const char* formula, const char* cut) 
  :MonValue(name,formula,cut){
  m_val = new ULong64_t[m_dim];
  reset();
}

  // D'tor, no-op
MonSecondListULong64::~MonSecondListULong64(){
  delete [] m_val;
}
  
  // Reset just nulls the values
void MonSecondListULong64::reset() {
    for (unsigned i=0;i<m_dim;i++)
      m_val[i] = 0;
}

void MonSecondListULong64::latchValue() {}

// Attach a MonSecondListULong64 node to a TTree (unsigned int)
int MonSecondListULong64::attach(TTree& tree, const std::string& prefix) const {

  std::string fullName;

  if(!IsTrackerMonJob)
    fullName = prefix + "OutLI_" + name();
  else
    fullName = prefix + name();

  std::string leafType = fullName + m_dimstring + "/l";
  
  Int_t BufSize = GetBufSize(Int_t(m_dim), "l");
  CheckLeafName(leafType.c_str());

  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str(),BufSize);
  return b != 0 ? 1 : -1;
}
  // value of m_val object is set
void MonSecondListULong64::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonSecondListULong64::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_val[i] = (ULong64_t)val[i];
  }
}



// Standard c'tor
MonSecondListUInt::MonSecondListUInt(const char* name, const char* formula, const char* cut) 
  :MonValue(name,formula,cut){
  m_val = new UInt_t[m_dim];
  reset();
}

  // D'tor, no-op
MonSecondListUInt::~MonSecondListUInt(){
  delete [] m_val;
}
  
  // Reset just nulls the values
void MonSecondListUInt::reset() {
    for (unsigned i=0;i<m_dim;i++)
      m_val[i] = 0;
}

void MonSecondListUInt::latchValue() {}

// Attach a MonSecondListUInt node to a TTree (unsigned int)
int MonSecondListUInt::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName;
   if(!IsTrackerMonJob)
    fullName = prefix + "OutUI_" + name();
  else
    fullName = prefix + name();

  std::string leafType = fullName + m_dimstring + "/i";
  
  Int_t BufSize = GetBufSize(Int_t(m_dim), "i");
  CheckLeafName(leafType.c_str());

  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str(),BufSize);
  return b != 0 ? 1 : -1;
}
  // value of m_val object is set
void MonSecondListUInt::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonSecondListUInt::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_val[i] = (UInt_t)val[i];

  }
}

// Standard c'tor
MonSecondListNumber::MonSecondListNumber(const char* name, const char* formula, const char* cut) 
  :MonValue(name,formula,cut){
  m_val = new UInt_t[m_dim];
  reset();
}

  // D'tor, no-op
MonSecondListNumber::~MonSecondListNumber(){
  delete [] m_val;
}
  
  // Reset just nulls the values
void MonSecondListNumber::reset() {
    for (unsigned i=0;i<m_dim;i++)
      m_val[i] = 0;
}

void MonSecondListNumber::latchValue() {}

// Attach a MonSecondListNumber node to a TTree (unsigned int)
int MonSecondListNumber::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName;
   if(!IsTrackerMonJob)
    fullName = prefix + "Number_" + name();
  else
    fullName = prefix + name();

  std::string leafType = fullName + m_dimstring + "/i";
  
  Int_t BufSize = GetBufSize(Int_t(m_dim), "i");
  CheckLeafName(leafType.c_str());

  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str(),BufSize);
  return b != 0 ? 1 : -1;
}
  // value of m_val object is set
void MonSecondListNumber::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonSecondListNumber::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_val[i] = (UInt_t)val[i];
  }
}


MonRate::MonRate(const char* name, const char* formula, const char* cut)
  :MonValue(name,formula,cut){
  m_current = new ULong64_t[m_dim];
  m_val = new Float_t[m_dim];
  m_err = new Float_t[m_dim];
  reset();
}

MonRate::~MonRate(){
  delete [] m_current;
  delete [] m_val;
  delete [] m_err;
  //  if(m_timeintervalobj)
  // delete m_timeintervalobj;
}

void MonRate::reset() {
  m_timebin = 100000000.0;
  for (unsigned i=0;i<m_dim;i++){
    m_current[i] = 0;
    m_val[i] = 0.;
    m_err[i] = 0.;
  }

}

// += addition operator
void MonRate::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonRate::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_current[i] += (ULong64_t)val[i];
  }
}


// Attach a MonRate node to a TTree (val and err as float)
int MonRate::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameVal = prefix + "Rate_"+ name();
  std::string leafTypeVal = fullNameVal + m_dimstring + "/F";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafTypeVal.c_str());

  TBranch* b = tree.Branch(fullNameVal.c_str(),m_val,leafTypeVal.c_str(),BufSize);
  if ( b == 0 ) return -1;
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + m_dimstring + "/F";

  BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafTypeErr.c_str());


  TBranch* bErr = tree.Branch(fullNameErr.c_str(),m_err,leafTypeErr.c_str(),BufSize);
  return bErr != 0 ? 2 : -1;
}

void MonRate::latchValue() {
  // get timeinterval for this bin
  
  m_timebin =TimeInterval::m_interval;

  // done

  for (unsigned i=0;i<m_dim;i++){
    m_val[i] = Float_t(m_current[i]);
    m_err[i] = sqrt(m_val[i]);
    if(m_timebin>0.0){
      m_val[i] /= Float_t(m_timebin);
      m_err[i] /= Float_t(m_timebin);
      /*
      std::cout << "MonRate::latchValue; Dimension " << i << std::endl
		<< "Time interval retrived = "  <<std::endl
		<<  m_timebin 
		<< ",   m_current= " << m_current[i] 
		<< std::endl
		<< "Rate= " << m_val[i] << " +/- " << m_err[i] << std::endl;
      */

    }
    else{
      std::cout << "MonRate::latchValue; WARNING" << std::endl
		<< "m_timebin = " << m_timebin << std::endl
		<< "Rate and error set to ZERO" << std::endl;
      m_val[i] = 0.0;
      m_err[i] = 0.0;
    }
  }
}




MonHist1d::MonHist1d(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels, const char* titlelabel) 
    :MonValue(name,formula,cut){
  m_histdim=1;
  m_fillhistoalways = 1;
  m_seterrorstozero = 0; // default is to have errors (sqrt(BinContent)) for the histogram bins
  m_nofillvalue = -1000;
  float lbx,ubx;
  int nbx;
  lbx=ubx=0;
  nbx=0;
  std::vector<std::string> tt=parse(type,"[",",","]");

 
  if(tt.size()==3 || tt.size()==4 || tt.size() == 5){
    lbx=atof(tt[1].c_str());
    ubx=atof(tt[2].c_str());
    nbx=atoi(tt[0].c_str());
    if(tt.size()>3 ){
      m_nofillvalue=atoi(tt[3].c_str());
       m_fillhistoalways = 0;
    }
    if(tt.size()>4 ){
      m_seterrorstozero=Bool_t(atoi(tt[4].c_str()));
    }
  }else{
    std::cerr<<"MonHist1d variable "<<name<<" parameter declaration error. Aborting."<<std::endl;
    assert(0);
  }
  tt=parse(axislabels,"[",",","]");
  m_hist=new TH1F*[m_dim];
  char nm[128];
  for (unsigned int i=0;i<m_dim;i++){
    sprintf(nm,"%s%s",m_name.c_str(),indexString(i).c_str());
    m_hist[i]=new TH1F(nm,nm,nbx,lbx,ubx);
    if (tt.size()>0)m_hist[i]->GetXaxis()->SetTitle(tt[0].c_str());
    if (tt.size()>1)m_hist[i]->GetYaxis()->SetTitle(tt[1].c_str());
    if (strlen(titlelabel)!=0)m_hist[i]->SetTitle(titlelabel);
  }

}
MonHist1d::~MonHist1d(){
  // for (unsigned int i=0;i<m_dim;i++){
    // m_hist[i];
    //}
    //delete m_hist;
}
void MonHist1d::singleincrement(Double_t* val, Double_t* val2) {

  
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonHist1d::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    if((val[i] != Double_t(m_nofillvalue)) || m_fillhistoalways ){
      m_hist[i]->Fill((Float_t)val[i]);
    }
  }
}  
void MonHist1d::reset(){}

void MonHist1d::latchValue(){
  for (unsigned int i=0;i<m_dim;i++){
    if(m_seterrorstozero){
      for(UInt_t ibin=1;ibin<=m_hist[i]->GetNbinsX();ibin++)
	m_hist[i]->SetBinError(ibin,0.0);
    }
  }
}

int MonHist1d::attach(TTree& t,const std::string& prefix) const {return 1;}



MonHist1d_VecDim::MonHist1d_VecDim(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels, const char* titlelabel) 
    :MonValue(name,formula,cut){
  m_histdim=1;
  m_fillhistoalways = 0; // The default in this type of objects is NOT to fill histos if val=0
  m_nofillvalue = 0;
  m_seterrorstozero = 0; // default is to have errors (sqrt(BinContent)) for the histogram bins
  float lbx,ubx;
  int nbx;
  lbx=ubx=0;
  nbx=0;
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()==3 || tt.size()==4 || tt.size() ==5){
    lbx=atof(tt[1].c_str());
    ubx=atof(tt[2].c_str());
    nbx=atoi(tt[0].c_str());
    if(tt.size()>3){
      m_nofillvalue=atoi(tt[3].c_str());
      m_fillhistoalways = 0;
    }
    if(tt.size()>4 ){
      m_seterrorstozero=Bool_t(atoi(tt[4].c_str()));
    }
  }else{
    std::cerr<<"MonHist1d_VecDim variable "<<name<<" parameter declaration error. Aborting."<<std::endl;
    assert(0);
  }

  m_vecdim = Int_t(nbx);
  m_dim = unsigned(nbx);
  //std::cout << "Object " << name << ":m_dim set to value " << m_dim << std::endl;  
  tt=parse(axislabels,"[",",","]");
  char nm[128];
  sprintf(nm,"%s",m_name.c_str());
  m_hist=new TH1F(nm,nm,nbx,lbx,ubx);
  if (tt.size()>0)m_hist->GetXaxis()->SetTitle(tt[0].c_str());
  if (tt.size()>1)m_hist->GetYaxis()->SetTitle(tt[1].c_str());
  if (strlen(titlelabel)!=0)m_hist->SetTitle(titlelabel);


}
MonHist1d_VecDim::~MonHist1d_VecDim(){
  // for (unsigned int i=0;i<m_dim;i++){
    // m_hist[i];
    //}
    //delete m_hist;
}
void MonHist1d_VecDim::singleincrement(Double_t* val, Double_t* val2) {
  //  std::cout << m_name.c_str() << std::endl;
  for (unsigned i=0;i<m_dim;i++){
    //std::cout << "i,val= " << i << ", " << val[i] << std::endl;
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonHist1d_VecDim::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    if((val[i] != Double_t(m_nofillvalue)) || m_fillhistoalways )
      m_hist->Fill(Double_t(i),(Double_t)val[i]);
  }
}  
void MonHist1d_VecDim::reset(){}

void MonHist1d_VecDim::latchValue(){
  if(m_seterrorstozero){
    for(UInt_t ibin=1;ibin<=m_hist->GetNbinsX();ibin++)
      m_hist->SetBinError(ibin,0.0);
  }
  
}


int MonHist1d_VecDim::attach(TTree& t,const std::string& prefix) const {return 1;}







MonHist2d::MonHist2d(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel) 
    :MonValue(name,formula,cut){
  m_histdim=2;
  m_fillhistoalways = 1; // The default in this type of objects is to fill histos ALWAYS
  m_nofillvalue = -1;
  float lbx,ubx,lby,uby;
  int nbx,nby;
  lbx=ubx=lby=uby=0;
  nbx=nby=0;
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()==6 || tt.size()==7){
    lbx=atof(tt[1].c_str());
    ubx=atof(tt[2].c_str());
    nbx=atoi(tt[0].c_str());
    lby=atof(tt[4].c_str());
    uby=atof(tt[5].c_str());
    nby=atoi(tt[3].c_str());
    if(tt.size()==7){
      m_nofillvalue = atoi(tt[6].c_str());
      m_fillhistoalways = 0;
    }
  }else{
    std::cerr<<"MonHist2d variable "<<name<<" parameter declaration error. Aborting."<<std::endl;
    assert(m_histdim);
  }
  tt=parse(axislabels,"[",",","]");
  m_hist=new TH2F*[m_dim];
  char nm[128];
  for (unsigned int i=0;i<m_dim;i++){
    sprintf(nm,"%s%s",m_name.c_str(),indexString(i).c_str());
    m_hist[i]=new TH2F(nm,nm,nbx,lbx,ubx,nby,lby,uby);
    if (tt.size()>0)m_hist[i]->GetXaxis()->SetTitle(tt[0].c_str());
    if (tt.size()>1)m_hist[i]->GetYaxis()->SetTitle(tt[1].c_str());
    if (tt.size()>2)m_hist[i]->GetZaxis()->SetTitle(tt[2].c_str());
    if (strlen(titlelabel)!=0)m_hist[i]->SetTitle(titlelabel);
  }
}

MonHist2d::~MonHist2d(){
  // for (unsigned int i=0;i<m_dim;i++){
    // m_hist[i];
    //}
    //delete m_hist;
}
void MonHist2d::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]) || isnan(val2[i]) || isinf(val2[i]))
    {
      std::cout << std::endl << "MonHist2d::singleincrement: WARNING" << std::endl
		<< "Parameter " << m_name.c_str() << " has a nan or inf value"
		<< std::endl << "This should not happen at this point of the chain... "
		<< std::endl << "This value will not be used in the calculations" 
		<< std::endl;
      continue;
    }
    if(val[i] != Double_t(m_nofillvalue) || m_fillhistoalways )
      m_hist[i]->Fill((Float_t)val[i],(Float_t)val2[i]);
    // tmp
    /*
    if(strstr(name().c_str(),"SuspCalHi_Highest") || strstr(name().c_str(),"SuspCalLo_Highest") ){
      std::cout << "MonHist2d::singleincrement() for object " 
		<< name().c_str() << std::endl
		<< "Histo filled in bins x, y = " << val[i] 
		<< ", " << val2[i] << std::endl;
    }
    */
    // endtmp


  }
}  
void MonHist2d::reset(){}

void MonHist2d::latchValue(){}

int MonHist2d::attach(TTree& t,const std::string& prefix) const {return 1;}


MonHist2d_VecDim::MonHist2d_VecDim(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel) 
    :MonValue(name,formula,cut){
  m_histdim=1; // effectively, in what concerns to formulae, it is like a 1dim histogram
  m_fillhistoalways = 0; // The default in this type of objects is NOT to fill histos if val=0
  m_nofillvalue = 0;
  float lbx,ubx,lby,uby;
  int nbx,nby;
  lbx=ubx=lby=uby=0;
  nbx=nby=0;
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()==6 || tt.size()==7){
    lbx=atof(tt[1].c_str());
    ubx=atof(tt[2].c_str());
    nbx=atoi(tt[0].c_str());
    lby=atof(tt[4].c_str());
    uby=atof(tt[5].c_str());
    nby=atoi(tt[3].c_str());
    if(tt.size()==7){
     m_nofillvalue=atoi(tt[6].c_str());
     m_fillhistoalways = 0;
    }
  }else{
    std::cerr<<"MonHist2d_VecDim variable "<<name<<" parameter declaration error. Aborting."<<std::endl;
    assert(m_histdim);
  }
  m_vecdim[0]=Int_t(nbx);
  m_vecdim[1]=Int_t(nby);
  m_dim = unsigned(nbx*nby);

  tt=parse(axislabels,"[",",","]");
  char nm[128];
  sprintf(nm,"%s",m_name.c_str());
  m_hist=new TH2F(nm,nm,nbx,lbx,ubx,nby,lby,uby);
  if (tt.size()>0)m_hist->GetXaxis()->SetTitle(tt[0].c_str());
  if (tt.size()>1)m_hist->GetYaxis()->SetTitle(tt[1].c_str());
  if (tt.size()>2)m_hist->GetZaxis()->SetTitle(tt[2].c_str());
  if (strlen(titlelabel)!=0)m_hist->SetTitle(titlelabel);
}



MonHist2d_VecDim::~MonHist2d_VecDim(){
  // for (unsigned int i=0;i<m_dim;i++){
    // m_hist[i];
    //}
    //delete m_hist;
}
void MonHist2d_VecDim::singleincrement(Double_t* val, Double_t* val2) {
  Int_t z = 0;
  //std::cout << m_name.c_str() << std::endl;
  for(Int_t i = 0; i < m_vecdim[0];i++){
    for(Int_t j = 0; j < m_vecdim[1];j++){
      //std::cout << "i,j,val= " << i << ", " << j << ", " << val[z] << std::endl; 
      z = i*m_vecdim[1]+j;
      if(isnan(val[z]) || isinf(val[z]))
	{
	  std::cout << std::endl << "MonHist2d_VecDim::singleincrement: WARNING" << std::endl
		    << "Parameter " << m_name.c_str() << " has a nan or inf value"
		    << std::endl << "This should not happen at this point of the chain... "
		    << std::endl << "This value will not be used in the calculations" 
		    << std::endl;
	  continue;
	}
      
      if((val[z] != Double_t(m_nofillvalue)) || m_fillhistoalways )
	m_hist->Fill(Double_t(i),Double_t(j),Double_t(val[z]));
    }
  }  
}


void MonHist2d_VecDim::reset(){}

void MonHist2d_VecDim::latchValue(){}

int MonHist2d_VecDim::attach(TTree& t,const std::string& prefix) const {return 1;}




/////

MonHist2d_Index::MonHist2d_Index(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel) 
    :MonValue(name,formula,cut){
  m_histdim=1; // effectively, in what concerns to formulae, it is like a 1dim histogram
  m_fillhistoalways = 1; // The default in this type of objects is to fill histos always
  m_nofillvalue = 0;

  float lbx,ubx,lby,uby;
  int nbx,nby;
  lbx=ubx=lby=uby=0;
  nbx=nby=0;
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()==6 || tt.size() == 7){
    lbx=atof(tt[1].c_str());
    ubx=atof(tt[2].c_str());
    nbx=atoi(tt[0].c_str()); 
    lby=atof(tt[4].c_str());
    uby=atof(tt[5].c_str());
    nby=atoi(tt[3].c_str());
    if(tt.size() == 7){
      m_nofillvalue=atoi(tt[6].c_str());
      m_fillhistoalways = 0;
    }

  }else{
    std::cerr<<"MonHist2d_Index variable "<<name<<" parameter declaration error. Aborting."<<std::endl;
    assert(m_histdim);
  }

  m_maxindex = unsigned(nbx); // this will be used to loop over vector components, filling nbx times this histo
  m_dim = m_maxindex;

  tt=parse(axislabels,"[",",","]");
  char nm[128];
  sprintf(nm,"%s",m_name.c_str());
  m_hist=new TH2F(nm,nm,nbx,lbx,ubx,nby,lby,uby);
  if (tt.size()>0)m_hist->GetXaxis()->SetTitle(tt[0].c_str());
  if (tt.size()>1)m_hist->GetYaxis()->SetTitle(tt[1].c_str());
  if (tt.size()>2)m_hist->GetZaxis()->SetTitle(tt[2].c_str());
  if (strlen(titlelabel)!=0)m_hist->SetTitle(titlelabel);
}



MonHist2d_Index::~MonHist2d_Index(){
  // for (unsigned int i=0;i<m_dim;i++){
    // m_hist[i];
    //}
    //delete m_hist;
}
void MonHist2d_Index::singleincrement(Double_t* val, Double_t* val2) {
  
  // std::cout << m_name.c_str() << std::endl;
  for(unsigned index = 0; index < m_maxindex;index++){
      // std::cout << "index,val= " << index << ", " << val[z] << std::endl; 
    if(isnan(val[index]) || isinf(val[index]))
      {
	std::cout << std::endl << "MonHist2d_Index::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    if((val[index] != Double_t(m_nofillvalue)) || m_fillhistoalways )
      m_hist->Fill(index, (Float_t)val[index]);
    
  }
}  



void MonHist2d_Index::reset(){}

void MonHist2d_Index::latchValue(){}

int MonHist2d_Index::attach(TTree& t,const std::string& prefix) const {return 1;}




MonMean::MonMean(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula,cut),
     m_nVals(0),m_sum(0),m_sum2(0),
     m_val(0),m_err(0){
    m_nVals=new ULong64_t[m_dim];
    m_sum=new Double_t[m_dim];
    m_sum2=new Double_t[m_dim];
    m_val=new Float_t[m_dim];
    m_err=new Float_t[m_dim];
    reset();
  }
  
  // D'tor
MonMean::~MonMean(){
    delete [] m_nVals;
    delete [] m_sum;
    delete [] m_sum2;
    delete [] m_val;
    delete [] m_err;
  }

  // Latch the values, so calculate mean, rms, err_on_mean
void MonMean::latchValue() {
    for (unsigned i=0;i<m_dim;i++){
      if ( m_nVals[i] < 1 ) continue;
      m_val[i] = m_sum[i] / ((Double_t)m_nVals[i]);
      Double_t err2 = m_sum2[i];
      err2 /= ((Double_t)m_nVals[i]);
      err2 -= m_val[i]*m_val[i];    
      err2 /= ((Double_t)m_nVals[i]);
      m_err[i] = err2 > 0 ? TMath::Sqrt(err2) : 0.;
    }
  }

  // reset, null everything
void MonMean::reset() {
    for (unsigned i=0;i<m_dim;i++){
      m_err[i] = 0.;
      m_val[i] = 0.;
      m_nVals[i] = 0;
      m_sum[i] = 0.;
      m_sum2[i] = 0.;
    }
  }

// Attach a MonMean node to a TTree (mean and err as float)
int MonMean::attach(TTree& tree, const std::string& prefix) const {

  // std::cout << " MonMean::attach : name = " << m_name << std::endl; 

  std::string fullNameVal = prefix + "Mean_" + name();
  std::string leafTypeVal = fullNameVal + m_dimstring + "/F";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafTypeVal.c_str());


  TBranch* b = tree.Branch(fullNameVal.c_str(),m_val,leafTypeVal.c_str(),BufSize);
  if ( b == 0 ) return -1;
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + m_dimstring + "/F";

  BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafTypeErr.c_str());

  TBranch* bErr = tree.Branch(fullNameErr.c_str(),m_err,leafTypeErr.c_str(),BufSize);
  if ( bErr == 0 ) return -1;
  std::string fullNameN = fullNameVal + "_n";
  std::string leafTypeN = fullNameN + m_dimstring + "/l";

  BufSize = GetBufSize(Int_t(m_dim), "l");
  CheckLeafName(leafTypeN.c_str());


  TBranch* bN = tree.Branch(fullNameN.c_str(),m_nVals,leafTypeN.c_str(),BufSize);
  return bN != 0 ? 3 : -1;
}
  // add a value input the mean, so add to running sums
void MonMean::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i =0;i<m_dim;i++){
    // check for nan/inf values. If found, issue warning and skip event
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonMean::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_nVals[i]++;
    m_sum[i] += val[i];
    m_sum2[i] += (val[i]*val[i]);    
  }
}

MonTruncatedMean::MonTruncatedMean(const char* name, const char* formula, const char* cut, const char* type) 
    :MonMean(name,formula,cut){
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()!=2){
    std::cerr<<"MonTruncatedMean variable "<<name<<" bounds declaration error. Aborting."<<std::endl;
    assert(0);
  }

  m_lowerbound=atof(tt[0].c_str());
  m_upperbound=atof(tt[1].c_str());

}
  
  
  
void MonTruncatedMean::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i =0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonTruncatedMean::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    if (val[i]>=m_lowerbound && val[i]<=m_upperbound){
      m_nVals[i]++;
      m_sum[i] += val[i];
      m_sum2[i] += (val[i]*val[i]);    
    }
  }
}
MonTruncatedMeanFrac::MonTruncatedMeanFrac(const char* name, const char* formula, const char* cut, const char* type) 
    :MonMean(name,formula,cut){
  std::vector<std::string> tt=parse(type,"[","","]");
  if(tt.size()!=1){
    std::cerr<<"MonTruncatedMeanFrac variable "<<name<<" bounds declaration error. Aborting."<<std::endl;
    assert(0);
  }

  m_fraction=atof(tt[0].c_str());
  m_list=new std::list<double>[m_dim];
}
  
MonTruncatedMeanFrac::~MonTruncatedMeanFrac(){
  delete [] m_list;
}

void MonTruncatedMeanFrac::reset(){
  for (unsigned i=0;i<m_dim;i++){
    m_list[i].clear();
  }
  MonMean::reset();
}

void MonTruncatedMeanFrac::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i =0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonTruncatedMeanFrac::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_list[i].push_back(val[i]);
  }
}

void MonTruncatedMeanFrac::latchValue(){

  for (unsigned i =0;i<m_dim;i++){
    if (m_list[i].size()==0)continue;
    m_list[i].sort();
    unsigned int numentries=m_list[i].size();
    unsigned int remove=(unsigned int)((1.-m_fraction)*numentries);
    if (remove>0){
      unsigned int frm=remove/2;
      unsigned int erm=remove-frm;
      for (unsigned int j=0;j<frm;j++)m_list[i].pop_front();
      for (unsigned int j=0;j<erm;j++)m_list[i].pop_back();
    }
    if (m_list[i].size()==0)continue;
    double sum,sum2;
    sum=sum2=0;
    for (std::list<double>::iterator it=m_list[i].begin();it!=m_list[i].end();it++){
      sum+=(*it);
      sum2+=(*it)*(*it);
    }
    unsigned int nvals=m_list[i].size();
    m_nVals[i]=nvals;
    m_val[i]=sum/(double)nvals;
    Double_t err2 = sum2;
    err2 /= (Double_t)nvals;
    err2 -= m_val[i]*m_val[i];    
    err2 /= (Double_t)nvals;
    m_err[i] = err2 > 0 ? TMath::Sqrt(err2) : 0.;

  }
}

MonTruncatedMeanBoundsAndFrac::MonTruncatedMeanBoundsAndFrac(const char* name, 
							     const char* formula, 
							     const char* cut, const char* type) 
    :MonMean(name,formula,cut){
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()!=3){
    std::cerr<<"MonTruncatedMeanBoundsAndFrac variable "<<name<<" bounds declaration error. Aborting."<<std::endl;
    assert(0);
  }
  m_lowerbound=atof(tt[0].c_str());
  m_upperbound=atof(tt[1].c_str());
  m_fraction=atof(tt[2].c_str());

  m_list=new std::list<double>[m_dim];
}


MonTruncatedMeanBoundsAndFrac::~MonTruncatedMeanBoundsAndFrac(){
  delete [] m_list;
}

void MonTruncatedMeanBoundsAndFrac::reset(){
  for (unsigned i=0;i<m_dim;i++){
    m_list[i].clear();
  }
  MonMean::reset();
}


void MonTruncatedMeanBoundsAndFrac::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i =0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonTruncatedMeanBoundsAndFrac::singleincrement: WARNING" << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    if(val[i] >=m_lowerbound && val[i]<=m_upperbound) 
      m_list[i].push_back(val[i]);
  }
}


void MonTruncatedMeanBoundsAndFrac::latchValue(){
  for (unsigned i =0;i<m_dim;i++){
    if (m_list[i].size()==0)continue;
    m_list[i].sort();
    unsigned int numentries=m_list[i].size();
    unsigned int remove=(unsigned int)((1.-m_fraction)*numentries);
    if (remove>0){
      unsigned int frm=remove/2;
      unsigned int erm=remove-frm;
      for (unsigned int j=0;j<frm;j++)m_list[i].pop_front();
      for (unsigned int j=0;j<erm;j++)m_list[i].pop_back();
    }
    if (m_list[i].size()==0)continue;
    double sum,sum2;
    sum=sum2=0;
    for (std::list<double>::iterator it=m_list[i].begin();it!=m_list[i].end();it++){
      sum+=(*it);
      sum2+=(*it)*(*it);
    }
    unsigned int nvals=m_list[i].size();
    m_nVals[i]=nvals;
    m_val[i]=sum/(double)nvals;
    Double_t err2 = sum2;
    err2 /= (Double_t)nvals;
    err2 -= m_val[i]*m_val[i];    
    err2 /= (Double_t)nvals;
    m_err[i] = err2 > 0 ? TMath::Sqrt(err2) : 0.;

    // std::cout << "dim " << i << "; m_val, m_err = " << m_val[i] << ", " << m_err[i] << std::endl;
  }
}

// HERE the one for equal number of events

MonTruncatedMeanBoundsAndFracBigDataEqualNEvents::MonTruncatedMeanBoundsAndFracBigDataEqualNEvents(const char* name, 
												   const char* formula, 
												   const char* cut, const char* type) 
  :MonTruncatedMeanBoundsAndFracBigData(name,formula,cut,type){

  // nothing to be done here
}


void MonTruncatedMeanBoundsAndFracBigDataEqualNEvents::singleincrement(Double_t* val, Double_t* val2) {

  for (unsigned i =0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonTruncatedMeanBoundsAndFracBigDataEqualNEvents::singleincrement: WARNING" 
		  << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_datavector[i] =m_lowerbound-2.0;
    m_datavector[i] = val[i];
    /*
    std::cout << " MonTruncatedMeanBoundsAndFracBigData::singleincrement:" << std::endl
	      << "val[" << i<< "] = " << m_datavector[i] << std::endl;
    */
  }
  
  //std::cout << "MonTruncatedMeanBoundsAndFracBigData::Name " <<m_name.c_str() << std::endl;
  //std::cout << "MonTruncatedMeanBoundsAndFracBigData::singleincrement:Evt number " << m_evtcounter << std::endl; 
  m_evtcounter++;
  
  Int_t result = m_tmptree->Fill();


  if(result<0){
    std::cout<<"MonTruncatedMeanBoundsAndFracBigDataEqualNEvents::singleincrement:ERROR" <<std::endl
	     << "Error when writing into tree " << m_tmptree->GetName() << std::endl;
    assert(0);
  }
  
  /*
  else{
  if(result ==0){
  std::cout<<"MonTruncatedMeanBoundsAndFracBigDataEqualNEvents::singleincrement:WARNING" <<std::endl
  << "No data was written into branch " << m_leafname[i].c_str() << std::endl;
  //assert(0);
  }
  */

  // check size of tree
  /*
  if(m_evtcounter%1000 == 0){
    std::cout <<"MonTruncatedMeanBoundsAndFracBigDataEqualNEvents::singleincrement: INFO"
	      << std::endl
	      << "m_evtcounter= " << m_evtcounter << std::endl
	      << "Check size of m_tmptree for parameter with name " << m_name.c_str() << std::endl
	      << "Size (MBytes) = " << m_tmptree->GetTotBytes()/1000000 << std::endl
	      << "Size FILE (MBytes) = " << m_tmpfile->GetSize()/1000000 << std::endl;
  }
  */

}




// HERE 

MonTruncatedMeanBoundsAndFracBigData::MonTruncatedMeanBoundsAndFracBigData(const char* name, 
							     const char* formula, 
							     const char* cut, const char* type) 
    :MonMean(name,formula,cut),m_evtcounter(0){
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()!=3){
    std::cerr<<"MonTruncatedMeanBoundsAndFracBigData variable "<<name<<" bounds declaration error. Aborting."<<std::endl;
    assert(0);
  }
  
  m_lowerbound_str= tt[0];
  m_upperbound_str= tt[1];
  m_lowerbound=atof(tt[0].c_str());
  m_upperbound=atof(tt[1].c_str());
  m_fraction=atof(tt[2].c_str());

  m_datavector = new Double_t[m_dim];

 
  // initialize ttree to store info
 
 
  m_tmptreename = m_name+"_tree";

  m_tmptree = new TTree(m_tmptreename.c_str(),"Used to store data temporaly");
  Long64_t maxTreeSize = 500000000000;
  m_tmptree->SetMaxTreeSize(maxTreeSize);
  m_tmptree->SetMaxVirtualSize(0);

  for(unsigned int i = 0; i < m_dim; i++)
    {
      std::string leafnamedim = m_name+"_";
      char dimstring[5];
      sprintf(dimstring,"%d",i);
      leafnamedim  += dimstring;
      m_leafname.push_back(leafnamedim);
      
      std::string leafnamedimAndType(m_leafname[i]);
      leafnamedimAndType  += "/D";
      // Small buffer size (the root default is 32000, and here I use 2000) is used 
      // so that the info is quickly saved. 
      // Keep in mind the m_dim can be 12000, and thus many objects collectively occupying lots of
      // memory would be floating in the dynamic memory !!!
      m_tmptree->Branch(m_leafname[i].c_str(),&m_datavector[i],leafnamedimAndType.c_str(),2000);
    }
  

  // silly test (tmp)
  

  // endtmp


  
  // CREATE TFile where the tmp tree will reside (info written to disk).
  // Writing is necessary if info from tmp tree, for a time bin, is close to 2 GB
  // which gets into 3 GB (limit on a on a IA32 linux for single process) with another 
  // root stuff, producing a SEG FAULT. 

  // This object is designed to handle big amounts of data. Therefore By the  tmp 
  // tree will be written to disk.

  m_tmpfilename= m_name+"_tmp.root";
  m_tmpdir = "./"; // TO BE CHANGED, user should be able to define this.  HELPME !!

 
  Bool_t FileCreated = createfile4tmptree(m_tmpdir,m_tmpfilename);
  if(!FileCreated){
    std::string filename(m_tmpdir);
    filename += m_tmpfilename;
    std::cout << "MonTruncatedMeanBoundsAndFracBigData::MonTruncatedMeanBoundsAndFracBigData(): ERROR" << std::endl
	      << "Problems opening file " << filename.c_str() << std::endl
	      << "Exiting... " << std::endl;
    assert(0);
  }
 



}



Bool_t MonTruncatedMeanBoundsAndFracBigData::createfile4tmptree(std::string dir, std::string filename){

  std::string completename = dir;
  completename+=filename;
  
  // tmnp
  /*
  std::cout << "MonTruncatedMeanBoundsAndFracBigData::createfile4tmptree: filename= " <<  completename.c_str() 
	    << std::endl;
  */
  /// endtmp

  TDirectory* currentdir = gDirectory;
  m_tmpfile = new TFile (completename.c_str(), "RECREATE");
  m_tmptree->SetDirectory(gDirectory);
  currentdir->cd();
  //std::cout << "Tree name = " << m_tmptree -> GetName() << std::endl;
  //std::cout << "Tree directory = " << m_tmptree->GetDirectory()->GetPath() << std::endl;

  return m_tmpfile->IsOpen();
}



MonTruncatedMeanBoundsAndFracBigData::~MonTruncatedMeanBoundsAndFracBigData(){

  //std::cout << "Closing file" << std::endl;
  m_tmpfile->Write();
  m_tmpfile->Close();


  //std::cout << "Releasing memory" << std::endl;
  delete [] m_datavector;
  //delete m_tmptree; // already done in reset

  // delete files

   std::string deletefile = "rm -rf ";
   deletefile +=m_tmpdir;
   deletefile +=m_tmpfilename;

   // std::cout << deletefile.c_str() << std::endl;

   int filedeletion = system(deletefile.c_str());
   if(filedeletion){
     std::cout << "MonTruncatedMeanBoundsAndFracBigData::~MonTruncatedMeanBoundsAndFracBigData(): WARNING" << std::endl
	       << "Problems deleting file used to store intermediate ttree: " << std::endl
	       << "Command failed: " << deletefile.c_str() << std::endl;
	
      }
}

void MonTruncatedMeanBoundsAndFracBigData::reset(){
  for (unsigned i=0;i<m_dim;i++){
    m_datavector[i]=0.0;
  }

  /*
  std::cout << "MonTruncatedMeanBoundsAndFracBigData::reset()" << std::endl;
  
  */

  m_tmptree->Reset();

  // std::cout << "Deleting tree... " << std::endl;

  delete m_tmptree;

 
  // recreate tfile

  MonMean::reset();

  // std::cout << "Recreating tree... " << std::endl;
  m_tmptree = new TTree(m_tmptreename.c_str(),"Used to store data temporaly");
  Long64_t maxTreeSize = 5000000000000;
  m_tmptree->SetMaxTreeSize(maxTreeSize);
  
  for(unsigned int i = 0; i < m_dim; i++)
    {
      std::string leafnamedimAndType(m_leafname[i].c_str());
      leafnamedimAndType  += "/D";
      m_tmptree->Branch(m_leafname[i].c_str(),&m_datavector[i],leafnamedimAndType.c_str());
    }


 

  Bool_t FileCreated = createfile4tmptree(m_tmpdir,m_tmpfilename);
  if(!FileCreated){
    std::string filename(m_tmpdir);
    filename += m_tmpfilename;
    std::cout << "MonTruncatedMeanBoundsAndFracBigData::MonTruncatedMeanBoundsAndFracBigData(): ERROR" << std::endl
	      << "Problems opening file " << filename.c_str() << std::endl
	      << "Exiting... " << std::endl;
    assert(0);
  }

  /*
   std::cout << "m_tmptree->Print() after reset" << std::endl;
   m_tmptree->Print();
   std::cout << "Tree directory = " << m_tmptree->GetDirectory()->GetPath() << std::endl;
  */
}


void MonTruncatedMeanBoundsAndFracBigData::singleincrement(Double_t* val, Double_t* val2) {

  for (unsigned i =0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonTruncatedMeanBoundsAndFracBigData::singleincrement: WARNING" 
		  << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_datavector[i] =m_lowerbound-2.0;
    m_datavector[i] = val[i];
    /*
    std::cout << " MonTruncatedMeanBoundsAndFracBigData::singleincrement:" << std::endl
	      << "val[" << i<< "] = " << m_datavector[i] << std::endl;
    */
  }
  
  // std::cout << "MonTruncatedMeanBoundsAndFracBigData::singleincrement:Evt number " << m_evtcounter << std::endl; 

  m_evtcounter++;

  // Fill only the branch which contains data in the specified range

  for (unsigned int i =0;i<m_dim;i++){
    if(val[i] >=m_lowerbound && val[i]<=m_upperbound){ 
      Int_t result = m_tmptree->GetBranch(m_leafname[i].c_str())->Fill();
      if(result<0){
	std::cout<<"MonTruncatedMeanBoundsAndFracBigData::singleincrement:ERROR" <<std::endl
		 << "Error when writing into branch " << m_leafname[i].c_str() << std::endl;
	assert(0);
      }
      else{
	if(result ==0){
	  std::cout<<"MonTruncatedMeanBoundsAndFracBigData::singleincrement:ERROR" <<std::endl
		   << "No data was written into branch " << m_leafname[i].c_str() << std::endl;
	  assert(0);
	}
      }
    }
  }
}


void MonTruncatedMeanBoundsAndFracBigData::latchValue(){

  /*
  std::cout << "MonTruncatedMeanBoundsAndFracBigData::latchValue(); name " 
	    << m_name.c_str() << std::endl;
  */
 
  // create std::list in heap 
  // the SAME list will be used for all dimensions
  std::list<double> currentlist;
  for (unsigned i =0;i<m_dim;i++){
      // Read info for dimension i from m_tmptree and fill list 
      // and sort events in ascending order
      
      //m_tmptree->SetBranchStatus("*",0);
      //m_tmptree->SetBranchStatus(m_leafname[i].c_str(),1);
      
      TBranch* thisbranch = m_tmptree->GetBranch(m_leafname[i].c_str());
      
      if(thisbranch==0)
	{
	  std::cout << "MonTruncatedMeanBoundsAndFracBigData::latchValue():ERROR" << std::endl
		    << "Problem retrieving branch " << m_leafname[i].c_str()<< std::endl;
	  assert(0);
	}
      Double_t thisval(0.0);
      thisbranch->SetAddress(&thisval);
      
      ULong64_t treeentries = thisbranch->GetEntries();
      /*
      std::cout << "Entries in branch " << m_leafname[i].c_str() << ": " 
		<< treeentries << std::endl;
      */
      if(treeentries!=0){
	for(ULong64_t evt = 0; evt< treeentries;evt++)
	  {
	    Int_t berr = thisbranch->GetEntry(evt);
	    if(berr<0){
	      std::cout<<"MonTruncatedMeanBoundsAndFracBigData::latchValue():ERROR" <<std::endl
		       << "Entry " << evt << ";Error reading branch " << m_leafname[i].c_str() << std::endl;
	      assert(0);
	    }
	    else{
	      if(berr ==0){
		std::cout<<"MonTruncatedMeanBoundsAndFracBigData::latchValue():ERROR" <<std::endl
			 << "Entry " << evt << "; Nothing was read from branch " 
			 << m_leafname[i].c_str() << std::endl;
		assert(0);
	      }
	    }

	    if(thisval >=m_lowerbound && thisval<=m_upperbound){ 
	      currentlist.push_back(thisval);
	    }
	  }
	
	if (currentlist.size()==0)
	  continue;
	
	// std::cout << "i=" << i <<"; currentlist.size() = " << currentlist.size() << std::endl;
	currentlist.sort();
	
	unsigned int numentries=currentlist.size();
	unsigned int remove=(unsigned int)((1.-m_fraction)*numentries);
	if (remove>0){
	  unsigned int frm=remove/2;
	  unsigned int erm=remove-frm;
	  for (unsigned int j=0;j<frm;j++)currentlist.pop_front();
	  for (unsigned int j=0;j<erm;j++)currentlist.pop_back();
	}
	if (currentlist.size()==0){
	  currentlist.clear();
	  continue;
	}
	
	
	if (currentlist.size()== 1){
	  m_nVals[i] = 1;
	  m_err[i] = 0.0;
	  std::list<double>::iterator it=currentlist.begin();
	  m_val[i] = Double_t(*it);
	  
	  // std::cout <<  "List with one event: m_val[i], m_err[i]:" <<  m_val[i] << ", " << m_err[i] << std::endl; 
	  
	  currentlist.clear();
	  continue;
	}
	
	
	// list has more than 2 events
	double sum,sum2;
	sum=sum2=0;
	for (std::list<double>::iterator it=currentlist.begin();it!=currentlist.end();it++){
	  sum+=(*it);
	  sum2+=(*it)*(*it);
	}
	
	//std::cout << "i=" << i <<"; currentlist.size() BEFORE CALC= " << currentlist.size() << std::endl;
	unsigned int nvals=currentlist.size();
	m_nVals[i]=nvals;
	m_val[i]=sum/(double)nvals;
	Double_t err2 = sum2;
	err2 /= (Double_t)nvals;
	err2 -= m_val[i]*m_val[i];    
	err2 /= (Double_t)nvals;
	m_err[i] = err2 > 0 ? TMath::Sqrt(err2) : 0.;
	
	// release memory allocated by the list
	currentlist.clear();
	//std::cout << "dim " << i << "; m_val, m_err = " << m_val[i] << ", " << m_err[i] << std::endl;
      }
  }
}


MonCounterDiff::MonCounterDiff(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula, cut){
  m_lo=new ULong64_t[m_dim];
  m_hi=new ULong64_t[m_dim];
  m_val=new ULong64_t[m_dim];
  reset();
}

  // D'tor, no-op
MonCounterDiff::~MonCounterDiff(){
  delete [] m_lo;
  delete [] m_hi;
  delete [] m_val;
}
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
void MonCounterDiff::reset() {
  for (unsigned i=0;i<m_dim;i++){
    m_lo[i] = m_lo[i] >= m_hi[i] ? s_maxVal64 : m_hi[i];
    m_hi[i] = m_lo[i] >= m_hi[i] ? 0 : m_hi[i];
    m_val[i] = 0;
  }
}

  // Take the difference hi-lo and move it to the output value
void MonCounterDiff::latchValue() {
  for (unsigned i=0;i<m_dim;i++){
    m_val[i] = m_lo[i] < m_hi[i] ? m_hi[i] - m_lo[i] : 0;
  }
}

// Attach a MonCounterDif node to a TTree (unsigned int)
int MonCounterDiff::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + "CounterDiff_" + name();
  std::string leafType = fullName + m_dimstring+"/l";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "l");
  CheckLeafName(leafType.c_str());


  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str(),BufSize);
  return b != 0 ? 1 : -1;

}

  // Update the value, check to make sure that things make sense
void MonCounterDiff::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonCounterDiff::singleincrement: WARNING" 
		  << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    if ( m_lo[i] == s_maxVal64 ) {
      m_lo[i] = (ULong64_t)val[i];
    }
    if ( val[i] > m_hi[i] ) {
      m_hi[i] = (ULong64_t)val[i];
    }
  }
}




MonCounterDiffRate::MonCounterDiffRate(const char* name, const char* formula, const char* cut, const char* type) 
    :MonValue(name,formula, cut){
  m_lo=new ULong64_t[m_dim];
  m_hi=new ULong64_t[m_dim];
  m_hi_previous=new ULong64_t[m_dim];
  m_offset=new ULong64_t[m_dim];
  m_val=new Float_t[m_dim];
  m_err = new Float_t[m_dim];

  // initialize values for this object
  for (unsigned i=0;i<m_dim;i++){
    m_offset[i] = 0;
    m_lo[i] = 0;
    m_hi[i] = 0;
    m_hi_previous[i] = 0;
    m_val[i] = 0;
    m_err[i] = 0;
  }

  // fetch values from type argument

  std::vector<std::string> tt=parse(type,"[",",","]");
  
 
  if(tt.size()!=3){
    std::cerr<<" MonCounterDiffRate variable "<<name<<" bounds declaration error. Aborting."<<std::endl;
    assert(0);
  }

  if(atoi(tt[1].c_str()) < 0 || atoi(tt[1].c_str()) > 50)
    {
      std::cerr << "MonCounterDiffRate variable "<<name
		<< ": second argument (m_jumpmagbit) is out of bounds [0,50]. Aborting." <<std::endl;
      assert(0);
    }

  if(atoi(tt[0].c_str()) < 1000)
    {
      std::cerr << "MonCounterDiffRate variable "<<name
		<< ": first argument (m_jumpid) is NOT >1000. Aborting." <<std::endl;
      assert(0);
    }

  
  m_jumpid=UInt_t(atoi(tt[0].c_str()));
  m_jumpmagbit= UShort_t(atof(tt[1].c_str()));
  m_dataparamtype = tt[2]; 

  reset();
}

  // D'tor, no-op
MonCounterDiffRate::~MonCounterDiffRate(){
  delete [] m_lo;
  delete [] m_hi;
  delete [] m_hi_previous;
  delete [] m_offset;
  delete [] m_val;
  delete [] m_err;
}
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo, hi -> hi_previous and go on
  // in not, reset hi, hi_previous and lo
void MonCounterDiffRate::reset() {

 
	    

  m_timebin = 100000000.0;
  for (unsigned i=0;i<m_dim;i++){
    m_lo[i] = m_lo[i] >= m_hi[i] ? MonCounterDiff::s_maxVal64 : m_hi[i];
    m_hi[i] = m_lo[i] >= m_hi[i] ? 0 : m_hi[i];
    m_hi_previous[i] = m_lo[i] >= m_hi[i] ? m_lo[i] : m_hi[i];
    
    m_val[i] = 0.;
    m_err[i] = 0.;
  }

  // tmp
  /*
   std::cout << "MonCounterDiffRate::reset()" << std::endl
	     << "m_dim= " << m_dim << std::endl
	     << m_lo[0] << "\t" << m_hi_previous[0] << "\t" << m_hi[0] << std::endl;
  */
  // endmp

}

  // Take the difference hi-lo and move it to the output value
void MonCounterDiffRate::latchValue() {

  // get timeinterval for this bin
  
  m_timebin =TimeInterval::m_interval;

  //std::cout << "Time interval = " << m_timebin << std::endl;

  for (unsigned i=0;i<m_dim;i++){
    m_val[i] = m_lo[i] < m_hi[i] ? Float_t(m_hi[i] - m_lo[i]) : 0.0;
     m_err[i] = sqrt(m_val[i]);
    if(m_timebin>0.0){
      m_val[i] /= Float_t(m_timebin);
      m_err[i] /= Float_t(m_timebin);
      /*
      std::cout << "MonCounterDiffRate::latchValue; Dimension " << i << std::endl
		<< "Time interval retrived = "  <<std::endl
		<<  m_timebin 
		<< ",   m_current= " << m_current[i] 
		<< std::endl
		<< "Rate= " << m_val[i] << " +/- " << m_err[i] << std::endl;
      */

    }
    else{
      std::cout << "MonCounterDiffRate::latchValue; WARNING" << std::endl
		<< "m_timebin = " << m_timebin << std::endl
		<< "Rate and error set to ZERO" << std::endl;
      m_val[i] = 0.0;
      m_err[i] = 0.0;
    }
  }

   // tmp
  /*  
   std::cout << "MonCounterDiffRate::latch()" << std::endl
	     << "m_dim= " << m_dim << std::endl
	     << m_lo[0] << "\t" << m_hi_previous[0] << "\t" << m_hi[0] << std::endl
	     << "Rate = " << m_val[0] << "+/-" << m_err[0] << std::endl; 
  */
  // endmp



}

// Attach a MonCounterDif node to a TTree (unsigned int)
int MonCounterDiffRate::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameVal = prefix + "CounterDiffRate_" + name();
  std::string leafTypeVal = fullNameVal + m_dimstring+"/F";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafTypeVal.c_str());

  TBranch* b = tree.Branch(fullNameVal.c_str(),m_val,leafTypeVal.c_str(),BufSize);
  if ( b == 0 ) return -1;
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + m_dimstring + "/F";

  BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafTypeErr.c_str());


  TBranch* bErr = tree.Branch(fullNameErr.c_str(),m_err,leafTypeErr.c_str(),BufSize);
  return bErr != 0 ? 2 : -1;


}


  // Update the value, check to make sure that things make sense
void MonCounterDiffRate::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonCounterDiffRate::singleincrement: WARNING" 
		  << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    if ( m_lo[i] == MonCounterDiff::s_maxVal64 ) { // First event
      if(getDataType()== "MC" && getDataType() == m_dataparamtype){
	m_offset[i] = (ULong64_t)val[i];
	if(m_offset[i]/(pow(2,m_jumpmagbit)-1.0))
	  m_jumpcounter = Int_t(m_offset[i]/(pow(2,m_jumpmagbit)-1.0) + 0.5);
      }
      m_lo[i] = ULong64_t((ULong64_t)val[i] - m_offset[i]);

      // tmp
      /*
      std::cout << "First Event of chunk: " <<std::endl
		<< "m_lo[0], m_offset[0],m_jumpcounter  = " 
		<< m_lo[0] << ", " << m_offset[0] << ", " << m_jumpcounter 
		<< std::endl; 
      */
      // endtmp

    }


    if(getDataType()== "MC" && getDataType() == m_dataparamtype){
      // is mc data from oktober tests and we are dealing with m_sequence
      //expect pow(2,17) jumps in m_sequence values
      // the vector m_hi_previous is being used to catch these jumps
      
      
      // tmp
      // Info
      /*
      std::cout << "MonCounterDiffRate::singleincrement " << std::endl
		<< "Jump,lo, previous, hi, offset, val, hi-lo: " 
		<< m_jumpcounter << "\t" << m_lo[i] << "\t" << m_hi_previous[i] 
		<< "\t" << m_hi[i] << "\t" << m_offset[i] << "\t" << val[i] 
		<< "\t" << m_hi[i]-m_lo[i] << std::endl;
      
      */
      // endtmp



      ULong64_t previous_offset = m_offset[i]; // only used if weird stuff occurs... 
      if ( (val[i]-m_offset[i]) >= m_hi[i])
	{
	  // val[i] is supposed to always increase
	  m_hi_previous[i] = m_hi[i]>m_lo[i] ? m_hi[i] : m_lo[i];
	  
	  if((val[i]-m_offset[i])-m_hi_previous[i] > m_jumpid)
	    { // there was a jump; update offset
	      m_jumpcounter++;
	      if(ULong64_t(m_jumpcounter* pow(2,m_jumpmagbit))<m_hi_previous[i])
		{
		   std::cout << "MonCounterDiffRate::singleincrement: ERROR" << std::endl
			     << "Object " << name().c_str() << std::endl
			     << "Weird values: m_jumpcounter* pow(2," << m_jumpmagbit << "))<m_hi_previous[i]" << std::endl
			     << "Jump,lo, previous, hi, offset, val, hi-lo: " 
			     << m_jumpcounter << "\t" << m_lo[i] << "\t" << m_hi_previous[i] 
			     << "\t" << m_hi[i] << "\t" << m_offset[i] << "\t" << val[i] 
			     << "\t" << m_hi[i]-m_lo[i] << std::endl;

		}
	      else
		m_offset[i] = ULong64_t(ULong64_t(m_jumpcounter* pow(2,m_jumpmagbit)) -  m_hi_previous[i]); 
	    }

	  if((val[i]-m_offset[i]) >=0)
	    m_hi[i] = ULong64_t(val[i])-m_offset[i];
	  else
	    {
	      std::cout << "MonCounterDiffRate::singleincrement: ERROR" << std::endl
			<< "Object " << name().c_str() << std::endl
			<< "Weird values: val[i]-m_offset[i] <0 " << std::endl
			<< "Jump,lo, previous, hi, offset, val, hi-lo: " 
			<< m_jumpcounter << "\t" << m_lo[i] << "\t" << m_hi_previous[i] 
			<< "\t" << m_hi[i] << "\t" << m_offset[i]<< "\t" << val[i] 
			<< "\t" << m_hi[i]-m_lo[i] <<  std::endl;

	      m_jumpcounter--;
	      m_offset[i] = previous_offset;
	      std::cout << "The offset was certainly to large... probably i should not jumped before... " 
			<< std::endl
			<< "Reducing the jumpcounter by one and retrieving the prevoius offset:" << std::endl
			<< "Current jumpcounter, offset = " << m_jumpcounter 
			<< "\t" << m_offset[i] << std::endl;

	      if((val[i]-m_offset[i]) >=0)
		m_hi[i] = ULong64_t(val[i])-m_offset[i];

	    }
	   /*
	  std::cout << "Info on value " << std::endl
		    << "Current Jump, lo, previous, hi, offset: " << m_jumpcounter << "\t" << m_lo[i] << "\t" << m_hi_previous[i] << "\t" << m_hi[i] << "\t" << m_offset[i] <<std::endl;
	  */
	}
      else
	{
	  std::cout << std::endl 
		    << "MonCounterDiffRate::singleincrement: WARNING" << std::endl
		    << "When dealing with quantity " << name().c_str() << "," << std::endl
		    << "it was found that  val[i] <= m_hi[i] for i = " << i << std::endl
		    << "val[i] = " << val[i] << "; m_hi[i] = " << m_hi[i] << std::endl
		    << "This should not happen for this parameter" << std::endl 
		    << std::endl;
	}
    }

    else{ // is experimental data, or mc data but we are not dealing with Sequence 
      // the vector m_hi_previous is not being used
      if ( val[i] > m_hi[i] ) {
	m_hi[i] = (ULong64_t)val[i];
      }
      
    }
    
  }
  
}


MonDoubleDiffRate::MonDoubleDiffRate(const char* name, const char* formula, const char* cut, const char* type) 
    :MonValue(name,formula, cut){
  m_lo=new ULong64_t[m_dim];
  m_hi=new ULong64_t[m_dim];
  //m_hi_previous=new ULong64_t[m_dim];
  //m_offset=new ULong64_t[m_dim];
  m_val=new Double_t[m_dim];
  //m_err = new Float_t[m_dim];

  // initialize values for this object
  for (unsigned i=0;i<m_dim;i++){
    //m_offset[i] = 0;
    m_lo[i] = 0;
    m_hi[i] = 0;
    //m_hi_previous[i] = 0;
    m_val[i] = 0.;
    //m_err[i] = 0.;
  }

  m_convertTicksToTime = 0.00000005;
  m_convertToPercent = 100.0;


   std::vector<std::string> tt=parse(type,"[",",","]");
  
 
  if(tt.size()!=1){
    std::cerr<<" MonDoubleDiffRate variable "<<name<<" bounds declaration error. Aborting."<<std::endl;
    assert(0);
  }


  m_dataparamtype = tt[0]; 



  reset();
}

  // D'tor, no-op
MonDoubleDiffRate::~MonDoubleDiffRate(){
  delete [] m_lo;
  delete [] m_hi;
  //delete [] m_hi_previous;
  //delete [] m_offset;
  delete [] m_val;
  //delete [] m_err;
}
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo, and go on
  // in not, reset hi, and lo
void MonDoubleDiffRate::reset() {

 
	    

  m_timebin = 100000000.0;
  for (unsigned i=0;i<m_dim;i++){
    m_lo[i] = m_lo[i] >= m_hi[i] ? MonCounterDiff::s_maxVal64 : m_hi[i];
    m_hi[i] = m_lo[i] >= m_hi[i] ? 0 : m_hi[i];
    //m_hi_previous[i] = m_lo[i] >= m_hi[i] ? m_lo[i] : m_hi[i];
    
    m_val[i] = 0.;
    //m_err[i] = 0.;
  }

}

  // Take the difference hi-lo and move it to the output value
void MonDoubleDiffRate::latchValue() {

  // get timeinterval for this bin
  
  m_timebin =TimeInterval::m_interval;

  //std::cout << "Time interval = " << m_timebin << std::endl;

  for (unsigned i=0;i<m_dim;i++){
    m_val[i] = m_lo[i] < m_hi[i] ? Double_t(m_hi[i] - m_lo[i]) : 0.0;
    m_val[i] *= Double_t(m_convertTicksToTime*m_convertToPercent);

    // m_err[i] = sqrt(m_val[i]);
    if(m_timebin>0.0){
      m_val[i] /= m_timebin;
      //m_err[i] /= Float_t(m_timebin);
      
      /*
      std::cout << "MonDoubleDiffRate::latchValue; Dimension " << i << std::endl
		<< "Time interval retrived = "  <<std::endl
		<<  m_timebin 
		<< ",   m_lo, m_hi= " << m_lo[i] << " " << m_hi[i] << std::endl 
		<< std::endl
		<< "Rate= " << m_val[i] << std::endl;
      */

    }
    else{
      std::cout << "MonDoubleDiffRate::latchValue; WARNING" << std::endl
		<< "m_timebin = " << m_timebin << std::endl
		<< "Rate set to ZERO" << std::endl;
      m_val[i] = 0.0;
      // m_err[i] = 0.0;
    }
  }


}

// Attach a MonCounterDif node to a TTree (unsigned int)
int MonDoubleDiffRate::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameVal = prefix + "DoubleDiffRate_" + name();
  std::string leafTypeVal = fullNameVal + m_dimstring+"/D";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "D");
  CheckLeafName(leafTypeVal.c_str());

  TBranch* b = tree.Branch(fullNameVal.c_str(),m_val,leafTypeVal.c_str(),BufSize);
  if ( b == 0 ) 
    return -1;
  else
    return 1;// 1 branch attached

  /*  ERRORS DO NOT APPLY TO THIS OBJECT
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + m_dimstring + "/D";

  BufSize = GetBufSize(Int_t(m_dim), "D");
  CheckLeafName(leafTypeErr.c_str());


  TBranch* bErr = tree.Branch(fullNameErr.c_str(),m_err,leafTypeErr.c_str(),BufSize);
  return bErr != 0 ? 2 : -1;
  */

}


  // Update the value, check to make sure that things make sense
void MonDoubleDiffRate::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonDoubleDiffRate::singleincrement: WARNING" 
		  << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }

    // If data type is MC and this quantity has flag MC in config file, 
    // then a different computation is required. 
    /// For the time being, nothing will be done, which measn that the 
    // final value will be zero. 

    if(getDataType()== "MC" && getDataType() == m_dataparamtype)
      continue;
    
    if ( m_lo[i] == MonCounterDiff::s_maxVal64 ) { // First event
      m_lo[i] = (ULong64_t)val[i];
    }

    if ( val[i] > m_hi[i] ) {
      m_hi[i] = (ULong64_t)val[i];
    }
    /*
    std::cout << "MonDoubleDiffRate::singleincrement; Dimension " << i << std::endl
	      << "m_lo, m_hi= " << m_lo[i] << ", " << m_hi[i] << std::endl 
	      << std::endl;
    */

    
  }
    
}





// Attach a MonMinMax node to a TTree (unsigned int)
int MonMinMax::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameMin = prefix + "Min_" + name();
  //fullNameMin += "_min";
  std::string leafTypeMin = fullNameMin+m_dimstring + "/F";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "F");
  CheckLeafName(leafTypeMin.c_str());


  std::string fullNameMax = prefix + "Max_" +name();
  //fullNameMax += "_max";
  std::string leafTypeMax = fullNameMax +m_dimstring+ "/F";

  CheckLeafName(leafTypeMax.c_str());

  TBranch* b = tree.Branch(fullNameMin.c_str(),m_min,leafTypeMin.c_str(),BufSize);
  if ( b == 0 ) return -1;
  b = tree.Branch(fullNameMin.c_str(),m_max,leafTypeMax.c_str(),BufSize);
  return b != 0 ? 2 : -1;
}

MonMinMax::MonMinMax(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula,cut){
  m_min=new Float_t[m_dim];
  m_max=new Float_t[m_dim];
  reset();
}

  // D'tor
MonMinMax::~MonMinMax(){
  delete [] m_min;
  delete [] m_max;
}
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
void MonMinMax::reset() {
  for (unsigned i=0;i<m_dim;i++){
    m_min[i] = s_huge;
    m_max[i] = -s_huge;
  }
}
  // Update the value, check to make sure that things make sense
void MonMinMax::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonMinMax::singleincrement: WARNING" 
		  << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }
    m_min[i] = m_min[i] < (Float_t)val[i] ? m_min[i] : (Float_t)val[i];
    m_max[i] = m_max[i] > (Float_t)val[i] ? m_max[i] : (Float_t)val[i];
  }
}

//reset 
void MonMinMax::latchValue(){
}

// Attach a MonValueChange node to a TTree 
int MonValueChange::attach(TTree& tree, const std::string& prefix) const {
  std::string branchName;
  std::string leafName;
  std::string fullName = prefix + "ValChange_" +name();
  branchName= fullName+"xxxnchanges";
  leafName= branchName+m_dimstring + "/i";

  Int_t BufSize = GetBufSize(Int_t(m_dim), "i");
  CheckLeafName(leafName.c_str());
  

  TBranch* b = tree.Branch(branchName.c_str(),m_nvalues,leafName.c_str(),BufSize);
  if ( b == 0 ) return -1;
  branchName= fullName+"xxxfirstval";
  leafName= branchName+m_dimstring + "/D";
  BufSize = GetBufSize(Int_t(m_dim), "D");
  CheckLeafName(leafName.c_str());
  b = tree.Branch(branchName.c_str(),m_firstval,leafName.c_str(),BufSize);
  if ( b == 0 ) return -1;
  branchName= fullName+"xxxlastval";
  leafName= branchName+m_dimstring + "/D";
  CheckLeafName(leafName.c_str());
  b = tree.Branch(branchName.c_str(),m_lastval,leafName.c_str(),BufSize);
  if ( b == 0 ) return -1;
  char valname[128];
  for (unsigned int i=0;i<m_numval;i++){
    sprintf(valname,"xxxnewvalxxx%d",i);
    branchName= fullName+valname;
    leafName= branchName+m_dimstring + "/D";
    CheckLeafName(leafName.c_str());
    b = tree.Branch(branchName.c_str(),m_values[i],leafName.c_str(),BufSize);
    if ( b == 0 ) return -1;
    sprintf(valname,"xxxnewtimexxx%d",i);
    branchName= fullName+valname;
    leafName= branchName+m_dimstring + "/D";
    CheckLeafName(leafName.c_str());
    b = tree.Branch(branchName.c_str(),m_times[i],leafName.c_str(),BufSize);
    if ( b == 0 ) return -1;
  }
  return 0;
}

MonValueChange::MonValueChange(const char* name, const char* formula, const char* cut,const char* type) 
    :MonValue(name,formula,cut){
  //m_histdim=2;
  std::vector<std::string> tt=parse(type,"[","","]"); 
  if(tt.size()!=1){
    std::cerr<<"MonValueChange variable "<<name<<" parameter declaration error. Aborting."<<std::endl;
    assert(0);
  }
  m_numval=atoi(tt[0].c_str());
  m_firstval=new Double_t[m_dim];
  m_lastval=new Double_t[m_dim];
  m_nvalues=new UInt_t[m_dim];
  m_startrun=new Bool_t [m_dim];
  
  m_values=new Double_t*[m_numval];
  m_times=new Double_t*[m_numval];
  for (unsigned i=0;i<m_numval;i++){
    m_values[i]=new Double_t[m_dim];
    m_times[i]=new Double_t[m_dim];
  }
  for (unsigned i=0;i<m_dim;i++)m_startrun[i]=true;
  reset();
}

  // D'tor
MonValueChange::~MonValueChange(){
  delete [] m_firstval;
  delete [] m_lastval;
  delete [] m_nvalues;;
  delete [] m_startrun;
  for (unsigned int i=0;i<m_numval;i++){
    delete [] m_values[i];
    delete [] m_times[i];
  }
  delete [] m_values;
  delete [] m_times;
}
  
  // Reset
void MonValueChange::reset() {
  for (unsigned i=0;i<m_dim;i++){
    m_firstval[i]=m_lastval[i];
    m_nvalues[i]=0;
    for (unsigned int j=0;j<m_numval;j++){
      m_values[j][i]=0;
      m_times[j][i]=0;
    }
  }
}
  // Update the value, check to make sure that things make sense
void MonValueChange::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if(isnan(val[i]) || isinf(val[i]))
      {
	std::cout << std::endl << "MonValueChange::singleincrement: WARNING" 
		  << std::endl
		  << "Parameter " << m_name.c_str() << " has a nan or inf value"
		  << std::endl << "This should not happen at this point of the chain... "
		  << std::endl << "This value will not be used in the calculations" 
		  << std::endl;
	continue;
      }

    if (val[i]!=m_lastval[i]&&m_startrun[i]==false){
      if(m_nvalues[i]<m_numval){
	m_values[m_nvalues[i]][i]=(Double_t)val[i];
	m_times[m_nvalues[i]][i]=Double_t(val2[i]);
      }
      m_lastval[i]=(Double_t)val[i];
      m_nvalues[i]++;
    }
    if(m_startrun[i]){
      m_firstval[i]=(Double_t)val[i];
      m_lastval[i]=(Double_t)val[i];
      m_startrun[i]=false;
    }
  }
}

void MonValueChange::latchValue() {
}

// Destructor for MonValueCol;

MonValueCol::~MonValueCol(){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    delete (*itr);
  }
}
// Add a node to a MonValueCol
// Note that this does not operater recursively
void MonValueCol::addVal(MonValue& val){
  std::map<std::string,MonValue*>::const_iterator itrFind = m_nameMap.find(val.name());
  if ( itrFind != m_nameMap.end() ) {
    //    std::cerr << "Already have a variable " << val.name() 
    //	      << " in this collection" << std::endl;
    return;
  }
  m_nameMap[val.name()] = &val;
  m_vals.push_back(&val);
}

// find a node inside a collection
// Note that this does not recursively search
MonValue* MonValueCol::findByName(const std::string& theName){
  std::map<std::string,MonValue*>::iterator itrFind = m_nameMap.find(theName);
  return itrFind != m_nameMap.end() ? itrFind->second : 0;
}

// Attach a collection of nodes to a tree
// This does operate recursively
int MonValueCol::attach(TTree& tree, const std::string& pref) const {
  int retVal(0);
  std::string fullPrefix = pref;
  fullPrefix += prefix();
  for ( std::list<MonValue*>::const_iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    int testVal = (*itr)->attach(tree,fullPrefix);
    if ( testVal < 0 ) return testVal;
    retVal += testVal;
  }
  return retVal;
}

// Reset all the nodes in a collection
// This does operate recursively
void MonValueCol::reset(){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->reset();
  }
}

// Latch the values for all the nodes in a collection
// This does operate recursively
void MonValueCol::latchValue() {
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->latchValue();
  }
}

// Increment the values for all the nodes in a collection
// This does operate recursively
void MonValueCol::increment(TTree* tree) {
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {

    //tmp
    /*
    std::cout << " MonValueCol::increment: Debug INFO; " << std::endl
	      << " Working with output parameter name " << (*itr)->name().c_str() 
	      << std::endl << std::endl;
    */
    // endtmp

    (*itr)->increment(tree);
  }
}

void MonValueCol::makeProxy(TTree* tree){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->makeProxy(tree);
  }
}
void MonValueCol::setSharedLibDir(std::string sodir){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->setSharedLibDir(sodir);
  }
}
void MonValueCol::setDontCompile(bool dont){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->setDontCompile(dont);
  }
}
void MonValueCol::setDataType(std::string type){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->setDataType(type);
  }
}



float MonValueCol::timeProfile(){
  float tp=0;
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    tp+=(*itr)->timeProfile();
  }
  std::cout<<setiosflags(std::ios::left);
  std::cout<<"-------------------------------------------------------"<<std::endl;
  std::string tm="Total time usage for collection "+m_name;
  std::cout<<std::setw(60)<<std::setfill(' ')<<tm<<": "<<tp<<" seconds"<<std::endl;
  return tp;
}

MonValue* MonValFactory::makeMonValue(std::map<std::string,std::string> obj){
  std::string type=obj["type"];
  std::string name=obj["name"];
  std::string formula=obj["formula"];
  std::string cut=obj["cut"];

  std::string axislabels=obj["axisdesc"];
  std::string titlelabel=obj["titledesc"];

  /*
  if (strstr(type.c_str(),"histogram-1d")){
    std::cout << "Name histo = " << name.c_str() << std::endl;
    std::cout << "Axis labels = " << axislabels.c_str() << std::endl;
    std::cout << "Title = " << titlelabel.c_str() << std::endl;
  }
  */

  if (type=="mean"){
    return new MonMean(name.c_str(),formula.c_str(),cut.c_str());
  }else if (strstr(type.c_str(),"truncatedmeanboundandfracbigdataequaln")){
    return new MonTruncatedMeanBoundsAndFracBigDataEqualNEvents(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"truncatedmeanboundandfracbigdata")){
    return new MonTruncatedMeanBoundsAndFracBigData(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"truncatedmeanboundandfrac")){
    return new MonTruncatedMeanBoundsAndFrac(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"truncatedmeanfrac")){
    return new MonTruncatedMeanFrac(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"truncatedmean")){
    return new MonTruncatedMean(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  }  else if (type=="counter"){
    return new MonCounter(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="rate"){
    return new MonRate(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="minmax"){
    return new MonMinMax(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="counterdiff"){
    return new MonCounterDiff(name.c_str(),formula.c_str(),cut.c_str());
  } else if (strstr(type.c_str(),"doublediffrate")){
    return new MonDoubleDiffRate(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"counterdiffrate")){
    return new MonCounterDiffRate(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (type=="outputdouble"){
    return new MonSecondListDouble(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="outputfloat"){
    return new MonSecondListFloat(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="outputuint"){
    return new MonSecondListUInt(name.c_str(),formula.c_str(),cut.c_str()); 
  } else if (type=="outputnumber"){
    return new MonSecondListNumber(name.c_str(),formula.c_str(),cut.c_str()); 
  } else if (type=="outputlint"){
    return new MonSecondListULong64(name.c_str(),formula.c_str(),cut.c_str()); 
  } else if (strstr(type.c_str(),"valuechange")){
    return new MonValueChange(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"histogram-1d")){
    return new MonHist1d(name.c_str(),formula.c_str(),cut.c_str(),type.c_str(),axislabels.c_str(),titlelabel.c_str());
  } else if (strstr(type.c_str(),"histogram-2d")){
    return new MonHist2d(name.c_str(),formula.c_str(),cut.c_str(),type.c_str(),axislabels.c_str(),titlelabel.c_str());
  } else if (strstr(type.c_str(),"histogram-vecdim-1d")){
    return new MonHist1d_VecDim(name.c_str(),formula.c_str(),cut.c_str(),type.c_str(),axislabels.c_str(),titlelabel.c_str());
  } else if (strstr(type.c_str(),"histogram-vecdim-2d")){
    return new MonHist2d_VecDim(name.c_str(),formula.c_str(),cut.c_str(),type.c_str(),axislabels.c_str(),titlelabel.c_str());
  } else if (strstr(type.c_str(),"histogram-index-2d")){
    return new MonHist2d_Index(name.c_str(),formula.c_str(),cut.c_str(),type.c_str(),axislabels.c_str(),titlelabel.c_str());
  }else{
    std::cerr<<"No such type "<<type<<std::endl;
    assert(0);
  }
}


MonValueCol* MonValFactory::makeMonValueCol(std::list<std::map<std::string,std::string> > monlist, const char* name,  const char* prefix){
  MonValueCol* newcol=new MonValueCol(name,prefix);
  for ( std::list<std::map<std::string,std::string> >::iterator itr = monlist.begin(); itr != monlist.end(); itr++ ) { 
    newcol->addVal(*makeMonValue(*itr));
  }
  return newcol;
}

// initialization of static data members

Double_t TimeInterval::m_interval = 10000000.0;
