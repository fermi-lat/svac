// Program to merge trending tuples
// C 2007 Martin Kocian, SLAC
#include <unistd.h>
#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TObjArray.h"

struct chunk{
  unsigned long long start;
  unsigned long long end;
  double timestamp;
  unsigned int binwidth;
  bool overlap;
};

std::vector<void*> createadd(std::vector<std::string> types,std::vector<unsigned> dims);
void attachadd(std::vector<std::string> leaves, std::vector<void*> adds, TTree* tree);
void mergebins(std::vector<void*> addout,std::vector<void*> addin1, std::vector<void*> addin2,std::vector<std::string> leaves,std::vector<unsigned> dims ); 

int main(int argn, char** argc) {
  std::vector<std::string> inputfiles;
  std::string outputfile;
  std::string treename;
  std::ifstream fl;
  int opt;
  while ( (opt = getopt(argn, argc, "hi:o:t:f:")) != EOF ) {
    switch (opt) {
    case 'h':   // help      
      std::cout<<"treemerge -i inputfile1 -i inputfile2 ... -o outputfile -t treename"<<std::endl; 
      std::cout<<" or "<<std::endl;
      std::cout<<"treemerge -f input_file_list -o outputfile -t treename"<<std::endl;
      return 0;
    case 'i':
      inputfiles.push_back(std::string(optarg));
      break;
    case 'f':
      fl.open(optarg);
      char name[512];
      while (!fl.eof()){
	name[0]='\0';
	fl>>name;
	if (strlen(name)>0){
	  inputfiles.push_back(std::string(name));
	}
      }
      break;
    case 'o':
      outputfile=std::string(optarg);
      break;
    case 't':
      treename=std::string(optarg);
      break;
    default:
      std::cerr<<"Bad option. Exiting."<<std::endl;
      return 2;
    }
  }
  if (inputfiles.size()==0 || outputfile.size()==0 || treename.size()==0){
    std::cout<<"Missing input parameters. Run treemerge.exe -h for help."<<std::endl;
    return 2;
  }
  std::cout<<"Inputfiles:"<<std::endl;
  for (unsigned i=0;i<inputfiles.size();i++)std::cout<<inputfiles[i]<<std::endl;
  std::cout<<"Outputfile: "<<outputfile<<std::endl;
  std::cout<<"treename: "<<treename<<std::endl;
  std::vector<chunk*> chunks;
  std::vector<std::string> branches;
  std::vector<std::string> leaves;
  std::vector<unsigned> dims;
  std::vector<std::string> types;
  unsigned int nbranches=0;
  unsigned long long start;
  unsigned long long end;
  double timestamp;
  for (unsigned int i=0;i<inputfiles.size();i++){
    TFile *f=TFile::Open(inputfiles[i].c_str());
    assert (!f->IsZombie());
    TTree* t=(TTree*)gDirectory->Get(treename.c_str());
    assert (t);
    if(i==0){
      nbranches=t->GetListOfBranches()->GetEntries();
      TObjArray* ar=t->GetListOfBranches();
      for (unsigned j=0;j<nbranches;j++){
	branches.push_back(std::string(ar->At(j)->GetTitle()));
      }
      for (unsigned j=0;j<nbranches;j++){
	leaves.push_back(std::string(ar->At(j)->GetName()));
	dims.push_back(t->FindLeaf(ar->At(j)->GetName())->GetLen());
	types.push_back(t->FindLeaf(ar->At(j)->GetName())->GetTypeName());
      }
    }else{
      if(t->GetListOfBranches()->GetEntries()!=(int)nbranches){
	std::cout<<inputfiles[i]<<" has a different number of branches than "<<inputfiles[0]<<std::endl;
	return 2;
      }
      TObjArray* ar=t->GetListOfBranches();
      for (unsigned j=0;j<nbranches;j++){
	if( find(branches.begin(),branches.end(),std::string(ar->At(j)->GetTitle()))==branches.end()){
	  std::cout<<ar->At(j)->GetTitle()<<" not found in original input file"<<std::endl;
	  return 2;
	}
      }
    }
    t->SetBranchAddress("Bin_Start",&start);
    t->SetBranchAddress("TimeStampFirstEvt",&timestamp);
    t->SetBranchAddress("Bin_End",&end);
    t->GetEntry(0);
    chunk* newchunk=new chunk;
    newchunk->binwidth=end-start;
    newchunk->start=start;
    newchunk->timestamp=timestamp;
    if(t->GetEntries()==1)newchunk->end=end;
    else{
      t->GetEntry(t->GetEntries()-1);
      newchunk->end=end;
    }
    chunks.push_back(newchunk);
    f->Close();
  }
  std::vector<unsigned int> order;
  for (unsigned i=0;i<chunks.size();i++){
    double st=1e100;
    unsigned index =0xffff;
    for (unsigned j=0;j<chunks.size();j++){
      if (chunks[j]->timestamp==st && find(order.begin(),order.end(),j)==order.end()){
	std::cout<<"Two chunks start with the same event. Exiting"<<std::endl;
	return 2;
      }
      if (chunks[j]->timestamp<=st && find(order.begin(),order.end(),j)==order.end()){
	st=chunks[j]->timestamp;
	index=j;
      }
    }
    if(index!=0xffff) {
      order.push_back(index);
    } else{
      std::cout<<"Could not order chunks."<<std::endl;
      return 2;
    }
  }
  //for (unsigned i=0;i<chunks.size();i++)std::cout<<order[i]<<std::endl;
  // check for overlap
  for (unsigned i=0;i<chunks.size();i++){
    if (i>0){
      if(chunks[order[i]]->start==chunks[order[i-1]]->end)chunks[order[i]]->overlap=false;
      else if (chunks[order[i]]->start+chunks[order[i]]->binwidth==chunks[order[i-1]]->end)chunks[order[i]]->overlap=true;
      else if(chunks[order[i]]->start>chunks[order[i-1]]->end){
	chunks[order[i]]->overlap=false;
	std::cout<<"Missing interval(s)..."<<std::endl;
      }
      else{
	std::cout<<"Bad overlap between two chunks."<<std::endl;
	std::cout<<order[i]<<std::endl;
	std::cout<<" start "<<chunks[order[i-1]]->start<<" end "<<chunks[order[i-1]]->end<<" binwidth"<<chunks[order[i-1]]->binwidth<<std::endl;
	std::cout<<" start "<<chunks[order[i]]->start<<" end "<<chunks[order[i]]->end<<" binwidth"<<chunks[order[i]]->binwidth<<std::endl;
	return 2;
      }
    }
    else chunks[order[i]]->overlap=false;
  }
  for (unsigned i=0;i<chunks.size();i++){
    std::cout<<"Chunk: "<<order[i]<<" Start: "<<chunks[order[i]]->start<<" End: "<<chunks[order[i]]->end<<" Binwidth: "<<chunks[order[i]]->binwidth<<" Overlap: "<<chunks[order[i]]->overlap<<std::endl;
  }
  //start merging files
  int evtnr=0;
  TFile *f=TFile::Open(inputfiles[order[0]].c_str());
  TTree* t=(TTree*)gDirectory->Get(treename.c_str());
  TFile newf(outputfile.c_str(),"recreate");
  int nentries=t->GetEntries()-1;
  if(chunks.size()==1)nentries++;
  TTree *newtree = t->CloneTree(nentries);
  evtnr=nentries;
  std::vector<void*> newadd=createadd(types,dims);
  std::vector<void*> firstadd=createadd(types,dims);
  std::vector<void*> secondadd=createadd(types,dims);
  f->Close();
  attachadd(leaves,newadd,newtree);
  if (find(leaves.begin(),leaves.end(),"Bin_Index")==leaves.end() ){
    std::cout<<"Tree is missing Bin_Index field"<<std::endl;
    return 2;
  }
  unsigned binindex=find(leaves.begin(),leaves.end(),"Bin_Index")-leaves.begin();
  bool binclosed=true;
  for (unsigned i=1;i<chunks.size();i++){
    TFile *f=TFile::Open(inputfiles[order[i-1]].c_str());
    TTree* t1=(TTree*)gDirectory->Get(treename.c_str());
    TFile *g=TFile::Open(inputfiles[order[i]].c_str());
    TTree* t2=(TTree*)gDirectory->Get(treename.c_str());
    // no overlap case
    if(chunks[order[i]]->overlap==false){
      if(binclosed==false){
	((UInt_t*)newadd[binindex])[0]= evtnr++;
	newtree->Fill();
	binclosed=true;
      }
      attachadd(leaves,newadd,t1);
      t1->GetEntry(t1->GetEntries()-1);
      ((UInt_t*)newadd[binindex])[0]= evtnr++;
      newtree->Fill();
      attachadd(leaves,newadd,t2);
      t2->GetEntry(0);
      ((UInt_t*)newadd[binindex])[0]= evtnr++;
      newtree->Fill();
    //overlap case
    }else{
      if (binclosed==false && chunks[order[i]]->start>chunks[order[i-1]]->start){
	//should not happen
	assert(0);
      }
      attachadd(leaves,firstadd,t1);
      t1->GetEntry(t1->GetEntries()-1);
      attachadd(leaves,secondadd,t2);
      t2->GetEntry(0);
      if(binclosed==true){
	mergebins(newadd,firstadd,secondadd,leaves,dims);
      }else{
	mergebins(newadd,newadd,secondadd,leaves,dims);
      }
      binclosed=false;
    }
    //now copy the rest of the second tree except perhaps for the last event
    attachadd(leaves,newadd,t2);
    int nentries=t2->GetEntries()-1;
    if(i==chunks.size()-1)nentries++;
    if (nentries>0 ||i==chunks.size()-1 ){
      binclosed=true;
      ((UInt_t*)newadd[binindex])[0]= evtnr++;
	newtree->Fill();
    }
    for (int j=1;j<nentries;j++){
      t2->GetEntry(j);
      ((UInt_t*)newadd[binindex])[0]= evtnr++;
      newtree->Fill();
    }
    f->Close();
    g->Close();
  }
  newf.cd();
  newtree->Write();
  newf.Close();
}

