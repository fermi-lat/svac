// Header file
#include "MonValueImpls_t.h"

// To attach to trees
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"

#include <iostream>
#include <iomanip>
#include <string.h>

const ULong64_t MonCounterDiff::s_maxVal64(0xFFFFFFFFFFFFFFFF);
const Float_t MonMinMax::s_huge(1e35);

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
  std::string fullName = prefix + name();
  std::string leafType = fullName + m_dimstring + "/l";
  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str());
  return b != 0 ? 1 : -1;
}
  // += addition operator
void MonCounter::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    m_current[i] += (ULong64_t)val[i];
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
  m_timebin = 100000000;
  for (unsigned i=0;i<m_dim;i++){
    m_current[i] = 0;
    m_val[i] = 0.;
    m_err[i] = 0.;
  }

  //m_timeintervalobj=new TimeInterval();
}

// += addition operator
void MonRate::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    m_current[i] += (ULong64_t)val[i];
  }
}


// Attach a MonRate node to a TTree (val and err as float)
int MonRate::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameVal = prefix + name();
  std::string leafTypeVal = fullNameVal + m_dimstring + "/F";
  TBranch* b = tree.Branch(fullNameVal.c_str(),m_val,leafTypeVal.c_str());
  if ( b == 0 ) return -1;
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + m_dimstring + "/F";
  TBranch* bErr = tree.Branch(fullNameErr.c_str(),m_err,leafTypeErr.c_str());
  return bErr != 0 ? 2 : -1;
}

void MonRate::latchValue() {
  // get timeinterval for this bin
  
  m_timebin =TimeInterval::m_interval;
 
  // done

  for (unsigned i=0;i<m_dim;i++){
    m_val[i] = Float_t(m_current[i]);
    m_err[i] = sqrt(m_val[i]);
    if(m_timebin>0){
      m_val[i] /= Float_t(m_timebin);
      m_err[i] /= Float_t(m_timebin);
    }
    else{
      // time interval is somewhere between 0 and 1. 
      // We choose a comprimise value of 0.5
      // The numbers are certainly not fully correct... 
      // but that is whaat we have.
      m_val[i] /= 0.5;
      m_err[i] /= 0.5;
    }
  }
}




MonHist1d::MonHist1d(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels, const char* titlelabel) 
    :MonValue(name,formula,cut){
  m_histdim=1;
  float lbx,ubx;
  int nbx;
  lbx=ubx=0;
  nbx=0;
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()==3){
    lbx=atof(tt[1].c_str());
    ubx=atof(tt[2].c_str());
    nbx=atoi(tt[0].c_str());
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
    m_hist[i]->Fill((Float_t)val[i]);
  }
}  
void MonHist1d::reset(){}

void MonHist1d::latchValue(){}

int MonHist1d::attach(TTree& t,const std::string& prefix) const {return 1;}

MonHist2d::MonHist2d(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel) 
    :MonValue(name,formula,cut){
  m_histdim=2;
  float lbx,ubx,lby,uby;
  int nbx,nby;
  lbx=ubx=lby=uby=0;
  nbx=nby=0;
  std::vector<std::string> tt=parse(type,"[",",","]");
  if(tt.size()==6){
    lbx=atof(tt[1].c_str());
    ubx=atof(tt[2].c_str());
    nbx=atoi(tt[0].c_str());
    lby=atof(tt[4].c_str());
    uby=atof(tt[5].c_str());
    nby=atoi(tt[3].c_str());
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
    m_hist[i]->Fill((Float_t)val[i],(Float_t)val2[i]);
  }
}  
void MonHist2d::reset(){}

void MonHist2d::latchValue(){}

int MonHist2d::attach(TTree& t,const std::string& prefix) const {return 1;}

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
  std::string fullNameVal = prefix + name();
  std::string leafTypeVal = fullNameVal + m_dimstring + "/F";
  TBranch* b = tree.Branch(fullNameVal.c_str(),m_val,leafTypeVal.c_str());
  if ( b == 0 ) return -1;
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + m_dimstring + "/F";
  TBranch* bErr = tree.Branch(fullNameErr.c_str(),m_err,leafTypeErr.c_str());
  if ( bErr == 0 ) return -1;
  std::string fullNameN = fullNameVal + "_n";
  std::string leafTypeN = fullNameN + m_dimstring + "/l";
  TBranch* bN = tree.Branch(fullNameN.c_str(),m_nVals,leafTypeN.c_str());
  return bN != 0 ? 3 : -1;
}
  // add a value input the mean, so add to running sums
void MonMean::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i =0;i<m_dim;i++){
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
  std::string fullName = prefix + name();
  std::string leafType = fullName + m_dimstring+"/l";
  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str());
  return b != 0 ? 1 : -1;

}

  // Update the value, check to make sure that things make sense
