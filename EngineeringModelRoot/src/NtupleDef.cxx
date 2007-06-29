#include "NtupleDef.h"

const char* NtupleDef::gRootNtupleDefStr = "RunID/i:EventID/i:McSeqNo/i:McId/I:McTotalEnergy/F:McX0/F:McY0/F:McZ0/F:McXDir/F:McYDir/F:McZDir/F:McConvPointX/F:McConvPointY/F:McConvPointZ/F:TkrNumDigis/I:TkrNumStrips[16][18][2]/I:tot[16][18][2][2]/I:totCorrL[16][18][2][2]/F:totCorrQ[16][18][2][2]/F:TkrDepositEne[16][18][2]/F:TkrNumClusters[16][18][2]/I:TkrNumTracks/I:TkrNumVertices/I:VtxX0/F:VtxY0/F:VtxZ0/F:VtxXDir/F:VtxYDir/F:VtxZDir/F:Vtx1Energy/F:Vtx1NumTkrs/I:Tkr1NumHits/I:Tkr2NumHits/I:Tkr1Chisq/F:Tkr2Chisq/F:Tkr1ChisqS/F:Tkr2ChisqS/F:Tkr1Rms/F:Tkr2Rms/F:Tkr1KalThetaMs/F:Tkr2KalThetaMs/F:Tkr1KalEne/F:Tkr2KalEne/F:Tkr1EndPos[3]/F:Tkr1EndDir[3]/F:Tkr2EndPos[3]/F:Tkr2EndDir[3]/F:CalEneSum/F:McCalEneSum/F:GltWord/i:CalXEcentr/F:CalYEcentr/F:CalZEcentr/F:McTkr1Ene/F:McTkr2Ene/F:EvtTime/D:McConvAngle/F:TkrTopTot[16]/F:Tkr1ConvTot/F:CalXtalEne[16][8][12][2]/F:CalMaxEne/F:CalNumHit[16]/I:EvtSecond/i:EvtNanoSecond/i:EvtUpperTime/i:EvtLowerTime/i:EvtTimeSeconds/i:CalTp[16][8]/i:TkrTp[16][8]/i:EvtSummary/i:GemConditionsWord/I:GemTkrVector[16]/I:GemRoiVector[16]/I:GemCalLeVector[16]/I:GemCalHeVector[16]/I:GemCnoVector[12]/I:GemLiveTime/i:GemTriggerTime/i:GemDeltaEventTime/i:GemOnePpsSeconds/i:GemOnePpsTime/i:GemPrescaled/i:GemDiscarded/i:GemAcdTilesXzp/i:GemAcdTilesXzm/i:GemAcdTilesYzp/i:GemAcdTilesYzM/i:GemAcdTilesXy/i:GemAcdTilesRbn/i:GemAcdTilesNa/i:GemCondArrivalTimeWord/i:GemCondArrivalTimeExt/i:GemCondArrivalTimeCno/i:GemCondArrivalTimeCalLe/i:GemCondArrivalTimeCalHe/i:GemCondArrivalTimeTkr/i:GemCondArrivalTimeRoi/i:GemDeltaWindowOpenTime/i:GemDeadZone/i:DigiTriRowBits[16]/i:TrgReqTriRowBits[16]/i:TemLength[16]/i:GemLength/i:OswLength/i:AemLength/i:ErrLength[16]/i:DiagLength[16]/i:EventFlags/i:TkrReq[16][18][2][2]/i:CalReq[16][8][2]/i:CalLogAccepts[16][8][2]/i:CalXtalPos[16][8][12][3]/F:TkrTotalHits[16]/i:TkrTotalClusters[16]/i:EventSize/i:AcdNumDigis/I:AcdPha[604][2]/I:AcdHitMap[604][2]/I:AcdRange[604][2]/I:AcdOddParityError[604][2]/I:AcdHeaderParityError[604][2]/I:AcdLowDisc[604][2]/I:AcdTileNumber[604]/I:AcdMCEnergy[604]/F:AcdTileMCEnergy/F:AcdDoca/F:AcdTileCount/I:AcdActiveDist/F:AcdMinDocaId/I:Acd10Ids[10]/I:AcdRibbonMCEnergy/F:AcdRibbonCount/I:AcdRibbonActiveDist/F:AcdMaxActiveDistId/I:AcdRibbonActiveDistId/I:AcdCornerDoca/F:AcdNumTrkIntSec/I:AcdTkrIntSecTileId[20]/I:AcdTkrIntSecTkrIndex[20]/I:AcdTkrIntSecGlobalX[20]/F:AcdTkrIntSecGlobalY[20]/F:AcdTkrIntSecGlobalZ[20]/F:AcdTkrIntSecLocalX[20]/F:AcdTkrIntSecLocalY[20]/F:AcdTkrIntSecLocalXXCov[20]/F:AcdTkrIntSecLocalYYCov[20]/F:AcdTkrIntSecLocalXYCov[20]/F:AcdTkrIntSecArcLengthToIntSec[20]/F:AcdTkrIntSecPathLengthInTile[20]/F:AcdTkrIntSecTileHit[20]/I:CalMip1Pos[3]/F:CalMip1Dir[3]/F:CalMip1Chi2/F:CalMip2Pos[3]/F:CalMip2Dir[3]/F:CalMip2Chi2/F:CalMipNum/I:CalMip1D2edge/F:CalMip1ArcLen/F:CalMip1Ecor/F:CalMip1EcorRms/F:CalMip1Erm/:CalMip2D2edge/F:CalMip2ArcLen/F:CalMip2Ecor/F:CalMip2EcorRms/F:CalMip2Erm/F:AcdNaPha[11][2]/I:AcdNaHitMap[11][2]/I:AcdNaRange[11][2]/I:AcdNaOddParityError[11][2]/I:AcdNaHeaderParityError[11][2]/I:AcdNaLowDisc[11][2]/I:AcdMips[604][2]/F:AcdPocaDoca[2][2]/F:AcdPocaDocaErr[2][2]/F:AcdPocaDocaRegion[2][2]/I:AcdPocaX[2][2]/F:AcdPocaY[2][2]/F:AcdPocaZ[2][2]/F:AcdPocaDirX[2][2]/F:AcdPocaDirY[2][2]/F:AcdPocaDirZ[2][2]/F:AcdPocaTileID[2][2]/I:AcdPocaTrackID[2][2]/I:AcdPocaNbrTrack1/I:AcdPocaNbrTrack2/I:ContextRunInfoPlatform/I:ContextRunInfoDataOrigin/I:ContextRunInfoID/i:ContextRunInfoStartTime/i:ContextDataGramInfoModeChanges/i:ContextDataGramInfoDatagrams/i:ContextDataGramInfoOpenAction/I:ContextDataGramInfoOpenReason/I:ContextDataGramInfoCrate/I:ContextDataGramInfoMode/I:ContextDataGramInfoCloseAction/I:ContextDataGramInfoCloseReason/I:ContextGemScalersElapsed/l:ContextGemScalersLivetime/l:ContextGemScalersPrescaled/l:ContextGemScalersDiscarded/l:ContextGemScalersSequence/l:ContextGemScalersDeadzone/l:ContextLsfTimeTimeToneCurrentIncomplete/i:ContextLsfTimeTimeToneCurrentTimeSecs/i:ContextLsfTimeTimeToneCurrentFlywheeling/i:ContextLsfTimeTimeToneCurrentFlagsValid/I:ContextLsfTimeTimeToneCurrentMissingGps/I:ContextLsfTimeTimeToneCurrentMissingCpuPps/I:ContextLsfTimeTimeToneCurrentMissingLatPps/I:ContextLsfTimeTimeToneCurrentMissingTimeTone/I:ContextLsfTimeTimeToneCurrentEarlyEvent/I:ContextLsfTimeTimeToneCurrentGemTimeHacks/i:ContextLsfTimeTimeToneCurrentGemTimeTicks/i:ContextLsfTimeTimeTonePreviousIncomplete/i:ContextLsfTimeTimeTonePreviousTimeSecs/i:ContextLsfTimeTimeTonePreviousFlywheeling/i:ContextLsfTimeTimeTonePreviousFlagsValid/I:ContextLsfTimeTimeTonePreviousMissingGps/I:ContextLsfTimeTimeTonePreviousMissingCpuPps/I:ContextLsfTimeTimeTonePreviousMissingLatPps/I:ContextLsfTimeTimeTonePreviousMissingTimeTone/I:ContextLsfTimeTimeTonePreviousEarlyEvent/I:ContextLsfTimeTimeTonePreviousGemTimeHacks/i:ContextLsfTimeTimeTonePreviousGemTimeTicks/i:ContextLsfTimeTimeToneGemTimeHacks/i:ContextLsfTimeTimeToneGemTimeTicks/i:ContextLsfTimeTimeTicks/i:ContextRunType/I:AcdGapPocaNbrTrack1/I:AcdGapPocaNbrTrack2/I:AcdGapPocaTrackID[2][2]/I:AcdGapPocaTileID[2][2]/I:AcdGapPocaDoca[2][2]/F:AcdTkrPointX[2]/F:AcdTkrPointY[2]/F:AcdTkrPointZ[2]/F:AcdTkrPointFace[2]/I:AcdMipsMax/F:AcdMipsMaxTileID/I:AcdMipsMaxPmt/I:AcdMipsSum/F:AcdMipsFlag[604][2]/I:AcdMipsPha[604][2]:EventBadEventSequence/I:EventBadTkrRecon/I:EventPacketError/I:EventTemError/I:EventTrgParityError/I:EventBadLdfStatus/I:EventGtrcPhase/I:EventGtfePhase/I:EventGtccFifo/I:EventGtccHdrParity/I:EventGtccWcParity/I:EventGtrcSummary/I:EventGtccDataParity/I:EventGtccTimeout/I:EventGcccError/I:EventGtccError/I:EventPhaseError/I:EventTimeoutError/I:EventReadout4/I:EventZeroSuppress/I:EventMarker/I:EventCalStrobe/I:EventTag/I:EventTACK/I:EvtMCLiveTime/D:CCSDSTime/D:CCSDSapID/I:CCSDSscID/I:ContextLsfTimeHackHacks/i:ContextLsfTimeHackTicks/i:";


