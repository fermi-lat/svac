#include <map>
#include <algorithm>
#include <utility>
#include <iterator>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <string>
#include "ElecToGeo.h"
#include "RootAnalyzer.h"
#include "TROOT.h"
#include "ToString.h"
#include "enums/TriggerBits.h"
#include "timestamps.h"

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

RootAnalyzer::RootAnalyzer() : m_outputFile(0), m_tree(0), m_branch(0),
			       m_mcChain(0), m_mcBranch(0), m_mcEvent(0), 
			       m_reconChain(0), m_reconBranch(0), 
			       m_reconEvent(0), m_digiChain(0),m_digiBranch(0),
			       m_digiEvent(0), m_histFile(0)
{
  // make sure unsigned int hold 32 bit data 
  assert(sizeof(unsigned int) == 4);

    // initialize ROOT if not already done
  if(gROOT == 0) {
    static TROOT gRoot("RootAnalyzer", "RootAnalyzer");
  }

  m_mcChain = new TChain("Mc");
  m_digiChain = new TChain("Digi");
  m_reconChain = new TChain("Recon");

  m_tkrCalib = new TkrHits( true );

  //m_tkrNoiseOcc = new TkrNoiseOcc();

  // open output ra root file
  // No need to delete m_outputFile as ROOT will do the garbage collection

}

RootAnalyzer::~RootAnalyzer()
{
  // since root will do the garbage collection automatically for objects such
  // as TTree and TH1, we don't want to deallocate them once more
  delete m_tkrCalib;
  //delete m_tkrNoiseOcc;
}

void RootAnalyzer::produceOutputFile()
{
  //  TDirectory* saveDir = gDirectory;

  if(m_outputFile) {
    m_outputFile->cd("TkrCalib");
    m_tkrCalib->saveAllHist();
    //m_tkrNoiseOcc->writeAnaToHis(m_tkrNoiseOcc_dir);
    m_outputFile->cd();
    m_outputFile->Write(0, TObject::kOverwrite);
    m_outputFile->Close();
  }

  if(m_histFile) {
    m_histFile->cd();
    m_histFile->Write(0, TObject::kOverwrite);
    m_histFile->Close();
  }

  //  saveDir->cd();
}


void RootAnalyzer::analyzeMcTree()
{
    m_ntuple.m_runId = (int) m_mcEvent->getRunId();

    m_ntuple.m_seqNo = (int) m_mcEvent->getSequence();

    // get info about primary particle
    McParticle* particle = m_mcEvent->getMcParticle(0);
    if(particle) {
      m_ntuple.m_parId = particle->getParticleId();
      m_ntuple.m_mcEnergy = particle->getInitialFourMomentum().E();
      const TVector3& pos = particle->getInitialPosition();
      m_ntuple.m_startPos[0] = (float) pos.X();
      m_ntuple.m_startPos[1] = (float) pos.Y();
      m_ntuple.m_startPos[2] = (float) pos.Z();
      const TLorentzVector& lor = particle->getInitialFourMomentum();
      float norm = sqrt(lor(0)*lor(0) + lor(1)*lor(1) + lor(2)*lor(2));
      m_ntuple.m_startDir[0] = lor(0)/norm;
      m_ntuple.m_startDir[1] = lor(1)/norm;
      m_ntuple.m_startDir[2] = lor(2)/norm;
    }

    // get gamma conversion (pair production) point
    int nPar = m_mcEvent->getMcParticleCount();

    // first particle produced by pair production, used in filling m_pairEne
    int iPair = 0;

    double x0=-9999.0, y0=-9999.0, z0=-9999.0, x1=-9999.0, y1=-999.0, z1=-9999.0;

    for(int iPar = 0; iPar != nPar; ++iPar) {
      McParticle* par = m_mcEvent->getMcParticle(iPar);
      if(par && par->getProcess() == "conv" && iPair == 0) {
	  const TVector3& pos = par->getInitialPosition();
	  m_ntuple.m_convPos[0] = (float) pos.X();
	  m_ntuple.m_convPos[1] = (float) pos.Y();
	  m_ntuple.m_convPos[2] = (float) pos.Z();
	  m_ntuple.m_pairEne[iPair++] = par->getInitialFourMomentum().Energy();
	  x0 = par->getInitialFourMomentum().Px();
	  y0 = par->getInitialFourMomentum().Py();
	  z0 = par->getInitialFourMomentum().Pz();
	  continue;
      }
      if(par && par->getProcess() == "conv" && iPair == 1) { 
	//second particle produced by pair production
	  m_ntuple.m_pairEne[iPair++] = par->getInitialFourMomentum().Energy();
	  x1 = par->getInitialFourMomentum().Px();
	  y1 = par->getInitialFourMomentum().Py();
	  z1 = par->getInitialFourMomentum().Pz();
      }
    }

    if(iPair == 2) { // there is a conversion
      double a = sqrt(x0*x0 + y0*y0 + z0*z0);
      double b = sqrt(x1*x1 + y1*y1 + z1*z1);
      m_ntuple.m_convAngle = acos((x0*x1 + y0*y1 + z0*z1) / (a * b) );
    }

    // fill in energy deposited in each TKR layer
    int nPosHit = m_mcEvent->getMcPositionHitCount();
    for(int iPosHit = 0; iPosHit != nPosHit; ++iPosHit) {
      McPositionHit* posHit = m_mcEvent->getMcPositionHit(iPosHit);
      if(posHit) {
	VolumeIdentifier id = posHit->getVolumeId();
	int iTower, iLayer, iView;
	if( extractTowerLayerView(id, iTower, iLayer, iView) ) {
	    m_ntuple.m_depositEne[iTower][iLayer][iView] += 
	      posHit->getDepositedEnergy();
	}
      }
    } 

    // fill in energy deposited in CAL
    int nIntHit = m_mcEvent->getIntegratingHitCount();
    m_ntuple.m_mcCalEnergy = 0.;
    for(int iIntHit = 0; iIntHit != nIntHit; ++iIntHit) {
      McIntegratingHit* intHit = m_mcEvent->getMcIntegratingHit(iIntHit);
      if(intHit) {
	VolumeIdentifier id = intHit->getVolumeId();
	// the 4th id must be 0 if the volume is a CAL crystal
	if(id[3] == 0) {
	  m_ntuple.m_mcCalEnergy += intHit->getTotalEnergy();
	}
      }
    }
}
 

