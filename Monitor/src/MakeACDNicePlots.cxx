// Authors: D. Paneque, SLAC
// Description
/*
This is a program that produces nice ACD hit maps. It uses histograms produced by the monitoring job on digi root files with the configuration file monconfig_digi_histos.xml. The program is based on the macro from Nicola Mazziota and Silvia Raino, called ACDCountsMapPlot.C.

*/



// stl stuff
#include <list>
#include <map>
#include <string>
#include <vector>

//
// io stuff
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <getopt.h>


// root classes
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TFile.h"
#include "TH1.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TString.h"
#include "TCanvas.h"
#include "TKey.h"
#include "TClass.h"
#include "TMath.h"
#include "TBox.h"
#include "TText.h"

// ACD tiles geometry
#include "ACDTiles.h"


using namespace std;

int usage()
{
   cout << endl
       << "MakeACDNicePlots" << endl
       << "This is a program that produces nice ACD hit maps (ps,gif,root format). It uses histograms produced by the monitoring job on digi root files with the configuration file monconfig_digi_histos.xml. The program is based on the macro from Nicola Mazziota and Silvia raino, called ACDCountsMapPlot.C. " << endl
       << endl;
  
  std::cout << "Usage:" << endl
       << "\t" << "MakeACDNicePlots -i <inputFile> -o <outputDir> -f <flag>" << endl 
       << std::endl;

  std::cout << "\t inputFile is the root file produced by the monitoring job. It contains the histograms with the ACD hit information " << std::endl
	    << "\t outputDir is the directory where the plots (.gif and .root) will be saved" << std::endl
	    << "\t flag is a suffix appended to the names of the output plots which is supposed to identify the input root file. A practical possibility for the flag is the run number. " <<std::endl;


  return -1;
}


int main(int argn, char** argc)

