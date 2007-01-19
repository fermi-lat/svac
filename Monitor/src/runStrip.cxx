
//
// stl
#include <string>
#include <fstream>

//
// ROOT-io
#include "TFile.h"

//
// Job configuration and options parser
#include "JobConfig.h"

//
// The thing that actually does the work
#include "MonEventLooper_Digi.h"


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

  Bool_t okToContinue = jc.checkDigi();
  if ( ! okToContinue ) return 1; // no input, fail

  // strip chart output do this before the event loop
  // so that we abort the output won't work
  std::string outputFile = jc.outputPrefix() + "_time.root";
  TFile* fout = TFile::Open(outputFile.c_str(),"CREATE");
  if ( fout == 0 || fout->IsZombie() ) {
    std::cerr << "Failed to open output File " << outputFile << std::endl;
    return -1;
  }

  // build filler & run over events
  MonEventLooper_Digi d(jc.digiChain(), jc.optval_b());
  d.go(jc.optval_n(),jc.optval_s());    
  
  // Ok, write the output and clean up
  fout->cd();
  d.tree()->Write();
  fout->Close();

  return 0;
}