void RootAnalyzer::analyzeReconTree()
{
  TkrRecon* tkrRecon = m_reconEvent->getTkrRecon();
 
  if (tkrRecon == 0) return;

  TObjArray* siClusterCol = tkrRecon->getClusterCol();
  if(siClusterCol) {
    int nClusters = siClusterCol->GetLast()+1;
    // fill in no of clusters in each layer
    for(int i = 0; i != nClusters; ++i) {
      TkrCluster* cluster = dynamic_cast<TkrCluster*>(siClusterCol->At(i));
      if(cluster) {

	TowerId tId(cluster->getTkrId().getTowerX(), cluster->getTkrId().getTowerY());
	int iTower = tId.id();
	int iLayer = cluster->getLayer();
	int iView = cluster->getTkrId().getView();

	assert(iLayer >= 0 && iLayer <= g_nTkrLayer - 1);

	++m_ntuple.m_nTkrClusters[iTower][iLayer][iView];
	++m_ntuple.m_totalClusters[iTower];

      }
    }
  }

  m_ntuple.m_nTkrTracks = tkrRecon->getTrackCol()->GetLast()+1;
  m_ntuple.m_nTkrVertices = tkrRecon->getVertexCol()->GetLast()+1;

  // fill in info stored in the very first vertex
  TObjArray* vertices = tkrRecon->getVertexCol();
  if(m_ntuple.m_nTkrVertices >= 1) {
    TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
    if(tkrVertex) {
      const TVector3& pos = tkrVertex->getPosition();
      const TVector3& dir = tkrVertex->getDirection();
      m_ntuple.m_pos[0] = pos.X();
      m_ntuple.m_pos[1] = pos.Y();
      m_ntuple.m_pos[2] = pos.Z();
      m_ntuple.m_dir[0] = dir.X();
      m_ntuple.m_dir[1] = dir.Y();
      m_ntuple.m_dir[2] = dir.Z();
      m_ntuple.m_fitTotalEnergy = tkrVertex->getEnergy();
      m_ntuple.m_vtxTrks = tkrVertex->getNumTracks();
    }
  }

  // fill in info stored in the very first and second track
  TObjArray* tracks = tkrRecon->getTrackCol();

  for(int i = 0; i != 2; ++i) {
    TkrTrack* tkrTrack = dynamic_cast<TkrTrack*>(tracks->At(i));
    if(tkrTrack) {
      m_ntuple.m_nFit[i] += (int) tkrTrack->getNumFitHits();
      m_ntuple.m_chi2[i] = tkrTrack->getChiSquareFilter();
      m_ntuple.m_chi2Smooth[i] = tkrTrack->getChiSquareSmooth();
      m_ntuple.m_rms[i] = tkrTrack->getScatter();
      m_ntuple.m_msAngle[i] = tkrTrack->getKalThetaMS();
      m_ntuple.m_tkrEnergy[i] = tkrTrack->getKalEnergy();


      // End-of-track parameters:
      TkrTrackHit* hit = (TkrTrackHit*) tkrTrack->Last();
      TVector3 endPos = hit->getPoint(TkrTrackHit::SMOOTHED);
      TVector3 endSlopeTmp = hit->getDirection(TkrTrackHit::SMOOTHED);
      TVector3 endSlope = endSlopeTmp.Unit();

      if (i == 0) {
        m_ntuple.m_tkr1EndPos[0] = endPos.x();
        m_ntuple.m_tkr1EndPos[1] = endPos.y();
        m_ntuple.m_tkr1EndPos[2] = endPos.z();
	// Need -1 here .....
        m_ntuple.m_tkr1EndDir[0] = -1.0*endSlope.x();
        m_ntuple.m_tkr1EndDir[1] = -1.0*endSlope.y();
        m_ntuple.m_tkr1EndDir[2] = -1.0*endSlope.z();
      } else {
        m_ntuple.m_tkr2EndPos[0] = endPos.x();
        m_ntuple.m_tkr2EndPos[1] = endPos.y();
        m_ntuple.m_tkr2EndPos[2] = endPos.z();
	// Need -1 here .....
        m_ntuple.m_tkr2EndDir[0] = -1.0*endSlope.x();
        m_ntuple.m_tkr2EndDir[1] = -1.0*endSlope.y();
        m_ntuple.m_tkr2EndDir[2] = -1.0*endSlope.z();
      }
    }
  }

  // calculate energy measured in calorimeter
  CalRecon* calRecon = m_reconEvent->getCalRecon();
  if(calRecon) {
    TObjArray* calClusterCol = calRecon->getCalClusterCol();
    if(calClusterCol) {
      // currently there is just one cluster in CAL
      CalCluster* calCluster = dynamic_cast<CalCluster*>(calClusterCol->At(0));
      if (calCluster) {
        m_ntuple.m_calPos[0] = calCluster->getParams().getCentroid().x();
        m_ntuple.m_calPos[1] = calCluster->getParams().getCentroid().y();
        m_ntuple.m_calPos[2] = calCluster->getParams().getCentroid().z();
        m_ntuple.m_calEnergy = calCluster->getParams().getEnergy();
      }
    }

    TObjArray* calXtalRecCol = calRecon->getCalXtalRecCol();

    if(calXtalRecCol) {
      int nCalRec = calXtalRecCol->GetLast() + 1;

      for(int i = 0; i != nCalRec; ++i) {
	CalXtalRecData* calData = 
	  dynamic_cast<CalXtalRecData*>(calXtalRecCol->At(i));
	if(calData) {

	  CalXtalId id = calData->getPackedId();
	  int iTower = id.getTower();
	  int iLayer = id.getLayer();
	  int iCol = id.getColumn();

	  float ene = calData->getEnergy();
          
          float enePos = calData->getEnergy(0,CalXtalId::POS);

	  if(ene >= 0) ++(m_ntuple.m_nCrystalHit[iTower]);

	  // CAL layer end energies:
          m_ntuple.m_xtalEne[iTower][iLayer][iCol] = enePos;

	  if(ene > m_ntuple.m_maxCalEnergy) m_ntuple.m_maxCalEnergy = ene;

	  TVector3 pos =  calData->getPosition();
	  m_ntuple.m_xtalPos[iTower][iLayer][iCol][0] = pos.x();
	  m_ntuple.m_xtalPos[iTower][iLayer][iCol][1] = pos.y();
	  m_ntuple.m_xtalPos[iTower][iLayer][iCol][2] = pos.z();

	}
      }
    }

    TObjArray* calMipTrackCol = calRecon->getCalMipTrackCol();
    if (calMipTrackCol) {
      int nCalMip = calMipTrackCol->GetLast() + 1;
      m_ntuple.m_calMipNum = nCalMip;

      for (int i = 0; i< std::min(2,nCalMip); i++) {
        CalMipTrack* calMip = dynamic_cast<CalMipTrack*>(calMipTrackCol->At(i));
        if (calMip) {
          TVector3 pos =  calMip->getPoint();
          TVector3 dir =  calMip->getDir();

          if (i == 0) {
            m_ntuple.m_calMip1Pos[0] = pos.x();
            m_ntuple.m_calMip1Pos[1] = pos.y();
            m_ntuple.m_calMip1Pos[2] = pos.z();

            m_ntuple.m_calMip1Dir[0] = dir.x();
            m_ntuple.m_calMip1Dir[1] = dir.y();
            m_ntuple.m_calMip1Dir[2] = dir.z();

            m_ntuple.m_calMip1Chi2    = calMip->getChi2();
            m_ntuple.m_calMip1D2edge  = calMip->getD2Edge();
            m_ntuple.m_calMip1ArcLen  = calMip->getArcLen();
            m_ntuple.m_calMip1Ecor    = calMip->getEcor();
            m_ntuple.m_calMip1EcorRms = calMip->getEcorRms();
            m_ntuple.m_calMip1Erm     = calMip->getErm();
          }
          if (i == 1) {
            m_ntuple.m_calMip2Pos[0] = pos.x();
            m_ntuple.m_calMip2Pos[1] = pos.y();
            m_ntuple.m_calMip2Pos[2] = pos.z();

            m_ntuple.m_calMip2Dir[0] = dir.x();
            m_ntuple.m_calMip2Dir[1] = dir.y();
            m_ntuple.m_calMip2Dir[2] = dir.z();

            m_ntuple.m_calMip2Chi2    = calMip->getChi2();
            m_ntuple.m_calMip2D2edge  = calMip->getD2Edge();
            m_ntuple.m_calMip2ArcLen  = calMip->getArcLen();
            m_ntuple.m_calMip2Ecor    = calMip->getEcor();
            m_ntuple.m_calMip2EcorRms = calMip->getEcorRms();
            m_ntuple.m_calMip2Erm     = calMip->getErm();
          }
        }
      }
    }
  }  // calRecon


  //
  // ACD recon:
  //
  AcdRecon* acdRecon = m_reconEvent->getAcdRecon();

  //
  if (acdRecon) {

    // Temporary max variable:
    float tmpMax       = -9999.0;
    int   tmpMaxTileID = -9999;
    int   tmpMaxPmt    = -9999;
    
    float tmpSum = 0.0;

    UInt_t nAcdHit = acdRecon->nAcdHit();
    for ( UInt_t iAcdHit(0); iAcdHit < nAcdHit; iAcdHit++ ) {
      const AcdHit* acdHit = acdRecon->getAcdHit(iAcdHit);

      const AcdId& acdId = acdHit->getId();
      int acdID = acdId.getId();  

      // Get rid of the NA (they have ID=899):
      if (acdID < 604) {
        m_ntuple.m_acdMips[acdID][0] = acdHit->getMips(AcdHit::A);
        m_ntuple.m_acdMips[acdID][1] = acdHit->getMips(AcdHit::B);

        m_ntuple.m_acdMipsPha[acdID][0] = acdHit->getPha(AcdHit::A);
        m_ntuple.m_acdMipsPha[acdID][1] = acdHit->getPha(AcdHit::B);

        m_ntuple.m_acdMipsFlag[acdID][0] = acdHit->getFlags(AcdHit::A);
        m_ntuple.m_acdMipsFlag[acdID][1] = acdHit->getFlags(AcdHit::B);

        if ((acdHit->getMips(AcdHit::A)) > tmpMax) {
          tmpMax       = acdHit->getMips(AcdHit::A);
          tmpMaxTileID = acdID;
          tmpMaxPmt    = 0;
        }
        if ((acdHit->getMips(AcdHit::B)) > tmpMax) {
          tmpMax       = acdHit->getMips(AcdHit::B);
          tmpMaxTileID = acdID;
          tmpMaxPmt    = 1;
        }
        if ((acdHit->getMips(AcdHit::A))>0 && (acdHit->getMips(AcdHit::B))>0) {
          tmpSum = tmpSum + 0.5*((acdHit->getMips(AcdHit::A)) + (acdHit->getMips(AcdHit::B)));
        }
        if ((acdHit->getMips(AcdHit::A))<=0 && (acdHit->getMips(AcdHit::B))>0) {
          tmpSum = tmpSum + acdHit->getMips(AcdHit::B);
        }
        if ((acdHit->getMips(AcdHit::A))>0 && (acdHit->getMips(AcdHit::B))<=0) {
          tmpSum = tmpSum + acdHit->getMips(AcdHit::A);
        }
      }
      m_ntuple.m_acdMipsMax       = tmpMax;
      m_ntuple.m_acdMipsMaxTileID = tmpMaxTileID;
      m_ntuple.m_acdMipsMaxPmt    = tmpMaxPmt;
      m_ntuple.m_acdMipsSum       = tmpSum;
    }

    //
    // Tkr Point
    //
     UInt_t nAcdTkrPoint = acdRecon->nAcdTkrPoint();

    int nAcdTkrPointTrack1(0); 
    for ( UInt_t iAcdTkrPoint(0); iAcdTkrPoint < nAcdTkrPoint; iAcdTkrPoint++ ) {
      const AcdTkrPoint* acdTkrPoint = acdRecon->getAcdTkrPoint(iAcdTkrPoint);

      int trackPointIndex = nAcdTkrPointTrack1;;
      int acdTkrPointFace = acdTkrPoint->getFace();
      
      if (trackPointIndex == 0) {
        m_ntuple.m_acdTkrPointX[0] = acdTkrPoint->getPoint().x();
        m_ntuple.m_acdTkrPointY[0] = acdTkrPoint->getPoint().y();
        m_ntuple.m_acdTkrPointZ[0] = acdTkrPoint->getPoint().z();

        m_ntuple.m_acdTkrPointFace[0] = acdTkrPointFace;

      } else if (trackPointIndex == 1) {

        m_ntuple.m_acdTkrPointX[1] = acdTkrPoint->getPoint().x();
        m_ntuple.m_acdTkrPointY[1] = acdTkrPoint->getPoint().y();
        m_ntuple.m_acdTkrPointZ[1] = acdTkrPoint->getPoint().z();

        m_ntuple.m_acdTkrPointFace[1] = acdTkrPointFace;
      }
      nAcdTkrPointTrack1++;
    }



    //
    // Gap POCA
    //
     UInt_t nAcdGapPoca = acdRecon->nAcdTkrGapPoca();

    int nGapTrack1(0); int nGapTrack2(0);
    for ( UInt_t iAcdGapPoca(0); iAcdGapPoca < nAcdGapPoca; iAcdGapPoca++ ) {
      const AcdTkrGapPoca* acdGapPoca = acdRecon->getAcdTkrGapPoca(iAcdGapPoca);

      int trackGapIndex = acdGapPoca->getTrackIndex();

      const AcdGapId& acdGapId = acdGapPoca->getGapId();
      int acdGapID = acdGapId.asShort();

      if (trackGapIndex == 0 && nGapTrack1 < 4) {
        m_ntuple.m_acdGapPocaDoca[0][nGapTrack1]     = acdGapPoca->getDoca();
        m_ntuple.m_acdGapPocaTileID[0][nGapTrack1]   = acdGapPoca->getGapId().closestTile();
        m_ntuple.m_acdGapPocaGapIndex[0][nGapTrack1] = acdGapPoca->getGapId().gap();
        m_ntuple.m_acdGapPocaGapType[0][nGapTrack1]  = acdGapPoca->getGapId().gapType();
        m_ntuple.m_acdGapPocaTrackID[0][nGapTrack1]  = trackGapIndex; 

      } else if (trackGapIndex == 1 && nGapTrack2 < 4) {
        m_ntuple.m_acdGapPocaDoca[1][nGapTrack2]     = acdGapPoca->getDoca();
        m_ntuple.m_acdGapPocaTileID[1][nGapTrack2]   = acdGapPoca->getGapId().closestTile();
        m_ntuple.m_acdGapPocaGapIndex[1][nGapTrack2] = acdGapPoca->getGapId().gap();
        m_ntuple.m_acdGapPocaGapType[1][nGapTrack2]  = acdGapPoca->getGapId().gapType();
        m_ntuple.m_acdGapPocaTrackID[1][nGapTrack2]  = trackGapIndex; 
      }
      if (trackGapIndex == 0) {
        nGapTrack1++;
      }
      if (trackGapIndex == 1) {
        nGapTrack2++;
      }
    }
    m_ntuple.m_acdGapPocaNbrTrack1 = nGapTrack1;
    m_ntuple.m_acdGapPocaNbrTrack2 = nGapTrack2;
  




    UInt_t nAcdPoca = acdRecon->nAcdTkrHitPoca();

    int nTrack1(0); int nTrack2(0);
    for ( UInt_t iAcdPoca(0); iAcdPoca < nAcdPoca; iAcdPoca++ ) {
      const AcdTkrHitPoca* acdPoca = acdRecon->getAcdTkrHitPoca(iAcdPoca);

      int trackIndex = acdPoca->getTrackIndex();

      const AcdId& acdId = acdPoca->getId();
      int acdID = acdId.getId();
      
      if (trackIndex == 0 && nTrack1 < 2) {
        m_ntuple.m_acdPocaDoca[0][nTrack1]       = acdPoca->getDoca();
        m_ntuple.m_acdPocaDocaErr[0][nTrack1]    = acdPoca->getDocaErr();
        m_ntuple.m_acdPocaDocaRegion[0][nTrack1] = acdPoca->getRegion();
        m_ntuple.m_acdPocaX[0][nTrack1]          = acdPoca->getPoca().X(); 
        m_ntuple.m_acdPocaY[0][nTrack1]          = acdPoca->getPoca().Y(); 
        m_ntuple.m_acdPocaZ[0][nTrack1]          = acdPoca->getPoca().Z(); 
        m_ntuple.m_acdPocaDirX[0][nTrack1]       = acdPoca->getPocaVector().Px();
        m_ntuple.m_acdPocaDirY[0][nTrack1]       = acdPoca->getPocaVector().Py();
        m_ntuple.m_acdPocaDirZ[0][nTrack1]       = acdPoca->getPocaVector().Pz();
        m_ntuple.m_acdPocaTileID[0][nTrack1]     = acdID;
        m_ntuple.m_acdPocaTrackID[0][nTrack1]    = trackIndex; 
      } else if (trackIndex == 1 && nTrack2 < 2) {
        m_ntuple.m_acdPocaDoca[1][nTrack2]       = acdPoca->getDoca();
        m_ntuple.m_acdPocaDocaErr[1][nTrack2]    = acdPoca->getDocaErr();
        m_ntuple.m_acdPocaDocaRegion[1][nTrack2] = acdPoca->getRegion();
        m_ntuple.m_acdPocaX[1][nTrack2]          = acdPoca->getPoca().X(); 
        m_ntuple.m_acdPocaY[1][nTrack2]          = acdPoca->getPoca().Y(); 
        m_ntuple.m_acdPocaZ[1][nTrack2]          = acdPoca->getPoca().Z(); 
        m_ntuple.m_acdPocaDirX[1][nTrack2]       = acdPoca->getPocaVector().Px();
        m_ntuple.m_acdPocaDirY[1][nTrack2]       = acdPoca->getPocaVector().Py();
        m_ntuple.m_acdPocaDirZ[1][nTrack2]       = acdPoca->getPocaVector().Pz();
        m_ntuple.m_acdPocaTileID[1][nTrack2]     = acdID;
        m_ntuple.m_acdPocaTrackID[1][nTrack2]    = trackIndex; 
      }
      if (trackIndex == 0) {
        nTrack1++;
      } 
      if (trackIndex == 1) {
        nTrack2++;
      } 
    }
    m_ntuple.m_acdPocaNbrTrack1 = nTrack1;
    m_ntuple.m_acdPocaNbrTrack2 = nTrack2;
  }

  //
  if (acdRecon) {
    m_ntuple.m_acdEnergy     = acdRecon->getEnergy();
    m_ntuple.m_acdDoca       = acdRecon->getDoca();
    m_ntuple.m_acdTileCount  = acdRecon->getTileCount();
    m_ntuple.m_acdActiveDist = acdRecon->getActiveDist();
    m_ntuple.m_acdMinDocaId  = acdRecon->getMinDocaId().getId();

    m_ntuple.m_acdRibbonMCEnergy     = acdRecon->getRibbonEnergy();
    m_ntuple.m_acdRibbonCount        = acdRecon->getRibbonCount();
    m_ntuple.m_acdRibbonActiveDist   = acdRecon->getRibbonActiveDist();
    m_ntuple.m_acdMaxActiveDistId    = acdRecon->getMaxActDistId().getId();
    m_ntuple.m_acdRibbonActiveDistId = acdRecon->getRibbonActDistId().getId();
    m_ntuple.m_acdCornerDoca         = acdRecon->getCornerDoca();

    // Eric's ACD-TKR intersection stuff:
    m_ntuple.m_acdNumTkrIntersection = acdRecon->nAcdIntersections();

    for (int iAcdTkrIntSec = 0; iAcdTkrIntSec < m_ntuple.m_acdNumTkrIntersection; iAcdTkrIntSec++) {
      int nInter = acdRecon->nAcdIntersections();
      for ( int iInter(0); iInter < nInter; iInter++ ) {
        const AcdTkrIntersection* acdInterRoot = acdRecon->getAcdTkrIntersection(iInter);
        if (iInter < 20) {
          m_ntuple.m_acdTkrIntersectionTileId[iInter]                  = acdInterRoot->getTileId().getId();
          m_ntuple.m_acdTkrIntersectionTkrIndex[iInter]                = acdInterRoot->getTrackIndex();
          m_ntuple.m_acdTkrIntersectionGlobalX[iInter]                 = acdInterRoot->getGlobalPosition().x();
          m_ntuple.m_acdTkrIntersectionGlobalY[iInter]                 = acdInterRoot->getGlobalPosition().y();
          m_ntuple.m_acdTkrIntersectionGlobalZ[iInter]                 = acdInterRoot->getGlobalPosition().z();
          m_ntuple.m_acdTkrIntersectionLocalX[iInter]                  = acdInterRoot->getLocalX();
          m_ntuple.m_acdTkrIntersectionLocalY[iInter]                  = acdInterRoot->getLocalY();
          m_ntuple.m_acdTkrIntersectionLocalXXCov[iInter]              = acdInterRoot->getLocalXXCov();
          m_ntuple.m_acdTkrIntersectionLocalYYCov[iInter]              = acdInterRoot->getLocalYYCov();
          m_ntuple.m_acdTkrIntersectionLocalXYCov[iInter]              = acdInterRoot->getLocalXYCov();  
          m_ntuple.m_acdTkrIntersectionArcLengthToIntersection[iInter] = acdInterRoot->getArcLengthToIntersection();
          m_ntuple.m_acdTkrIntersectionPathLengthInTile[iInter]        = acdInterRoot->getPathLengthInTile();
          m_ntuple.m_acdTkrIntersectionTileHit[iInter]                 = acdInterRoot->tileHit();
	}
      }
    }
  }
}
  
