#ifndef TkrHits_Class
#define TkrHits_Class

#include "facilities/Util.h"

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

#include "TROOT.h"
#include "TGraphErrors.h"
#include "TChain.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TF1.h"
#include "TProfile.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphErrors.h"
#include "TNtuple.h"
#include "digiRootData/DigiEvent.h"
#include "reconRootData/ReconEvent.h"

#include "GeoConstants.h"

static const float stripPitch = 0.228; // strip pitch

static const int g_nLayer = 18;
static const int g_nUniPlane = g_nLayer*g_nView;

static const int g_nFecd = 24;
static const int g_nStrip = 1536;
//static const int g_nTower = 16;

// group of strips so that each group has enough statistics
static const int g_nDiv = 24; //used to be 64;takuya  
  
static const int g_nWafer = 4, g_nBad=7, g_nTime=5, g_nMerge=4;

const int nTotHistBin = 200;

const float ladderGap = 2.148;
const float posZ[g_nView][g_nLayer] = { 
  {44.765, 74.335, 108.965, 139.538, 175.165, 205.738, 241.365,  271.14, 305.965, 335.74, 370.565, 400.34, 435.165, 464.94, 499.765, 529.54, 564.365, 594.14},
  {42.315, 76.865, 106.435, 142.065, 172.638, 208.265, 238.838, 273.665, 303.44, 338.265, 368.04, 402.865, 432.64, 467.465, 497.24, 532.065, 561.84, 596.665} };

//
// ****** class layerId *****
//
class layerId{
 public:
      layerId(){;};
      layerId( int, int, int twr=0 );
      layerId( int, std::string, int twr=0 );
      layerId( int );
      ~layerId(){;};
      
      void setLayer( int, int, int twr=0 );
      void setTray( int, std::string, int twr=0 );
      void setUniPlane( int, int twr=0 );
      void setTower( int tw ){ tower = tw; };
      
      void trayToUniPlane();
      void trayToLayer();
      void layerToTray();
      inline void layerToUniPlane(){ layerToTray(); trayToUniPlane(); };
      void uniPlaneToTray();
      inline void uniPlaneToLayer(){ uniPlaneToTray(); trayToLayer(); };
      
      int tower;
      int layer;
      int view;
      int uniPlane;
      int tray;
      std::string which;
      
};

//
// cluster class
//
class Cluster{
 public:
  Cluster( int strip, int TOT=0)
  {
    firstStrip = strip;
    lastStrip = strip;
    tower = -1;
    uniPlane = -1;
    tot = TOT;
    correctedTot = -100.0; 
  }
  ~Cluster(){;};
  bool addStrip( int );

 protected:
  int tower;
  int uniPlane;
  int firstStrip; // first strip number
  int lastStrip; // last strip number
  int tot;
  float correctedTot;
  TVector3 pos; // position

 public:
  inline void setId( int tw, int unp ){ tower = tw; uniPlane = unp; };
  inline int getTowerId(){ return tower; };
  inline int getUniPlane(){ return uniPlane; };
  inline int getFirstStrip(){ return firstStrip; };
  inline int getLastStrip(){ return lastStrip; };
  inline int getSize(){ return lastStrip-firstStrip+1; };
  inline void setTot( int val ){ tot = val; };
  inline int getRawToT(){ return tot; };
  inline void setCorrectedTot( float val ){ correctedTot = val; };
  inline float getCorrectedTot(){ return correctedTot; };
  inline TVector3 getPosition(){ return pos; };
  inline void setXYZ( float x, float y, float z ){ pos.SetXYZ( x, y, z ); };
};

//
// bad strips variables
//
struct badStripVar{
  int eHits[g_nStrip];
  int tHits[g_nStrip];
  int lHits[g_nStrip];
  int nHits[g_nStrip][g_nWafer][g_nTime]; 
  std::vector<int> badStrips[g_nBad];
  std::vector<int> knownBadStrips[g_nBad];
};

//
// tot calibration variable
//
struct totCalibVar{
  float totQuadra[g_nStrip];
  float totGain[g_nStrip];
  float totOffset[g_nStrip];
  float chargeScale[g_nDiv];
  int chargeDist[g_nDiv][nTotHistBin];
};

