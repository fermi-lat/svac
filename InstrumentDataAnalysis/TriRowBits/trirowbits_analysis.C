{
#include <stdio.h>
#include <string.h>
#include "trirowbits_analysis.h"



gStyle->SetOptStat(0);
gStyle->SetPalette(1);

TChain *svac;

char *line, *filename, *svac_path;
svac_path = "$SVAC_DATA/";

if (svac)
   svac->Delete();
   else
   svac = new TChain("Output");

readchainfile(svac);

int n_fakehits, n_inconsistent_events, n_miss;
TH2D *plot = new TH2D("plot", "", 200, 0, 17, 200, 0, 17);

int tower =0;  //Tower to be analyzed 0-15

check_consistency(tower);


}