void RootAnalyzer::analyzeDigiTree()
{
  m_ntuple.m_runId = m_digiEvent->getRunId();
  m_ntuple.m_eventId = m_digiEvent->getEventId();

  unsigned int word = m_digiEvent->getL1T().getTriggerWord();
  unsigned bitMask = 0;
  int ibit = enums::number_of_trigger_bits;
  while(ibit--) { bitMask |= 1<<ibit; }
  m_ntuple.m_trigger = word & bitMask;

  m_ntuple.m_timeStamp = m_digiEvent->getTimeStamp();

  m_ntuple.m_summaryWord = m_digiEvent->getEventSummaryData().summary();
  m_ntuple.m_eventSize   = m_digiEvent->getEventSummaryData().eventSizeInBytes();

  m_ntuple.m_eventMCLivetime = m_digiEvent->getLiveTime();

  //
  // OBF:
  //
  m_ntuple.m_obfPassedGamma = 0;
  m_ntuple.m_obfPassedMip   = 0;
  m_ntuple.m_obfPassedHFC   = 0;
  m_ntuple.m_obfPassedDFC   = 0;

  
  if (m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::GammaFilter) != 0) {
    if ((m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::GammaFilter)->getStatus32() & m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::GammaFilter)->getVetoBit()) == 0) {
      m_ntuple.m_obfPassedGamma = 1;
    }
  }
  if (m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::MipFilter) != 0) {
    if ((m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::MipFilter)->getStatus32() & m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::MipFilter)->getVetoBit()) == 0) {
      m_ntuple.m_obfPassedMip = 1;
    }
  }
  if (m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::HFCFilter) != 0) { 
    if ((m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::HFCFilter)->getStatus32() & m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::HFCFilter)->getVetoBit()) == 0) {
      m_ntuple.m_obfPassedHFC = 1;
    }
  }
  if (m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::DFCFilter) != 0) {
    if ((m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::DFCFilter)->getStatus32() & m_digiEvent->getObfFilterStatus().getFilterStatus(ObfFilterStatus::DFCFilter)->getVetoBit()) == 0) {
      m_ntuple.m_obfPassedDFC = 1;
    }
  }

  //
  // Context information:
  //
  m_ntuple.m_contextRunInfoPlatform = m_digiEvent->getMetaEvent().run().platform();
  m_ntuple.m_contextRunInfoDataOrigin = m_digiEvent->getMetaEvent().run().dataOrigin();
  m_ntuple.m_contextRunInfoID = m_digiEvent->getMetaEvent().run().id();
  m_ntuple.m_contextRunInfoStartTime = m_digiEvent->getMetaEvent().run().startTime();

  m_ntuple.m_contextDataGramInfoModeChanges = m_digiEvent->getMetaEvent().datagram().modeChanges();
  m_ntuple.m_contextDataGramInfoDatagrams = m_digiEvent->getMetaEvent().datagram().datagrams();
  m_ntuple.m_contextDataGramInfoOpenAction = m_digiEvent->getMetaEvent().datagram().openAction();
  m_ntuple.m_contextDataGramInfoOpenReason = m_digiEvent->getMetaEvent().datagram().openReason();
  m_ntuple.m_contextDataGramInfoCrate = m_digiEvent->getMetaEvent().datagram().crate();
  m_ntuple.m_contextDataGramInfoMode = m_digiEvent->getMetaEvent().datagram().mode();
  m_ntuple.m_contextDataGramInfoCloseAction = m_digiEvent->getMetaEvent().datagram().closeAction();
  m_ntuple.m_contextDataGramInfoCloseReason = m_digiEvent->getMetaEvent().datagram().closeReason();

  m_ntuple.m_contextGemScalersElapsed = m_digiEvent->getMetaEvent().scalers().elapsed();
  m_ntuple.m_contextGemScalersLivetime = m_digiEvent->getMetaEvent().scalers().livetime();
  m_ntuple.m_contextGemScalersPrescaled = m_digiEvent->getMetaEvent().scalers().prescaled();
  m_ntuple.m_contextGemScalersDiscarded = m_digiEvent->getMetaEvent().scalers().discarded();
  m_ntuple.m_contextGemScalersSequence = m_digiEvent->getMetaEvent().scalers().sequence();
  m_ntuple.m_contextGemScalersDeadzone = m_digiEvent->getMetaEvent().scalers().deadzone();

  m_ntuple.m_contextLsfTimeTimeToneCurrentIncomplete = m_digiEvent->getMetaEvent().time().current().incomplete();
  m_ntuple.m_contextLsfTimeTimeToneCurrentTimeSecs = m_digiEvent->getMetaEvent().time().current().timeSecs();
  m_ntuple.m_contextLsfTimeTimeToneCurrentFlywheeling = m_digiEvent->getMetaEvent().time().current().flywheeling();
  m_ntuple.m_contextLsfTimeTimeToneCurrentFlagsValid = m_digiEvent->getMetaEvent().time().current().flagsValid();
  m_ntuple.m_contextLsfTimeTimeToneCurrentIsSourceGps = m_digiEvent->getMetaEvent().time().current().missingGps();
  m_ntuple.m_contextLsfTimeTimeToneCurrentMissingCpuPps = m_digiEvent->getMetaEvent().time().current().missingCpuPps();
  m_ntuple.m_contextLsfTimeTimeToneCurrentMissingLatPps = m_digiEvent->getMetaEvent().time().current().missingLatPps();
  m_ntuple.m_contextLsfTimeTimeToneCurrentMissingTimeTone = m_digiEvent->getMetaEvent().time().current().missingTimeTone();
  m_ntuple.m_contextLsfTimeTimeToneCurrentEarlyEvent = m_digiEvent->getMetaEvent().time().current().earlyEvent();
  m_ntuple.m_contextLsfTimeTimeToneCurrentGemTimeHacks = m_digiEvent->getMetaEvent().time().current().timeHack().hacks();
  m_ntuple.m_contextLsfTimeTimeToneCurrentGemTimeTicks = m_digiEvent->getMetaEvent().time().current().timeHack().ticks();

  m_ntuple.m_contextLsfTimeTimeTonePreviousIncomplete      = m_digiEvent->getMetaEvent().time().previous().incomplete();
  m_ntuple.m_contextLsfTimeTimeTonePreviousTimeSecs        = m_digiEvent->getMetaEvent().time().previous().timeSecs();
  m_ntuple.m_contextLsfTimeTimeTonePreviousFlywheeling     = m_digiEvent->getMetaEvent().time().previous().flywheeling();
  m_ntuple.m_contextLsfTimeTimeTonePreviousFlagsValid      = m_digiEvent->getMetaEvent().time().previous().flagsValid();
  m_ntuple.m_contextLsfTimeTimeTonePreviousIsSourceGps     = m_digiEvent->getMetaEvent().time().previous().missingGps();
  m_ntuple.m_contextLsfTimeTimeTonePreviousMissingCpuPps   = m_digiEvent->getMetaEvent().time().previous().missingCpuPps();
  m_ntuple.m_contextLsfTimeTimeTonePreviousMissingLatPps   = m_digiEvent->getMetaEvent().time().previous().missingLatPps();
  m_ntuple.m_contextLsfTimeTimeTonePreviousMissingTimeTone = m_digiEvent->getMetaEvent().time().previous().missingTimeTone();
  m_ntuple.m_contextLsfTimeTimeTonePreviousEarlyEvent      = m_digiEvent->getMetaEvent().time().previous().earlyEvent();
  m_ntuple.m_contextLsfTimeTimeTonePreviousGemTimeHacks    = m_digiEvent->getMetaEvent().time().previous().timeHack().hacks();
  m_ntuple.m_contextLsfTimeTimeTonePreviousGemTimeTicks    = m_digiEvent->getMetaEvent().time().previous().timeHack().ticks();

  m_ntuple.m_contextLsfTimeTimeTicks = m_digiEvent->getMetaEvent().time().timeTicks();

  m_ntuple.m_contextLsfTimeTimeHackHacks = m_digiEvent->getMetaEvent().time().timeHack().hacks();
  m_ntuple.m_contextLsfTimeTimeHackTicks = m_digiEvent->getMetaEvent().time().timeHack().ticks();


  m_ntuple.m_contextRunType = m_digiEvent->getMetaEvent().runType();


  // GEM information:
  m_ntuple.m_gemConditionsWord = m_digiEvent->getGem().getConditionSummary();

  m_ntuple.m_gemLiveTime             = m_digiEvent->getGem().getLiveTime();
  m_ntuple.m_gemTriggerTime          = m_digiEvent->getGem().getTriggerTime();
  m_ntuple.m_gemDeltaEventTime       = m_digiEvent->getGem().getDeltaEventTime();
  m_ntuple.m_gemOnePpsSeconds        = m_digiEvent->getGem().getOnePpsTime().getSeconds();
  m_ntuple.m_gemOnePpsTime           = m_digiEvent->getGem().getOnePpsTime().getTimebase();
  m_ntuple.m_gemPrescaled            = m_digiEvent->getGem().getPrescaled();
  m_ntuple.m_gemDiscarded            = m_digiEvent->getGem().getDiscarded();
  m_ntuple.m_gemCondArrivalTimeWord  = m_digiEvent->getGem().getCondArrTime().condArr();
  m_ntuple.m_gemCondArrivalTimeExt   = m_digiEvent->getGem().getCondArrTime().external();
  m_ntuple.m_gemCondArrivalTimeCno   = m_digiEvent->getGem().getCondArrTime().cno();
  m_ntuple.m_gemCondArrivalTimeCalLe = m_digiEvent->getGem().getCondArrTime().calLE();
  m_ntuple.m_gemCondArrivalTimeCalHe = m_digiEvent->getGem().getCondArrTime().calHE();
  m_ntuple.m_gemCondArrivalTimeTkr   = m_digiEvent->getGem().getCondArrTime().tkr();
  m_ntuple.m_gemCondArrivalTimeRoi   = m_digiEvent->getGem().getCondArrTime().roi();
  m_ntuple.m_gemDeltaWindowOpenTime  = m_digiEvent->getGem().getDeltaWindowOpenTime();
  m_ntuple.m_gemDeadZone             = m_digiEvent->getGem().getMissed();

  m_ntuple.m_gemAcdTilesXzp = m_digiEvent->getGem().getTileList().getXzp();
  m_ntuple.m_gemAcdTilesXzm = m_digiEvent->getGem().getTileList().getXzm();
  m_ntuple.m_gemAcdTilesYzp = m_digiEvent->getGem().getTileList().getYzp();
  m_ntuple.m_gemAcdTilesYzm = m_digiEvent->getGem().getTileList().getYzm();
  m_ntuple.m_gemAcdTilesXy  = m_digiEvent->getGem().getTileList().getXy();
  m_ntuple.m_gemAcdTilesRbn = m_digiEvent->getGem().getTileList().getRbn();
  m_ntuple.m_gemAcdTilesNa  = m_digiEvent->getGem().getTileList().getNa();

  unsigned tmpGemTkr   = m_digiEvent->getGem().getTkrVector();
  unsigned tmpGemRoi   = m_digiEvent->getGem().getRoiVector();
  unsigned tmpGemCalLe = m_digiEvent->getGem().getCalLeVector();
  unsigned tmpGemCalHe = m_digiEvent->getGem().getCalHeVector();
  unsigned tmpGemCno   = m_digiEvent->getGem().getCnoVector();
  

  unsigned int tmpEbfSecond     = m_digiEvent->getEbfTimeSec();
  unsigned int tmpEbfNanoSecond = m_digiEvent->getEbfTimeNanoSec();

  m_ntuple.m_triggerTicks = evtTicks(m_ntuple.m_gemTriggerTime,m_ntuple.m_gemOnePpsSeconds, m_ntuple.m_gemOnePpsTime,tmpEbfSecond, tmpEbfNanoSecond);

  for (int iTower = 0; iTower<g_nTower; iTower++) {
    m_ntuple.m_gemTkrVector[iTower]   = ((tmpGemTkr >> iTower) & 1) ;      
    m_ntuple.m_gemRoiVector[iTower]   = ((tmpGemRoi >> iTower) & 1) ;      
    m_ntuple.m_gemCalLeVector[iTower] = ((tmpGemCalLe >> iTower) &1 ) ;      
    m_ntuple.m_gemCalHeVector[iTower] = ((tmpGemCalHe >> iTower) &1 ) ;      
  }
  for (int iCno = 0; iCno<g_nCno; iCno++) {
    m_ntuple.m_gemCnoVector[iCno] = ((tmpGemCno >> iCno) & 1) ;      
  }
 
  // Luis's three-in-a-row trigger bits:
  for (int iTower = 0; iTower<g_nTower; iTower++) {
    m_ntuple.m_digiTriRowBits[iTower] = m_digiEvent->getL1T().getDigiTriRowBits(iTower);
    m_ntuple.m_trgReqTriRowBits[iTower] = m_digiEvent->getL1T().getTrgReqTriRowBits(iTower);
  }
  
  // Event sizes:
  for (int iTower = 0; iTower<g_nTower; iTower++) {
    m_ntuple.m_temLength[iTower] = m_digiEvent->getEventSummaryData().temLength(iTower);
  }

  m_ntuple.m_gemLength  = m_digiEvent->getEventSummaryData().gemLength();
  m_ntuple.m_oswLength  = m_digiEvent->getEventSummaryData().oswLength();
  m_ntuple.m_aemLength  = m_digiEvent->getEventSummaryData().aemLength();
  
  for (int iTower = 0; iTower<g_nTower; iTower++) {
    m_ntuple.m_errLength[iTower]  = m_digiEvent->getEventSummaryData().errLength(iTower);
    m_ntuple.m_diagLength[iTower] = m_digiEvent->getEventSummaryData().diagLength(iTower);
  }

  // Event quality:
  m_ntuple.m_eventFlags = m_digiEvent->getEventSummaryData().eventFlags();

  parseDiagnosticData(); 

  // Error flags:
  m_ntuple.m_eventBadEventSequence = m_digiEvent->getEventSummaryData().badEventSequence();
  m_ntuple.m_eventBadTkrRecon      = m_digiEvent->getEventSummaryData().badTkrRecon();
  m_ntuple.m_eventPacketError      = m_digiEvent->getEventSummaryData().packetError();
  m_ntuple.m_eventTemError         = m_digiEvent->getEventSummaryData().temError();
  m_ntuple.m_eventTrgParityError   = m_digiEvent->getEventSummaryData().trgParityError();
  m_ntuple.m_eventBadLdfStatus     = m_digiEvent->getEventSummaryData().badLdfStatus();
  m_ntuple.m_eventGtrcPhase        = m_digiEvent->getEventSummaryData().gtrcPhase();
  m_ntuple.m_eventGtfePhase        = m_digiEvent->getEventSummaryData().gtfePhase();
  m_ntuple.m_eventGtccFifo         = m_digiEvent->getEventSummaryData().gtccFifo();
  m_ntuple.m_eventGtccHdrParity    = m_digiEvent->getEventSummaryData().gtccHdrParity();
  m_ntuple.m_eventGtccWcParity     = m_digiEvent->getEventSummaryData().gtccWcParity();
  m_ntuple.m_eventGtrcSummary      = m_digiEvent->getEventSummaryData().gtrcSummary();
  m_ntuple.m_eventGtccDataParity   = m_digiEvent->getEventSummaryData().gtccDataParity();
  m_ntuple.m_eventGtccTimeout      = m_digiEvent->getEventSummaryData().gtccTimeout();
  m_ntuple.m_eventGcccError        = m_digiEvent->getEventSummaryData().gcccError();
  m_ntuple.m_eventGtccError        = m_digiEvent->getEventSummaryData().gtccError();
  m_ntuple.m_eventPhaseError       = m_digiEvent->getEventSummaryData().phaseError();
  m_ntuple.m_eventTimeoutError     = m_digiEvent->getEventSummaryData().timeoutError();

  m_ntuple.m_eventReadout4     = m_digiEvent->getEventSummaryData().readout4( );
  m_ntuple.m_eventZeroSuppress = m_digiEvent->getEventSummaryData().zeroSuppress();
  m_ntuple.m_eventMarker       = m_digiEvent->getEventSummaryData().marker();
  m_ntuple.m_eventCalStrobe    = m_digiEvent->getEventSummaryData().calStrobe();
  m_ntuple.m_eventTag          = m_digiEvent->getEventSummaryData().tag();
  m_ntuple.m_eventTACK         = m_digiEvent->getEventSummaryData().TACK();
  
  // CCSDS info:
  m_ntuple.m_cCSDStime = m_digiEvent->getCcsds().getUtc();
  m_ntuple.m_cCSDSapID = m_digiEvent->getCcsds().getApid(); 
  m_ntuple.m_cCSDSscID = m_digiEvent->getCcsds().getScid();


  //
  // ACD digi:
  //
  const TObjArray* acdDigiCol = m_digiEvent->getAcdDigiCol();
  assert(acdDigiCol != 0);

  // Number of digis:
  int nAcdDigi = acdDigiCol->GetLast()+1;
  m_ntuple.m_acdNumDigis = nAcdDigi;

  // For the first 10 digis:
  int i10Count = 0;

  // Loop over all digis:
  for(int iDigi = 0; iDigi != nAcdDigi; ++iDigi) {

    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi != 0);

    // Tile ID:
    int AcdID = acdDigi->getId().getId();

    // Attached tile and ID out of bounds?
    if (acdDigi->getId().getNa()==0 && (AcdID>603 || AcdID<0)) {
      std::cout << "ACD tile ID for attached tile is >603! - " << AcdID << std::endl;
    }


    // Attached tile?
    if (acdDigi->getId().getNa()==0 && AcdID>-1 && AcdID<604) {

      if (i10Count < 10) {
        m_ntuple.m_acd10Ids[i10Count] = AcdID;
        i10Count++;
      }

      m_ntuple.m_acdPha[AcdID][0] = acdDigi->getPulseHeight(AcdDigi::A);
      m_ntuple.m_acdPha[AcdID][1] = acdDigi->getPulseHeight(AcdDigi::B);

      m_ntuple.m_acdHitMap[AcdID][0] = acdDigi->getHitMapBit(AcdDigi::A);
      m_ntuple.m_acdHitMap[AcdID][1] = acdDigi->getHitMapBit(AcdDigi::B);

      m_ntuple.m_acdRange[AcdID][0] = acdDigi->getRange(AcdDigi::A);
      m_ntuple.m_acdRange[AcdID][1] = acdDigi->getRange(AcdDigi::B);

      m_ntuple.m_acdOddParityError[AcdID][0] = acdDigi->getOddParityError(AcdDigi::A);
      m_ntuple.m_acdOddParityError[AcdID][1] = acdDigi->getOddParityError(AcdDigi::B);

      m_ntuple.m_acdHeaderParityError[AcdID][0] = acdDigi->getHeaderParityError(AcdDigi::A);
      m_ntuple.m_acdHeaderParityError[AcdID][1] = acdDigi->getHeaderParityError(AcdDigi::B);

      m_ntuple.m_acdLowDisc[AcdID][0] = acdDigi->getAcceptMapBit(AcdDigi::A);
      m_ntuple.m_acdLowDisc[AcdID][1] = acdDigi->getAcceptMapBit(AcdDigi::B);

      m_ntuple.m_acdTileNumber[AcdID] = acdDigi->getTileNumber();
      m_ntuple.m_acdMCEnergy[AcdID]   = acdDigi->getEnergy();
    }


    // Non-Attached tile?
    if (acdDigi->getId().getNa()==1) {

      // NA tile ID:
      int AcdNaID = -1;

      // Get the name of the tile: NA0, NA1, ...., NA9, NA10
      const char* AcdNaName = acdDigi->getTileName();

      // Easier to manipulate:
      std::string tmpAcdNaName = (std::string) AcdNaName;

      // Lenght of string:
      int AcdNaNameLength = tmpAcdNaName.size();

      if ( AcdNaNameLength == 4) {
	// Can only mean NA10:
	AcdNaID = 10;
      } else {
	// Now we only have NAx:
	char* p = &tmpAcdNaName[2];
        AcdNaID = atoi(p);
      }

      if (AcdNaID<0 || AcdNaID>10) {
	std::cout << "ACD tile ID for non-attached tile is not in range! AcdNaID is: " << AcdNaID << std::endl;        
      }

      if (AcdNaID>-1 && AcdNaID<11) {
	m_ntuple.m_acdNaPha[AcdNaID][0] = acdDigi->getPulseHeight(AcdDigi::A);
        m_ntuple.m_acdNaPha[AcdNaID][1] = acdDigi->getPulseHeight(AcdDigi::B);

	m_ntuple.m_acdNaHitMap[AcdNaID][0] = acdDigi->getHitMapBit(AcdDigi::A);
        m_ntuple.m_acdNaHitMap[AcdNaID][1] = acdDigi->getHitMapBit(AcdDigi::B);

	m_ntuple.m_acdNaRange[AcdNaID][0] = acdDigi->getRange(AcdDigi::A);
        m_ntuple.m_acdNaRange[AcdNaID][1] = acdDigi->getRange(AcdDigi::B);

	m_ntuple.m_acdNaOddParityError[AcdNaID][0] = acdDigi->getOddParityError(AcdDigi::A);
        m_ntuple.m_acdNaOddParityError[AcdNaID][1] = acdDigi->getOddParityError(AcdDigi::B);

	m_ntuple.m_acdNaHeaderParityError[AcdNaID][0] = acdDigi->getHeaderParityError(AcdDigi::A);
        m_ntuple.m_acdNaHeaderParityError[AcdNaID][1] = acdDigi->getHeaderParityError(AcdDigi::B);

        m_ntuple.m_acdNaLowDisc[AcdNaID][0] = acdDigi->getAcceptMapBit(AcdDigi::A);
        m_ntuple.m_acdNaLowDisc[AcdNaID][1] = acdDigi->getAcceptMapBit(AcdDigi::B);
      }
    }
  }





  // fill in no of Tkr digis and TOTs
  m_ntuple.m_nTkrDigis = m_digiEvent->getTkrDigiCol()->GetLast()+1;

  for(int i = 0; i != m_ntuple.m_nTkrDigis; ++i) {
    const TkrDigi* tkrDigi = m_digiEvent->getTkrDigi(i);

    assert(tkrDigi != 0);

   // fill hit patterns for each plane
    fillStripHits(tkrDigi);

    int iTower = tkrDigi->getTower().id();
    int iLayer = tkrDigi->getBilayer();
    GlastAxis::axis iView = tkrDigi->getView();
  
    int nStrips = tkrDigi->getNumHits();

    m_ntuple.m_totalStripHits[iTower] += nStrips;

    if(iView == GlastAxis::X) {
      m_ntuple.m_nStrips[iTower][iLayer][0] = nStrips;
      m_ntuple.m_tot[iTower][iLayer][0][0] = tkrDigi->getToT(0);
      m_ntuple.m_tot[iTower][iLayer][0][1] = tkrDigi->getToT(1);
    }
    else if(iView == GlastAxis::Y) {
      m_ntuple.m_nStrips[iTower][iLayer][1] = nStrips;
      m_ntuple.m_tot[iTower][iLayer][1][0] = tkrDigi->getToT(0);
      m_ntuple.m_tot[iTower][iLayer][1][1] = tkrDigi->getToT(1);
    }

      // fill in corrected tot
    /*
      if(m_mcFile == 0) {
	correctTotDataLinear(tkrDigi);
	correctTotDataQuad(tkrDigi);
      }
    */
  }

  /*
  // ACD digi
  const TObjArray* acdDigiCol = m_digiEvent->getAcdDigiCol();
  if (!acdDigiCol) return;

  int nAcdDigi = acdDigiCol->GetLast() + 1;
  cout << nAcdDigi << endl;
  */
}