//
//
// tower variable class
//
class towerVar{
 public:
  towerVar( int twr, bool badStrips);
  ~towerVar(){;};
  void saveHists( bool );
  void readHists( TFile*, UInt_t, UInt_t );

  int towerId;
  float center[g_nView];
  std::string hwserial, runid;

  // clusters
  std::vector<Cluster> digiClusters[g_nUniPlane];
  const TkrCluster* reconClusters[g_nUniPlane];

  // do not use histogram since it will slow down significantly.
  // these will be converted to histograms later in saveHits method.
  int rHits[g_nUniPlane][g_nStrip];
  int dHits[g_nUniPlane][g_nStrip];
  std::vector<badStripVar> bsVar;
  std::vector<totCalibVar> tcVar;
};

//
// ***** class TkrHits *****
//
class TkrHits {
 public:
  TkrHits( bool initHistsFlag=true );
  //  TkrHits( const std::string, const std::string );
  ~TkrHits(){};
  
  void setOutputFile( TFile* outputFile ) {m_rootFile=outputFile;}  
  void analyzeEvent();
  
  void setNevents(int nEvent) {m_nEvents = nEvent;}

  void setEventPtrs(DigiEvent* digiEvent, ReconEvent* reconEvent)
  {
    m_digiEvent=digiEvent;
    m_reconEvent=reconEvent;
  }

  void saveAllHist( bool saveTimeOcc=false );

 protected:

  void initOccHists();
  void saveOccHists();

  void initCommonHists();
  void setTowerInfo();
  
  bool passCut();
  
  void getDigiClusters();
  void getReconClusters();
  void selectGoodClusters();
  layerId getLayerId( const TkrCluster* );
  layerId getLayerId( Cluster* );
  bool closeToTrack( const TkrCluster*, TkrCluster*[g_nTower][g_nUniPlane] );
  float getTrackRMS();
  Double_t leastSquareLinearFit( std::vector<Double_t> &vy, 
			     std::vector<Double_t> &vx, 
			     Double_t &y0, Double_t &dydx );
  
  TH1F *m_nTrackDist, *m_maxHitDist, *m_trkRMS, *m_numClsDist, *m_dirzDist, 
    *m_armsDist, *m_brmsDist[g_nLayer/3];
  
  TH1F *m_fracErrDist, *m_chisqDist, *m_fracBatTot, *m_chist[5];
  TH1F *m_chargeScale, *m_entries, *m_langauWidth, *m_langauGSigma;
  TProfile *m_dirProfile;

  int m_nEvents;

  ReconEvent* m_reconEvent;
  DigiEvent* m_digiEvent;
  TFile* m_rootFile; 
 
  // reconstructed track and direction
  TkrTrack* m_track;
  TVector3 m_pos, m_dir;
  
  std::vector<Cluster*> m_clusters;

  int m_lastRC0Strip[g_nTower][g_nLayer][g_nView];
  
  //file stream for log output
  std::ofstream m_log;
  
  // tower variables
  std::vector<int> m_towerList;
  int m_towerPtr[g_nTower];
  std::vector<towerVar> m_towerVar;
  std::vector<int> m_trackTowerList;
  
  //xml related parameters  
  std::string m_version, m_tag;

  // bad strips analysis related stuff
  void fillOccupancy( int );
  void calculateEfficiency();
  
  bool m_badStrips, m_towerInfoDefined; 
  TH1F* m_aPos[g_nWafer+1];
  TH1F *m_occDist, *m_poissonDist, *m_lrec, *m_ldigi, *m_lcls, *m_htwr, *m_locc, *m_leff, *m_ltrk, *m_dist;

  float m_maxDirZ, m_maxTrackRMS, m_maxDelta;
  float m_trackRMS;

};

// Gaussian convolved Landau function
Double_t langaufun(Double_t *x, Double_t *par); 
// Two Gaussian convolved Landau function
Double_t langau2fun(Double_t *x, Double_t *par); 
#endif
