{
gROOT->Reset();

unsigned int startTime = 1097232000;
unsigned int endTime = startTime + 3600;
unsigned int offset = startTime - 1092105000;

TString s("(EvtSecond > ");
s += startTime;
s += " && EvtSecond < ";
s += endTime;
s += ")";

TCut cut1(s.Data());

TFile f("/nfs/farm/g/glast/u01/italyOneTower/em_v3r0404p2/306000163/041008101639_svac.root", "READ");

gStyle->SetTimeOffset(0);

TCanvas* c = new TCanvas;

Output->Draw("TkrNumTracks:EvtSecond >> temp", cut1, "prof");

TProfile* h = (TProfile*) gDirectory->Get("temp");
h->GetXaxis()->SetTimeDisplay(1);
h->GetXaxis()->SetTimeFormat("%H:%M:%S");
h->SetStats(kFALSE);
h->Draw();

TFile f1("/nfs/slac/g/svac/chen/svac/ExtractDb/v0/output/hk.root");
TString s1("(name == \"LHKT0TKRC0T0\" && (time+");
s1 += offset;
s1 += ") > ";
s1 += startTime;
s1 += " && (time+";
s1 += offset;
s1 += ") < ";
s1 += endTime;
s1 += ")";
TCut cut2(s1.Data());

TString dr("value:(time+");
dr += offset;
dr += ")";
hk->SetEstimate((int) hk->GetEntries());
hk->Draw(dr.Data(), cut2, "goff");
Double_t* x = hk->GetV2();
Double_t* y = hk->GetV1();
int n = hk->GetSelectedRows();
Double_t max = y[0], min = y[0];
for(int i = 1; i != n; ++i) {
  if(y[i] > max) max = y[i];
  else if(y[i] < min) min = y[i];
}

if(max > 0) {
  max *= 1.1;
}
else {
  max *= 0.9;
}
if(min > 0) {
  min *= 0.9;
}
else {
  min *= 1.1;
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
//gr->GetXaxis()->SetTimeDisplay(1);
//gr->GetXaxis()->SetTimeFormat("%H-%M");
//gPad->Modified();

}