void RootAnalyzer::fillOutputTree()
{
  if(m_outputFile) {
    TDirectory* saveDir = gDirectory;
    m_outputFile->cd();
    m_tree->Fill();
    saveDir->cd();
  }
}

bool RootAnalyzer::isRootFile(const string& f)
{
  TFile rootF(f.c_str());
  if(rootF.IsZombie()) {
    return false;
  }
  else {
    return true;
  }
}

void RootAnalyzer::makeTChain(const string& line, TChain* chain)
{
  std::istringstream stream(line);
  string f;
  while(stream >> f) {
    if(isRootFile(f)) {
      chain->Add(f.c_str());
    }
    else {
      cout << f << " does not exist or is not a root file! It will not be used to make the SVAC ntuple and histogram files!" << endl;
    } 
  }
}

void RootAnalyzer::parseLine(const string& line, string& str)
{
  std::istringstream stream(line);
  stream >> str;
}

void RootAnalyzer::parseOptionFile(const char* f)
{
  ifstream optF(f);
  string line;

  while( getline(optF, line) ) {
    if(!isEmptyOrCommentStr(line)) break;
  }
  cout << "Input mc file(s): " << line << endl;
  makeTChain(line, m_mcChain);
  
  while( getline(optF, line) ) {
    if(!isEmptyOrCommentStr(line)) break;
  }
  cout << "Input digi file(s): " << line << endl;
  makeTChain(line, m_digiChain);
  
  while( getline(optF, line) ) {
    if(!isEmptyOrCommentStr(line)) break;
  }
  cout << "Input recon file(s): " << line << endl;
  makeTChain(line, m_reconChain);

  while( getline(optF, line) ) {
    if(!isEmptyOrCommentStr(line)) break;
  }
  string svacF;
  parseLine(line, svacF);
  cout << "Output SVAC ntuple file: " << svacF << endl;
  m_outputFile = new TFile(svacF.c_str(), "RECREATE");
  m_outputFile->mkdir("TkrCalib");
  //m_tkrNoiseOcc_dir = m_outputFile->mkdir("TkrNoiseOcc");
  m_tree = new TTree("Output", "Root Analyzer");

  // Set max file size to 500 GB:
  Long64_t maxTreeSize = 5000000000000;
  m_tree->SetMaxTreeSize(maxTreeSize);

  // create branches for each ntuple variable
  createBranches();

  while( getline(optF, line) ) {
    if(!isEmptyOrCommentStr(line)) break;
  }
  string histF;
  parseLine(line, histF);
  cout << "Output hist file: " << histF << endl;
  m_histFile = new TFile(histF.c_str(), "RECREATE");

  // create histograms for strip hits

  for(int iTower = 0; iTower != g_nTower; ++iTower) {
    for(int iLayer = 0; iLayer != g_nTkrLayer; ++iLayer) {
      for(int iView = 0; iView != g_nView; ++iView) {

	char name1[] = "hit00000";
	sprintf(name1, "hit%02d%02d%1d", iTower, iLayer, iView);

	m_stripHits[iTower][iLayer][iView] = 
	  new TH1F(name1, name1, g_nStripsPerLayer, 0, g_nStripsPerLayer);

	char name2[] = "map00000";
	sprintf(name2, "map%02d%02d%1d", iTower, iLayer, iView);

	m_stripMap[iTower][iLayer][iView] = 
	  new TH2F(name2, name2, g_nFEC, 0, g_nFEC, g_nStripsPerLayer/g_nFEC,
		   0, g_nStripsPerLayer/g_nFEC);

      }
    }
  }
}

