#ifndef NtupleDef_Class
#define NtupleDef_Class

struct NtupleDef {

  enum {g_nTower=16, g_nTkrLayer=18, g_nView=2, g_nCalLayer=8, g_nCol=12, 
	g_nTot=2, g_nStripsPerLayer=1536, g_nFace=2, g_nTP=8, g_nCno=12};

  int m_runId;
  int m_eventId;
  int m_seqNo;

  // PDG encoding of the primary particle
  int m_parId;

  // energy of the primary particle, note this includes it's mass besides
  // it's kinetic energy
  float m_mcEnergy;

  // position of starting point
  float m_startPos[3];     //startPosX, startPosY, startPosZ

  // direction of primary particle
  float m_startDir[3];    //startDirX, startDirY, startDirZ

  // position of gamma convertion to electron, it is determined by requiring
  // process name to be 'conv'
  float m_convPos[3];    //convPosX, convPosY, convPosZ

  int m_nTkrDigis;    //nTkrDigis

  // no of hit strips per tower, per layer, per view
  int m_nStrips[g_nTower][g_nTkrLayer][g_nView];    //nStrips

  // every tot values 
  int m_tot[g_nTower][g_nTkrLayer][g_nView][g_nTot]; //tot

  // every corrected tot values using Hiro's linear correction 
  float m_totCorrLinear[g_nTower][g_nTkrLayer][g_nView][g_nTot]; //totCorr

  // every corrected tot values using Hiro's linear correction 
  float m_totCorrQuad[g_nTower][g_nTkrLayer][g_nView][g_nTot]; //totCorr

  // energy deposited in each tower, each layer and each view
  float m_depositEne[g_nTower][g_nTkrLayer][g_nView]; //depositEne

  // no of clusters in each layer, assuming 18 planes (not 19 trays)
  // note here difinition of the plane is different to difinition of the
  // layer. Plane 0 is at top !!!  We can rearrange this to use layer number
  // as index.

  int m_nTkrClusters[g_nTower][g_nTkrLayer][g_nView];   

  int m_nTkrTracks;              //nTkTracks
  int m_nTkrVertices;

  //position and direction stored in the first vertex
  float m_pos[3];                  //xPos, yPos, zPos
  float m_dir[3];                  //xDir, yDir, zDir
  float m_fitTotalEnergy;          //fitTotalEne
  int m_vtxTrks;               // no of tracks associated with the first vertex
 
  //fit parameters returned by the Kalman Filter for the first and second track
  //If there is no second track, it will be filled with -9999 
  int m_nFit[2];  // no of hitplanes(clusters) used in the fit
  float m_chi2[2];
  float m_chi2Smooth[2];
  float m_rms[2];
  float m_msAngle[2];
  float m_tkrEnergy[2];
  float m_tkr1EndPos[3];
  float m_tkr1EndDir[3];
  float m_tkr2EndPos[3];
  float m_tkr2EndDir[3];

  // Cal measured energy
  float m_calEnergy;

  // Cal deposited energy (MC)
  float m_mcCalEnergy;

  int m_trigger;

  // centroid of the CAL cluster. Currently there is no real clustering 
  // for CAL, just bind all hits into a cluster
  float m_calPos[3];   //calXPos, calYPos, calZPos

  // energy of e-/e+ produced by gamma conversion (pair production)
  float m_pairEne[2];

  // only valid for MC events
  double m_timeStamp;

  // openning angle of e+/e- pair by gamma conversion
  float m_convAngle;

  // maximal TOT value at the top hit layer at each tower
  float m_topTot[g_nTower];

  // maximal TOT value at the layer of the fit vertex point
  float m_convTot;

  // energy deposited in each crystal
  // default values are -9999
  float m_xtalEne[g_nTower][g_nCalLayer][g_nCol][g_nFace];

  // maximal deposited energy in a single crystal
  float m_maxCalEnergy;

  // number of crystals with energy above the threshold in every tower
  int m_nCrystalHit[g_nTower];

  // time information. This may change depending on future data format
  unsigned int m_ebfSecond, m_ebfNanoSecond;
  unsigned int m_upperTime, m_lowerTime;

  //diagnostic info
  //For array info, look at online doc: http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, page 104, figure 118
  unsigned m_tpCal[g_nTower][g_nTP];
  unsigned m_tpTkr[g_nTower][g_nTP];

  // event summary word
  unsigned m_summaryWord;

  // GEM information:
  unsigned m_gemConditionsWord;

  int m_gemTkrVector[g_nTower];
  int m_gemRoiVector[g_nTower];
  int m_gemCalLeVector[g_nTower];
  int m_gemCalHeVector[g_nTower];
  int m_gemCnoVector[g_nCno];

  unsigned m_gemLiveTime;
  unsigned m_gemTriggerTime;
  unsigned m_gemDeltaEventTime;
  unsigned m_gemOnePpsSeconds;
  unsigned m_gemOnePpsTime;
  unsigned m_gemPrescaled;
  unsigned m_gemDiscarded;
  unsigned m_gemSent;

  unsigned m_gemAcdTilesXzp;
  unsigned m_gemAcdTilesXzm;
  unsigned m_gemAcdTilesYzp;
  unsigned m_gemAcdTilesYzm;
  unsigned m_gemAcdTilesXy;
  unsigned m_gemAcdTilesRbn;
  unsigned m_gemAcdTilesNa;

  // Event sizes:
  unsigned m_temLength[g_nTower];
  unsigned m_gemLength;
  unsigned m_oswLength;
  unsigned m_aemLength;
  unsigned m_errLength;
  unsigned m_diagLength;

  // Event quality/flags:
  unsigned m_eventSequence;
  unsigned m_eventFlags;
  int m_goodEvent;

  // decoded trigger primitive for the tracker
  // e.g.: m_tkrReq[0][3][0][0]=1 means tower 0, lower half of layer X3 sends the trigger request
  // e.g.: m_tkrReq[0][3][1][1]=1 means tower 0, upper half of layer Y3 sends the trigger request
  // layer 0 is at the bottom
  unsigned m_tkrReq[g_nTower][g_nTkrLayer][g_nView][2];

  // decoded trigger primitive for the calorimeter
  // e.g.: m_calReq[0][3][0] contains 16 bit diagnostic data for tower 0, layer 3, negative end 
  // e.g.: m_calReq[0][3][1] contains 16 bit diagnostic data for tower 0, layer 3, positive end 
  // layer 0 is at the top (different to the tracker)
  unsigned m_calReq[g_nTower][g_nCalLayer][g_nFace];

  static const char* gRootNtupleDefStr;

  NtupleDef();

  void reset();

};

#endif
