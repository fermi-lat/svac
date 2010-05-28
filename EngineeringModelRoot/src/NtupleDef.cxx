#include "NtupleDef.h"

const char* NtupleDef::gRootNtupleDefStr = "RunID/i:EventID/i:McSeqNo/i:McId/I:McTotalEnergy/F:McX0/F:McY0/F:McZ0/F:McXDir/F:McYDir/F:McZDir/F:McConvPointX/F:McConvPointY/F:McConvPointZ/F:TkrNumDigis/I:TkrNumStrips[16][18][2]/I:tot[16][18][2][2]/I:totCorrL[16][18][2][2]/F:totCorrQ[16][18][2][2]/F:TkrDepositEne[16][18][2]/F:TkrNumClusters[16][18][2]/I:TkrNumTracks/I:TkrNumVertices/I:VtxX0/F:VtxY0/F:VtxZ0/F:VtxXDir/F:VtxYDir/F:VtxZDir/F:Vtx1Energy/F:Vtx1NumTkrs/I:Tkr1NumHits/I:Tkr2NumHits/I:Tkr1Chisq/F:Tkr2Chisq/F:Tkr1ChisqS/F:Tkr2ChisqS/F:Tkr1Rms/F:Tkr2Rms/F:Tkr1KalThetaMs/F:Tkr2KalThetaMs/F:Tkr1KalEne/F:Tkr2KalEne/F:Tkr1EndPos[3]/F:Tkr1EndDir[3]/F:Tkr2EndPos[3]/F:Tkr2EndDir[3]/F:CalEneSum/F:McCalEneSum/F:GltWord/i:CalXEcentr/F:CalYEcentr/F:CalZEcentr/F:McTkr1Ene/F:McTkr2Ene/F:EvtTime/D:McConvAngle/F:TkrTopTot[16]/F:Tkr1ConvTot/F:CalXtalEne[16][8][12][2]/F:CalMaxEne/F:CalNumHit[16]/I:EvtSecond/i:EvtNanoSecond/i:EvtUpperTime/i:EvtLowerTime/i:EvtTimeSeconds/i:CalTp[16][8]/i:TkrTp[16][8]/i:EvtSummary/i:GemConditionsWord/I:GemTkrVector[16]/I:GemRoiVector[16]/I:GemCalLeVector[16]/I:GemCalHeVector[16]/I:GemCnoVector[12]/I:GemLiveTime/i:GemTriggerTime/i:GemDeltaEventTime/i:GemOnePpsSeconds/i:GemOnePpsTime/i:GemPrescaled/i:GemDiscarded/i:GemAcdTilesXzp/i:GemAcdTilesXzm/i:GemAcdTilesYzp/i:GemAcdTilesYzM/i:GemAcdTilesXy/i:GemAcdTilesRbn/i:GemAcdTilesNa/i:GemCondArrivalTimeWord/i:GemCondArrivalTimeExt/i:GemCondArrivalTimeCno/i:GemCondArrivalTimeCalLe/i:GemCondArrivalTimeCalHe/i:GemCondArrivalTimeTkr/i:GemCondArrivalTimeRoi/i:GemDeltaWindowOpenTime/i:GemDeadZone/i:DigiTriRowBits[16]/i:TrgReqTriRowBits[16]/i:TemLength[16]/i:GemLength/i:OswLength/i:AemLength/i:ErrLength[16]/i:DiagLength[16]/i:EventFlags/i:TkrReq[16][18][2][2]/i:CalReq[16][8][2]/i:CalLogAccepts[16][8][2]/i:CalXtalPos[16][8][12][3]/F:TkrTotalHits[16]/i:TkrTotalClusters[16]/i:EventSize/i:AcdNumDigis/I:AcdPha[604][2]/I:AcdHitMap[604][2]/I:AcdRange[604][2]/I:AcdOddParityError[604][2]/I:AcdHeaderParityError[604][2]/I:AcdLowDisc[604][2]/I:AcdTileNumber[604]/I:AcdMCEnergy[604]/F:AcdEnergy/F:AcdDoca/F:AcdGammaDoca/F:AcdTileCount/I:AcdActiveDist/F:AcdMinDocaId/I:Acd10Ids[10]/I:AcdRibbonMCEnergy/F:AcdRibbonCount/I:AcdRibbonActiveDist/F:AcdMaxActiveDistId/I:AcdRibbonActiveDistId/I:AcdNumTrkIntSec/I:AcdTkrIntSecTileId[10]/I:AcdTkrIntSecTkrIndex[10]/I:AcdTkrIntSecGlobalX[10]/F:AcdTkrIntSecGlobalY[10]/F:AcdTkrIntSecGlobalZ[10]/F:AcdTkrIntSecLocalX[10]/F:AcdTkrIntSecLocalY[10]/F:AcdTkrIntSecLocalXXCov[10]/F:AcdTkrIntSecLocalYYCov[10]/F:AcdTkrIntSecLocalXYCov[10]/F:AcdTkrIntSecArcLengthToIntSec[10]/F:AcdTkrIntSecPathLengthInTile[10]/F:AcdTkrIntSecTileHit[10]/I";


NtupleDef::NtupleDef() 
{
  reset();
}