bool RootAnalyzer::isEmptyOrCommentStr(const string& s)
{
  int len = s.length();
  if(len == 0) return true;
  bool empty = true;
  for(int i = 0; i != len; ++i) {
    if(s[0] != ' ') empty = false;
  }
  if(empty) return true;

  if(len >= 2 && s[0] == '/' && s[1] == '/') {
    return true;
  }
  else {
    return false;
  }
}

void RootAnalyzer::analyzeData()
{
  Long64_t nMc = m_mcChain->GetEntries();
  cout << "No. of Mc events to be processed: " << nMc << endl;

  Long64_t nDigi = m_digiChain->GetEntries();
  cout << "No. of Digi events to be processed: " << nDigi << endl;

  Long64_t nRecon = m_reconChain->GetEntries();
  cout << "No. of Recon events to be processed: " << nRecon << endl;

  Long64_t nEvent = std::max(std::max(nMc, nDigi), nRecon);
  if( (nEvent != nMc && nMc != 0) || (nEvent != nDigi && nDigi != 0) ||
      (nEvent != nRecon && nRecon != 0) ) {
    cout << "No. of events in mc, digi or recon files are not identical with each other, stop processing!" << endl;
    exit(1);
  }

  if(nMc != 0) {
    m_mcEvent = 0;  
    // what is stored in the root tree is actually a pointer rather than
    // mc event
    m_mcChain->SetBranchAddress("McEvent", &m_mcEvent);
  }

  if(nRecon != 0) {
    m_reconEvent = 0;
    m_reconChain->SetBranchAddress("ReconEvent", &m_reconEvent);
  }

  if(nDigi != 0) {
    m_digiEvent = 0;
    m_digiChain->SetBranchAddress("DigiEvent", &m_digiEvent);
  }


  // awb
  //nEvent = 1000;

  m_tkrCalib->setNevents(nEvent);
  m_tkrCalib->setOutputFile(m_outputFile);
  //Load current event pointers in TkrCalibManager
  m_tkrCalib->setEventPtrs(m_digiEvent, m_reconEvent);
  
  //TkrNoiseOcc::initAnalysis(int nEvent, int evt_interval)
  //m_tkrNoiseOcc->initAnalysis(nEvent, 1000);
  //m_tkrNoiseOcc->setDigiEvtPtr(m_digiEvent);
  
  for(Long64_t  iEvent = 0; iEvent != nEvent; ++iEvent) {

    m_ntuple.reset();  
    if(m_mcEvent) m_mcEvent->Clear();
    if(m_digiEvent) m_digiEvent->Clear();
    if(m_reconEvent) m_reconEvent->Clear();

    if(nMc != 0) {
      m_mcChain->GetEvent(iEvent);
      analyzeMcTree();
    }

    if(nDigi != 0) {
      m_digiChain->GetEvent(iEvent);
      analyzeDigiTree();
    }

    if(nRecon != 0) {
      m_reconChain->GetEvent(iEvent);
      analyzeReconTree();
    }

    analyzeTot();
    
    //Tracker Calibration Analysis
    m_tkrCalib->analyzeEvent();
    //m_tkrNoiseOcc->anaDigiEvt();

    fillOutputTree();
    if(m_mcEvent) m_mcEvent->Clear();
    if(m_digiEvent) m_digiEvent->Clear();
    if(m_reconEvent) m_reconEvent->Clear();
  }  

}

bool RootAnalyzer::extractTowerLayerView(const VolumeIdentifier& id, 
					 int& iTower, int& iLayer, 
					 int& iView) const
{
  // id code is formatted as the following (if only one tower is simulated):
  // Tower(0)/TowerY(0)/TowerX(0)/TKR(1)/TrayNo(0-18)/Measure(0,1)/View(0,1)/
  // Ladder/Waffer

  iTower = id[0];

  // not Tracker
  if(id[3] != 1) return 0;

  int iTray = id[4];
  iView = id[5];  // Measure X: 0, Measure Y: 1
  int iBotTop = id[6];  // Bott: 0, Top: 1

  iLayer = iTray -1 + iBotTop;

  // check boundary condition
  if(iTower<0 || iTower>15 || iLayer<0 || iLayer>17 || iView<0 || 
     iView>1) return 0;

  return 1;
}

void RootAnalyzer::fillStripHits(const TkrDigi* tkrDigi)
{

  int tower = tkrDigi->getTower().id();
  int layer = tkrDigi->getBilayer(); 
  int view = tkrDigi->getView();

  int nStrips = tkrDigi->getNumHits();

  TDirectory* saveDir = gDirectory;
  m_histFile->cd();

  for(int i = 0; i != nStrips; ++i) {

    int stripId = tkrDigi->getStrip(i);
    m_stripHits[tower][layer][view]->Fill(stripId);

    int nStripPerFEC = g_nStripsPerLayer / g_nFEC;

    int fec = stripId / nStripPerFEC;
    int res = stripId - fec * nStripPerFEC;

    m_stripMap[tower][layer][view]->Fill(fec, res);

  }

  saveDir->cd();
}

void RootAnalyzer::analyzeTot()
{
  for(int iTower = 0; iTower != g_nTower; ++iTower) {
    for(int iLayer = (g_nTkrLayer-1); iLayer >= 0; --iLayer) {

      if(m_ntuple.m_nStrips[iTower][iLayer][0] > 0 &&
	 m_ntuple.m_nStrips[iTower][iLayer][1] > 0) {

	float totX = std::max(m_ntuple.m_tot[iTower][iLayer][0][0], 
			      m_ntuple.m_tot[iTower][iLayer][0][1]);
	float totY = std::max(m_ntuple.m_tot[iTower][iLayer][1][0], 
			      m_ntuple.m_tot[iTower][iLayer][1][1]);

	m_ntuple.m_topTot[iTower] = std::max(totX, totY);
	break;
      }
    }

  }

  if(m_ntuple.m_nTkrTracks > 0) {

    TkrRecon* tkrRecon = m_reconEvent->getTkrRecon();
    TObjArray* vertices = tkrRecon->getVertexCol();
    if(m_ntuple.m_nTkrVertices >= 1) {
      TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
      if(tkrVertex) {

	TkrTrack* trk = (TkrTrack*) tkrVertex->getTrack(0);
	TkrTrackHit* hit = (TkrTrackHit*) trk->First();
	commonRootData::TkrId id = hit->getClusterPtr()->getTkrId();
	TowerId tId(id.getTowerX(), id.getTowerX());
	int convLayer = hit->getClusterPtr()->getLayer();
	int convTower = tId.id();

	assert(convLayer >= 0 && convLayer <g_nTkrLayer);
	float totX = std::max(m_ntuple.m_tot[convTower][convLayer][0][0], 
			      m_ntuple.m_tot[convTower][convLayer][0][1]);
	float totY = std::max(m_ntuple.m_tot[convTower][convLayer][1][0], 
			      m_ntuple.m_tot[convTower][convLayer][1][1]);

	m_ntuple.m_convTot = std::max(totX, totY);
      }
    }
  }
 
}

void RootAnalyzer::parseDiagnosticData()
{
  if(m_digiEvent->getTkrDiagnosticCol()) {
    int nTkrDiag = m_digiEvent->getTkrDiagnosticCol()->GetLast()+1;

    for(int i = 0; i != nTkrDiag; ++i) {

      const TkrDiagnosticData* pDiag = m_digiEvent->getTkrDiagnostic(i);
      int iTower = pDiag->tower();
      if(m_ntuple.m_diagLength[iTower]) {
	m_ntuple.m_tpTkr[iTower][pDiag->gtcc()] = pDiag->getDataWord();
      }
    }

    ElecToGeo::getInstance()->decodeTkrTp(m_ntuple.m_tpTkr,m_ntuple.m_tkrReq);
  }

  if(m_digiEvent->getCalDiagnosticCol()) {

    int nCalDiag = m_digiEvent->getCalDiagnosticCol()->GetLast()+1;

    for(int i = 0; i != nCalDiag; ++i) {

      const CalDiagnosticData* pDiag = m_digiEvent->getCalDiagnostic(i);

      int iTower = pDiag->tower();
      if(m_ntuple.m_diagLength[iTower]) {
	m_ntuple.m_tpCal[pDiag->tower()][pDiag->layer()] = pDiag->getDataWord();
      }
    }

    ElecToGeo::getInstance()->decodeCalTp(m_ntuple.m_tpCal, m_ntuple.m_calReq,
					  m_ntuple.m_calLogAccepts);

  }
}

