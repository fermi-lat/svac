void anaSvacNtuple(const char* ra, TNtuple* tuple, TH1F** h) {

  TFile f(ra);

  TTree* t1 = (TTree*) f.Get("Output");

  int m_nStrips[16][18][2];
  int m_nTkrNumDigis;
  float m_dir[3];

  TBranch* brTkrNumStrips = t1->GetBranch("TkrNumStrips");
  brTkrNumStrips->SetAddress(&m_nStrips);
  TBranch* brTkrNumTracks = t1->GetBranch("TkrNumDigis");
  brTkrNumTracks->SetAddress(&m_nTkrNumDigis);
  TBranch* brVtxXDir = t1->GetBranch("VtxXDir");
  brVtxXDir->SetAddress(&m_dir[0]);
  TBranch* brVtxYDir = t1->GetBranch("VtxYDir");
  brVtxYDir->SetAddress(&m_dir[1]);
  TBranch* brVtxZDir = t1->GetBranch("VtxZDir");
  brVtxZDir->SetAddress(&m_dir[2]);
  int nEvt = (int) t1->GetEntries();

  cout << "nEvent = " << nEvt << endl;

  for(int i = 0; i != nEvt; ++i) {
    
    t1->GetEntry(i);

    tuple->Fill(m_nTkrNumDigis, m_dir[0], m_dir[1], m_dir[2]);
  
    if(m_nTkrNumDigis >= 6) continue;

    for(int biLayer = 0; biLayer != 18; ++biLayer) {
      for(int view = 0; view != 2; ++view) {
	if(m_nStrips[0][biLayer][view] > 0) {
	  h[0]->Fill(getPlane(biLayer, view));
	}
      }
    } 

  }

}


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
