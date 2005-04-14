#include "NtupleDef.h"

const char* NtupleDef::gRootNtupleDefStr = "Run/I:Event_ID/I:McSeqNo/I:McId/I:McTotalEnergy/F:McX0/F:McY0/F:McZ0/F:McXDir/F:McYDir/F:McZDir/F:McConvPointX/F:McConvPointY/F:McConvPointZ/F:TkrNumDigis/I:TkrNumStrips[16][18][2]/I:tot[16][18][2][2]/I:totCorrL[16][18][2][2]/F:totCorrQ[16][18][2][2]/F:TkrDepositEne[16][18][2]/F:TkrNumClusters[16][18][2]/I:TkrNumTracks/I:TkrNumVertices/I:VtxX0/F:VtxY0/F:VtxZ0/F:VtxXDir/F:VtxYDir/F:VtxZDir/F:EvtEnergySumOpt/F:Vtx1NumTkrs/I:Tkr1NumHits/I:Tkr2NumHits/I:Tkr1Chisq/F:Tkr2Chisq/F:Tkr1ChisqS/F:Tkr2ChisqS/F:Tkr1Rms/F:Tkr2Rms/F:Tkr1KalThetaMs/F:Tkr2KalThetaMs/F:Tkr1KalEne/F:Tkr2KalEne/F:CalEneSum/F:McCalEneSum/F:GltWord/I:CalXEcentr/F:CalYEcentr/F:CalZEcentr/F:McTkr1Ene/F:McTkr2Ene/F:EvtTime/D:McConvAngle/F:TkrTopTot[16]/F:Tkr1ConvTot/F:CalXtalEne[16][8][12]/F:CalMaxEne/F:CalNumHit[16]/I:EvtSecond/I:EvtNanoSecond/I:EvtUpperTime/I:EvtLowerTime/I:CalTp[16][8]/I:TkrTp[16][8]/I:EvtSummary/I:TkrReq[16][18][2][2]/I:CalReq[16][8][2]";

NtupleDef::NtupleDef() 
{
  reset();
}

void NtupleDef::reset()
{
  m_runId = -9999; 
  m_eventId = -9999; 
  m_seqNo = -9999;
  m_parId = -9999;
  m_mcEnergy = 0.;
  m_nTkrDigis = 0;
  m_nTkrTracks = 0; 
  m_nTkrVertices = 0;
  m_calEnergy = -9999;
  m_mcCalEnergy = 0.;
  m_fitTotalEnergy = -9999.;
  m_trigger = 0;
  m_timeStamp = -9999;
  m_convAngle = -9999;
  m_convTot = -9999;
  m_vtxTrks = -9999;
  m_maxCalEnergy = -9999;
  m_ebfSecond = -9999;
  m_ebfNanoSecond = -9999;
  m_upperTime = -9999;
  m_lowerTime = -9999;
  m_summaryWord = 0;

  for(int iTower = 0; iTower != g_nTower; ++iTower){

    m_nCrystalHit[iTower] = 0;
    m_topTot[iTower] = 0;

    for(int iLayer = 0; iLayer != g_nTkrLayer; ++iLayer){
      for(int iView = 0; iView != g_nView; ++iView){

	m_nStrips[iTower][iLayer][iView] = 0;
	m_depositEne[iTower][iLayer][iView] = 0;
	m_nTkrClusters[iTower][iLayer][iView] = 0;

	for(int iTot = 0; iTot != g_nTot; ++iTot){
	  m_tot[iTower][iLayer][iView][iTot] = -9999;
	  m_totCorrLinear[iTower][iLayer][iView][iTot] = -9999;
	  m_totCorrQuad[iTower][iLayer][iView][iTot] = -9999;
	  m_tkrReq[iTower][iLayer][iView][iTot] = 0;
	}
      }
    }

    for(int iCalLayer = 0; iCalLayer != g_nCalLayer; ++iCalLayer) {
      for(int iCol = 0; iCol != g_nCol; ++iCol) {

	m_xtalEne[iTower][iCalLayer][iCol] = 0;

	for(int iFace = 0; iFace != g_nFace; ++iFace){
	  m_calReq[iTower][iCalLayer][iFace] = 0;
	}
      }
    }

    for(int iTP = 0; iTP != g_nTP; ++iTP) {
      m_tpTkr[iTower][iTP] = 0;
      m_tpCal[iTower][iTP] = 0;
    }

  }

  for(int i = 0; i != 3; ++i) {
    m_startPos[i] = -9999.;
    m_startDir[i] = -9999.;
    m_convPos[i] = -9999.;
    m_pos[i] = -9999.;
    m_dir[i] = -9999.;
    m_calPos[i] = -9999.;
  }

  for(int i = 0; i != 2; ++i) {
    m_nFit[i] = 0;
    m_chi2[i] = -9999.;
    m_chi2Smooth[i] = -9999.;
    m_rms[i] = -9999.;
    m_msAngle[i] = -9999.;
    m_tkrEnergy[i] = -9999.;
    m_pairEne[i] = -9999;
  }

}
