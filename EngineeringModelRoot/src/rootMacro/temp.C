{

gROOT->Reset();

TCanvas* c1 = new TCanvas;
c1->Divide(1,2);
gPad->SetBorderMode(0);
gPad->SetFillColor(10);

TFile f1("normal.root");
c1->cd(1);
gPad->SetBorderMode(0);
gPad->SetFillColor(10);
n2->Draw("dirZ", "nMLayers>=3 && nTracks>0");

TFile f2("noisy.root");
c1->cd(2);
gPad->SetBorderMode(0);
gPad->SetFillColor(10);
n1->Draw("dirZ", "nMLayers>=3 && nTracks>0");

}
