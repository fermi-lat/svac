#ifndef NtupleDef_Class
#define NtupleDef_Class

#include "GeoConstants.h"

struct NtupleDef {

  int m_runId;
  int m_eventId;
  int m_seqNo;

  // Event size in bytes:
  int m_eventSize;

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

  // TOT values 
  int m_tkrToTRaw[g_nTower][g_nTkrLayer][g_nView][g_nTot]; 
  float m_tkrToTMips[g_nTower][g_nTkrLayer][g_nView][g_nTot]; 

  // energy deposited in each tower, each layer and each view
  float m_depositEne[g_nTower][g_nTkrLayer][g_nView]; //depositEne

  // no of clusters in each layer, assuming 18 biLayers (not 19 trays)
  // biLayer 0 is at the bottom
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

  float m_tkr1Pos[3];
  float m_tkr2Pos[3];
  float m_tkr1Dir[3];
  float m_tkr2Dir[3];



  // ACD Digi information:
  float m_acdMCEnergy[g_nAcdTile];
  int m_acdPha[g_nAcdTile][2];
  int m_acdHitMap[g_nAcdTile][2];
  int m_acdRange[g_nAcdTile][2];
  int m_acdOddParityError[g_nAcdTile][2];
  int m_acdHeaderParityError[g_nAcdTile][2];
  int m_acdLowDisc[g_nAcdTile][2];
  int m_acdTileNumber[g_nAcdTile];
  int m_acdNumDigis;
  int m_acd10Ids[10];

  // ACD NA:
  int m_acdNaPha[g_nAcdNaTile][2];
  int m_acdNaHitMap[g_nAcdNaTile][2];
  int m_acdNaRange[g_nAcdNaTile][2];
  int m_acdNaOddParityError[g_nAcdNaTile][2];
  int m_acdNaHeaderParityError[g_nAcdNaTile][2];
  int m_acdNaLowDisc[g_nAcdNaTile][2];

  // ACD Recon information:
  float m_acdEnergy;
  float m_acdGammaDoca;
  float m_acdActiveDist;
  int   m_acdTileCount;

  float m_acdRibbonActiveDist;
  float m_acdRibbonMCEnergy;
  int m_acdRibbonCount;
  int m_acdMaxActiveDistId;
  int m_acdRibbonActiveDistId;
  float m_acdCornerDoca;


  // ACD-TKR intersection information:
  int m_acdNumTkrIntersection;
  int m_acdTkrIntersectionTileId[20];
  int m_acdTkrIntersectionTkrIndex[20];
  float m_acdTkrIntersectionGlobalX[20];
  float m_acdTkrIntersectionGlobalY[20];
  float m_acdTkrIntersectionGlobalZ[20];
  float m_acdTkrIntersectionLocalX[20];
  float m_acdTkrIntersectionLocalY[20];
  float m_acdTkrIntersectionLocalXXCov[20];
  float m_acdTkrIntersectionLocalYYCov[20];
  float m_acdTkrIntersectionLocalXYCov[20];
  float m_acdTkrIntersectionArcLengthToIntersection[20];
  float m_acdTkrIntersectionPathLengthInTile[20];
  int m_acdTkrIntersectionTileHit[20];

  // ACD MIPs:
  float m_acdMips[604][2];

  int m_acdMipsPha[604][2];
  int m_acdMipsFlag[604][2];


  float m_acdMipsMax;
  int   m_acdMipsMaxTileID;
  int   m_acdMipsMaxPmt;
  float m_acdMipsSum;


  // Tkr Point:
  float m_acdTkrPointX[2];
  float m_acdTkrPointY[2];
  float m_acdTkrPointZ[2];
  int m_acdTkrPointFace[2];

  // ACD Gap POCA:
  int m_acdGapPocaNbrTrack1;
  int m_acdGapPocaNbrTrack2;

  int m_acdGapPocaTrackID[2][4];
  int m_acdGapPocaTileID[2][4];
  float m_acdGapPocaDoca[2][4];
  int m_acdGapPocaGapIndex[2][2];
  int m_acdGapPocaGapType[2][2];

  // ACD POCA:
  float m_acdPocaDoca[2][2];
  float m_acdPocaDocaErr[2][2];
  float m_acdPocaDocaRegion[2][2];
  float m_acdPocaX[2][2];
  float m_acdPocaY[2][2];
  float m_acdPocaZ[2][2];
  float m_acdPocaDirX[2][2];
  float m_acdPocaDirY[2][2];
  float m_acdPocaDirZ[2][2];
  int   m_acdPocaTileID[2][2];
  int   m_acdPocaTrackID[2][2];
  int   m_acdPocaNbrTrack1;
  int   m_acdPocaNbrTrack2;

