#include "NtupleDef.h"

const char* NtupleDef::gRootNtupleDefStr = "Run/i:Event_ID/i:McSeqNo/i:McId/I:McTotalEnergy/F:McX0/F:McY0/F:McZ0/F:McXDir/F:McYDir/F:McZDir/F:McConvPointX/F:McConvPointY/F:McConvPointZ/F:TkrNumDigis/I:TkrNumStrips[16][18][2]/I:tot[16][18][2][2]/I:totCorrL[16][18][2][2]/F:totCorrQ[16][18][2][2]/F:TkrDepositEne[16][18][2]/F:TkrNumClusters[16][18][2]/I:TkrNumTracks/I:TkrNumVertices/I:VtxX0/F:VtxY0/F:VtxZ0/F:VtxXDir/F:VtxYDir/F:VtxZDir/F:EvtEnergySumOpt/F:Vtx1NumTkrs/I:Tkr1NumHits/I:Tkr2NumHits/I:Tkr1Chisq/F:Tkr2Chisq/F:Tkr1ChisqS/F:Tkr2ChisqS/F:Tkr1Rms/F:Tkr2Rms/F:Tkr1KalThetaMs/F:Tkr2KalThetaMs/F:Tkr1KalEne/F:Tkr2KalEne/F:Tkr1EndPos[3]/F:Tkr1EndDir[3]/F:Tkr2EndPos[3]/F:Tkr2EndDir[3]/F:CalEneSum/F:McCalEneSum/F:GltWord/i:CalXEcentr/F:CalYEcentr/F:CalZEcentr/F:McTkr1Ene/F:McTkr2Ene/F:EvtTime/D:McConvAngle/F:TkrTopTot[16]/F:Tkr1ConvTot/F:CalXtalEne[16][8][12][2]/F:CalMaxEne/F:CalNumHit[16]/I:EvtSecond/i:EvtNanoSecond/i:EvtUpperTime/i:EvtLowerTime/i:CalTp[16][8]/i:TkrTp[16][8]/i:EvtSummary/i:GemConditionsWord/I:GemTkrVector[16]/I:GemRoiVector[16]/I:GemCalLeVector[16]/I:GemCalHeVector[16]/I:GemCnoVector[12]/I:GemLiveTime/i:GemTriggerTime/i:GemDeltaEventTime/i:GemOnePpsSeconds/i:GemOnePpsTime/i:GemPrescaled/i:GemDiscarded/i:GemAcdTilesXzp/i:GemAcdTilesXzm/i:GemAcdTilesYzp/i:GemAcdTilesYzM/i:GemAcdTilesXy/i:GemAcdTilesRbn/i:GemAcdTilesNa/i:GemCondArrivalTimeWord/i:GemCondArrivalTimeExt/i:GemCondArrivalTimeCno/i:GemCondArrivalTimeCalLe/i:GemCondArrivalTimeCalHe/i:GemCondArrivalTimeTkr/i:GemCondArrivalTimeRoi/i:GemDeltaWindowOpenTime/i:TrgTriRowBits[16]/i:TemLength[16]/i:GemLength/i:OswLength/i:AemLength/i:ErrLength/i:DiagLength/i:EventSequence/i:EventFlags/i:GoodEvent/I:TkrReq[16][18][2][2]/i:CalReq[16][8][2]/i";

NtupleDef::NtupleDef() 
{
  reset();
}

void NtupleDef::reset()
{
  m_runId = 0; 
  m_eventId = 0; 
  m_seqNo = 0;
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
  m_ebfSecond = 0;
  m_ebfNanoSecond = 0;
  m_upperTime = 0;
  m_lowerTime = 0;
  m_summaryWord = 0;

  m_gemConditionsWord       = 0;
  m_gemLiveTime             = 0;
  m_gemTriggerTime          = 0;
  m_gemDeltaEventTime       = 0;
  m_gemOnePpsSeconds        = 0;
  m_gemOnePpsTime           = 0;
  m_gemPrescaled            = 0;
  m_gemDiscarded            = 0;
  m_gemCondArrivalTimeWord  = 0;
  m_gemCondArrivalTimeExt   = 0;
  m_gemCondArrivalTimeCno   = 0;
  m_gemCondArrivalTimeCalLe = 0;
  m_gemCondArrivalTimeCalHe = 0;
  m_gemCondArrivalTimeTkr   = 0;
  m_gemCondArrivalTimeRoi   = 0;
  m_gemDeltaWindowOpenTime  = 0;
  
  m_gemAcdTilesXzp = 0;
  m_gemAcdTilesXzm = 0;
  m_gemAcdTilesYzp = 0;
  m_gemAcdTilesYzm = 0;
  m_gemAcdTilesXy  = 0;
  m_gemAcdTilesRbn = 0;
  m_gemAcdTilesNa  = 0;

  m_gemLength  = 0;
  m_oswLength  = 0;
  m_aemLength  = 0;
  m_errLength  = 0;
  m_diagLength = 0;
  
  m_eventSequence = 0;
  m_eventFlags    = 0;
  m_goodEvent     = 0; 

  for(int iCno = 0; iCno < 12; iCno++){
    m_gemCnoVector [iCno] = 0;
  }

  for(int iTower = 0; iTower != g_nTower; ++iTower){

    m_nCrystalHit[iTower] = 0;
    m_topTot[iTower] = 0;

    m_gemTkrVector[iTower] = 0;
    m_gemRoiVector[iTower] = 0;
    m_gemCalLeVector[iTower] = 0;
    m_gemCalHeVector[iTower] = 0;

    m_temLength[iTower] = 0;

    m_trgTriRowBits[iTower] = 0;

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
	for(int iFace = 0; iFace != g_nFace; ++iFace){
	  m_calReq[iTower][iCalLayer][iFace] = 0;
  	  m_xtalEne[iTower][iCalLayer][iCol][iFace] = 0.0;
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

  for(int i = 0; i != 3; ++i) {
    m_tkr1EndPos[i] = -9999.0;
    m_tkr2EndPos[i] = -9999.0;
    m_tkr1EndDir[i] = -9999.0;
    m_tkr2EndDir[i] = -9999.0;
  }

}
