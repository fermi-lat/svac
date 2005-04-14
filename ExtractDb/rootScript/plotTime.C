void main()
{
gROOT->Reset();

#include <iostream>
#include <time.h>
#include <stdlib.h>


// time range to plot, must formatted as YYYY-MM-DD HH:MI:SS
const char* startTimeStr = "2005-03-26 19:25:50";
const char* endTimeStr = "2005-03-26 20:25:51";

gSystem->Setenv("TZ", "UTC");
TDatime start(startTimeStr);
unsigned int startTime  = (unsigned int) start.Convert(1);
TDatime end(endTimeStr);
unsigned int endTime  = (unsigned int) end.Convert(1);

unsigned int offset = startTime;

// Unlike what root tutorial describes, the offset should be set as 0 rather 
// than start time.
gStyle->SetTimeOffset(0);

TCanvas* c = new TCanvas;
gPad->SetBorderMode(0);
gPad->SetFillColor(10);


TString s("(EvtSecond > ");
s += startTime;
s += " && EvtSecond < ";
s += endTime;
s += " && TkrNumStrips[0][1][1]>0)";



TFile* f = new TFile("/nfs/farm/g/glast/u12/Integration/rootData/135000894/v4r060302p8/calib-v1r0/svacTuple/emRootv0r0/svacTuple-v3r1p2_135000894_svac_svac.root", "READ");

Output->Draw("TkrNumStrips[0][1][1]:EvtSecond >> temp", s.Data(), "prof");

TProfile* h = (TProfile*) gDirectory->Get("temp");
h->SetStats(kFALSE);
h->Draw();
h->GetXaxis()->SetTimeDisplay(1);
h->GetXaxis()->SetTimeFormat("%H:%M:%S");


TFile f1("/nfs/farm/g/glast/u06/chen/svac/ExtractDb/v0/output/hk.root");
TTree* hk = (TTree*) gDirectory->Get("hk");
TString s1("(name == \"LHKT0TKRC0T0\" && time");
s1 += " > ";
s1 += startTime;
s1 += " && time";
s1 += " < ";
s1 += endTime;
s1 += ")";
 cout << s1.Data() << endl;
TCut cut2 = s1.Data();

TString dr("value:time");
 cout << "estimates = " << hk->GetEntries() << endl;
hk->SetEstimate((int) hk->GetEntries());
hk->Draw(dr.Data(), s1.Data(), "goff");
Double_t* x = hk->GetV2();
Double_t* y = hk->GetV1();
int n = hk->GetSelectedRows();
cout << "selected rows = " << n << endl;

Double_t max = y[0], min = y[0];
for(int i = 1; i != n; ++i) {
  if(y[i] > max) max = y[i];
  else if(y[i] < min) min = y[i];
}

if(max > 0) {
  max *= 1.02;
}
else {
  max *= 0.98;
}
if(min > 0) {
  min *= 0.98;
}
else {
  min *= 1.02;
}

// must call Update() so that gPad->GetUxmax() produces correct value
c->Update();
TGaxis* axis = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(),
			  gPad->GetUymax(), min, max);
axis->SetLineColor(kRed);
axis->SetTextColor(kRed);
axis->SetLabelColor(kRed);
axis->Draw();

Float_t scale = (gPad->GetUymax()-gPad->GetUymin())/(max-min);
Float_t shift = gPad->GetUymin() - scale*min;

printf("%f %f %f %f\n", max, min, scale, shift);
for(int i = 0; i != n; ++i) {
  y[i] =  scale * y[i] + shift;
}

TGraph* gr = new TGraph(n, x, y);
gr->SetMarkerColor(2);
gr->Draw("*");

}