void RootAnalyzer::createBranches()
{

  // Event information:
  m_tree->Branch("RunID", &(m_ntuple.m_runId), "RunID/i");
  m_tree->Branch("EventID", &(m_ntuple.m_eventId), "EventID/i");
  m_tree->Branch("EventSize", &(m_ntuple.m_eventSize), "EventSize/i");
  m_tree->Branch("EventFlags", &(m_ntuple.m_eventFlags), "EventFlags/i");
  m_tree->Branch("EvtTime", &(m_ntuple.m_timeStamp), "EvtTime/D");
  m_tree->Branch("EvtTicks", &(m_ntuple.m_triggerTicks),"EvtTicks/D");
  m_tree->Branch("EvtSummary", &(m_ntuple.m_summaryWord), "EvtSummary/i");
  m_tree->Branch("EvtMCLiveTime", &(m_ntuple.m_eventMCLivetime), "EvtMCLiveTime/D");

  // Error flags:
  m_tree->Branch("EventBadEventSequence", &(m_ntuple.m_eventBadEventSequence), "EventBadEventSequence/I");
  m_tree->Branch("EventBadTkrRecon", &(m_ntuple.m_eventBadTkrRecon), "EventBadTkrRecon/I");
  m_tree->Branch("EventPacketError", &(m_ntuple.m_eventPacketError), "EventPacketError/I");
  m_tree->Branch("EventTemError", &(m_ntuple.m_eventTemError), "EventTemError/I");
  m_tree->Branch("EventTrgParityError", &(m_ntuple.m_eventTrgParityError), "EventTrgParityError/I");
  m_tree->Branch("EventBadLdfStatus", &(m_ntuple.m_eventBadLdfStatus), "EventBadLdfStatus/I");
  m_tree->Branch("EventGtrcPhase", &(m_ntuple.m_eventGtrcPhase), "EventGtrcPhase/I");
  m_tree->Branch("EventGtfePhase", &(m_ntuple.m_eventGtfePhase), "EventGtfePhase/I");
  m_tree->Branch("EventGtccFifo", &(m_ntuple.m_eventGtccFifo), "EventGtccFifo/I");
  m_tree->Branch("EventGtccHdrParity", &(m_ntuple.m_eventGtccHdrParity), "EventGtccHdrParity/I");
  m_tree->Branch("EventGtccWcParity", &(m_ntuple.m_eventGtccWcParity), "EventGtccWcParity/I");
  m_tree->Branch("EventGtrcSummary", &(m_ntuple.m_eventGtrcSummary), "EventGtrcSummary/I");
  m_tree->Branch("EventGtccDataParity", &(m_ntuple.m_eventGtccDataParity), "EventGtccDataParity/I");
  m_tree->Branch("EventGtccTimeout", &(m_ntuple.m_eventGtccTimeout), "EventGtccTimeout/I");
  m_tree->Branch("EventGcccError", &(m_ntuple.m_eventGcccError), "EventGcccError/I");
  m_tree->Branch("EventGtccError", &(m_ntuple.m_eventGtccError), "EventGtccError/I");
  m_tree->Branch("EventPhaseError", &(m_ntuple.m_eventPhaseError), "EventPhaseError/I");
  m_tree->Branch("EventTimeoutError", &(m_ntuple.m_eventTimeoutError), "EventTimeoutError/I");

  m_tree->Branch("EventReadout4", &(m_ntuple.m_eventReadout4), "EventReadout4/I");
  m_tree->Branch("EventZeroSuppress", &(m_ntuple.m_eventZeroSuppress), "EventZeroSuppress/I");
  m_tree->Branch("EventMarker", &(m_ntuple.m_eventMarker), "EventMarker/I");
  m_tree->Branch("EventCalStrobe", &(m_ntuple.m_eventCalStrobe), "EventCalStrobe/I");
  m_tree->Branch("EventTag", &(m_ntuple.m_eventTag), "EventTag/I");
  m_tree->Branch("EventTACK", &(m_ntuple.m_eventTACK), "EventTACK/I");


  // MC information:
  m_tree->Branch("McSeqNo", &(m_ntuple.m_seqNo), "McSeqNo/i");
  m_tree->Branch("McId", &(m_ntuple.m_parId), "McId/I");
  m_tree->Branch("McTotalEnergy", &(m_ntuple.m_mcEnergy), "McTotalEnergy/F");
  m_tree->Branch("McX0", &(m_ntuple.m_startPos[0]), "McX0/F");
  m_tree->Branch("McY0", &(m_ntuple.m_startPos[1]), "McY0/F");
  m_tree->Branch("McZ0", &(m_ntuple.m_startPos[2]), "McZ0/F");
  m_tree->Branch("McXDir", &(m_ntuple.m_startDir[0]), "McXDir/F");
  m_tree->Branch("McYDir", &(m_ntuple.m_startDir[1]), "McYDir/F");
  m_tree->Branch("McZDir", &(m_ntuple.m_startDir[2]), "McZDir/F");
  m_tree->Branch("McConvPointX", &(m_ntuple.m_convPos[0]), "McConvPointX/F");
  m_tree->Branch("McConvPointY", &(m_ntuple.m_convPos[1]), "McConvPointY/F");
  m_tree->Branch("McConvPointZ", &(m_ntuple.m_convPos[2]), "McConvPointZ/F");
  m_tree->Branch("McCalEneSum", &(m_ntuple.m_mcCalEnergy), "McCalEneSum/F");
  m_tree->Branch("McTkr1Ene", &(m_ntuple.m_pairEne[0]), "McTkr1Ene/F");
  m_tree->Branch("McTkr2Ene", &(m_ntuple.m_pairEne[1]), "McTkr2Ene/F");
  m_tree->Branch("McConvAngle", &(m_ntuple.m_convAngle), "McConvAngle/F");

  // TKR information:
  m_tree->Branch("TkrNumDigis", &(m_ntuple.m_nTkrDigis), "TkrNumDigis/I");
  m_tree->Branch("TkrNumStrips", &(m_ntuple.m_nStrips), "TkrNumStrips[16][18][2]/I");
  m_tree->Branch("tot", &(m_ntuple.m_tot), "tot[16][18][2][2]/I");
  m_tree->Branch("TkrDepositEne", &(m_ntuple.m_depositEne), "TkrDepositEne[16][18][2]/F");
  m_tree->Branch("TkrNumClusters", &(m_ntuple.m_nTkrClusters), "TkrNumClusters[16][18][2]/I");
  m_tree->Branch("TkrNumTracks", &(m_ntuple.m_nTkrTracks), "TkrNumTracks/I");
  m_tree->Branch("TkrNumVertices", &(m_ntuple.m_nTkrVertices), "TkrNumVertices/I");
  m_tree->Branch("TkrTotalHits", &(m_ntuple.m_totalStripHits), "TkrTotalHits[16]/i");
  m_tree->Branch("TkrTotalClusters", &(m_ntuple.m_totalClusters), "TkrTotalClusters[16]/i");
  m_tree->Branch("Tkr1NumHits", &(m_ntuple.m_nFit[0]), "Tkr1NumHits/I");
  m_tree->Branch("Tkr2NumHits", &(m_ntuple.m_nFit[1]), "Tkr2NumHits/I");
  m_tree->Branch("Tkr1Chisq", &(m_ntuple.m_chi2[0]), "Tkr1Chisq/F");
  m_tree->Branch("Tkr2Chisq", &(m_ntuple.m_chi2[1]), "Tkr2Chisq/F");
  m_tree->Branch("Tkr1ChisqS", &(m_ntuple.m_chi2Smooth[0]), "Tkr1ChisqS/F");
  m_tree->Branch("Tkr2ChisqS", &(m_ntuple.m_chi2Smooth[1]), "Tkr2ChisqS/F");
  m_tree->Branch("Tkr1Rms", &(m_ntuple.m_rms[0]), "Tkr1Rms/F");
  m_tree->Branch("Tkr2Rms", &(m_ntuple.m_rms[1]), "Tkr2Rms/F");
  m_tree->Branch("Tkr1KalThetaMs", &(m_ntuple.m_msAngle[0]), "Tkr1KalThetaMs/F");
  m_tree->Branch("Tkr2KalThetaMs", &(m_ntuple.m_msAngle[1]), "Tkr1Ka2ThetaMs/F");
  m_tree->Branch("Tkr1KalEne", &(m_ntuple.m_tkrEnergy[0]), "Tkr1KalEne/F");
  m_tree->Branch("Tkr2KalEne", &(m_ntuple.m_tkrEnergy[1]), "Tkr2KalEne/F");
  m_tree->Branch("Tkr1EndPos", &(m_ntuple.m_tkr1EndPos), "Tkr1EndPos[3]/F");
  m_tree->Branch("Tkr2EndPos", &(m_ntuple.m_tkr2EndPos), "Tkr2EndPos[3]/F");
  m_tree->Branch("Tkr1EndDir", &(m_ntuple.m_tkr1EndDir), "Tkr1EndDir[3]/F");
  m_tree->Branch("Tkr2EndDir", &(m_ntuple.m_tkr2EndDir), "Tkr2EndDir[3]/F");
  m_tree->Branch("TkrTopTot", &(m_ntuple.m_topTot), "TkrTopTot[16]/F");
  m_tree->Branch("Tkr1ConvTot", &(m_ntuple.m_convTot), "Tkr1ConvTot/F");


  // Vertex information:
  m_tree->Branch("VtxX0", &(m_ntuple.m_pos[0]), "VtxX0/F");
  m_tree->Branch("VtxY0", &(m_ntuple.m_pos[1]), "VtxY0/F");
  m_tree->Branch("VtxZ0", &(m_ntuple.m_pos[2]), "VtxZ0/F");
  m_tree->Branch("VtxXDir", &(m_ntuple.m_dir[0]), "VtxXDir/F");
  m_tree->Branch("VtxYDir", &(m_ntuple.m_dir[1]), "VtxYDir/F");
  m_tree->Branch("VtxZDir", &(m_ntuple.m_dir[2]), "VtxZDir/F");
  m_tree->Branch("Vtx1Energy", &(m_ntuple.m_fitTotalEnergy), "Vtx1Energy/F");
  m_tree->Branch("Vtx1NumTkrs", &(m_ntuple.m_vtxTrks), "Vtx1NumTkrs/I");


  // CAL information:
  m_tree->Branch("CalEneSum", &(m_ntuple.m_calEnergy), "CalEneSum/F");
  m_tree->Branch("CalXEcentr", &(m_ntuple.m_calPos[0]), "CalXEcentr/F");
  m_tree->Branch("CalYEcentr", &(m_ntuple.m_calPos[1]), "CalYEcentr/F");
  m_tree->Branch("CalZEcentr", &(m_ntuple.m_calPos[2]), "CalZEcentr/F");
  m_tree->Branch("CalXtalEne", &(m_ntuple.m_xtalEne), "CalXtalEne[16][8][12]/F");
  m_tree->Branch("CalMaxEne", &(m_ntuple.m_maxCalEnergy), "CalMaxEne/F");
  m_tree->Branch("CalNumHit", &(m_ntuple.m_nCrystalHit), "CalNumHit[16]/I");
  m_tree->Branch("CalXtalPos", &(m_ntuple.m_xtalPos), "CalXtalPos[16][8][12][3]/F");

  m_tree->Branch("CalMipNum", &(m_ntuple.m_calMipNum),"CalMipNum/I");

  m_tree->Branch("CalMip1Pos", &(m_ntuple.m_calMip1Pos),"CalMip1Pos[3]/F");
  m_tree->Branch("CalMip1Dir", &(m_ntuple.m_calMip1Dir),"CalMip1Dir[3]/F");
  m_tree->Branch("CalMip1Chi2", &(m_ntuple.m_calMip1Chi2),"CalMip1Chi2/F");
  m_tree->Branch("CalMip1D2edge", &(m_ntuple.m_calMip1D2edge),"CalMip1D2edge");
  m_tree->Branch("CalMip1ArcLen", &(m_ntuple.m_calMip1ArcLen),"CalMip1ArcLen/F");
  m_tree->Branch("CalMip1Ecor", &(m_ntuple.m_calMip1Ecor),"CalMip1Ecor/F");
  m_tree->Branch("CalMip1EcorRms", &(m_ntuple.m_calMip1EcorRms),"CalMip1EcorRms/F");
  m_tree->Branch("CalMip1Erm", &(m_ntuple.m_calMip1Erm),"CalMip1Erm/F");

  m_tree->Branch("CalMip2Pos", &(m_ntuple.m_calMip2Pos),"CalMip2Pos[3]/F");
  m_tree->Branch("CalMip2Dir", &(m_ntuple.m_calMip2Dir),"CalMip2Dir[3]/F");
  m_tree->Branch("CalMip2Chi2", &(m_ntuple.m_calMip2Chi2),"CalMip2Chi2/F"); 
  m_tree->Branch("CalMip2D2edge", &(m_ntuple.m_calMip2D2edge),"CalMip2D2edge");
  m_tree->Branch("CalMip2ArcLen", &(m_ntuple.m_calMip2ArcLen),"CalMip2ArcLen/F");
  m_tree->Branch("CalMip2Ecor", &(m_ntuple.m_calMip2Ecor),"CalMip2Ecor/F");
  m_tree->Branch("CalMip2EcorRms", &(m_ntuple.m_calMip2EcorRms),"CalMip2EcorRms/F");
  m_tree->Branch("CalMip2Erm", &(m_ntuple.m_calMip2Erm),"CalMip2Erm/F");

  // GLT information:
  m_tree->Branch("GltWord", &(m_ntuple.m_trigger), "GltWord/i");

  //                                                                                                                                                                                                           
  // Context information:                                                                                                                                                                                      
  //                                                                                                                                                                                                           
  m_tree->Branch("ContextRunInfoPlatform", &(m_ntuple.m_contextRunInfoPlatform), "ContextRunInfoPlatform/I");
  m_tree->Branch("ContextRunInfoDataOrigin", &(m_ntuple.m_contextRunInfoDataOrigin), "ContextRunInfoDataOrigin/I");
  m_tree->Branch("ContextRunInfoID", &(m_ntuple.m_contextRunInfoID), "ContextRunInfoID/i");
  m_tree->Branch("ContextRunInfoStartTime", &(m_ntuple.m_contextRunInfoStartTime), "ContextRunInfoStartTime/i");

  m_tree->Branch("ContextDataGramInfoModeChanges", &(m_ntuple.m_contextDataGramInfoModeChanges), "ContextDataGramInfoModeChanges/i");
  m_tree->Branch("ContextDataGramInfoDatagrams", &(m_ntuple.m_contextDataGramInfoDatagrams), "ContextDataGramInfoDatagrams/i");
  m_tree->Branch("ContextDataGramInfoOpenAction", &(m_ntuple.m_contextDataGramInfoOpenAction), "ContextDataGramInfoOpenAction/I");
  m_tree->Branch("ContextDataGramInfoOpenReason", &(m_ntuple.m_contextDataGramInfoOpenReason), "ContextDataGramInfoOpenReason/I");
  m_tree->Branch("ContextDataGramInfoCrate", &(m_ntuple.m_contextDataGramInfoCrate), "ContextDataGramInfoCrate/I");
  m_tree->Branch("ContextDataGramInfoMode", &(m_ntuple.m_contextDataGramInfoMode), "ContextDataGramInfoMode/I");
  m_tree->Branch("ContextDataGramInfoCloseAction", &(m_ntuple.m_contextDataGramInfoCloseAction), "ContextDataGramInfoCloseAction/I");
  m_tree->Branch("ContextDataGramInfoCloseReason", &(m_ntuple.m_contextDataGramInfoCloseReason), "ContextDataGramInfoCloseReason/I");

  m_tree->Branch("ContextGemScalersElapsed", &(m_ntuple.m_contextGemScalersElapsed), "ContextGemScalersElapsed/l");
  m_tree->Branch("ContextGemScalersLivetime", &(m_ntuple.m_contextGemScalersLivetime), "ContextGemScalersLivetime/l");
  m_tree->Branch("ContextGemScalersPrescaled", &(m_ntuple.m_contextGemScalersPrescaled), "ContextGemScalersPrescaled/l");
  m_tree->Branch("ContextGemScalersDiscarded", &(m_ntuple.m_contextGemScalersDiscarded), "ContextGemScalersDiscarded/l");
  m_tree->Branch("ContextGemScalersSequence", &(m_ntuple.m_contextGemScalersSequence), "ContextGemScalersSequence/l");
  m_tree->Branch("ContextGemScalersDeadzone", &(m_ntuple.m_contextGemScalersDeadzone), "ContextGemScalersDeadzone/l");

  m_tree->Branch("ContextLsfTimeTimeToneCurrentIncomplete", &(m_ntuple.m_contextLsfTimeTimeToneCurrentIncomplete), "ContextLsfTimeTimeToneCurrentIncomplete/i");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentTimeSecs", &(m_ntuple.m_contextLsfTimeTimeToneCurrentTimeSecs), "ContextLsfTimeTimeToneCurrentTimeSecs/i");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentFlywheeling", &(m_ntuple.m_contextLsfTimeTimeToneCurrentFlywheeling), "ContextLsfTimeTimeToneCurrentFlywheeling/i");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentFlagsValid", &(m_ntuple.m_contextLsfTimeTimeToneCurrentFlagsValid), "ContextLsfTimeTimeToneCurrentFlagsValid/I");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentIsSourceGps", &(m_ntuple.m_contextLsfTimeTimeToneCurrentIsSourceGps), "ContextLsfTimeTimeToneCurrentIsSourceGps/I");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentMissingCpuPps", &(m_ntuple.m_contextLsfTimeTimeToneCurrentMissingCpuPps), "ContextLsfTimeTimeToneCurrentMissingCpuPps/I");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentMissingLatPps", &(m_ntuple.m_contextLsfTimeTimeToneCurrentMissingLatPps), "ContextLsfTimeTimeToneCurrentMissingLatPps/I");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentMissingTimeTone", &(m_ntuple.m_contextLsfTimeTimeToneCurrentMissingTimeTone), "ContextLsfTimeTimeToneCurrentMissingTimeTone/I");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentEarlyEvent", &(m_ntuple.m_contextLsfTimeTimeToneCurrentEarlyEvent), "ContextLsfTimeTimeToneCurrentEarlyEvent/I");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentGemTimeHacks", &(m_ntuple.m_contextLsfTimeTimeToneCurrentGemTimeHacks), "ContextLsfTimeTimeToneCurrentGemTimeHacks/i");
  m_tree->Branch("ContextLsfTimeTimeToneCurrentGemTimeTicks", &(m_ntuple.m_contextLsfTimeTimeToneCurrentGemTimeTicks), "ContextLsfTimeTimeToneCurrentGemTimeTicks/i");

  m_tree->Branch("ContextLsfTimeTimeTonePreviousIncomplete", &(m_ntuple.m_contextLsfTimeTimeTonePreviousIncomplete), "ContextLsfTimeTimeTonePreviousIncomplete/i");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousTimeSecs", &(m_ntuple.m_contextLsfTimeTimeTonePreviousTimeSecs), "ContextLsfTimeTimeTonePreviousTimeSecs/i");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousFlywheeling", &(m_ntuple.m_contextLsfTimeTimeTonePreviousFlywheeling), "ContextLsfTimeTimeTonePreviousFlywheeling/i");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousFlagsValid", &(m_ntuple.m_contextLsfTimeTimeTonePreviousFlagsValid), "ContextLsfTimeTimeTonePreviousFlagsValid/I");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousIsSourceGps", &(m_ntuple.m_contextLsfTimeTimeTonePreviousIsSourceGps), "ContextLsfTimeTimeTonePreviousIsSourceGps/I");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousMissingCpuPps", &(m_ntuple.m_contextLsfTimeTimeTonePreviousMissingCpuPps), "ContextLsfTimeTimeTonePreviousMissingCpuPps/I");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousMissingLatPps", &(m_ntuple.m_contextLsfTimeTimeTonePreviousMissingLatPps), "ContextLsfTimeTimeTonePreviousMissingLatPps/I");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousMissingTimeTone", &(m_ntuple.m_contextLsfTimeTimeTonePreviousMissingTimeTone), "ContextLsfTimeTimeTonePreviousMissingTimeTone/I");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousEarlyEvent", &(m_ntuple.m_contextLsfTimeTimeTonePreviousEarlyEvent), "ContextLsfTimeTimeTonePreviousEarlyEvent/I");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousGemTimeHacks", &(m_ntuple.m_contextLsfTimeTimeTonePreviousGemTimeHacks), "ContextLsfTimeTimeTonePreviousGemTimeHacks/i");
  m_tree->Branch("ContextLsfTimeTimeTonePreviousGemTimeTicks", &(m_ntuple.m_contextLsfTimeTimeTonePreviousGemTimeTicks), "ContextLsfTimeTimeTonePreviousGemTimeTicks/i");

  m_tree->Branch("ContextLsfTimeTimeTicks",&(m_ntuple.m_contextLsfTimeTimeTicks),"ContextLsfTimeTimeTicks/i");

  m_tree->Branch("ContextLsfTimeHackHacks",&(m_ntuple.m_contextLsfTimeTimeHackHacks),"ContextLsfTimeHackHacks/i");
  m_tree->Branch("ContextLsfTimeHackTicks",&(m_ntuple.m_contextLsfTimeTimeHackTicks),"ContextLsfTimeHackTicks/i");


  m_tree->Branch("ContextRunType", &(m_ntuple.m_contextRunType), "ContextRunType/I");

  // OBF:
  m_tree->Branch("ObfPassedGamma", &(m_ntuple.m_obfPassedGamma), "ObfPassedGamma/I");
  m_tree->Branch("ObfPassedMip", &(m_ntuple.m_obfPassedMip), "ObfPassedMip/I");
  m_tree->Branch("ObfPassedHFC", &(m_ntuple.m_obfPassedHFC), "ObfPassedHFC/I");
  m_tree->Branch("ObfPassedDFC", &(m_ntuple.m_obfPassedDFC), "ObfPassedDFC/I");


  // GEM information:
  m_tree->Branch("GemConditionsWord", &(m_ntuple.m_gemConditionsWord), "GemConditionsWord/I");
  m_tree->Branch("GemTkrVector", &(m_ntuple.m_gemTkrVector), "GemTkrVector[16]/I");
  m_tree->Branch("GemRoiVector", &(m_ntuple.m_gemRoiVector), "GemRoiVector[16]/I");
  m_tree->Branch("GemCalLeVector", &(m_ntuple.m_gemCalLeVector), "GemCalLeVector[16]/I");
  m_tree->Branch("GemCalHeVector", &(m_ntuple.m_gemCalHeVector), "GemCalHeVector[16]/I");
  m_tree->Branch("GemCnoVector", &(m_ntuple.m_gemCnoVector), "GemCnoVector[12]/I");
  m_tree->Branch("GemLiveTime", &(m_ntuple.m_gemLiveTime), "GemLiveTime/i");
  m_tree->Branch("GemTriggerTime", &(m_ntuple.m_gemTriggerTime), "GemTriggerTime/i");
  m_tree->Branch("GemDeltaEventTime", &(m_ntuple.m_gemDeltaEventTime), "GemDeltaEventTime/i");
  m_tree->Branch("GemOnePpsSeconds", &(m_ntuple.m_gemOnePpsSeconds), "GemOnePpsSeconds/i");
  m_tree->Branch("GemOnePpsTime", &(m_ntuple.m_gemOnePpsTime), "GemOnePpsTime/i");
  m_tree->Branch("GemPrescaled", &(m_ntuple.m_gemPrescaled), "GemPrescaled/i");
  m_tree->Branch("GemDiscarded", &(m_ntuple.m_gemDiscarded), "GemDiscarded/i");
  m_tree->Branch("GemCondArrivalTimeWord",&(m_ntuple.m_gemCondArrivalTimeWord), "GemCondArrivalTimeWord/i");
  m_tree->Branch("GemCondArrivalTimeExt",&(m_ntuple.m_gemCondArrivalTimeExt), "GemCondArrivalTimeExt/i");
  m_tree->Branch("GemCondArrivalTimeCno",&(m_ntuple.m_gemCondArrivalTimeCno), "GemCondArrivalTimeCno/i");
  m_tree->Branch("GemCondArrivalTimeCalLe",&(m_ntuple.m_gemCondArrivalTimeCalLe), "GemCondArrivalTimeCalLe/i");
  m_tree->Branch("GemCondArrivalTimeCalHe",&(m_ntuple.m_gemCondArrivalTimeCalHe), "GemCondArrivalTimeCalHe/i");
  m_tree->Branch("GemCondArrivalTimeTkr",&(m_ntuple.m_gemCondArrivalTimeTkr), "GemCondArrivalTimeTkr/i");
  m_tree->Branch("GemCondArrivalTimeRoi",&(m_ntuple.m_gemCondArrivalTimeRoi), "GemCondArrivalTimeRoi/i");
  m_tree->Branch("GemDeltaWindowOpenTime",&(m_ntuple.m_gemDeltaWindowOpenTime), "GemDeltaWindowOpenTime/i");
  m_tree->Branch("GemDeadZone",&(m_ntuple.m_gemDeadZone), "GemDeadZone/i");
  m_tree->Branch("GemAcdTilesXzp", &(m_ntuple.m_gemAcdTilesXzp), "GemAcdTilesXzp/i");
  m_tree->Branch("GemAcdTilesXzm", &(m_ntuple.m_gemAcdTilesXzm), "GemAcdTilesXzm/i");
  m_tree->Branch("GemAcdTilesYzp", &(m_ntuple.m_gemAcdTilesYzp), "GemAcdTilesYzp/i");
  m_tree->Branch("GemAcdTilesYzm", &(m_ntuple.m_gemAcdTilesYzm), "GemAcdTilesYzm/i");
  m_tree->Branch("GemAcdTilesXy", &(m_ntuple.m_gemAcdTilesXy), "GemAcdTilesXy/i");
  m_tree->Branch("GemAcdTilesRbn", &(m_ntuple.m_gemAcdTilesRbn), "GemAcdTilesRbn/i");
  m_tree->Branch("GemAcdTilesNa", &(m_ntuple.m_gemAcdTilesNa), "GemAcdTilesNa/i");


  // TME diagnostic information:
  m_tree->Branch("DigiTriRowBits",&(m_ntuple.m_digiTriRowBits),"DigiTriRowBits[16]/i");
  m_tree->Branch("TrgReqTriRowBits",&(m_ntuple.m_trgReqTriRowBits),"TrgReqTriRowBits[16]/i");
  m_tree->Branch("TkrReq", &(m_ntuple.m_tkrReq), "TkrReq[16][18][2][2]/i");
  m_tree->Branch("TkrTp", &(m_ntuple.m_tpTkr), "TkrTp[16][8]/i");
  m_tree->Branch("CalReq", &(m_ntuple.m_calReq), "CalReq[16][8][2]/i");
  m_tree->Branch("CalTp", &(m_ntuple.m_tpCal), "CalTp[16][8]/i");


  // Contribution lenghts:
  m_tree->Branch("DiagLength", &(m_ntuple.m_diagLength), "DiagLength[16]/i");
  m_tree->Branch("TemLength", &(m_ntuple.m_temLength), "TemLength[16]/i");
  m_tree->Branch("GemLength", &(m_ntuple.m_gemLength), "GemLength/i");
  m_tree->Branch("OswLength", &(m_ntuple.m_oswLength), "OswLength/i");
  m_tree->Branch("AemLength", &(m_ntuple.m_aemLength), "AemLength/i");
  m_tree->Branch("ErrLength", &(m_ntuple.m_errLength), "ErrLength[16]/i");


  // ACD digi:
  m_tree->Branch("AcdNumDigis", &(m_ntuple.m_acdNumDigis), "AcdNumDigis/I");
  m_tree->Branch("AcdPha", &(m_ntuple.m_acdPha), "AcdPha[604][2]/I");
  m_tree->Branch("AcdHitMap", &(m_ntuple.m_acdHitMap), "AcdHitMap[604][2]/I");
  m_tree->Branch("AcdRange", &(m_ntuple.m_acdRange), "AcdRange[604][2]/I");
  m_tree->Branch("AcdOddParityError", &(m_ntuple.m_acdOddParityError), "AcdOddParityError[604][2]/I");
  m_tree->Branch("AcdHeaderParityError", &(m_ntuple.m_acdHeaderParityError), "AcdHeaderParityError[604][2]/I");
  m_tree->Branch("AcdLowDisc", &(m_ntuple.m_acdLowDisc), "AcdLowDisc[604][2]/I");
  m_tree->Branch("Acd10Ids", &(m_ntuple.m_acd10Ids), "Acd10Ids[10]/I");
  m_tree->Branch("AcdTileNumber", &(m_ntuple.m_acdTileNumber), "AcdTileNumber[604]/I");
  m_tree->Branch("AcdMCEnergy", &(m_ntuple.m_acdMCEnergy), "AcdMCEnergy[604]/F");

  // NA ACD digis:
  m_tree->Branch("AcdNaPha", &(m_ntuple.m_acdNaPha), "AcdNaPha[11][2]/I");
  m_tree->Branch("AcdNaHitMap", &(m_ntuple.m_acdNaHitMap), "AcdNaHitMap[11][2]/I");
  m_tree->Branch("AcdNaRange", &(m_ntuple.m_acdNaRange), "AcdNaRange[11][2]/I");
  m_tree->Branch("AcdNaOddParityError", &(m_ntuple.m_acdNaOddParityError), "AcdNaOddParityError[11][2]/I");
  m_tree->Branch("AcdNaHeaderParityError", &(m_ntuple.m_acdNaHeaderParityError), "AcdNaHeaderParityError[11][2]/I");
  m_tree->Branch("AcdNaLowDisc", &(m_ntuple.m_acdNaLowDisc), "AcdNaLowDisc[11][2]/I");

  // ACD recon:
  m_tree->Branch("AcdTileMCEnergy", &(m_ntuple.m_acdEnergy),"AcdTileMCEnergy/F");
  m_tree->Branch("AcdDoca", &(m_ntuple.m_acdDoca),"AcdDoca/F");
  m_tree->Branch("AcdTileCount", &(m_ntuple.m_acdTileCount),"AcdTileCount/I");
  m_tree->Branch("AcdActiveDist", &(m_ntuple.m_acdActiveDist),"AcdActiveDist/F");
  m_tree->Branch("AcdMinDocaId", &(m_ntuple.m_acdMinDocaId),"AcdMinDocaId/I");
  m_tree->Branch("AcdRibbonMCEnergy", &(m_ntuple.m_acdRibbonMCEnergy),"AcdRibbonMCEnergy/F");
  m_tree->Branch("AcdRibbonCount", &(m_ntuple.m_acdRibbonCount),"AcdRibbonCount/I");
  m_tree->Branch("AcdRibbonActiveDist", &(m_ntuple.m_acdRibbonActiveDist),"AcdRibbonActiveDist/F");
  m_tree->Branch("AcdMaxActiveDistId", &(m_ntuple.m_acdMaxActiveDistId),"AcdMaxActiveDistId/I");
  m_tree->Branch("AcdRibbonActiveDistId", &(m_ntuple.m_acdRibbonActiveDistId),"AcdRibbonActiveDistId/I");
  m_tree->Branch("AcdCornerDoca", &(m_ntuple.m_acdCornerDoca),"AcdCornerDoca/F");

  // Eric's ACD-TKR intersection stuff:
  m_tree->Branch("AcdNumTkrIntSec", &(m_ntuple.m_acdNumTkrIntersection),"AcdNumTkrIntSec/I");
  m_tree->Branch("AcdTkrIntSecTileId", &(m_ntuple.m_acdTkrIntersectionTileId),"AcdTkrIntSecTileId[20]/I");
  m_tree->Branch("AcdTkrIntSecTkrIndex", &(m_ntuple.m_acdTkrIntersectionTkrIndex),"AcdTkrIntSecTkrIndex[20]/I");
  m_tree->Branch("AcdTkrIntSecGlobalX", &(m_ntuple.m_acdTkrIntersectionGlobalX),"AcdTkrIntSecGlobalX[20]/F");
  m_tree->Branch("AcdTkrIntSecGlobalY", &(m_ntuple.m_acdTkrIntersectionGlobalY),"AcdTkrIntSecGlobalY[20]/F");
  m_tree->Branch("AcdTkrIntSecGlobalZ", &(m_ntuple.m_acdTkrIntersectionGlobalZ),"AcdTkrIntSecGlobalZ[20]/F");
  m_tree->Branch("AcdTkrIntSecLocalX", &(m_ntuple.m_acdTkrIntersectionLocalX),"AcdTkrIntSecLocalX[20]/F");
  m_tree->Branch("AcdTkrIntSecLocalY", &(m_ntuple.m_acdTkrIntersectionLocalY),"AcdTkrIntSecLocalY[20]/F");
  m_tree->Branch("AcdTkrIntSecLocalXXCov", &(m_ntuple.m_acdTkrIntersectionLocalXXCov),"AcdTkrIntSecLocalXXCov[20]/F");
  m_tree->Branch("AcdTkrIntSecLocalYYCov", &(m_ntuple.m_acdTkrIntersectionLocalYYCov),"AcdTkrIntSecLocalYYCov[20]/F");
  m_tree->Branch("AcdTkrIntSecLocalXYCov", &(m_ntuple.m_acdTkrIntersectionLocalXYCov),"AcdTkrIntSecLocalXYCov[20]/F");
  m_tree->Branch("AcdTkrIntSecArcLengthToIntSec", &(m_ntuple.m_acdTkrIntersectionArcLengthToIntersection),"AcdTkrIntSecArcLengthToIntSec[20]/F");
  m_tree->Branch("AcdTkrIntSecPathLengthInTile", &(m_ntuple.m_acdTkrIntersectionPathLengthInTile),"AcdTkrIntSecPathLengthInTile[20]/F");
  m_tree->Branch("AcdTkrIntSecTileHit", &(m_ntuple.m_acdTkrIntersectionTileHit),"AcdTkrIntSecTileHit[20]/I");

  // ACD MIPs:
  m_tree->Branch("AcdMips", &(m_ntuple.m_acdMips),"AcdMips[604][2]/F");
  m_tree->Branch("AcdMipsPha", &(m_ntuple.m_acdMipsPha),"AcdMipsPha[604][2]/I");
  m_tree->Branch("AcdMipsFlag", &(m_ntuple.m_acdMipsFlag),"AcdMipsFlag[604][2]/I");

  m_tree->Branch("AcdMipsMax", &(m_ntuple.m_acdMipsMax),"AcdMipsMax/F");
  m_tree->Branch("AcdMipsMaxTileID", &(m_ntuple.m_acdMipsMaxTileID),"AcdMipsMaxTileID/I");
  m_tree->Branch("AcdMipsMaxPmt", &(m_ntuple.m_acdMipsMaxPmt),"AcdMipsMaxPmt/I");
  m_tree->Branch("AcdMipsSum", &(m_ntuple.m_acdMipsSum),"AcdMipsSum/F");

  

  // ACD POCA:
  m_tree->Branch("AcdPocaDoca", &(m_ntuple.m_acdPocaDoca),"AcdPocaDoca[2][2]/F");
  m_tree->Branch("AcdPocaDocaErr", &(m_ntuple.m_acdPocaDocaErr),"AcdPocaDocaErr[2][2]/F");
  m_tree->Branch("AcdPocaDocaRegion", &(m_ntuple.m_acdPocaDocaRegion),"AcdPocaDocaRegion[2][2]/F");
  m_tree->Branch("AcdPocaX", &(m_ntuple.m_acdPocaX),"AcdPocaX[2][2]/F");
  m_tree->Branch("AcdPocaY", &(m_ntuple.m_acdPocaY),"AcdPocaY[2][2]/F");
  m_tree->Branch("AcdPocaZ", &(m_ntuple.m_acdPocaZ),"AcdPocaZ[2][2]/F");
  m_tree->Branch("AcdPocaDirX", &(m_ntuple.m_acdPocaDirX),"AcdPocaDirX[2][2]/F");
  m_tree->Branch("AcdPocaDirY", &(m_ntuple.m_acdPocaDirY),"AcdPocaDirY[2][2]/F");
  m_tree->Branch("AcdPocaDirZ", &(m_ntuple.m_acdPocaDirZ),"AcdPocaDirZ[2][2]/F");
  m_tree->Branch("AcdPocaTileID", &(m_ntuple.m_acdPocaTileID),"AcdPocaTileID[2][2]/I");
  m_tree->Branch("AcdPocaTrackID", &(m_ntuple.m_acdPocaTrackID),"AcdPocaTrackID[2][2]/I");
  m_tree->Branch("AcdPocaNbrTrack1", &(m_ntuple.m_acdPocaNbrTrack1),"AcdPocaNbrTrack1/I");
  m_tree->Branch("AcdPocaNbrTrack2", &(m_ntuple.m_acdPocaNbrTrack2),"AcdPocaNbrTrack2/I");


  // ACD Gap POCA:
  m_tree->Branch("AcdGapPocaDoca", &(m_ntuple.m_acdGapPocaDoca),"AcdGapPocaDoca[2][2]/F");
  m_tree->Branch("AcdGapPocaTileID", &(m_ntuple.m_acdGapPocaTileID),"AcdGapPocaTileID[2][2]/I");
  m_tree->Branch("AcdGapPocaGapIndex", &(m_ntuple.m_acdGapPocaGapIndex),"AcdGapPocaGapIndex[2][4]/I");
  m_tree->Branch("AcdGapPocaGapType", &(m_ntuple.m_acdGapPocaGapType),"AcdGapPocaGapType[2][4]/I");
  m_tree->Branch("AcdGapPocaTrackID", &(m_ntuple.m_acdGapPocaTrackID),"AcdGapPocaTrackID[2][2]/I");
  m_tree->Branch("AcdGapPocaNbrTrack1", &(m_ntuple.m_acdGapPocaNbrTrack1),"AcdGapPocaNbrTrack1/I");
  m_tree->Branch("AcdGapPocaNbrTrack2", &(m_ntuple.m_acdGapPocaNbrTrack2),"AcdGapPocaNbrTrack2/I");

  // Tkr Point:
  m_tree->Branch("AcdTkrPointX",&(m_ntuple.m_acdTkrPointX),"AcdTkrPointX[2]/F");
  m_tree->Branch("AcdTkrPointY",&(m_ntuple.m_acdTkrPointY),"AcdTkrPointY[2]/F");
  m_tree->Branch("AcdTkrPointZ",&(m_ntuple.m_acdTkrPointZ),"AcdTkrPointZ[2]/F");

  m_tree->Branch("AcdTkrPointFace",&(m_ntuple.m_acdTkrPointFace),"AcdTkrPointFace[2]/I");

  m_tree->Branch("CCSDSTime", &(m_ntuple.m_cCSDStime),"CCSDSTime/D");
  m_tree->Branch("CCSDSapID", &(m_ntuple.m_cCSDSapID),"CCSDSapID/I");
  m_tree->Branch("CCSDSscID", &(m_ntuple.m_cCSDSscID),"CCSDSscID/I");


}