std::vector<void*> createadd(std::vector<std::string> types,std::vector<unsigned> dims){
  std::vector<void*> pointers;
  for (unsigned i=0;i<types.size();i++){
    if(types[i]=="Float_t")
      pointers.push_back((void*)new Float_t[dims[i]]);
    else if(types[i]=="ULong64_t")
      pointers.push_back((void*)new ULong64_t[dims[i]]);
    else if(types[i]=="UInt_t")
      pointers.push_back((void*)new Int_t[dims[i]]);
    else if(types[i]=="Double_t")
      pointers.push_back((void*)new Double_t[dims[i]]);
    else {
      std::cerr<<"Type "<<types[i]<<" not implemented."<<std::endl;
      assert(0);
    }
  }
  return pointers;
}

void attachadd(std::vector<std::string> leaves, std::vector<void*> adds, TTree* tree){
  for (unsigned i=0;i<leaves.size();i++){
    tree->SetBranchAddress(leaves[i].c_str(),adds[i]);
  }
}

void mergebins(std::vector<void*> addout,std::vector<void*> addin1, std::vector<void*> addin2,std::vector<std::string> leaves,std::vector<unsigned> dims ){ 
  // keep track if we actually merged everything
  std::vector<std::string>::iterator it ;
  std::vector<bool> used;
  Int_t trueint=-1;
  for (unsigned i=0;i<leaves.size();i++)used.push_back(false);
  for (unsigned i=0;i<leaves.size();i++){
    // Merge branches that exist in all Time trees first
    if (leaves[i]=="Bin_Index" ){
      used[i]=true;
      continue;
    }
    if (leaves[i]=="Bin_Flags"){
      ((UInt_t*)addout[i])[0]= ((UInt_t*)addin1[i])[0];
      used[i]=true;
      continue;
    }
    if (leaves[i]=="Bin_Start" ||leaves[i]=="Bin_End" ){
      if(((ULong64_t*)addin1[i])[0]!=((ULong64_t*)addin2[i])[0]){
	std::cout<<leaves[i]<<" in merged bin is different in the two chunks. Exiting"<<std::endl;
	assert(0);
      }
      ((ULong64_t*)addout[i])[0]=((ULong64_t*)addin1[i])[0];
      used[i]=true;
      continue;
    }
    if (leaves[i]=="nEvents" ||leaves[i]=="nPassed"){
      ((UInt_t*)addout[i])[0]= ((UInt_t*)addin1[i])[0]+((UInt_t*)addin2[i])[0];
      used[i]=true;
      continue;
    }
    if (leaves[i]=="TrueTimeInterval"){
      ((Double_t*)addout[i])[0]= ((Double_t*)addin1[i])[0]+((Double_t*)addin2[i])[0];
      used[i]=true;
      trueint=i;
      continue;
    }
    if (leaves[i]=="TimeStampFirstEvt"){
      ((Double_t*)addout[i])[0]= ((Double_t*)addin1[i])[0];
      used[i]=true;
      continue;
    }
    if (leaves[i]=="TimeStampLastEvt"){
      ((Double_t*)addout[i])[0]= ((Double_t*)addin2[i])[0];
      used[i]=true;
      continue;
    }
    if (leaves[i].find("Counter_")==0 || leaves[i].find("CounterDiff_")==0){
      used[i]=true;
      for (unsigned j=0;j<dims[i];j++){
	((ULong64_t*)addout[i])[j]= ((ULong64_t*)addin1[i])[j]+((ULong64_t*)addin2[i])[j];	
      }
      continue;
    }
    if (leaves[i].find("Min_")==0 ){
      used[i]=true;
      for (unsigned j=0;j<dims[i];j++){
	if( ((Float_t*)addin1[i])[j]<((Float_t*)addin2[i])[j]) ((Float_t*)addout[i])[j]= ((Float_t*)addin1[i])[j];	
	else ((Float_t*)addout[i])[j]= ((Float_t*)addin2[i])[j];
      }
      continue;
    }
    if (leaves[i].find("Max_")==0 ){
      used[i]=true;
      for (unsigned j=0;j<dims[i];j++){
	if( ((Float_t*)addin1[i])[j]>((Float_t*)addin2[i])[j]) ((Float_t*)addout[i])[j]= ((Float_t*)addin1[i])[j];	
	else ((Float_t*)addout[i])[j]= ((Float_t*)addin2[i])[j];
      }
      continue;
    }
    if (leaves[i].find("Mean_")==0 && leaves[i].find("_err")!=leaves[i].length()-strlen("_err")&& leaves[i].find("_n")!=leaves[i].length()-strlen("_n")){
      used[i]=true;
      unsigned errindex,nindex;
      errindex=nindex=0;
      it=find(leaves.begin(),leaves.end(),leaves[i]+"_err");
      if(it==leaves.end()){
	std::cout<<leaves[i]<<"_err"<<" not found. Exiting."<<std::endl;
	assert(0);
      }else errindex=it-leaves.begin();
      used[errindex]=true;
      it=find(leaves.begin(),leaves.end(),leaves[i]+"_n");
      if(it==leaves.end()){
	std::cout<<leaves[i]<<"_n"<<" not found. Exiting."<<std::endl;
	assert(0);
      }else nindex=it-leaves.begin();
      used[nindex]=true;
      for (unsigned j=0;j<dims[i];j++){
	unsigned long long n1=  ((ULong64_t*)addin1[nindex])[j];
	unsigned long long n2=  ((ULong64_t*)addin2[nindex])[j];
	unsigned long long nadd=n1+n2;
	((ULong64_t*)addout[nindex])[j]=nadd; 
	float val1=((Float_t*)addin1[i])[j];
	float val2=((Float_t*)addin2[i])[j];
	float sig1=((Float_t*)addin1[errindex])[j]*sqrt(n1);
	float sig2=((Float_t*)addin2[errindex])[j]*sqrt(n2);
	if (nadd>0){
	  float xm=(val1*n1+val2*n2)/nadd;
	  ((Float_t*)addout[i])[j]=xm;
	  float xs=(sig1*sig1+val1*val1)*n1+(sig2*sig2+val2*val2)*n2;
	  ((Float_t*)addout[errindex])[j]=sqrt((xs/nadd-xm*xm)/nadd);
	}else{
	  ((Float_t*)addout[i])[j]=0;
	  ((Float_t*)addout[errindex])[j]=0;
	}
      }
      continue;
    }
    if (leaves[i].find("OutF_")==0 && leaves[i].find("_err")!=leaves[i].length()-strlen("_err")){
      used[i]=true;
      unsigned errindex=0;
      it=find(leaves.begin(),leaves.end(),leaves[i]+"_err");
      if(it==leaves.end()){
	std::cout<<leaves[i]<<"_err"<<" not found. Exiting."<<std::endl;
	assert(0);
      }else errindex=it-leaves.begin();
      used[errindex]=true;
      for (unsigned j=0;j<dims[i];j++){
	float val1=((Float_t*)addin1[i])[j];
	float val2=((Float_t*)addin2[i])[j];
	float sig1=((Float_t*)addin1[errindex])[j];
	float sig2=((Float_t*)addin2[errindex])[j];
	if (sig1>0&&sig2>0){
	  ((Float_t*)addout[i])[j]=(val1/(sig1*sig1)+val2/(sig2*sig2))/(1/(sig1*sig1)+1/(sig2*sig2));
	  ((Float_t*)addout[errindex])[j]=sqrt(1/(1/(sig1*sig1)+1/(sig2*sig2)));
	}else if (sig1==0){
	  ((Float_t*)addout[i])[j]=val2;
	  ((Float_t*)addout[errindex])[j]=sig2;
	} else if(sig2==0){
	  ((Float_t*)addout[i])[j]=val1;
	  ((Float_t*)addout[errindex])[j]=sig1;
	}else{
	  std::cout<<leaves[i]<<" has an error lower than 0"<<std::endl;
	  std::cout<<"val 1: "<<val1<<" error 1: "<<sig1<<std::endl;
	  std::cout<<"val 2: "<<val1<<" error 2: "<<sig1<<std::endl;
	  assert(0);
	}
      }
      continue;
    }
    if (leaves[i].find("OutD_")==0&& leaves[i].find("_err")!=leaves[i].length()-strlen("_err") ){
      used[i]=true;
      unsigned errindex=0;
      it=find(leaves.begin(),leaves.end(),leaves[i]+"_err");
      if(it==leaves.end()){
	std::cout<<leaves[i]<<"_err"<<" not found. Exiting."<<std::endl;
	assert(0);
      }else errindex=it-leaves.begin();
      used[errindex]=true;
      for (unsigned j=0;j<dims[i];j++){
	double val1=((Double_t*)addin1[i])[j];
	double val2=((Double_t*)addin2[i])[j];
	double sig1=((Double_t*)addin1[errindex])[j];
	double sig2=((Double_t*)addin2[errindex])[j];
	if (sig1>0&&sig2>0){
	  ((Double_t*)addout[i])[j]=(val1/(sig1*sig1)+val2/(sig2*sig2))/(1/(sig1*sig1)+1/(sig2*sig2));
	  ((Double_t*)addout[errindex])[j]=sqrt(1/(1/(sig1*sig1)+1/(sig2*sig2)));
	}else if (sig1==0){
	  ((Double_t*)addout[i])[j]=val2;
	  ((Double_t*)addout[errindex])[j]=sig2;
	} else if(sig2==0){
	  ((Double_t*)addout[i])[j]=val1;
	  ((Double_t*)addout[errindex])[j]=sig1;
	}else{
	  std::cout<<leaves[i]<<" has an error lower than 0"<<std::endl;
	  std::cout<<"val 1: "<<val1<<" error 1: "<<sig1<<std::endl;
	  std::cout<<"val 2: "<<val1<<" error 2: "<<sig1<<std::endl;
	  assert(0);
	}
      }
      continue;
    }
    if (leaves[i].find("ValChange_")==0 &&leaves[i].find("_nchanges")==leaves[i].length()-strlen("_nchanges") ){
      used[i]=true;
      std::string name=leaves[i].substr(0,leaves[i].length()-strlen("_nchanges"));
      unsigned fvalindex,lastvalindex;
      fvalindex=lastvalindex=0;
      it=find(leaves.begin(),leaves.end(),name+"_firstval");
      if(it==leaves.end()){
	std::cout<<name<<"_firstval"<<" not found. Exiting."<<std::endl;
	assert(0);
      }else fvalindex=it-leaves.begin();
      used[fvalindex]=true;
      it=find(leaves.begin(),leaves.end(),name+"_lastval");
      if(it==leaves.end()){
	std::cout<<name<<"_lastval"<<" not found. Exiting."<<std::endl;
	assert(0);
      }else lastvalindex=it-leaves.begin();
      used[lastvalindex]=true;
      unsigned int numval=0;
      unsigned int numtim=0;
      char numstring[128];
      std::vector<unsigned> newvalind;
      std::vector<unsigned> newtimind;
      while (1){
	sprintf(numstring,"%d",numval);
	if (find(leaves.begin(),leaves.end(),name+"_newval_"+numstring)==leaves.end())break;
	newvalind.push_back(find(leaves.begin(),leaves.end(),name+"_newval_"+numstring)-leaves.begin());
	used[newvalind[numval]]=true;
	numval++;
      }
      if (numval==0){
	std::cout<<"No values found for ValueChange variable "<<name<<std::endl;
	assert(0);
      }
     while (1){
	sprintf(numstring,"%d",numtim);
	if (find(leaves.begin(),leaves.end(),name+"_newtime_"+numstring)==leaves.end())break;
	newtimind.push_back(find(leaves.begin(),leaves.end(),name+"_newtime_"+numstring)-leaves.begin());
	used[newtimind[numtim]]=true;
	numtim++;
      }
      if (numtim==0){
	std::cout<<"No values found for ValueChange variable "<<name<<std::endl;
	assert(0);
      }else if (numtim!=numval){
	std::cout<<"Different number of new time and new value fields for "<<name<<". Exiting."<<std::endl;
      }
      for (unsigned j=0;j<dims[i];j++){
	unsigned int n1=((UInt_t*)addin1[i])[j];
	unsigned int n2=((UInt_t*)addin2[i])[j];
	((UInt_t*)addout[i])[j]=n1+n2;
	((Double_t*)addout[lastvalindex])[j]=((Double_t*)addin2[lastvalindex])[j];
	((Double_t*)addout[fvalindex])[j]=((Double_t*)addin1[fvalindex])[j];
	unsigned int numind1=n1<numval ? n1 : numval;
	unsigned int numind2=n2<numval-numind1? n2 : numval-numind1;
	for (unsigned k=0;k<numind1;k++){
	  ((Double_t*)addout[newvalind[k]])[j]=((Double_t*)addin1[newvalind[k]])[j];
	  ((Double_t*)addout[newtimind[k]])[j]=((Double_t*)addin1[newtimind[k]])[j];
	} 
	for (unsigned k=0;k<numind2;k++){
	  ((Double_t*)addout[newvalind[k+numind1]])[j]=((Double_t*)addin2[newvalind[k]])[j];
	  ((Double_t*)addout[newtimind[k+numind1]])[j]=((Double_t*)addin2[newtimind[k]])[j];
	} 
      }
      continue;
    }
  }
  for (unsigned i=0;i<leaves.size();i++){
    if (leaves[i].find("DoubleDiffRate_")==0 ){
      used[i]=true;
      // The true interval index is set
      assert (trueint>-1);
      Double_t iv1=((Double_t*)addin1[trueint])[0];
      Double_t iv2=((Double_t*)addin2[trueint])[0];
      for (unsigned j=0;j<dims[i];j++){
	Double_t val1=((Double_t*)addin1[i])[j];
	Double_t val2=((Double_t*)addin2[i])[j];
	// The total time interval is gt 0
	assert (iv1+iv2>0);
	((Double_t*)addout[i])[j]=(val1*iv1+val2*iv2)/(iv1+iv2);
      }
    }

    // temporal solution to merge outputnumber objects (D.P. 2008/05/19)
    if (leaves[i].find("Number_")==0 ){
      used[i]=true;
      // The true interval index is set
      assert (trueint>-1);
      Double_t iv1=((Double_t*)addin1[trueint])[0];
      Double_t iv2=((Double_t*)addin2[trueint])[0];
      for (unsigned j=0;j<dims[i];j++){
	UInt_t val1=((UInt_t*)addin1[i])[j];
	UInt_t val2=((UInt_t*)addin2[i])[j];
	// The total time interval is gt 0
	assert (iv1+iv2>0);
	if(iv2>0)
	  ((UInt_t*)addout[i])[j]= val2;
	else
	  ((UInt_t*)addout[i])[j]= val1;
      }
    }

    // end tmp


    if ((leaves[i].find("Rate_")==0 || leaves[i].find("CounterDiffRate_")==0 )&& leaves[i].find("_err")!=leaves[i].length()-strlen("_err")){
      used[i]=true;
      assert (trueint>-1);
      unsigned errindex=0;
      it=find(leaves.begin(),leaves.end(),leaves[i]+"_err");
      if(it==leaves.end()){
	std::cout<<leaves[i]<<"_err"<<" not found. Exiting."<<std::endl;
	assert(0);
      }else errindex=it-leaves.begin();
      used[errindex]=true;
      for (unsigned j=0;j<dims[i];j++){
	float val1=((Float_t*)addin1[i])[j];
	float val2=((Float_t*)addin2[i])[j];
	float sig1=((Float_t*)addin1[errindex])[j];
	float sig2=((Float_t*)addin2[errindex])[j];
	float n1,n2;
	Double_t t1,t2;
	if (sig1>0){
	  n1=val1/sig1*val1/sig1;
	}
	else {
	  n1=0;
	}
	t1=((Double_t*)addin1[trueint])[0];
	if (sig2>0){
	  n2=val2/sig2*val2/sig2;
	}
	else {
	  n2=0;
	}
	t2=((Double_t*)addin2[trueint])[0];
	float nadd=n1+n2;
	float tadd=(float)t1+t2;
	if (nadd>0 && tadd>0)((Float_t*)addout[i])[j]=nadd/tadd;
	else((Float_t*)addout[i])[j]=0;
	if (nadd>0 && tadd>0)((Float_t*)addout[errindex])[j]=sqrt(nadd)/tadd;
	else ((Float_t*)addout[errindex])[j]=0;
      }
      continue;
    }
  }
	
  for (unsigned i=0;i<leaves.size();i++){
    if (used[i]==false){
      std::cout<<"Don't know how to merge "<<leaves[i]<<std::endl;
      assert(0);
    }
  }
}
	