NtupleDef::NtupleDef() 
{
  reset();
}

void NtupleDef::reset()
{
  m_contextRunInfoPlatform   = -9999;
  m_contextRunInfoDataOrigin = -9999;
  m_contextRunInfoID         = 0;
  m_contextRunInfoStartTime  = 0;

  m_contextDataGramInfoModeChanges = 0;
  m_contextDataGramInfoDatagrams   = 0;
  m_contextDataGramInfoOpenAction  = -9999;
  m_contextDataGramInfoOpenReason  = -9999;
  m_contextDataGramInfoCrate       = -9999;
  m_contextDataGramInfoMode        = -9999;
  m_contextDataGramInfoCloseAction = -9999;
  m_contextDataGramInfoCloseReason = -9999;

  m_contextGemScalersElapsed   = 0;
  m_contextGemScalersLivetime  = 0;
  m_contextGemScalersPrescaled = 0;
  m_contextGemScalersDiscarded = 0;
  m_contextGemScalersSequence  = 0;
  m_contextGemScalersDeadzone  = 0;

  m_contextLsfTimeTimeToneCurrentIncomplete      = 0;
  m_contextLsfTimeTimeToneCurrentTimeSecs        = 0;
  m_contextLsfTimeTimeToneCurrentFlywheeling     = 0;
  m_contextLsfTimeTimeToneCurrentFlagsValid      = -9999;
  m_contextLsfTimeTimeToneCurrentMissingGps      = -9999;
  m_contextLsfTimeTimeToneCurrentMissingCpuPps   = -9999;
  m_contextLsfTimeTimeToneCurrentMissingLatPps   = -9999;
  m_contextLsfTimeTimeToneCurrentMissingTimeTone = -9999;
  m_contextLsfTimeTimeToneCurrentEarlyEvent      = -9999;  
  m_contextLsfTimeTimeToneCurrentGemTimeHacks    = 0;
  m_contextLsfTimeTimeToneCurrentGemTimeTicks    = 0;

  m_contextLsfTimeTimeTonePreviousIncomplete      = 0;
  m_contextLsfTimeTimeTonePreviousTimeSecs        = 0;
  m_contextLsfTimeTimeTonePreviousFlywheeling     = 0;
  m_contextLsfTimeTimeTonePreviousFlagsValid      = -9999;
  m_contextLsfTimeTimeTonePreviousMissingGps      = -9999;
  m_contextLsfTimeTimeTonePreviousMissingCpuPps   = -9999;
  m_contextLsfTimeTimeTonePreviousMissingLatPps   = -9999;
  m_contextLsfTimeTimeTonePreviousMissingTimeTone = -9999;
  m_contextLsfTimeTimeTonePreviousEarlyEvent      = -9999;
  m_contextLsfTimeTimeTonePreviousGemTimeHacks    = 0;
  m_contextLsfTimeTimeTonePreviousGemTimeTicks    = 0;
  m_contextLsfTimeTimeToneGemTimeHacks            = 0;
  m_contextLsfTimeTimeToneGemTimeTicks            = 0;
  m_contextLsfTimeTimeTicks                       = 0;

  m_contextLsfTimeTimeHackHacks = 0;
  m_contextLsfTimeTimeHackTicks = 0;


  m_contextRunType = -9999;

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

  m_eventBadEventSequence = 0;
  m_eventBadTkrRecon      = 0;
  m_eventPacketError      = 0; 
  m_eventTemError         = 0;
  m_eventTrgParityError   = 0;
  m_eventBadLdfStatus     = 0;
  m_eventGtrcPhase        = 0;
  m_eventGtfePhase        = 0;
  m_eventGtccFifo         = 0;
  m_eventGtccHdrParity    = 0;
  m_eventGtccWcParity     = 0;  
  m_eventGtrcSummary      = 0;
  m_eventGtccDataParity   = 0;
  m_eventGtccTimeout      = 0; 
  m_eventGcccError        = 0;
  m_eventGtccError        = 0;
  m_eventPhaseError       = 0;
  m_eventTimeoutError     = 0;

  m_eventReadout4     = 0;
  m_eventZeroSuppress = 0;
  m_eventMarker       = 0;
  m_eventCalStrobe    = 0 ;
  m_eventTag          = 0;
  m_eventTACK         = 0;

  m_eventMCLivetime = 0.0;

  m_cCSDStime  = 0.0;
  m_cCSDSapID  = 0;
  m_cCSDSscID  = 0;

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
    m_acdMips[iAcdTile][0]              = -9999.0;
    m_acdMips[iAcdTile][1]              = -9999.0;
    m_acdMipsFlag[iAcdTile][0]          = -9999;
    m_acdMipsFlag[iAcdTile][1]          = -9999;
    m_acdMipsPha[iAcdTile][0]           = -9999;
    m_acdMipsPha[iAcdTile][1]           = -9999;
  }


  for (int iAcdTile=0; iAcdTile != g_nAcdNaTile; ++iAcdTile) {
    m_acdNaPha[iAcdTile][0]               = -9999;
    m_acdNaPha[iAcdTile][1]               = -9999;
    m_acdNaHitMap[iAcdTile][0]            = -9999;
    m_acdNaHitMap[iAcdTile][1]            = -9999;
    m_acdNaRange[iAcdTile][0]             = -9999;
    m_acdNaRange[iAcdTile][1]             = -9999;
    m_acdNaOddParityError[iAcdTile][0]    = -9999;
    m_acdNaOddParityError[iAcdTile][1]    = -9999;
    m_acdNaHeaderParityError[iAcdTile][0] = -9999;
    m_acdNaHeaderParityError[iAcdTile][1] = -9999;
    m_acdNaLowDisc[iAcdTile][0]           = -9999;
    m_acdNaLowDisc[iAcdTile][1]           = -9999;
  }
  for (int iAcdTkr=0; iAcdTkr < 2; iAcdTkr++) {
    for (int iAcdTiles=0; iAcdTiles < 2; iAcdTiles++) {
      m_acdPocaDoca[iAcdTkr][iAcdTiles]       = -9999.0;
      m_acdPocaDocaErr[iAcdTkr][iAcdTiles]    = -9999.0;
      m_acdPocaDocaRegion[iAcdTkr][iAcdTiles] = -9999.0;
      m_acdPocaX[iAcdTkr][iAcdTiles]          = -9999.0;
      m_acdPocaY[iAcdTkr][iAcdTiles]          = -9999.0;
      m_acdPocaZ[iAcdTkr][iAcdTiles]          = -9999.0;
      m_acdPocaDirX[iAcdTkr][iAcdTiles]       = -9999.0;
      m_acdPocaDirY[iAcdTkr][iAcdTiles]       = -9999.0;
      m_acdPocaDirZ[iAcdTkr][iAcdTiles]       = -9999.0;
      m_acdPocaTileID[iAcdTkr][iAcdTiles]     = -9999;
      m_acdPocaTrackID[iAcdTkr][iAcdTiles]    = -9999;

      m_acdGapPocaTrackID[iAcdTkr][iAcdTiles] = -9999;
      m_acdGapPocaTileID[iAcdTkr][iAcdTiles]  = -9999;
      m_acdGapPocaDoca[iAcdTkr][iAcdTiles]    = -9999.0;
    }
      m_acdTkrPointX[iAcdTkr]    = -9999.0;
      m_acdTkrPointY[iAcdTkr]    = -9999.0;
      m_acdTkrPointZ[iAcdTkr]    = -9999.0;
      m_acdTkrPointFace[iAcdTkr] = -9999;
  }

  m_acdMipsMax       = -9999.0;
  m_acdMipsMaxTileID = -9999;
  m_acdMipsMaxPmt    = -9999;
  m_acdMipsSum       = -9999.0;

  m_acdGapPocaNbrTrack1 = -9999;
  m_acdGapPocaNbrTrack2 = -9999;

  m_acdPocaNbrTrack1 = -9999;
  m_acdPocaNbrTrack2 = -9999;

  m_acdNumDigis = 0;

  m_acdEnergy     = -9999.0;
  m_acdDoca       = -9999.0;
  m_acdActiveDist = -9999.0;
  m_acdTileCount  = -9999;
  m_acdMinDocaId  = -9999;
  m_acdCornerDoca = -9999.0;

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

  for (int iAcdTkr=0; iAcdTkr < 20; iAcdTkr++) {
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


  for (int i=0; i<3; i++) {
    m_calMip1Pos[i] = -9999.0;
    m_calMip1Dir[i] = -9999.0;
    m_calMip2Pos[i] = -9999.0;
    m_calMip2Dir[i] = -9999.0;
  }
  m_calMip1Chi2    = -9999.0;
  m_calMip1D2edge  = -9999.0;
  m_calMip1ArcLen  = -9999.0;
  m_calMip1Ecor    = -9999.0; 
  m_calMip1EcorRms = -9999.0; 
  m_calMip1Erm     = -9999.0;
  m_calMip2Chi2    = -9999.0;
  m_calMip2D2edge  = -9999.0;
  m_calMip2ArcLen  = -9999.0;
  m_calMip2Ecor    = -9999.0; 
  m_calMip2EcorRms = -9999.0; 
  m_calMip2Erm     = -9999.0;


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