void MonCounterDiff::singleincrement(Double_t* val, Double_t* val2) {
  for (unsigned i=0;i<m_dim;i++){
    if ( m_lo[i] == s_maxVal64 ) {
      m_lo[i] = (ULong64_t)val[i];
    }
    if ( val[i] > m_hi[i] ) {
      m_hi[i] = (ULong64_t)val[i];
    }
  }
}

// Attach a MonMinMax node to a TTree (unsigned int)
int MonMinMax::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameMin = prefix + name();
  fullNameMin += "_min";
  std::string leafTypeMin = fullNameMin+m_dimstring + "/F";
  std::string fullNameMax = prefix + name();
  fullNameMax += "_max";
  std::string leafTypeMax = fullNameMax +m_dimstring+ "/F";
  TBranch* b = tree.Branch(fullNameMin.c_str(),m_min,leafTypeMin.c_str());
  if ( b == 0 ) return -1;
  b = tree.Branch(fullNameMin.c_str(),m_max,leafTypeMax.c_str());
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
  std::string fullName = prefix + name();
  branchName= fullName+"_nchanges";
  leafName= branchName+m_dimstring + "/i";
  TBranch* b = tree.Branch(branchName.c_str(),m_nvalues,leafName.c_str());
  if ( b == 0 ) return -1;
  branchName= fullName+"_firstval";
  leafName= branchName+m_dimstring + "/L";
  b = tree.Branch(branchName.c_str(),m_firstval,leafName.c_str());
  if ( b == 0 ) return -1;
  branchName= fullName+"_lastval";
  leafName= branchName+m_dimstring + "/L";
  b = tree.Branch(branchName.c_str(),m_lastval,leafName.c_str());
  if ( b == 0 ) return -1;
  char valname[128];
  for (unsigned int i=0;i<m_numval;i++){
    sprintf(valname,"_newval_%d",i);
    branchName= fullName+valname;
    leafName= branchName+m_dimstring + "/L";
    b = tree.Branch(branchName.c_str(),m_values[i],leafName.c_str());
    if ( b == 0 ) return -1;
    sprintf(valname,"_newtime_%d",i);
    branchName= fullName+valname;
    leafName= branchName+m_dimstring + "/D";
    b = tree.Branch(branchName.c_str(),m_times[i],leafName.c_str());
    if ( b == 0 ) return -1;
  }
  return 0;
}

MonValueChange::MonValueChange(const char* name, const char* formula, const char* cut,const char* type) 
    :MonValue(name,formula,cut){
  m_histdim=2;
  std::vector<std::string> tt=parse(type,"[","","]"); 
  if(tt.size()!=1){
    std::cerr<<"MonValueChange variable "<<name<<" parameter declaration error. Aborting."<<std::endl;
    assert(0);
  }
  m_numval=atoi(tt[0].c_str());
  m_firstval=new Long64_t[m_dim];
  m_lastval=new Long64_t[m_dim];
  m_nvalues=new UInt_t[m_dim];
  m_startrun=new Bool_t [m_dim];
  
  m_values=new Long64_t*[m_numval];
  m_times=new Double_t*[m_numval];
  for (unsigned i=0;i<m_numval;i++){
    m_values[i]=new Long64_t[m_dim];
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
    if (val[i]!=m_lastval[i]&&m_startrun[i]==false){
      if(m_nvalues[i]<m_numval){
	m_values[m_nvalues[i]][i]=(Long64_t)val[i];
	m_times[m_nvalues[i]][i]=val2[i];
      }
      m_lastval[i]=(Long64_t)val[i];
      m_nvalues[i]++;
    }
    if(m_startrun[i]){
      m_firstval[i]=(Long64_t)val[i];
      m_lastval[i]=(Long64_t)val[i];
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

  if (type=="mean"){
    return new MonMean(name.c_str(),formula.c_str(),cut.c_str());
  } else if (strstr(type.c_str(),"truncatedmeanfrac")){
    return new MonTruncatedMeanFrac(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"truncatedmean")){
    return new MonTruncatedMean(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (type=="counter"){
    return new MonCounter(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="minmax"){
    return new MonMinMax(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="counterdiff"){
    return new MonCounterDiff(name.c_str(),formula.c_str(),cut.c_str());
  } else if (strstr(type.c_str(),"valuechange")){
    return new MonValueChange(name.c_str(),formula.c_str(),cut.c_str(),type.c_str());
  } else if (strstr(type.c_str(),"histogram-1d")){
    return new MonHist1d(name.c_str(),formula.c_str(),cut.c_str(),type.c_str(),axislabels.c_str(),titlelabel.c_str());
  } else if (strstr(type.c_str(),"histogram-2d")){
    return new MonHist2d(name.c_str(),formula.c_str(),cut.c_str(),type.c_str(),axislabels.c_str(),titlelabel.c_str());
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
