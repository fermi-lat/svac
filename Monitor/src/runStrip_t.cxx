
//
// stl
#include <string>
#include <list>
#include <fstream>

//
// ROOT-io
#include "TFile.h"

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
#include "MonValueImpls_t.h"
#include "MonConfigParser.h"



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
  if (jc.digiChain())digiinpcol=new MonInputCollection_Digi(jc.digiChain(),"DigiEvent");
  if (jc.reconChain())reconinpcol=new MonInputCollection_Recon(jc.reconChain(),"ReconEvent");
  if (jc.mcChain())mcinpcol=new MonInputCollection_Mc(jc.mcChain(),"McEvent");
  MonObjFactory fact;
  bool tsfound=false;
  for (std::list<string>::const_iterator itr=inputlist.begin();
       itr != inputlist.end();itr++){
    MonInputObject* obj=fact.getMonInputObject(*itr);
    assert(obj!=0);
    bool added=false;
    if(digiinpcol && obj->getInputSource()=="DigiEvent"){
      digiinpcol->addInputObject(obj);
      added=true;
    }
    if(reconinpcol && obj->getInputSource()=="ReconEvent"){
      reconinpcol->addInputObject(obj);
      added=true;
    }
    if(mcinpcol && obj->getInputSource()=="McEvent"){
      mcinpcol->addInputObject(obj);
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
  if(digiinpcol)ndigiobjects= digiinpcol->nObjects();
  if (ndigiobjects>0)allinpcol.push_back(digiinpcol);
  if(reconinpcol)nreconobjects= reconinpcol->nObjects();
  if(nreconobjects>0)allinpcol.push_back(reconinpcol);
  if(mcinpcol )nmcobjects= mcinpcol->nObjects();
  if(nmcobjects>0)allinpcol.push_back(mcinpcol);
  if (ndigiobjects+nreconobjects+nmcobjects==0){
    std::cerr<<"No input objects defined. Exiting..."<<std::cerr;
    assert(0);
  }
  // now the output 
  std::list<std::map<std::string,std::string> > outputlist=p.getOutputList();
  MonValFactory mf;
  std::string eventcut=p.getEventCut();
  std::cout<<"Event cut "<<eventcut<<std::endl;
  MonValueCol* outcol=mf.makeMonValueCol(outputlist,"Top",eventcut.c_str());
  // Attach digi tree to input object
  // build filler & run over events
  MonEventLooper d(jc.optval_b(), outcol,allinpcol, eventcut,timestamp);
  Int_t nTotal=jc.digiChain()->GetEntries();
  Long64_t numevents=jc.optval_n()  < 1 ? nTotal : TMath::Min(jc.optval_n()+jc.optval_s(),nTotal);
  d.go(numevents,jc.optval_s());    
  
  // Ok, write the output and clean up
  fout->cd();
  d.tree()->Write();
  fout->Close();

  if (digiinpcol)delete digiinpcol;
  if (reconinpcol)delete mcinpcol;
  if (mcinpcol)delete mcinpcol;
  return 0;
}