void NtupleDef::reset()
{
  m_runId          = 0; 
  m_eventId        = 0; 
  m_seqNo          = 0;
  m_eventSize      = -9999;
  m_parId          = -9999;
  m_mcEnergy       = 0.;
  m_nTkrDigis      = 0;
  m_nTkrTracks     = 0; 
  m_nTkrVertices   = 0;
  m_calEnergy      = -9999;
  m_mcCalEnergy    = 0.;
  m_fitTotalEnergy = -9999.;
  m_trigger        = 0;
  m_timeStamp      = -9999;
  m_convAngle      = -9999;
  m_convTot        = -9999;
  m_vtxTrks        = -9999;
  m_maxCalEnergy   = -9999;
  m_ebfSecond      = 0;
  m_ebfNanoSecond  = 0;
  m_upperTime      = 0;
  m_lowerTime      = 0;
  m_timeSeconds    = 0;
  m_summaryWord    = 0;

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
  m_gemDeadZone             = 0;
  
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
  
  m_eventFlags = 0;

  for(int iCno = 0; iCno < 12; iCno++){
    m_gemCnoVector [iCno] = 0;
  }


  for (int iAcdTile=0; iAcdTile != g_nAcdTile; ++iAcdTile) {
    m_acdPha[iAcdTile][0]               = -9999;
    m_acdPha[iAcdTile][1]               = -9999;
    m_acdHitMap[iAcdTile][0]            = -9999;
    m_acdHitMap[iAcdTile][1]            = -9999;
    m_acdRange[iAcdTile][0]             = -9999;
    m_acdRange[iAcdTile][1]             = -9999;
    m_acdOddParityError[iAcdTile][0]    = -9999;
    m_acdOddParityError[iAcdTile][1]    = -9999;
    m_acdHeaderParityError[iAcdTile][0] = -9999;
    m_acdHeaderParityError[iAcdTile][1] = -9999;
    m_acdLowDisc[iAcdTile][0]           = -9999;
    m_acdLowDisc[iAcdTile][1]           = -9999;
    m_acdTileNumber[iAcdTile]           = -9999;
    m_acdMCEnergy[iAcdTile]             = -9999.0;
  }

  m_acdNumDigis = 0;

  m_acdEnergy     = -9999.0;
  m_acdDoca       = -9999.0;
  m_acdGammaDoca  = -9999.0;
  m_acdActiveDist = -9999.0;
  m_acdTileCount  = -9999;
  m_acdMinDocaId  = -9999;

  m_acdRibbonActiveDist   = -9999.0;
  m_acdRibbonMCEnergy     = -9999.0;
  m_acdRibbonCount        = -9999;
  m_acdMaxActiveDistId    = -9999;
  m_acdRibbonActiveDistId = -9999;


  for (int iLoop=0; iLoop != 10; ++iLoop) {
    m_acd10Ids[iLoop] = -9999;
  }


  // Eric's ACD-TKR intersection stuff:
  m_acdNumTkrIntersection = -9999;

  for (int iAcdTkr=0; iAcdTkr < 10; iAcdTkr++) {
    m_acdTkrIntersectionTileId[iAcdTkr]                  = -9999;
    m_acdTkrIntersectionTkrIndex[iAcdTkr]                = -9999;
    m_acdTkrIntersectionGlobalX[iAcdTkr]                 = -9999.0;
    m_acdTkrIntersectionGlobalY[iAcdTkr]                 = -9999.0;
    m_acdTkrIntersectionGlobalZ[iAcdTkr]                 = -9999.0;
    m_acdTkrIntersectionLocalX[iAcdTkr]                  = -9999,0;
    m_acdTkrIntersectionLocalY[iAcdTkr]                  = -9999,0;
    m_acdTkrIntersectionLocalXXCov[iAcdTkr]              = -9999.0;
    m_acdTkrIntersectionLocalYYCov[iAcdTkr]              = -9999.0;
    m_acdTkrIntersectionLocalXYCov[iAcdTkr]              = -9999.0;
    m_acdTkrIntersectionArcLengthToIntersection[iAcdTkr] = -9999.0;
    m_acdTkrIntersectionPathLengthInTile[iAcdTkr]        = -9999.0;
    m_acdTkrIntersectionTileHit[iAcdTkr]                 = -9999;
  }





  for(int iTower = 0; iTower != g_nTower; ++iTower){

    m_errLength[iTower]  = 0;
    m_diagLength[iTower] = 0;

    m_nCrystalHit[iTower] = 0;
    m_topTot[iTower] = 0;

    m_gemTkrVector[iTower] = 0;
    m_gemRoiVector[iTower] = 0;
    m_gemCalLeVector[iTower] = 0;
    m_gemCalHeVector[iTower] = 0;

    m_temLength[iTower] = 0;

    m_digiTriRowBits[iTower] = 0;
    m_trgReqTriRowBits[iTower] = 0;

    m_totalStripHits[iTower] = 0;
    m_totalClusters[iTower] = 0;

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

	m_xtalPos[iTower][iCalLayer][iCol][0] = -9999;
	m_xtalPos[iTower][iCalLayer][iCol][1] = -9999;
	m_xtalPos[iTower][iCalLayer][iCol][2] = -9999;

	for(int iFace = 0; iFace != g_nFace; ++iFace){
	  m_calReq[iTower][iCalLayer][iFace] = 0;
	  m_calLogAccepts[iTower][iCalLayer][iFace] = 0;
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
