
//
// stl
#include <string>
#include <list>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <time.h>
//
// ROOT-io
#include "TFile.h"
#include "TSystem.h"
#include "TString.h"
#include "TList.h"

//
// Job configuration and options parser
#include "JobConfig.h"

//
// The thing that actually does the work
#include "MonEventLooper_t.h"

#include "MonObjFactory.h"
#include "MonInputCollection_Digi.h"
#include "MonInputCollection_Recon.h"
#include "MonInputCollection_Mc.h"
#include "MonInputCollection_Merit.h"
#include "MonInputCollection_Svac.h"
#include "MonInputCollection_Cal.h"
#include "MonGlobalCut.h"
#include "MonValueImpls_t.h"
#include "MonConfigParser.h"

#include "TestReport.h"



//
int main(int argn, char** argc) {

  // configure
  JobConfig jc("runStrip.exe","This utility time series strip chart code");

  Int_t parseValue = jc.parse(argn,argc); 
  switch ( parseValue ) {
  case 0: // ok to proceed
    break;  
  case 1: // called -h option terminate processesing normally
    return 0; 
  default: 
    return parseValue;  // parse failed, return failure code
  }

  // strip chart output do this before the event loop
  // so that we abort the output won't work
  std::string outputFile = jc.outputPrefix() + "_time.root";
  TFile* fout = TFile::Open(outputFile.c_str(),"RECREATE");
  if ( fout == 0 || fout->IsZombie() ) {
    std::cerr << "Failed to open output File " << outputFile << std::endl;
    return -1;
  }
  // parse the monitoring configuration xml file
  MonConfigParser p(jc.configFile().c_str());
  std::list<std::string> inputlist=p.getInputList();
  std::string timestamp=p.getTimeStamp();
  if (timestamp==""){
    std::cerr<<"You must define a timestamp object in your xml file!!!"<<std::endl;
    assert(0);
  }
  
  //build input objects
  MonInputCollection* digiinpcol=0;
  MonInputCollection* reconinpcol=0;
  MonInputCollection* mcinpcol=0;
  MonInputCollection* meritinpcol=0;
  MonInputCollection* svacinpcol=0;
  MonInputCollection* calinpcol=0;
  Int_t nTotal=0;
  if (jc.digiChain()){
    digiinpcol=new MonInputCollection_Digi(jc.digiChain(),"DigiEvent");
    if (nTotal==0)nTotal=jc.digiChain()->GetEntries();
    else if (nTotal!=jc.digiChain()->GetEntries()){
      std::cerr<<"Different number of events in Digi chain. Exiting"<<std::endl;
      assert(0);
    }
  }
  if (jc.reconChain()){
    reconinpcol=new MonInputCollection_Recon(jc.reconChain(),"ReconEvent");
    if (nTotal==0)nTotal=jc.reconChain()->GetEntries();
    else if (nTotal!=jc.reconChain()->GetEntries()){
      std::cerr<<"Different number of events in Recon chain. Exiting"<<std::endl;
      assert(0);
    }
  }
  if (jc.mcChain()){
    mcinpcol=new MonInputCollection_Mc(jc.mcChain(),"McEvent");
    if (nTotal==0)nTotal=jc.mcChain()->GetEntries();
    else if (nTotal!=jc.mcChain()->GetEntries()){
      std::cerr<<"Different number of events in Mc chain. Exiting"<<std::endl;
      assert(0);
    }
  }
  if (jc.meritChain()){
    meritinpcol=new MonInputCollection_Merit(jc.meritChain(),"MeritEvent");
    if (nTotal==0)nTotal=jc.meritChain()->GetEntries();
    else if (nTotal!=jc.meritChain()->GetEntries()){
      std::cerr<<"Different number of events in Merit chain. Exiting"<<std::endl;
      assert(0);
    }
  }
  if (jc.svacChain()){
    svacinpcol=new MonInputCollection_Svac(jc.svacChain(),"SvacEvent");
    if (nTotal==0)nTotal=jc.svacChain()->GetEntries();
    else if (nTotal!=jc.svacChain()->GetEntries()){
      std::cerr<<"Different number of events in Svac chain. Exiting"<<std::endl;
      assert(0);
    }
  }
  if (jc.calChain()){
    calinpcol=new MonInputCollection_Cal(jc.calChain(),"CalEvent");
    if (nTotal==0)nTotal=jc.calChain()->GetEntries();
    else if (nTotal!=jc.calChain()->GetEntries()){
      std::cerr<<"Different number of events in cal Chain. Exiting"<<std::endl;
      assert(0);
    }
  }
  std::vector<std::map<std::string,std::string> > digidesc;
  std::vector<std::map<std::string,std::string> > recondesc;
  std::vector<std::map<std::string,std::string> > mcdesc;
  std::vector<std::map<std::string,std::string> > svacdesc;
  std::vector<std::map<std::string,std::string> > meritdesc;
  std::vector<std::map<std::string,std::string> > caldesc;
  MonObjFactory fact;
  bool tsfound=false;
  for (std::list<string>::const_iterator itr=inputlist.begin();
       itr != inputlist.end();itr++){
    MonInputObject* obj=fact.getMonInputObject(*itr);
    assert(obj!=0);
    std::map<std::string,std::string> mmap;
    mmap["source"]=obj->getInputSource();
    mmap["name"]=(*itr);
    mmap["description"]=obj->getDescription();
    bool added=false;
    if(digiinpcol && obj->getInputSource()=="DigiEvent"){
      digiinpcol->addInputObject(obj);
      digidesc.push_back(mmap);
      added=true;
    }
    if(reconinpcol && obj->getInputSource()=="ReconEvent"){
      reconinpcol->addInputObject(obj);
      digidesc.push_back(mmap);
      added=true;
    }
    if(mcinpcol && obj->getInputSource()=="McEvent"){
      mcinpcol->addInputObject(obj);
      mcdesc.push_back(mmap);
      added=true;
    }
    if(meritinpcol && obj->getInputSource()=="MeritEvent"){
      meritinpcol->addInputObject(obj);
      meritdesc.push_back(mmap);
      added=true;
    }
    if(svacinpcol && obj->getInputSource()=="SvacEvent"){
      svacinpcol->addInputObject(obj);
      svacdesc.push_back(mmap);
      added=true;
    }
    if(calinpcol && obj->getInputSource()=="CalEvent"){
      calinpcol->addInputObject(obj);
      caldesc.push_back(mmap);
      added=true;
    }
    if ((*itr)==timestamp){
      tsfound=true;
      if (added==false){
	std::cerr<<"Timestamp object could not be added to collection!"<<std::endl;
	assert(0);
      }
    }
    if (added==false){
      std::cerr<<"Warning: Input object "<<(*itr)<<" could not be added to collection"<<std::endl;
    }
  }
  if (tsfound==false){
    std::cerr<<"Timestamp object is not among input objects. Exiting"<<std::endl;
    assert(0);
  }
  std::vector<MonInputCollection*> allinpcol;
  int ndigiobjects=0;
  int nreconobjects=0;
  int nmcobjects=0;
  int nmeritobjects=0;
  int nsvacobjects=0;
  int ncalobjects=0;
  if(digiinpcol)ndigiobjects= digiinpcol->nObjects();
  if (ndigiobjects>0)allinpcol.push_back(digiinpcol);
  if(reconinpcol)nreconobjects= reconinpcol->nObjects();
  if(nreconobjects>0)allinpcol.push_back(reconinpcol);
  if(mcinpcol )nmcobjects= mcinpcol->nObjects();
  if(nmcobjects>0)allinpcol.push_back(mcinpcol);
  if(meritinpcol )nmeritobjects= meritinpcol->nObjects();
  if(nmeritobjects>0)allinpcol.push_back(meritinpcol);
  if(svacinpcol )nsvacobjects= svacinpcol->nObjects();
  if(nsvacobjects>0)allinpcol.push_back(svacinpcol);
  if(calinpcol )ncalobjects= calinpcol->nObjects();
  if(ncalobjects>0)allinpcol.push_back(calinpcol);
  if (ndigiobjects+nreconobjects+nmcobjects+nmeritobjects+nsvacobjects+ncalobjects==0){
    std::cerr<<"No input objects defined. Exiting..."<<std::cerr;
    assert(0);
  }
  // global event cut
  std::string eventcut=p.getEventCut();
  MonGlobalCut* globalCut=new MonGlobalCut("globalCut",eventcut.c_str());
  std::cout<<"Event cut "<<eventcut<<std::endl;
  // now the output 
  std::list<std::map<std::string,std::string> > outputlist=p.getOutputList();
  std::list<std::map<std::string,std::string> > outputlistprimary;
  std::list<std::map<std::string,std::string> > outputlistsecondary;
  for(std::list<std::map<std::string,std::string> >::iterator itr=outputlist.begin();
      itr !=outputlist.end();itr++){
    if ((*itr)["source"]=="output") outputlistsecondary.push_back(*itr);
    else outputlistprimary.push_back(*itr);
  }      
  MonValFactory mf;
  MonValueCol* outcolprim=mf.makeMonValueCol(outputlistprimary,"Primary");
  MonValueCol* outcolsec=mf.makeMonValueCol(outputlistsecondary,"Secondary");
  char inclpath[512];
  sprintf(inclpath," -I%s ",getenv("CONFIGDATAROOT"));
  gSystem->AddIncludePath(inclpath);
  TString cmd = gSystem->GetMakeSharedLib(); 
  cmd.ReplaceAll("-W ","-W -Wno-unused-parameter ");
  gSystem->SetMakeSharedLib(cmd);
  // Attach digi tree to input object
  // build filler & run over events
  MonEventLooper d(jc.optval_b(), outcolprim,outcolsec,allinpcol, globalCut,timestamp);
  Long64_t numevents=jc.optval_n()  < 1 ? nTotal : TMath::Min(jc.optval_n()+jc.optval_s(),nTotal);
  struct timespec ts1, ts2;
  clock_gettime(CLOCK_REALTIME, &ts1);
  d.go(numevents,jc.optval_s());    
  clock_gettime(CLOCK_REALTIME, &ts2);
  unsigned long starttime=ts1.tv_sec*1000000+ts1.tv_nsec/1000;
  unsigned long endtime=ts2.tv_sec*1000000+ts2.tv_nsec/1000;
  
  // Ok, write the output and clean up
  d.tree()->Write();
  TList* list=(TList*)gDirectory->GetList();
  TIter iter(list);
  while(TObject* obj=iter.Next()){
    if((strstr(obj->ClassName(),"TH2")||strstr(obj->ClassName(),"TH1")) && !strstr(obj->GetName(),"htemp"))obj->Write();
  }
  fout->Close();
  // Write an html report
  std::string html=jc.htmlFile();
  if(html=="")html="Monitoring.html";
  TestReport r(html.c_str());
  r.newheadline("General information");
  char name[128];
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  sprintf(name,"%s",asctime(timeinfo));
  std::string currenttime(name);
  r.additem("Date", name);
  r.additem("Monitoring configuration file",jc.configFile().c_str());
  r.additem("Output root file",outputFile.c_str());
  sprintf(name,"%d",(int)numevents-jc.optval_s());
  r.additem("Number of events",name);
  sprintf(name,"%d",jc.optval_b());
  r.additem("Time interval",name);
  if(eventcut!="")r.additem("Global event cut",eventcut.c_str());
  r.newheadline("Event input files");
  if (digiinpcol)r.additem("Digi file(s)",jc.inputDigiFileStr().c_str());
  if (reconinpcol)r.additem("Recon file(s)",jc.inputDigiFileStr().c_str());
  if (mcinpcol)r.additem("Mc file(s)",jc.inputDigiFileStr().c_str());
  if (svacinpcol)r.additem("Svac file(s)",jc.inputDigiFileStr().c_str());
  if (meritinpcol)r.additem("Merit file(s)",jc.inputDigiFileStr().c_str());
  if (calinpcol)r.additem("Cal file(s)",jc.inputDigiFileStr().c_str());
  r.newheadline("<b><center>Input variables</b></center>");
  char* inptable[]={"Name","Source","Description"};
  char* line[5];
  for (int j=0;j<5;j++)line[j]=new char[512];
  r.starttable(inptable,3);
  for (std::vector<std::map<std::string,std::string> >::iterator itr=digidesc.begin();
       itr != digidesc.end();itr++){
    strcpy(line[0],((*itr)["name"]).c_str());
    strcpy(line[1],((*itr)["source"]).c_str());
    strcpy(line[2],((*itr)["description"]).c_str());
    r.addtableline(line,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=recondesc.begin();
       itr != recondesc.end();itr++){
    strcpy(line[0],((*itr)["name"]).c_str());
    strcpy(line[1],((*itr)["source"]).c_str());
    strcpy(line[2],((*itr)["description"]).c_str());
    r.addtableline(line,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=mcdesc.begin();
       itr != mcdesc.end();itr++){
    strcpy(line[0],((*itr)["name"]).c_str());
    strcpy(line[1],((*itr)["source"]).c_str());
    strcpy(line[2],((*itr)["description"]).c_str());
    r.addtableline(line,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=meritdesc.begin();
       itr != meritdesc.end();itr++){
    strcpy(line[0],((*itr)["name"]).c_str());
    strcpy(line[1],((*itr)["source"]).c_str());
    strcpy(line[2],((*itr)["description"]).c_str());
    r.addtableline(line,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=svacdesc.begin();
       itr != svacdesc.end();itr++){
    strcpy(line[0],((*itr)["name"]).c_str());
    strcpy(line[1],((*itr)["source"]).c_str());
    strcpy(line[2],((*itr)["description"]).c_str());
    r.addtableline(line,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=caldesc.begin();
       itr != caldesc.end();itr++){
    strcpy(line[0],((*itr)["name"]).c_str());
    strcpy(line[1],((*itr)["source"]).c_str());
    strcpy(line[2],((*itr)["description"]).c_str());
    r.addtableline(line,3);
  }
  r.endtable();
  r.newheadline("<b><center>Output variables</b></center>");
  char* outtable[]={"Name","Type","Formula","Cut","Description"};
  r.starttable(outtable,5);
  for(std::list<std::map<std::string,std::string> >::iterator itr=outputlist.begin();
      itr !=outputlist.end();itr++){
    strcpy(line[0],((*itr)["name"]).c_str());  
    strcpy(line[1],((*itr)["type"]).c_str());  
    strcpy(line[2],((*itr)["formula"]).c_str());  
    strcpy(line[3],((*itr)["cut"]).c_str());  
    strcpy(line[4],((*itr)["description"]).c_str());  
    r.addtableline(line,5);
}
  r.endtable();

  r.writereport();
  // Time profiling of the input variables
  for(unsigned int i=0;i<allinpcol.size();i++){
    allinpcol[i]->timeProfile();
  }
  std::cout<<std::endl;
  // Time profiling of the output variables
  std::cout<<"Time profile of primary output variables:"<<std::endl;
  std::cout<<"========================================="<<std::endl;
  outcolprim->timeProfile();
  std::cout<<std::endl;
  std::cout<<"Time profile of secondary output variables:"<<std::endl;
  std::cout<<"==========================================="<<std::endl;
  outcolsec->timeProfile();
  std::cout<<std::endl;
  globalCut->timeProfile();
  std::cout<<setiosflags(std::ios::left);
  std::cout<<std::setw(60)<<std::setfill(' ')<<"Total time spent in event loop "<<": "<<(float)(endtime-starttime)/1e6<<" seconds"<<std::endl;
  
  // Write an html report with parameters used (input/output)
  std::string htmlparamssuffix("_Parameters.html");
  std::string htmlparams=html+htmlparamssuffix;
  TestReport r2(htmlparams.c_str());
  r2.newheadline("<center><b>Input/Output parameters information</b></center>");
  
  r2.additem("Date", currenttime.c_str());
  r2.additem("Monitoring configuration file",jc.configFile().c_str());
  
  if(eventcut!="")r2.additem("Global event cut",eventcut.c_str());
  
  

  r2.newheadline("<center><b>Input variables</b></center>");
  char* inptableparams[]={"Name","Source","Description"};
  char* lineparams[3];
  for (int j=0;j<3;j++)lineparams[j]=new char[512];
  r2.starttable(inptableparams,3);
  for (std::vector<std::map<std::string,std::string> >::iterator itr=digidesc.begin();
       itr != digidesc.end();itr++){
    strcpy(lineparams[0],((*itr)["name"]).c_str());
    strcpy(lineparams[1],((*itr)["source"]).c_str());
    strcpy(lineparams[2],((*itr)["description"]).c_str());
    r2.addtableline(lineparams,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=recondesc.begin();
       itr != recondesc.end();itr++){
    strcpy(lineparams[0],((*itr)["name"]).c_str());
    strcpy(lineparams[1],((*itr)["source"]).c_str());
    strcpy(lineparams[2],((*itr)["description"]).c_str());
    r2.addtableline(lineparams,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=mcdesc.begin();
       itr != mcdesc.end();itr++){
    strcpy(lineparams[0],((*itr)["name"]).c_str());
    strcpy(lineparams[1],((*itr)["source"]).c_str());
    strcpy(lineparams[2],((*itr)["description"]).c_str());
    r2.addtableline(lineparams,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=meritdesc.begin();
       itr != meritdesc.end();itr++){
    strcpy(lineparams[0],((*itr)["name"]).c_str());
    strcpy(lineparams[1],((*itr)["source"]).c_str());
    strcpy(lineparams[2],((*itr)["description"]).c_str());
    r2.addtableline(lineparams,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=svacdesc.begin();
       itr != svacdesc.end();itr++){
    strcpy(lineparams[0],((*itr)["name"]).c_str());
    strcpy(lineparams[1],((*itr)["source"]).c_str());
    strcpy(lineparams[2],((*itr)["description"]).c_str());
    r2.addtableline(lineparams,3);
  }
  for (std::vector<std::map<std::string,std::string> >::iterator itr=caldesc.begin();
       itr != caldesc.end();itr++){
    strcpy(lineparams[0],((*itr)["name"]).c_str());
    strcpy(lineparams[1],((*itr)["source"]).c_str());
    strcpy(lineparams[2],((*itr)["description"]).c_str());
    r2.addtableline(lineparams,3);
  }
  r2.endtable();
  r2.newheadline("<b><center>Output variables</b></center>");
  char* outtableparams[]={"Name","Type","Description"};
  r2.starttable(outtableparams,3);
  for(std::list<std::map<std::string,std::string> >::iterator itr=outputlist.begin();
      itr !=outputlist.end();itr++){
    strcpy(lineparams[0],((*itr)["name"]).c_str());  
    strcpy(lineparams[1],((*itr)["type"]).c_str());  
    strcpy(lineparams[2],((*itr)["description"]).c_str());  
    r2.addtableline(lineparams,3);
}
  r2.endtable();

  r2.writereport();







  if (digiinpcol)delete digiinpcol;
  if (reconinpcol)delete mcinpcol;
  if (mcinpcol)delete mcinpcol;
  if (svacinpcol)delete svacinpcol;
  if (meritinpcol)delete meritinpcol;
  if (calinpcol)delete calinpcol;
  delete outcolprim;
  delete outcolsec;
  return 0;
}