{

  std::string infile;
  std::string outplotpath;
  std::string plotflag;

// parse options

  int opt;
  while ( (opt = getopt(argn, argc, "ho:i:f:")) != EOF ) {
    switch (opt) {
    case 'h':   // help      
      usage();
      return 2;
    case 'i':   // input root file 
      infile = std::string(optarg);
      break;
    case 'o':   //  outputDir
      outplotpath = std::string(optarg);
      break;
    case 'f':   // flag
      plotflag = std::string(optarg);
      break; 
    case '?':
      usage();
      return 2;
    default:
      std::cerr << opt << " not parsable..." << std::endl;
      std::cerr << "Run MakeACDNicePlots.exe -h for help" << std::endl;
      // parse options
    }
  }
  
  if (infile.size()==0 || outplotpath.size()==0 || plotflag.size()==0){
    std::cout<<"Missing input parameters. Run  MakeACDNicePlots.exe -h for help."<<std::endl;
    return 2;
  }
  

  // std::string infile = "/nfs/farm/g/glast/u33/dpaneque/DataMonitoring/20080227/svac/Monitor/rh9_gcc32opt/test_2008March/Digi_Histos_rootTEST_time.root";
  

  const Int_t NHistos=6;
  const Int_t NChannels = 604;
  char* vhistoname[NHistos] = {"AcdVetoA_DigiIdMap_TH1",
			       "AcdVetoB_DigiIdMap_TH1",
			       "AcdVetoA_Or_B_DigiIdMap_TH1",
			       "AcdVetoA_And_B_DigiIdMap_TH1",
			       "AcdVetoB_And_NotA_DigiIdMap_TH1",
			       "AcdVetoA_And_NotB_DigiIdMap_TH1"};

  Int_t SavePlots = 1; // 1 for YES, 0 for NO
  //std::string outplotpath = "/nfs/farm/g/glast/u33/dpaneque/DataMonitoring/20080227/svac/Monitor/rh9_gcc32opt/test_2008March/ADCPlots";
  //std::string plotflag = "SillyTest"; // it could be the run number


  std::vector <std::string> vplotname;
  for(Int_t i=0;i<NHistos;i++)
    {
      std::string tmp(outplotpath);
      tmp+="/";
      tmp+=vhistoname[i];
      tmp.resize(tmp.size()-3); // remove the TH1 ending
      tmp+=plotflag;
      // The plotnames will be completed with the suffix .gif and .root before saving.
      vplotname.push_back(tmp);
    }
    
  Int_t CleanAndReleaseMemory = 1; // 1 for YES and 0 for NO.


  TH1F* vhisto[NHistos];
  TFile* f = new TFile(infile.c_str(), "READ");
  if(!f->IsOpen())
    {
      std::cout << "MakeACDNicePlots::ERROR " << std::endl
		<< "File " << infile.c_str()<< " could not be opened" << std::endl
		<< "Aborting" << std::endl;
      return 1;
    }

  // Get histograms

  for (Int_t i=0; i <NHistos; i++)
    {
      vhisto[i] = (TH1F*)f->Get(vhistoname[i]);
      vhisto[i]->SetDirectory(0);
      if(vhisto[i] == NULL)
	{
	  std::cout << "MakeACDNicePlots::ERROR " << std::endl
		    << "Histogram " << vhistoname[i] << " could not be retrieved" 
		    << "Aborting" << std::endl;
	  return 2;
	}
    }
  f->Close();

  // Definition of the geometry and vectors to count hits

  float xmax, ymax, x0, y0, x1, y1;
  float offset = 5., offset1=5;
  // int i(0), j(0), k(0);
  const Int_t NtileTop=5;
  const Int_t NtileSide=4;
  float StileTop = 10., StileSide=4;
  xmax = NtileTop*StileTop + 2*NtileSide*StileSide + 2.*offset + 2.*offset1 ;
  ymax = xmax;

  TString CTop[NtileTop][NtileTop] = {{"000", "010", "020", "030", "040"}, 
				       {"001", "011", "021", "031", "041"},
				       {"002", "012", "022", "032", "042"},
				       {"003", "013", "023", "033", "043"},
				       {"004", "014", "024", "034", "044"}};


  TString CSide1[NtileSide-1][NtileTop] = {{"120", "121", "122", "123", "124"}, 
					   {"110", "111", "112", "113", "114"}, 
					   {"100", "101", "102", "103", "104"}};  

  TString CSide2[NtileSide-1][NtileTop] = {{"220", "221", "222","223","224"}, 
					    {"210", "211", "212","213","214"},
					    {"200", "201", "202","203","204"}};

  TString CSide3[NtileSide-1][NtileTop] = {{"300", "301", "302", "303", "304"}, 
					   {"310", "311", "312", "313", "314"},
					   {"320", "321", "322", "323", "324"}};

  TString CSide4[NtileSide-1][NtileTop]  = {{"400", "401", "402","403","404"}, 
					    {"410", "411", "412","413","414"},
					    {"420", "421", "422","423","424"}};


  //

  float hitcount[NChannels][NHistos];
  float count0[NChannels];
  float count1[NChannels];
  float count2[NChannels];
  float count3[NChannels];
  float count4[NChannels];
  float count5[NChannels];




  for (int i=0; i<NChannels; i++){
    for(int number=0; number<NHistos; ++number){
      hitcount[i][number] = vhisto[number]->GetBinContent(i+1);
    }
  }
 

  float MaxCount[NHistos];
  for (int i=0; i<NChannels; i++){
    count0[i]=hitcount[i][0];
    count1[i]=hitcount[i][1];
    count2[i]=hitcount[i][2];
    count3[i]=hitcount[i][3];
    count4[i]=hitcount[i][4];
    count5[i]=hitcount[i][5];
  }

 

  MaxCount[0]= TMath::MaxElement(NChannels,count0);
  MaxCount[1]= TMath::MaxElement(NChannels,count1);
  MaxCount[2]= TMath::MaxElement(NChannels,count2);
  MaxCount[3]= TMath::MaxElement(NChannels,count3);
  MaxCount[4]= TMath::MaxElement(NChannels,count4);
  MaxCount[5]= TMath::MaxElement(NChannels,count5);
  

  float icol;
  int tileID;

  TCanvas* canv[NHistos];
  TString ctitle, ctitle1;
  
  for (int k=0; k<NHistos; k++){
    ctitle = "canv[";
    ctitle += k;
    ctitle += "]";
    
    canv[k] = new TCanvas(ctitle, ctitle1,0,0,1100,900);
    canv[k]->SetFillStyle(4000);
    canv[k]->SetFillColor(0);
    canv[k]->SetBorderSize(3); 
    canv[k]->SetFrameBorderMode(0);
    canv[k]->SetFrameBorderSize(3);
    canv[k]->SetFrameLineWidth(2);
    //    gStyle->SetLineWidth(2);
  }


  for (int k=0; k<NHistos; k++){
    canv[k]->cd();
    switch(k){
    case 0: ctitle1 = "PMT A"; break;
    case 1: ctitle1 = "PMT B"; break; 
    case 2: ctitle1 = "PMTA OR PMTB"; break;
    case 3: ctitle1 = "PMTA AND PMTB"; break;
    case 4: ctitle1 = "!PMTA AND PMTB"; break;
    case 5: ctitle1 = "PMTA AND !PMTB"; break;
    }
  
    TH1F *frame1 = gPad->DrawFrame(0., 0., xmax, ymax);
    frame1->SetTitle(ctitle1);
    frame1->GetXaxis()->CenterTitle();
    frame1->GetYaxis()->CenterTitle();
    frame1->GetXaxis()->SetTitle(0);
    frame1->GetYaxis()->SetTitle(0);
    frame1->GetXaxis()->SetLabelColor(0);
    frame1->GetYaxis()->SetLabelColor(0);
    frame1->GetXaxis()->SetNdivisions(kFALSE);
    frame1->GetYaxis()->SetNdivisions(kFALSE);
    

    for (int i=0; i<NtileTop; i++) {
      x0 = offset +  NtileSide*StileSide + offset1 + i*StileTop;
      x1 = x0 + StileTop;
      for (int j=0; j<NtileTop; j++) {
	y0 = offset +  NtileSide*StileSide + offset1 + j*StileTop;
	y1 = y0 + StileTop;
	TBox *box = new TBox(x0, y0, x1, y1);
	tileID = toptiles(i,j);
	if ( hitcount[tileID][k] <= 1) {
	  icol=0;
	} else {
	  icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
	}
	box->SetFillStyle(1);
	box->SetFillColor(Short_t(icol)); 
	box->Draw("l");
	TText *tt = new TText((x0+x1)/2, (y0+y1)/2, CTop[i][j]);
	tt->SetTextSize(0.03);
	tt->SetTextAlign(22);
	tt->Draw();
      }
    }
    
    // Side 1 
    x0 = offset;
    x1 = x0 + StileSide;
    y0 = offset + NtileSide*StileSide + offset1;
    y1 = y0 + NtileTop*StileTop;
    TBox *box = new TBox(x0, y0, x1, y1);
    tileID=singletiles(0);
    if ( hitcount[tileID][k] <= 1) {
      icol=0;
    } else {
      icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
    }
    box->SetFillStyle(1);
    box->SetFillColor(Short_t(icol));
    box->Draw("l");
    TText *tt = new TText((x0+x1)/2, (y0+y1)/2, "130");
    tt->SetTextSize(0.03);
    tt->SetTextAlign(22);
    tt->SetTextAngle(-90);
    tt->Draw();
    
    
    for (int i=0; i<NtileSide-1; i++) {
      x0 = offset +  (i+1)*StileSide;
      x1 = x0 + StileSide;
      for (int j=0; j<NtileTop; j++) {
	y0 = offset + NtileSide*StileSide + NtileTop*StileTop*j/5 + offset1;
	y1 = y0 + NtileTop*StileTop/5;
	TBox *box = new TBox(x0, y0, x1, y1);
	box->Draw("l");
	tileID=side1tiles(i,j);
	if ( hitcount[tileID][k] <= 1) {
	  icol=0;
	} else {
	  icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
	}
	box->SetFillStyle(1);
	box->SetFillColor(Short_t(icol));
	box->Draw("l");
	TText *tt = new TText((x0+x1)/2, (y0+y1)/2, CSide1[i][j]);
	tt->SetTextSize(0.03);
	tt->SetTextAlign(22);
	tt->SetTextAngle(-90);
	tt->Draw();
      }
    }
    
    
    // Side 3
    x0 = offset + NtileTop*StileTop +  (NtileSide+3)*StileSide + 2*offset1;
    x1 = x0 + StileSide;
    y0 = offset + NtileSide*StileSide + offset1;
    y1 = y0 + NtileTop*StileTop;
    box = new TBox(x0, y0, x1, y1);
    tileID=singletiles(2);
    if ( hitcount[tileID][k] <= 1) {
      icol=0;
    } else {
      icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
    }
    box->SetFillStyle(1);
    box->SetFillColor(Short_t(icol));
    box->Draw("l");
    tt = new TText((x0+x1)/2, (y0+y1)/2, "330");
    tt->SetTextSize(0.03);
    tt->SetTextAlign(22);
    tt->SetTextAngle(90);
    tt->Draw();
    
    
    for (int i=0; i<NtileSide-1; i++) {
      x0 = offset +   NtileTop*StileTop + (NtileSide-1)*StileSide + 2*offset1 + (i+1)*StileSide;
      x1 = x0 + StileSide;
      for (int j=0; j<NtileTop; j++) {
	y0 = offset + NtileSide*StileSide + NtileTop*StileTop*j/5 + offset1;
	y1 = y0 + NtileTop*StileTop/5;
	TBox *box = new TBox(x0, y0, x1, y1);
	box->Draw("l");
	tileID=side3tiles(i,j);
	if ( hitcount[tileID][k] <= 1) {
	  icol=0;
	} else {
       icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
	}
	box->SetFillStyle(1);
	box->SetFillColor(Short_t(icol));
	box->Draw("l");
	TText *tt = new TText((x0+x1)/2, (y0+y1)/2, CSide3[i][j]);
	tt->SetTextSize(0.03);
	tt->SetTextAlign(22);
	tt->SetTextAngle(90);
	tt->Draw();
      }
    }
    
    // Side 2
    y0 = offset;
    y1 = y0 + StileSide;
    x0 = offset + NtileSide*StileSide + offset1;
    x1 = x0 + NtileTop*StileTop;
    box = new TBox(x0, y0, x1, y1);
    tileID=singletiles(1);
    if ( hitcount[tileID][k] <= 1) {
      icol=0;
    } else {
      icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
    }
    box->SetFillStyle(1);
    box->SetFillColor(Short_t(icol));
    box->Draw("l");
    tt = new TText((x0+x1)/2, (y0+y1)/2, "230");
    tt->SetTextSize(0.03);
    tt->SetTextAlign(22);
    tt->SetTextAngle(0);
    tt->Draw();
    
    
    for (int i=0; i<NtileSide-1; i++) {
      y0 = offset +  (i+1)*StileSide;
      y1 = y0 + StileSide;
      for (int j=0; j<NtileTop; j++) {
	x0 = offset + NtileSide*StileSide + NtileTop*StileTop*j/5 + offset1;
	x1 = x0 + NtileTop*StileTop/5;
	TBox *box = new TBox(x0, y0, x1, y1);
	box->Draw("l");
	tileID=side2tiles(i,j);
	if ( hitcount[tileID][k] <= 1) {
	  icol=0;
	} else {
	  icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
	}
	box->SetFillStyle(1);
	box->SetFillColor(Short_t(icol));
	box->Draw("l");
	TText *tt = new TText((x0+x1)/2, (y0+y1)/2, CSide2[i][j]);
	tt->SetTextSize(0.03);
	tt->SetTextAlign(22);
	tt->SetTextAngle(0);
	tt->Draw();
      }
    }
    
    
    // Side 4
    y0 = offset + NtileTop*StileTop +  (NtileSide+3)*StileSide + 2*offset1;
    y1 = y0 + StileSide;
    x0 = offset + NtileSide*StileSide + offset1;
    x1 = x0 + NtileTop*StileTop;
    box = new TBox(x0, y0, x1, y1);
    box->Draw("l");
    tileID=singletiles(3);
    if ( hitcount[tileID][k] <= 1) {
      icol=0;
    } else {
      icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
    }
    box->SetFillStyle(1);
    box->SetFillColor(Short_t(icol));
    box->Draw("l");
    tt = new TText((x0+x1)/2, (y0+y1)/2, "430");
    tt->SetTextSize(0.03);
    tt->SetTextAlign(22);
    tt->SetTextAngle(0);
    tt->Draw();
    
    
    
    for (int i=0; i<NtileSide-1; i++) {
      y0 = offset +   NtileTop*StileTop + (NtileSide-1)*StileSide + 2*offset1 + (i+1)*StileSide;
      y1 = y0 + StileSide;
      for (int j=0; j<NtileTop; j++) {
	x0 = offset + NtileSide*StileSide + NtileTop*StileTop*j/5 + offset1;
	x1 = x0 + NtileTop*StileTop/5;
	TBox *box = new TBox(x0, y0, x1, y1);
	box->Draw("l");
	tileID=side4tiles(i,j);
	if ( hitcount[tileID][k] <= 1) {
	  icol=0;
	} else {
	  icol =29 + 20*hitcount[tileID][k]/MaxCount[k];
	}
	box->SetFillStyle(1);
	box->SetFillColor(Short_t(icol));
	box->Draw("l");
	TText *tt = new TText((x0+x1)/2, (y0+y1)/2, CSide4[i][j]);
	tt->SetTextSize(0.03);
	tt->SetTextAlign(22);
	tt->SetTextAngle(0);
	tt->Draw();
      }
    }
  
 int nn0 = int(TMath::Log10(MaxCount[k]));

 int ScaleMax = int((TMath::Ceil(MaxCount[k]/TMath::Power(10,nn0-1))*TMath::Power(10,nn0-1)));

 int scaletext[22];
 scaletext[0]=1;
 scaletext[21]=ScaleMax;
 for (int l=1; l<21; l++){
   int temp = int((TMath::Ceil(ScaleMax/21))*l);
   scaletext[l]= temp;
 }

 TString scale[22];
 for (int l=0; l<22; l++){
   scale[l]= " ";
   scale[l] += scaletext[l];
   //cout << scale[l] << endl;
 }

 float x0nbox, x1nbox;
 x0nbox=100;
 x1nbox=105;
 float y0nbox, y1nbox, boxcol;
   for (int i=0; i<22; i++){
     y0nbox = 2+4.5*i;
     y1nbox = 6.5+4.5*i;
        TBox *box = new TBox(x0nbox, y0nbox, x1nbox, y1nbox);
	//     box->Draw("l");
	if (i == 0) {
	  boxcol=0;
	} else {
	  boxcol =28 + i;
	}
	box->SetFillColor(Short_t(boxcol));       
	box->Draw("l");
   
	TText *ttsc = new TText((x1nbox), y1nbox, scale[i]);
	ttsc->SetTextSize(0.02);
	ttsc->SetTextAngle(0);
	ttsc->Draw();
   }
   
   canv[k]->Modified();
   canv[k]->Update();
  } // end for su k


  if(SavePlots)
    {
      std::string plotname;
      for(Int_t iplot=0; iplot <NHistos;iplot++)
	{
	  plotname= vplotname[iplot];
	  plotname+=".gif";
	  canv[iplot]->SaveAs(plotname.c_str());
	  plotname= vplotname[iplot];
	  plotname+=".root";
	  canv[iplot]->SaveAs(plotname.c_str());
	  plotname= vplotname[iplot];
	  plotname+=".ps";
	  canv[iplot]->SaveAs(plotname.c_str());
	}
    }


  if(CleanAndReleaseMemory)
    {
      // std::cout << "Cleaning stuff" << std::endl;
      for(Int_t i = 0; i < NHistos;i++){
	delete vhisto[i];
	delete canv[i];
      }
    }

  return 0;
 
}


