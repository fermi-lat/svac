void anaSvacNtuple(const char* ra, TNtuple* tuple, TH1F** h) {

  int nLayers = 4;

  TFile f(ra);

  TTree* t1 = (TTree*) f.Get("Output");

  int m_nStrips[16][18][2];
  int m_nTkrTracks;
  float m_dir[3];

  TBranch* brTkrNumStrips = t1->GetBranch("TkrNumStrips");
  brTkrNumStrips->SetAddress(&m_nStrips);
  TBranch* brTkrNumTracks = t1->GetBranch("TkrNumTracks");
  brTkrNumTracks->SetAddress(&m_nTkrTracks);
  TBranch* brVtxXDir = t1->GetBranch("VtxXDir");
  brVtxXDir->SetAddress(&m_dir[0]);
  TBranch* brVtxYDir = t1->GetBranch("VtxYDir");
  brVtxYDir->SetAddress(&m_dir[1]);
  TBranch* brVtxZDir = t1->GetBranch("VtxZDir");
  brVtxZDir->SetAddress(&m_dir[2]);

  int nEvt = (int) t1->GetEntries();

  printf("nEvent = %i \n", nEvt);

  for(int i = 0; i != nEvt; ++i) {
    
    t1->GetEntry(i);
  
    int nMuonLayers = 0;

    for(int j = 0; j != 15; ++j) {
      if(m_nStrips[9][j][0] > 0 && m_nStrips[9][j][1] > 0) {
	++nMuonLayers;
      }
    } 

    tuple->Fill(nMuonLayers, m_nTkrTracks, m_dir[0], 
		m_dir[1], m_dir[2]);

  }

}


