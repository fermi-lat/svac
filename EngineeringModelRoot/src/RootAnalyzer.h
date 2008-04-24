#ifndef RootAnalyzer_Class
#define RootAnalyzer_Class

#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "mcRootData/McEvent.h"
#include "reconRootData/ReconEvent.h"
#include "digiRootData/DigiEvent.h"
#include "idents/CalXtalId.h"
#include "NtupleDef.h"

class RootAnalyzer {
 public:

  RootAnalyzer(const char* raFileName, const char* histFileName);
  ~RootAnalyzer();

  void analyzeTrees(const char* mcFileName,
		    const char* digiFileName,
		    const char* reconFileName);

 private:

  void analyzeMcTree();

  void analyzeReconTree();

  void analyzeDigiTree();

  // fill diagnostic info (trigger primitive)
  void diagnostic();

  // extract tower number (from 0 to 16) layer number (from 0 to 17) and view 
  // number (X:0, Y:1) from id
  // return false if the volume identified by id is not a tracker si wafer
  // or tower or layer or view number fall outside the boundary.
  // Convertion is hardwired so it may not work if identifier in xml files
  // changed
  bool extractTowerLayerView(const VolumeIdentifier& id, int& iTower, 
			     int& iLayer, int& iView) const;

  // fill stripHits and map histogrammes
  void fillStripHits(const TkrDigi* tkrDigi);

  void fillOutputTree();

  // calculate a couple of tot values based on event topology
  void analyzeTot();

  // read in constants used in TOT correction
  void readTotCorrLinear(int layer, int view, const char* file);
  void readTotCorrQuad(int layer, int view, const char* file);

  // for real data, we need to do strip by strip correction, only works
  // for EM data. Using two functions provided b Hiro
  void correctTotDataLinear(const TkrDigi* tkrDigi);
  void correctTotDataQuad(const TkrDigi* tkrDigi);

  double quadTotFormula(int layer, int view, int strip, double tot);

  // determine boundary of tot0 and tot1, only valid for EM1
  int midStripId(int iLayer, GlastAxis::axis iView) const;

  // create branches for each ntuple variable
  void createBranches();

  TFile* m_outputFile;
  TTree* m_tree;
  TBranch* m_branch;
  NtupleDef m_ntuple;

  TFile* m_mcFile;
  TTree* m_mcTree;
  TBranch* m_mcBranch;
  McEvent* m_mcEvent;

  TFile* m_reconFile;
  TTree* m_reconTree;
  TBranch* m_reconBranch;
  ReconEvent* m_reconEvent;

  TFile* m_digiFile;
  TTree* m_digiTree;
  TBranch* m_digiBranch;
  DigiEvent* m_digiEvent;

  enum {g_nTower=16, g_nTkrLayer=18, g_nView=2, g_nCalLayer=8, g_nCol=12, 
	g_nTot=2, g_nStripsPerLayer=1536, g_nFace=2, g_nTP=8, g_nFEC=24, g_nCno=12};

  TFile* m_histFile;
  TH1F* m_stripHits[g_nTower][g_nTkrLayer][g_nView];
  TH2F* m_stripMap[g_nTower][g_nTkrLayer][g_nView];

  // tot correction constants created by Hiro, only valid for EM
  float m_totGain[g_nTkrLayer][g_nView][g_nStripsPerLayer];
  float m_totOffset[g_nTkrLayer][g_nView][g_nStripsPerLayer];
  float m_totP0[g_nTkrLayer][g_nView][g_nStripsPerLayer];
  float m_totP1[g_nTkrLayer][g_nView][g_nStripsPerLayer];
  float m_totP2[g_nTkrLayer][g_nView][g_nStripsPerLayer];
  float m_aveTotGain[g_nTkrLayer][g_nView];
  float m_aveTotOffset[g_nTkrLayer][g_nView];

  // number of events with no root when doing tot correction using quadratic formula
  int m_nTotNoRoot;

  // number of events with negative root when doing tot correction using quadratic formula
  int m_nTotNegRoot;

};

#endif
