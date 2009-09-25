{

gROOT->Reset();

TExec ex;
ex.Exec(".L anaSvacNtuple.C");

TFile f1("temp.root", "RECREATE");
TH1F* h[5];
TNtuple* n = new TNtuple("n1", "n1", "TkrNumDigis:VtxXDir:VtxYDir:VtxZDir");
h[0] = new TH1F("h1", "h1", 36, -0.5, 35.5);
anaSvacNtuple("/nfs/farm/g/glast/u12/EM2/rootData/398000371/calib-v1r0/svacRoot/emRootv0r0/svacTuple-EM2-v1r0_398000371_svac_svac.root", n, h);
f1.cd();
f1.Write(0, TObject::kOverwrite);
f1.Close();

}