  // Cal measured energy
  float m_calEnergy;

  // Cal deposited energy (MC)
  float m_mcCalEnergy;

  unsigned int m_trigger;

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
  float m_topToT[g_nTower];

  // maximal TOT value at the layer of the fit vertex point
  float m_convToT;

  // energy deposited in each crystal
  // default values are -9999
  float m_xtalEne[g_nTower][g_nCalLayer][g_nCol];

  // maximal deposited energy in a single crystal
  float m_maxCalEnergy;

  // number of crystals with energy above the threshold in every tower
  int m_nCrystalHit[g_nTower];

  //                                                                                                                                                                                                           
  // Context information:                                                                                                                                                                                      
  //                                                                                                                                                                                                           
  int m_contextRunInfoPlatform;
  int m_contextRunInfoDataOrigin;
  unsigned int m_contextRunInfoID;
  unsigned int m_contextRunInfoStartTime;

  unsigned int m_contextDataGramInfoModeChanges;
  unsigned int m_contextDataGramInfoDatagrams;
  int m_contextDataGramInfoOpenAction;
  int m_contextDataGramInfoOpenReason;
  int m_contextDataGramInfoCrate;
  int m_contextDataGramInfoMode;
  int m_contextDataGramInfoCloseAction;
  int m_contextDataGramInfoCloseReason;

  unsigned long long m_contextGemScalersElapsed;
  unsigned long long m_contextGemScalersLivetime;
  unsigned long long m_contextGemScalersPrescaled;
  unsigned long long m_contextGemScalersDiscarded;
  unsigned long long m_contextGemScalersSequence;
  unsigned long long m_contextGemScalersDeadzone;

  unsigned int m_contextLsfTimeTimeToneCurrentIncomplete;
  unsigned int m_contextLsfTimeTimeToneCurrentTimeSecs;
  unsigned int m_contextLsfTimeTimeToneCurrentFlywheeling;
  int m_contextLsfTimeTimeToneCurrentFlagsValid;
  int m_contextLsfTimeTimeToneCurrentIsSourceGps;
  int m_contextLsfTimeTimeToneCurrentMissingCpuPps;
  int m_contextLsfTimeTimeToneCurrentMissingLatPps;
  int m_contextLsfTimeTimeToneCurrentMissingTimeTone;
  int m_contextLsfTimeTimeToneCurrentEarlyEvent;
  unsigned int m_contextLsfTimeTimeToneCurrentGemTimeHacks;
  unsigned int m_contextLsfTimeTimeToneCurrentGemTimeTicks;

  unsigned int m_contextLsfTimeTimeTonePreviousIncomplete;
  unsigned int m_contextLsfTimeTimeTonePreviousTimeSecs;
  unsigned int m_contextLsfTimeTimeTonePreviousFlywheeling;
  int m_contextLsfTimeTimeTonePreviousFlagsValid;
  int m_contextLsfTimeTimeTonePreviousIsSourceGps;
  int m_contextLsfTimeTimeTonePreviousMissingCpuPps;
  int m_contextLsfTimeTimeTonePreviousMissingLatPps;
  int m_contextLsfTimeTimeTonePreviousMissingTimeTone;
  int m_contextLsfTimeTimeTonePreviousEarlyEvent;
  unsigned int m_contextLsfTimeTimeTonePreviousGemTimeHacks;
  unsigned int m_contextLsfTimeTimeTonePreviousGemTimeTicks;
  unsigned int m_contextLsfTimeTimeToneGemTimeHacks;
  unsigned int m_contextLsfTimeTimeToneGemTimeTicks;
  unsigned int m_contextLsfTimeTimeTicks;

  unsigned int m_contextLsfTimeTimeHackHacks;
  unsigned int m_contextLsfTimeTimeHackTicks;

  int m_contextRunType;


  // OBF:
  int m_obfPassedGAMMA;
  int m_obfPassedMIP;
  int m_obfPassedHIP;
  int m_obfPassedDGN; 

  //diagnostic info
  //For array info, look at online doc: http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, page 104, figure 118
  unsigned int m_tpCal[g_nTower][g_nCalLayer];
  unsigned int m_tpTkr[g_nTower][g_nGTCC];

  // event summary word
  unsigned int m_summaryWord;

