{

// an example to analyze info stored in the svac ntuple.
// to run the macro, simply do .x ana.C
// the macro will fill a histogram of planes that are hit for events with less
// than 6 digis, fill a ntuple containing reconstructed direction and number
// of digis for each event, then store the histigram and the ntuple in a root
// file

gROOT->Reset();

TExec ex;
ex.Exec(".L anaSvacNtuple.C");

// open the root file to store results of running the macro
TFile f1("temp.root", "RECREATE");

// open an array of histograms and an ntuple to pass to another macro
TH1F* h[5];
TNtuple* n = new TNtuple("Output", "Output", "TotalHits:TotalClusters");
//h[0] = new TH1F("h1", "h1", 36, -0.5, 35.5);

// run the macro which does the real work
anaSvacNtuple("/nfs/farm/g/glast/u12/EM2/rootData/398000310/calib-v1r0/svacRoot/emRootv0r0/svacTuple-EM2-v1r0_398000310_svac_svac.root", n, h);

f1.cd();
f1.Write(0, TObject::kOverwrite);
f1.Close();

}
