{

gROOT->Reset();

TExec ex;
ex.Exec(".L anaSvacNtuple.C");

TFile f1("noisy.root", "RECREATE");
TNtuple* n1 = new TNtuple("n1", "n1", "nMLayers:nTracks:dirX:dirY:dirZ");
anaSvacNtuple("/nfs/slac/g/svac/mc/em_v3r0407p1/oneTowerNoisyAm/surface_muons_100000_0_svac.root", n1, 0);
f1.cd();
f1.Write(0, TObject::kOverwrite);
f1.Close();

TFile f2("normal.root", "RECREATE");
TNtuple* n2 = new TNtuple("n2", "n2", "nMLayers:nTracks:dirX:dirY:dirZ");
anaSvacNtuple("/nfs/slac/g/svac/mc/em_v3r0404p2/1Tower/surface_muons_200000_0_svac.root", n2, 0);
f2.cd();
f2.Write(0, TObject::kOverwrite);
f2.Close();
}
