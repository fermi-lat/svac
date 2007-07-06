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

  // every tot values 
  int m_tot[g_nTower][g_nTkrLayer][g_nView][g_nTot]; //tot

  // every corrected tot values using Hiro's linear correction 
  float m_totCorrLinear[g_nTower][g_nTkrLayer][g_nView][g_nTot]; //totCorr

  // every corrected tot values using Hiro's linear correction 
  float m_totCorrQuad[g_nTower][g_nTkrLayer][g_nView][g_nTot]; //totCorr

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

  // ACD:
  float m_acdMCEnergy[g_nAcdTile];
  int m_acdPha[g_nAcdTile][2];
  int m_acdHitMap[g_nAcdTile][2];
  int m_acdRange[g_nAcdTile][2];
  int m_acdOddParityError[g_nAcdTile][2];
  int m_acdHeaderParityError[g_nAcdTile][2];
  int m_acdLowDisc[g_nAcdTile][2];
  int m_acdHighDisc[g_nAcdTile][2];
  int m_acdTileNumber[g_nAcdTile];
  int m_acdNumDigis;
  int m_acd10Ids[10];

  float m_acdEnergy;
  float m_acdDoca;
  float m_acdGammaDoca;
  float m_acdActiveDist;
  int   m_acdMinDocaId;
  int   m_acdTileCount;

  float m_acdRibbonActiveDist;
  float m_acdRibbonMCEnergy;
  int m_acdRibbonCount;
  int m_acdMaxActiveDistId;
  int m_acdRibbonActiveDistId;

  int m_acdNumTkrIntersection;
  int m_acdTkrIntersectionTileId[10];
  int m_acdTkrIntersectionTkrIndex[10];
  float m_acdTkrIntersectionGlobalX[10];
  float m_acdTkrIntersectionGlobalY[10];
  float m_acdTkrIntersectionGlobalZ[10];
  float m_acdTkrIntersectionLocalX[10];
  float m_acdTkrIntersectionLocalY[10];
  float m_acdTkrIntersectionLocalXXCov[10];
  float m_acdTkrIntersectionLocalYYCov[10];
  float m_acdTkrIntersectionLocalXYCov[10];
  float m_acdTkrIntersectionArcLengthToIntersection[10];
  float m_acdTkrIntersectionPathLengthInTile[10];
  int m_acdTkrIntersectionTileHit[10];


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
  double m_timeSeconds;
  double m_triggerTicks;


  //diagnostic info
  //For array info, look at online doc: http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, page 104, figure 118
  unsigned int m_tpCal[g_nTower][g_nCalLayer];
  unsigned int m_tpTkr[g_nTower][g_nGTCC];

  // event summary word
  unsigned int m_summaryWord;

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