  // Trigger engines:
  int m_trgEngineGlt;
  int m_trgEngineGem;

  // GEM information:
  int m_gemConditionsWord;

  int m_gemTkrVector[g_nTower];
  int m_gemRoiVector[g_nTower];
  int m_gemCalLeVector[g_nTower];
  int m_gemCalHeVector[g_nTower];
  int m_gemCnoVector[g_nCno];

  unsigned int m_gemLiveTime;
  unsigned int m_gemTriggerTime;
  unsigned int m_gemDeltaEventTime;
  unsigned int m_gemOnePpsSeconds;
  unsigned int m_gemOnePpsTime;
  unsigned int m_gemPrescaled;
  unsigned int m_gemDiscarded;
  unsigned int m_gemCondArrivalTimeWord;
  unsigned int m_gemCondArrivalTimeExt;
  unsigned int m_gemCondArrivalTimeCno;
  unsigned int m_gemCondArrivalTimeCalLe;
  unsigned int m_gemCondArrivalTimeCalHe;
  unsigned int m_gemCondArrivalTimeTkr;
  unsigned int m_gemCondArrivalTimeRoi;
  unsigned int m_gemDeltaWindowOpenTime;  
  
  int m_gemDeadZone;

  unsigned int m_gemAcdTilesXzp;
  unsigned int m_gemAcdTilesXzm;
  unsigned int m_gemAcdTilesYzp;
  unsigned int m_gemAcdTilesYzm;
  unsigned int m_gemAcdTilesXy;
  unsigned int m_gemAcdTilesRbn;
  unsigned int m_gemAcdTilesNa;

  // Luis's three-in-arow trigger bits:
  unsigned int m_digiTriRowBits[g_nTower];
  unsigned int m_trgReqTriRowBits[g_nTower];

  // Event sizes:
  unsigned int m_temLength[g_nTower];
  unsigned int m_gemLength;
  unsigned int m_oswLength;
  unsigned int m_aemLength;
  unsigned int m_errLength[g_nTower];
  unsigned int m_diagLength[g_nTower];

  // Event quality:
  unsigned int m_eventFlags;

  // Error flags:
  int m_eventBadEventSequence;
  int m_eventBadTkrRecon;
  int m_eventPacketError;
  int m_eventTemError;
  int m_eventTrgParityError;
  int m_eventBadLdfStatus;
  int m_eventGtrcPhase;
  int m_eventGtfePhase;
  int m_eventGtccFifo;
  int m_eventGtccHdrParity;
  int m_eventGtccWcParity;
  int m_eventGtrcSummary;
  int m_eventGtccDataParity;
  int m_eventGtccTimeout;
  int m_eventGcccError;
  int m_eventGtccError;
  int m_eventPhaseError;
  int m_eventTimeoutError;

  int m_eventReadout4;
  int m_eventZeroSuppress;
  int m_eventMarker;
  int m_eventCalStrobe;
  int m_eventTag;
  int m_eventTACK;

  double m_eventMCLivetime;
 
  double m_cCSDStime;
  int    m_cCSDSapID;
  int    m_cCSDSscID;


  // decoded trigger primitive for the tracker
  // e.g.: m_tkrReq[0][3][0][0]=1 means tower 0, lower half of layer X3 sends the trigger request
  // e.g.: m_tkrReq[0][3][1][1]=1 means tower 0, upper half of layer Y3 sends the trigger request
  // layer 0 is at the bottom
  unsigned int m_tkrReq[g_nTower][g_nTkrLayer][g_nView][2];

  // decoded trigger request for the calorimeter
  // e.g.: m_calReq[0][3][0] = 1 means a trigger request for low energy trigger
  // was sent from crystals at tower 0, layer 3, negative end; =2 means a 
  // trigger request was sent to high energy trigger; =3 means a trigger 
  // request was sent to both high and low energy trigger
  // layer 0 is at the top (different to the tracker)
  unsigned int m_calReq[g_nTower][g_nCalLayer][g_nFace];

  // log accept info
  unsigned int m_calLogAccepts[g_nTower][g_nCalLayer][g_nFace];

  // xyz position measured in each crystal, default values are -9999
  float m_xtalPos[g_nTower][g_nCalLayer][g_nCol][3];

  // total no. of hits per tower
  unsigned int m_totalStripHits[g_nTower];

  // total no. of clusters per tower
  unsigned int m_totalClusters[g_nTower];

  static const char* gRootNtupleDefStr;

  NtupleDef();

  void reset();

};

#endif
