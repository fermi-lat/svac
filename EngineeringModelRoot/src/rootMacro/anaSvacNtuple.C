void anaSvacNtuple(const char* ra, TNtuple* tuple, TH1F** h) {

  TFile f(ra);

  TTree* t1 = (TTree*) f.Get("Output");

  // declare variables to hold data read from the tree
  // note some variables in the svac ntuple are arrays, so it is neccessary
  // to have an array to hold the data loaded from the svac ntuple file.
  // check the description of the svac ntuple on the web to determine size and
  // dimension of the array
  int nStrips[16][18][2];
  int nTkrNumDigis;
  float dir[3];

  // load an branch. The branch name is the same as the variable name in the
  // svac ntuple
  TBranch* brTkrNumStrips = t1->GetBranch("TkrNumStrips");
  brTkrNumStrips->SetAddress(&nStrips);
  TBranch* brVtxXDir = t1->GetBranch("VtxXDir");
  brVtxXDir->SetAddress(&dir[0]);
  TBranch* brVtxYDir = t1->GetBranch("VtxYDir");
  brVtxYDir->SetAddress(&dir[1]);
  TBranch* brVtxZDir = t1->GetBranch("VtxZDir");
  brVtxZDir->SetAddress(&dir[2]);
  int nEvt = (int) t1->GetEntries();

  cout << "nEvent = " << nEvt << endl;

  for(int i = 0; i != nEvt; ++i) {
    
    t1->GetEntry(i);

    tuple->Fill(nTkrNumDigis, dir[0], dir[1], dir[2]);
  
    if(nTkrNumDigis >= 6) continue;

    for(int biLayer = 0; biLayer != 18; ++biLayer) {
      for(int view = 0; view != 2; ++view) {
	if(nStrips[0][biLayer][view] > 0) {
	  h[0]->Fill(getPlane(biLayer, view));
	}
      }
    } 

  }

}


// given the biLayer number and the view, return the corresponding plane number
// plane 0 is at the bottom.
int getPlane(int biLayer, int view)
{
  static int map[18][2];
  static bool first = true;
  if(first) {
    map[0][1] = 0;
    map[0][0] = 1;
    map[1][0] = 2;
    map[1][1] = 3;
    map[2][1] = 4;
    map[2][0] = 5;
    map[3][0] = 6;
    map[3][1] = 7;
    map[4][1] = 8;
    map[4][0] = 9;
    map[5][0] = 10;
    map[5][1] = 11;
    map[6][1] = 12;
    map[6][0] = 13;
    map[7][0] = 14;
    map[7][1] = 15;
    map[8][1] = 16;
    map[8][0] = 17;
    map[9][0] = 18;
    map[9][1] = 19;
    map[10][1] = 20;
    map[10][0] = 21;
    map[11][0] = 22;
    map[11][1] = 23;
    map[12][1] = 24;
    map[12][0] = 25;
    map[13][0] = 26;
    map[13][1] = 27;
    map[14][1] = 28;
    map[14][0] = 29;
    map[15][0] = 30;
    map[15][1] = 31;
    map[16][1] = 32;
    map[16][0] = 33;
    map[17][0] = 34;
    map[17][1] = 35;
    first = false;
  }

  return map[biLayer][view];
}
