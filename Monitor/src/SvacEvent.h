//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  6 11:40:12 2007 by ROOT version 5.10/00
// from TTree Output/Root Analyzer
// found on file: /nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/svacTuple/v3r0p3/svacTuple-v3r9p1_077014005_svac_svac.root
//////////////////////////////////////////////////////////

#ifndef SvacEvent_h
#define SvacEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>

class SvacEvent:public TObject {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   UInt_t          RunID;
   UInt_t          EventID;
   UInt_t          EventSize;
   UInt_t          EventFlags;
   Double_t        EvtTime;
   UInt_t          EvtSecond;
   UInt_t          EvtNanoSecond;
   UInt_t          EvtUpperTime;
   UInt_t          EvtLowerTime;
   Double_t        EvtTimeSeconds;
   Double_t        EvtTicks;
   UInt_t          EvtSummary;
   Double_t        EvtMCLiveTime;
   Int_t           EventBadEventSequence;
   Int_t           EventBadTkrRecon;
   Int_t           EventPacketError;
   Int_t           EventTemError;
   Int_t           EventTrgParityError;
   Int_t           EventBadLdfStatus;
   Int_t           EventGtrcPhase;
   Int_t           EventGtfePhase;
   Int_t           EventGtccFifo;
   Int_t           EventGtccHdrParity;
   Int_t           EventGtccWcParity;
   Int_t           EventGtrcSummary;
   Int_t           EventGtccDataParity;
   Int_t           EventGtccTimeout;
   Int_t           EventGcccError;
   Int_t           EventGtccError;
   Int_t           EventPhaseError;
   Int_t           EventTimeoutError;
   Int_t           EventReadout4;
   Int_t           EventZeroSuppress;
   Int_t           EventMarker;
   Int_t           EventCalStrobe;
   Int_t           EventTag;
   Int_t           EventTACK;
   UInt_t          McSeqNo;
   Int_t           McId;
   Float_t         McTotalEnergy;
   Float_t         McX0;
   Float_t         McY0;
   Float_t         McZ0;
   Float_t         McXDir;
   Float_t         McYDir;
   Float_t         McZDir;
   Float_t         McConvPointX;
   Float_t         McConvPointY;
   Float_t         McConvPointZ;
   Float_t         McCalEneSum;
   Float_t         McTkr1Ene;
   Float_t         McTkr2Ene;
   Float_t         McConvAngle;
   Int_t           TkrNumDigis;
   Int_t           TkrNumStrips[16][18][2];
   Int_t           tot[16][18][2][2];
   Float_t         totCorrL[16][18][2][2];
   Float_t         totCorrQ[16][18][2][2];
   Float_t         TkrDepositEne[16][18][2];
   Int_t           TkrNumClusters[16][18][2];
   Int_t           TkrNumTracks;
   Int_t           TkrNumVertices;
   UInt_t          TkrTotalHits[16];
   UInt_t          TkrTotalClusters[16];
   Int_t           Tkr1NumHits;
   Int_t           Tkr2NumHits;
   Float_t         Tkr1Chisq;
   Float_t         Tkr2Chisq;
   Float_t         Tkr1ChisqS;
   Float_t         Tkr2ChisqS;
   Float_t         Tkr1Rms;
   Float_t         Tkr2Rms;
   Float_t         Tkr1KalThetaMs;
   Float_t         Tkr2KalThetaMs;
   Float_t         Tkr1KalEne;
   Float_t         Tkr2KalEne;
   Float_t         Tkr1EndPos[3];
   Float_t         Tkr2EndPos[3];
   Float_t         Tkr1EndDir[3];
   Float_t         Tkr2EndDir[3];
   Float_t         TkrTopTot[16];
   Float_t         Tkr1ConvTot;
   Float_t         VtxX0;
   Float_t         VtxY0;
   Float_t         VtxZ0;
   Float_t         VtxXDir;
   Float_t         VtxYDir;
   Float_t         VtxZDir;
   Float_t         Vtx1Energy;
   Int_t           Vtx1NumTkrs;
   Float_t         CalEneSum;
   Float_t         CalXEcentr;
   Float_t         CalYEcentr;
   Float_t         CalZEcentr;
   Float_t         CalXtalEne[16][8][12][2];
   Float_t         CalMaxEne;
   Int_t           CalNumHit[16];
   Float_t         CalXtalPos[16][8][12][3];
   Int_t           CalMipNum;
   Float_t         CalMip1Pos[3];
   Float_t         CalMip1Dir[3];
   Float_t         CalMip1Chi2;
   Float_t         CalMip1D2edge;
   Float_t         CalMip1ArcLen;
   Float_t         CalMip1Ecor;
   Float_t         CalMip1EcorRms;
   Float_t         CalMip1Erm;
   Float_t         CalMip2Pos[3];
   Float_t         CalMip2Dir[3];
   Float_t         CalMip2Chi2;
   Float_t         CalMip2D2edge;
   Float_t         CalMip2ArcLen;
   Float_t         CalMip2Ecor;
   Float_t         CalMip2EcorRms;
   Float_t         CalMip2Erm;
   UInt_t          GltWord;
   Int_t           ContextRunInfoPlatform;
   Int_t           ContextRunInfoDataOrigin;
   UInt_t          ContextRunInfoID;
   UInt_t          ContextRunInfoStartTime;
   UInt_t          ContextDataGramInfoModeChanges;
   UInt_t          ContextDataGramInfoDatagrams;
   Int_t           ContextDataGramInfoOpenAction;
   Int_t           ContextDataGramInfoOpenReason;
   Int_t           ContextDataGramInfoCrate;
   Int_t           ContextDataGramInfoMode;
   Int_t           ContextDataGramInfoCloseAction;
   Int_t           ContextDataGramInfoCloseReason;
   ULong64_t       ContextGemScalersElapsed;
   ULong64_t       ContextGemScalersLivetime;
   ULong64_t       ContextGemScalersPrescaled;
   ULong64_t       ContextGemScalersDiscarded;
   ULong64_t       ContextGemScalersSequence;
   ULong64_t       ContextGemScalersDeadzone;
   UInt_t          ContextLsfTimeTimeToneCurrentIncomplete;
   UInt_t          ContextLsfTimeTimeToneCurrentTimeSecs;
   UInt_t          ContextLsfTimeTimeToneCurrentFlywheeling;
   Int_t           ContextLsfTimeTimeToneCurrentFlagsValid;
   Int_t           ContextLsfTimeTimeToneCurrentMissingGps;
   Int_t           ContextLsfTimeTimeToneCurrentMissingCpuPps;
   Int_t           ContextLsfTimeTimeToneCurrentMissingLatPps;
   Int_t           ContextLsfTimeTimeToneCurrentMissingTimeTone;
   UInt_t          ContextLsfTimeTimeToneCurrentGemTimeHacks;
   UInt_t          ContextLsfTimeTimeToneCurrentGemTimeTicks;
   UInt_t          ContextLsfTimeTimeTonePreviousIncomplete;
   UInt_t          ContextLsfTimeTimeTonePreviousTimeSecs;
   UInt_t          ContextLsfTimeTimeTonePreviousFlywheeling;
   Int_t           ContextLsfTimeTimeTonePreviousFlagsValid;
   Int_t           ContextLsfTimeTimeTonePreviousMissingGps;
   Int_t           ContextLsfTimeTimeTonePreviousMissingCpuPps;
   Int_t           ContextLsfTimeTimeTonePreviousMissingLatPps;
   Int_t           ContextLsfTimeTimeTonePreviousMissingTimeTone;
   UInt_t          ContextLsfTimeTimeTonePreviousGemTimeHacks;
   UInt_t          ContextLsfTimeTimeTonePreviousGemTimeTicks;
   UInt_t          ContextLsfTimeTimeTicks;
   UInt_t          ContextLsfTimeHackHacks;
   UInt_t          ContextLsfTimeHackTicks;
   Int_t           ContextRunType;
   Int_t           GemConditionsWord;
   Int_t           GemTkrVector[16];
   Int_t           GemRoiVector[16];
   Int_t           GemCalLeVector[16];
   Int_t           GemCalHeVector[16];
   Int_t           GemCnoVector[12];
   UInt_t          GemLiveTime;
   UInt_t          GemTriggerTime;
   UInt_t          GemDeltaEventTime;
   UInt_t          GemOnePpsSeconds;
   UInt_t          GemOnePpsTime;
   UInt_t          GemPrescaled;
   UInt_t          GemDiscarded;
   UInt_t          GemCondArrivalTimeWord;
   UInt_t          GemCondArrivalTimeExt;
   UInt_t          GemCondArrivalTimeCno;
   UInt_t          GemCondArrivalTimeCalLe;
   UInt_t          GemCondArrivalTimeCalHe;
   UInt_t          GemCondArrivalTimeTkr;
   UInt_t          GemCondArrivalTimeRoi;
   UInt_t          GemDeltaWindowOpenTime;
   UInt_t          GemDeadZone;
   UInt_t          GemAcdTilesXzp;
   UInt_t          GemAcdTilesXzm;
   UInt_t          GemAcdTilesYzp;
   UInt_t          GemAcdTilesYzm;
   UInt_t          GemAcdTilesXy;
   UInt_t          GemAcdTilesRbn;
   UInt_t          GemAcdTilesNa;
   UInt_t          DigiTriRowBits[16];
   UInt_t          TrgReqTriRowBits[16];
   UInt_t          TkrReq[16][18][2][2];
   UInt_t          TkrTp[16][8];
   UInt_t          CalReq[16][8][2];
   UInt_t          CalTp[16][8];
   UInt_t          DiagLength[16];
   UInt_t          TemLength[16];
   UInt_t          GemLength;
   UInt_t          OswLength;
   UInt_t          AemLength;
   UInt_t          ErrLength[16];
   Int_t           AcdNumDigis;
   Int_t           AcdPha[604][2];
   Int_t           AcdHitMap[604][2];
   Int_t           AcdRange[604][2];
   Int_t           AcdOddParityError[604][2];
   Int_t           AcdHeaderParityError[604][2];
   Int_t           AcdLowDisc[604][2];
   Int_t           Acd10Ids[10];
   Int_t           AcdTileNumber[604];
   Float_t         AcdMCEnergy[604];
   Int_t           AcdNaPha[11][2];
   Int_t           AcdNaHitMap[11][2];
   Int_t           AcdNaRange[11][2];
   Int_t           AcdNaOddParityError[11][2];
   Int_t           AcdNaHeaderParityError[11][2];
   Int_t           AcdNaLowDisc[11][2];
   Float_t         AcdTileMCEnergy;
   Float_t         AcdDoca;
   Int_t           AcdTileCount;
   Float_t         AcdActiveDist;
   Int_t           AcdMinDocaId;
   Float_t         AcdRibbonMCEnergy;
   Int_t           AcdRibbonCount;
   Float_t         AcdRibbonActiveDist;
   Int_t           AcdMaxActiveDistId;
   Int_t           AcdRibbonActiveDistId;
   Float_t         AcdCornerDoca;
   Int_t           AcdNumTkrIntSec;
   Int_t           AcdTkrIntSecTileId[20];
   Int_t           AcdTkrIntSecTkrIndex[20];
   Float_t         AcdTkrIntSecGlobalX[20];
   Float_t         AcdTkrIntSecGlobalY[20];
   Float_t         AcdTkrIntSecGlobalZ[20];
   Float_t         AcdTkrIntSecLocalX[20];
   Float_t         AcdTkrIntSecLocalY[20];
   Float_t         AcdTkrIntSecLocalXXCov[20];
   Float_t         AcdTkrIntSecLocalYYCov[20];
   Float_t         AcdTkrIntSecLocalXYCov[20];
   Float_t         AcdTkrIntSecArcLengthToIntSec[20];
   Float_t         AcdTkrIntSecPathLengthInTile[20];
   Int_t           AcdTkrIntSecTileHit[20];
   Float_t         AcdMips[604][2];
   Int_t           AcdMipsPha[604][2];
   Int_t           AcdMipsFlag[604][2];
   Float_t         AcdMipsMax;
   Int_t           AcdMipsMaxTileID;
   Int_t           AcdMipsMaxPmt;
   Float_t         AcdMipsSum;
   Float_t         AcdPocaDoca[2][2];
   Float_t         AcdPocaDocaErr[2][2];
   Float_t         AcdPocaDocaRegion[2][2];
   Float_t         AcdPocaX[2][2];
   Float_t         AcdPocaY[2][2];
   Float_t         AcdPocaZ[2][2];
   Float_t         AcdPocaDirX[2][2];
   Float_t         AcdPocaDirY[2][2];
   Float_t         AcdPocaDirZ[2][2];
   Int_t           AcdPocaTileID[2][2];
   Int_t           AcdPocaTrackID[2][2];
   Int_t           AcdPocaNbrTrack1;
   Int_t           AcdPocaNbrTrack2;
   Float_t         AcdGapPocaDoca[2][2];
   Int_t           AcdGapPocaTileID[2][2];
   Int_t           AcdGapPocaTrackID[2][2];
   Int_t           AcdGapPocaNbrTrack1;
   Int_t           AcdGapPocaNbrTrack2;
   Float_t         AcdTkrPointX[2];
   Float_t         AcdTkrPointY[2];
   Float_t         AcdTkrPointZ[2];
   Int_t           AcdTkrPointFace[2];
   Double_t        CCSDSTime;
   Int_t           CCSDSapID;
   Int_t           CCSDSscID;

   // List of branches
   TBranch        *b_RunID;   //!
   TBranch        *b_EventID;   //!
   TBranch        *b_EventSize;   //!
   TBranch        *b_EventFlags;   //!
   TBranch        *b_EvtTime;   //!
   TBranch        *b_EvtSecond;   //!
   TBranch        *b_EvtNanoSecond;   //!
   TBranch        *b_EvtUpperTime;   //!
   TBranch        *b_EvtLowerTime;   //!
   TBranch        *b_EvtTimeSeconds;   //!
   TBranch        *b_EvtTicks;   //!
   TBranch        *b_EvtSummary;   //!
   TBranch        *b_EvtMCLiveTime;   //!
   TBranch        *b_EventBadEventSequence;   //!
   TBranch        *b_EventBadTkrRecon;   //!
   TBranch        *b_EventPacketError;   //!
   TBranch        *b_EventTemError;   //!
   TBranch        *b_EventTrgParityError;   //!
   TBranch        *b_EventBadLdfStatus;   //!
   TBranch        *b_EventGtrcPhase;   //!
   TBranch        *b_EventGtfePhase;   //!
   TBranch        *b_EventGtccFifo;   //!
   TBranch        *b_EventGtccHdrParity;   //!
   TBranch        *b_EventGtccWcParity;   //!
   TBranch        *b_EventGtrcSummary;   //!
   TBranch        *b_EventGtccDataParity;   //!
   TBranch        *b_EventGtccTimeout;   //!
   TBranch        *b_EventGcccError;   //!
   TBranch        *b_EventGtccError;   //!
   TBranch        *b_EventPhaseError;   //!
   TBranch        *b_EventTimeoutError;   //!
   TBranch        *b_EventReadout4;   //!
   TBranch        *b_EventZeroSuppress;   //!
   TBranch        *b_EventMarker;   //!
   TBranch        *b_EventCalStrobe;   //!
   TBranch        *b_EventTag;   //!
   TBranch        *b_EventTACK;   //!
   TBranch        *b_McSeqNo;   //!
   TBranch        *b_McId;   //!
   TBranch        *b_McTotalEnergy;   //!
   TBranch        *b_McX0;   //!
   TBranch        *b_McY0;   //!
   TBranch        *b_McZ0;   //!
   TBranch        *b_McXDir;   //!
   TBranch        *b_McYDir;   //!
   TBranch        *b_McZDir;   //!
   TBranch        *b_McConvPointX;   //!
   TBranch        *b_McConvPointY;   //!
   TBranch        *b_McConvPointZ;   //!
   TBranch        *b_McCalEneSum;   //!
   TBranch        *b_McTkr1Ene;   //!
   TBranch        *b_McTkr2Ene;   //!
   TBranch        *b_McConvAngle;   //!
   TBranch        *b_TkrNumDigis;   //!
   TBranch        *b_TkrNumStrips;   //!
   TBranch        *b_tot;   //!
   TBranch        *b_totCorrL;   //!
   TBranch        *b_totCorrQ;   //!
   TBranch        *b_TkrDepositEne;   //!
   TBranch        *b_TkrNumClusters;   //!
   TBranch        *b_TkrNumTracks;   //!
   TBranch        *b_TkrNumVertices;   //!
   TBranch        *b_TkrTotalHits;   //!
   TBranch        *b_TkrTotalClusters;   //!
   TBranch        *b_Tkr1NumHits;   //!
   TBranch        *b_Tkr2NumHits;   //!
   TBranch        *b_Tkr1Chisq;   //!
   TBranch        *b_Tkr2Chisq;   //!
   TBranch        *b_Tkr1ChisqS;   //!
   TBranch        *b_Tkr2ChisqS;   //!
   TBranch        *b_Tkr1Rms;   //!
   TBranch        *b_Tkr2Rms;   //!
   TBranch        *b_Tkr1KalThetaMs;   //!
   TBranch        *b_Tkr1Ka2ThetaMs;   //!
   TBranch        *b_Tkr1KalEne;   //!
   TBranch        *b_Tkr2KalEne;   //!
   TBranch        *b_Tkr1EndPos;   //!
   TBranch        *b_Tkr2EndPos;   //!
   TBranch        *b_Tkr1EndDir;   //!
   TBranch        *b_Tkr2EndDir;   //!
   TBranch        *b_TkrTopTot;   //!
   TBranch        *b_Tkr1ConvTot;   //!
   TBranch        *b_VtxX0;   //!
   TBranch        *b_VtxY0;   //!
   TBranch        *b_VtxZ0;   //!
   TBranch        *b_VtxXDir;   //!
   TBranch        *b_VtxYDir;   //!
   TBranch        *b_VtxZDir;   //!
   TBranch        *b_Vtx1Energy;   //!
   TBranch        *b_Vtx1NumTkrs;   //!
   TBranch        *b_CalEneSum;   //!
   TBranch        *b_CalXEcentr;   //!
   TBranch        *b_CalYEcentr;   //!
   TBranch        *b_CalZEcentr;   //!
   TBranch        *b_CalXtalEne;   //!
   TBranch        *b_CalMaxEne;   //!
   TBranch        *b_CalNumHit;   //!
   TBranch        *b_CalXtalPos;   //!
   TBranch        *b_CalMipNum;   //!
   TBranch        *b_CalMip1Pos;   //!
   TBranch        *b_CalMip1Dir;   //!
   TBranch        *b_CalMip1Chi2;   //!
   TBranch        *b_CalMip1D2edge;   //!
   TBranch        *b_CalMip1ArcLen;   //!
   TBranch        *b_CalMip1Ecor;   //!
   TBranch        *b_CalMip1EcorRms;   //!
   TBranch        *b_CalMip1Erm;   //!
   TBranch        *b_CalMip2Pos;   //!
   TBranch        *b_CalMip2Dir;   //!
   TBranch        *b_CalMip2Chi2;   //!
   TBranch        *b_CalMip2D2edge;   //!
   TBranch        *b_CalMip2ArcLen;   //!
   TBranch        *b_CalMip2Ecor;   //!
   TBranch        *b_CalMip2EcorRms;   //!
   TBranch        *b_CalMip2Erm;   //!
   TBranch        *b_GltWord;   //!
   TBranch        *b_ContextRunInfoPlatform;   //!
   TBranch        *b_ContextRunInfoDataOrigin;   //!
   TBranch        *b_ContextRunInfoID;   //!
   TBranch        *b_ContextRunInfoStartTime;   //!
   TBranch        *b_ContextDataGramInfoModeChanges;   //!
   TBranch        *b_ContextDataGramInfoDatagrams;   //!
   TBranch        *b_ContextDataGramInfoOpenAction;   //!
   TBranch        *b_ContextDataGramInfoOpenReason;   //!
   TBranch        *b_ContextDataGramInfoCrate;   //!
   TBranch        *b_ContextDataGramInfoMode;   //!
   TBranch        *b_ContextDataGramInfoCloseAction;   //!
   TBranch        *b_ContextDataGramInfoCloseReason;   //!
   TBranch        *b_ContextGemScalersElapsed;   //!
   TBranch        *b_ContextGemScalersLivetime;   //!
   TBranch        *b_ContextGemScalersPrescaled;   //!
   TBranch        *b_ContextGemScalersDiscarded;   //!
   TBranch        *b_ContextGemScalersSequence;   //!
   TBranch        *b_ContextGemScalersDeadzone;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentIncomplete;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentTimeSecs;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentFlywheeling;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentFlagsValid;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentMissingGps;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentMissingCpuPps;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentMissingLatPps;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentMissingTimeTone;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentGemTimeHacks;   //!
   TBranch        *b_ContextLsfTimeTimeToneCurrentGemTimeTicks;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousIncomplete;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousTimeSecs;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousFlywheeling;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousFlagsValid;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousMissingGps;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousMissingCpuPps;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousMissingLatPps;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousMissingTimeTone;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousGemTimeHacks;   //!
   TBranch        *b_ContextLsfTimeTimeTonePreviousGemTimeTicks;   //!
   TBranch        *b_ContextLsfTimeTimeTicks;   //!
   TBranch        *b_ContextLsfTimeHackHacks;   //!
   TBranch        *b_ContextLsfTimeHackTicks;   //!
   TBranch        *b_ContextRunType;   //!
   TBranch        *b_GemConditionsWord;   //!
   TBranch        *b_GemTkrVector;   //!
   TBranch        *b_GemRoiVector;   //!
   TBranch        *b_GemCalLeVector;   //!
   TBranch        *b_GemCalHeVector;   //!
   TBranch        *b_GemCnoVector;   //!
   TBranch        *b_GemLiveTime;   //!
   TBranch        *b_GemTriggerTime;   //!
   TBranch        *b_GemDeltaEventTime;   //!
   TBranch        *b_GemOnePpsSeconds;   //!
   TBranch        *b_GemOnePpsTime;   //!
   TBranch        *b_GemPrescaled;   //!
   TBranch        *b_GemDiscarded;   //!
   TBranch        *b_GemCondArrivalTimeWord;   //!
   TBranch        *b_GemCondArrivalTimeExt;   //!
   TBranch        *b_GemCondArrivalTimeCno;   //!
   TBranch        *b_GemCondArrivalTimeCalLe;   //!
   TBranch        *b_GemCondArrivalTimeCalHe;   //!
   TBranch        *b_GemCondArrivalTimeTkr;   //!
   TBranch        *b_GemCondArrivalTimeRoi;   //!
   TBranch        *b_GemDeltaWindowOpenTime;   //!
   TBranch        *b_GemDeadZone;   //!
   TBranch        *b_GemAcdTilesXzp;   //!
   TBranch        *b_GemAcdTilesXzm;   //!
   TBranch        *b_GemAcdTilesYzp;   //!
   TBranch        *b_GemAcdTilesYzm;   //!
   TBranch        *b_GemAcdTilesXy;   //!
   TBranch        *b_GemAcdTilesRbn;   //!
   TBranch        *b_GemAcdTilesNa;   //!
   TBranch        *b_DigiTriRowBits;   //!
   TBranch        *b_TrgReqTriRowBits;   //!
   TBranch        *b_TkrReq;   //!
   TBranch        *b_TkrTp;   //!
   TBranch        *b_CalReq;   //!
   TBranch        *b_CalTp;   //!
   TBranch        *b_DiagLength;   //!
   TBranch        *b_TemLength;   //!
   TBranch        *b_GemLength;   //!
   TBranch        *b_OswLength;   //!
   TBranch        *b_AemLength;   //!
   TBranch        *b_ErrLength;   //!
   TBranch        *b_AcdNumDigis;   //!
   TBranch        *b_AcdPha;   //!
   TBranch        *b_AcdHitMap;   //!
   TBranch        *b_AcdRange;   //!
   TBranch        *b_AcdOddParityError;   //!
   TBranch        *b_AcdHeaderParityError;   //!
   TBranch        *b_AcdLowDisc;   //!
   TBranch        *b_Acd10Ids;   //!
   TBranch        *b_AcdTileNumber;   //!
   TBranch        *b_AcdMCEnergy;   //!
   TBranch        *b_AcdNaPha;   //!
   TBranch        *b_AcdNaHitMap;   //!
   TBranch        *b_AcdNaRange;   //!
   TBranch        *b_AcdNaOddParityError;   //!
   TBranch        *b_AcdNaHeaderParityError;   //!
   TBranch        *b_AcdNaLowDisc;   //!
   TBranch        *b_AcdTileMCEnergy;   //!
   TBranch        *b_AcdDoca;   //!
   TBranch        *b_AcdTileCount;   //!
   TBranch        *b_AcdActiveDist;   //!
   TBranch        *b_AcdMinDocaId;   //!
   TBranch        *b_AcdRibbonMCEnergy;   //!
   TBranch        *b_AcdRibbonCount;   //!
   TBranch        *b_AcdRibbonActiveDist;   //!
   TBranch        *b_AcdMaxActiveDistId;   //!
   TBranch        *b_AcdRibbonActiveDistId;   //!
   TBranch        *b_AcdCornerDoca;   //!
   TBranch        *b_AcdNumTkrIntSec;   //!
   TBranch        *b_AcdTkrIntSecTileId;   //!
   TBranch        *b_AcdTkrIntSecTkrIndex;   //!
   TBranch        *b_AcdTkrIntSecGlobalX;   //!
   TBranch        *b_AcdTkrIntSecGlobalY;   //!
   TBranch        *b_AcdTkrIntSecGlobalZ;   //!
   TBranch        *b_AcdTkrIntSecLocalX;   //!
   TBranch        *b_AcdTkrIntSecLocalY;   //!
   TBranch        *b_AcdTkrIntSecLocalXXCov;   //!
   TBranch        *b_AcdTkrIntSecLocalYYCov;   //!
   TBranch        *b_AcdTkrIntSecLocalXYCov;   //!
   TBranch        *b_AcdTkrIntSecArcLengthToIntSec;   //!
   TBranch        *b_AcdTkrIntSecPathLengthInTile;   //!
   TBranch        *b_AcdTkrIntSecTileHit;   //!
   TBranch        *b_AcdMips;   //!
   TBranch        *b_AcdMipsPha;   //!
   TBranch        *b_AcdMipsFlag;   //!
   TBranch        *b_AcdMipsMax;   //!
   TBranch        *b_AcdMipsMaxTileID;   //!
   TBranch        *b_AcdMipsMaxPmt;   //!
   TBranch        *b_AcdMipsSum;   //!
   TBranch        *b_AcdPocaDoca;   //!
   TBranch        *b_AcdPocaDocaErr;   //!
   TBranch        *b_AcdPocaDocaRegion;   //!
   TBranch        *b_AcdPocaX;   //!
   TBranch        *b_AcdPocaY;   //!
   TBranch        *b_AcdPocaZ;   //!
   TBranch        *b_AcdPocaDirX;   //!
   TBranch        *b_AcdPocaDirY;   //!
   TBranch        *b_AcdPocaDirZ;   //!
   TBranch        *b_AcdPocaTileID;   //!
   TBranch        *b_AcdPocaTrackID;   //!
   TBranch        *b_AcdPocaNbrTrack1;   //!
   TBranch        *b_AcdPocaNbrTrack2;   //!
   TBranch        *b_AcdGapPocaDoca;   //!
   TBranch        *b_AcdGapPocaTileID;   //!
   TBranch        *b_AcdGapPocaTrackID;   //!
   TBranch        *b_AcdGapPocaNbrTrack1;   //!
   TBranch        *b_AcdGapPocaNbrTrack2;   //!
   TBranch        *b_AcdTkrPointX;   //!
   TBranch        *b_AcdTkrPointY;   //!
   TBranch        *b_AcdTkrPointZ;   //!
   TBranch        *b_AcdTkrPointFace;   //!
   TBranch        *b_CCSDSTime;   //!
   TBranch        *b_CCSDSapID;   //!
   TBranch        *b_CCSDSscID;   //!

   SvacEvent(TTree *tree=0);
   virtual ~SvacEvent();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SvacEvent_cxx
SvacEvent::SvacEvent(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/svacTuple/v3r0p3/svacTuple-v3r9p1_077014005_svac_svac.root");
      if (!f) {
         f = new TFile("/nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/svacTuple/v3r0p3/svacTuple-v3r9p1_077014005_svac_svac.root");
      }
      tree = (TTree*)gDirectory->Get("Output");

   }
   Init(tree);
}

SvacEvent::~SvacEvent()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SvacEvent::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SvacEvent::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SvacEvent::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunID",&RunID);
   fChain->SetBranchAddress("EventID",&EventID);
   fChain->SetBranchAddress("EventSize",&EventSize);
   fChain->SetBranchAddress("EventFlags",&EventFlags);
   fChain->SetBranchAddress("EvtTime",&EvtTime);
   fChain->SetBranchAddress("EvtSecond",&EvtSecond);
   fChain->SetBranchAddress("EvtNanoSecond",&EvtNanoSecond);
   fChain->SetBranchAddress("EvtUpperTime",&EvtUpperTime);
   fChain->SetBranchAddress("EvtLowerTime",&EvtLowerTime);
   fChain->SetBranchAddress("EvtTimeSeconds",&EvtTimeSeconds);
   fChain->SetBranchAddress("EvtTicks",&EvtTicks);
   fChain->SetBranchAddress("EvtSummary",&EvtSummary);
   fChain->SetBranchAddress("EvtMCLiveTime",&EvtMCLiveTime);
   fChain->SetBranchAddress("EventBadEventSequence",&EventBadEventSequence);
   fChain->SetBranchAddress("EventBadTkrRecon",&EventBadTkrRecon);
   fChain->SetBranchAddress("EventPacketError",&EventPacketError);
   fChain->SetBranchAddress("EventTemError",&EventTemError);
   fChain->SetBranchAddress("EventTrgParityError",&EventTrgParityError);
   fChain->SetBranchAddress("EventBadLdfStatus",&EventBadLdfStatus);
   fChain->SetBranchAddress("EventGtrcPhase",&EventGtrcPhase);
   fChain->SetBranchAddress("EventGtfePhase",&EventGtfePhase);
   fChain->SetBranchAddress("EventGtccFifo",&EventGtccFifo);
   fChain->SetBranchAddress("EventGtccHdrParity",&EventGtccHdrParity);
   fChain->SetBranchAddress("EventGtccWcParity",&EventGtccWcParity);
   fChain->SetBranchAddress("EventGtrcSummary",&EventGtrcSummary);
   fChain->SetBranchAddress("EventGtccDataParity",&EventGtccDataParity);
   fChain->SetBranchAddress("EventGtccTimeout",&EventGtccTimeout);
   fChain->SetBranchAddress("EventGcccError",&EventGcccError);
   fChain->SetBranchAddress("EventGtccError",&EventGtccError);
   fChain->SetBranchAddress("EventPhaseError",&EventPhaseError);
   fChain->SetBranchAddress("EventTimeoutError",&EventTimeoutError);
   fChain->SetBranchAddress("EventReadout4",&EventReadout4);
   fChain->SetBranchAddress("EventZeroSuppress",&EventZeroSuppress);
   fChain->SetBranchAddress("EventMarker",&EventMarker);
   fChain->SetBranchAddress("EventCalStrobe",&EventCalStrobe);
   fChain->SetBranchAddress("EventTag",&EventTag);
   fChain->SetBranchAddress("EventTACK",&EventTACK);
   fChain->SetBranchAddress("McSeqNo",&McSeqNo);
   fChain->SetBranchAddress("McId",&McId);
   fChain->SetBranchAddress("McTotalEnergy",&McTotalEnergy);
   fChain->SetBranchAddress("McX0",&McX0);
   fChain->SetBranchAddress("McY0",&McY0);
   fChain->SetBranchAddress("McZ0",&McZ0);
   fChain->SetBranchAddress("McXDir",&McXDir);
   fChain->SetBranchAddress("McYDir",&McYDir);
   fChain->SetBranchAddress("McZDir",&McZDir);
   fChain->SetBranchAddress("McConvPointX",&McConvPointX);
   fChain->SetBranchAddress("McConvPointY",&McConvPointY);
   fChain->SetBranchAddress("McConvPointZ",&McConvPointZ);
   fChain->SetBranchAddress("McCalEneSum",&McCalEneSum);
   fChain->SetBranchAddress("McTkr1Ene",&McTkr1Ene);
   fChain->SetBranchAddress("McTkr2Ene",&McTkr2Ene);
   fChain->SetBranchAddress("McConvAngle",&McConvAngle);
   fChain->SetBranchAddress("TkrNumDigis",&TkrNumDigis);
   fChain->SetBranchAddress("TkrNumStrips",TkrNumStrips);
   fChain->SetBranchAddress("tot",tot);
   fChain->SetBranchAddress("totCorrL",totCorrL);
   fChain->SetBranchAddress("totCorrQ",totCorrQ);
   fChain->SetBranchAddress("TkrDepositEne",TkrDepositEne);
   fChain->SetBranchAddress("TkrNumClusters",TkrNumClusters);
   fChain->SetBranchAddress("TkrNumTracks",&TkrNumTracks);
   fChain->SetBranchAddress("TkrNumVertices",&TkrNumVertices);
   fChain->SetBranchAddress("TkrTotalHits",TkrTotalHits);
   fChain->SetBranchAddress("TkrTotalClusters",TkrTotalClusters);
   fChain->SetBranchAddress("Tkr1NumHits",&Tkr1NumHits);
   fChain->SetBranchAddress("Tkr2NumHits",&Tkr2NumHits);
   fChain->SetBranchAddress("Tkr1Chisq",&Tkr1Chisq);
   fChain->SetBranchAddress("Tkr2Chisq",&Tkr2Chisq);
   fChain->SetBranchAddress("Tkr1ChisqS",&Tkr1ChisqS);
   fChain->SetBranchAddress("Tkr2ChisqS",&Tkr2ChisqS);
   fChain->SetBranchAddress("Tkr1Rms",&Tkr1Rms);
   fChain->SetBranchAddress("Tkr2Rms",&Tkr2Rms);
   fChain->SetBranchAddress("Tkr1KalThetaMs",&Tkr1KalThetaMs);
   fChain->SetBranchAddress("Tkr2KalThetaMs",&Tkr2KalThetaMs);
   fChain->SetBranchAddress("Tkr1KalEne",&Tkr1KalEne);
   fChain->SetBranchAddress("Tkr2KalEne",&Tkr2KalEne);
   fChain->SetBranchAddress("Tkr1EndPos",Tkr1EndPos);
   fChain->SetBranchAddress("Tkr2EndPos",Tkr2EndPos);
   fChain->SetBranchAddress("Tkr1EndDir",Tkr1EndDir);
   fChain->SetBranchAddress("Tkr2EndDir",Tkr2EndDir);
   fChain->SetBranchAddress("TkrTopTot",TkrTopTot);
   fChain->SetBranchAddress("Tkr1ConvTot",&Tkr1ConvTot);
   fChain->SetBranchAddress("VtxX0",&VtxX0);
   fChain->SetBranchAddress("VtxY0",&VtxY0);
   fChain->SetBranchAddress("VtxZ0",&VtxZ0);
   fChain->SetBranchAddress("VtxXDir",&VtxXDir);
   fChain->SetBranchAddress("VtxYDir",&VtxYDir);
   fChain->SetBranchAddress("VtxZDir",&VtxZDir);
   fChain->SetBranchAddress("Vtx1Energy",&Vtx1Energy);
   fChain->SetBranchAddress("Vtx1NumTkrs",&Vtx1NumTkrs);
   fChain->SetBranchAddress("CalEneSum",&CalEneSum);
   fChain->SetBranchAddress("CalXEcentr",&CalXEcentr);
   fChain->SetBranchAddress("CalYEcentr",&CalYEcentr);
   fChain->SetBranchAddress("CalZEcentr",&CalZEcentr);
   fChain->SetBranchAddress("CalXtalEne",CalXtalEne);
   fChain->SetBranchAddress("CalMaxEne",&CalMaxEne);
   fChain->SetBranchAddress("CalNumHit",CalNumHit);
   fChain->SetBranchAddress("CalXtalPos",CalXtalPos);
   fChain->SetBranchAddress("CalMipNum",&CalMipNum);
   fChain->SetBranchAddress("CalMip1Pos",CalMip1Pos);
   fChain->SetBranchAddress("CalMip1Dir",CalMip1Dir);
   fChain->SetBranchAddress("CalMip1Chi2",&CalMip1Chi2);
   fChain->SetBranchAddress("CalMip1D2edge",&CalMip1D2edge);
   fChain->SetBranchAddress("CalMip1ArcLen",&CalMip1ArcLen);
   fChain->SetBranchAddress("CalMip1Ecor",&CalMip1Ecor);
   fChain->SetBranchAddress("CalMip1EcorRms",&CalMip1EcorRms);
   fChain->SetBranchAddress("CalMip1Erm",&CalMip1Erm);
   fChain->SetBranchAddress("CalMip2Pos",CalMip2Pos);
   fChain->SetBranchAddress("CalMip2Dir",CalMip2Dir);
   fChain->SetBranchAddress("CalMip2Chi2",&CalMip2Chi2);
   fChain->SetBranchAddress("CalMip2D2edge",&CalMip2D2edge);
   fChain->SetBranchAddress("CalMip2ArcLen",&CalMip2ArcLen);
   fChain->SetBranchAddress("CalMip2Ecor",&CalMip2Ecor);
   fChain->SetBranchAddress("CalMip2EcorRms",&CalMip2EcorRms);
   fChain->SetBranchAddress("CalMip2Erm",&CalMip2Erm);
   fChain->SetBranchAddress("GltWord",&GltWord);
   fChain->SetBranchAddress("ContextRunInfoPlatform",&ContextRunInfoPlatform);
   fChain->SetBranchAddress("ContextRunInfoDataOrigin",&ContextRunInfoDataOrigin);
   fChain->SetBranchAddress("ContextRunInfoID",&ContextRunInfoID);
   fChain->SetBranchAddress("ContextRunInfoStartTime",&ContextRunInfoStartTime);
   fChain->SetBranchAddress("ContextDataGramInfoModeChanges",&ContextDataGramInfoModeChanges);
   fChain->SetBranchAddress("ContextDataGramInfoDatagrams",&ContextDataGramInfoDatagrams);
   fChain->SetBranchAddress("ContextDataGramInfoOpenAction",&ContextDataGramInfoOpenAction);
   fChain->SetBranchAddress("ContextDataGramInfoOpenReason",&ContextDataGramInfoOpenReason);
   fChain->SetBranchAddress("ContextDataGramInfoCrate",&ContextDataGramInfoCrate);
   fChain->SetBranchAddress("ContextDataGramInfoMode",&ContextDataGramInfoMode);
   fChain->SetBranchAddress("ContextDataGramInfoCloseAction",&ContextDataGramInfoCloseAction);
   fChain->SetBranchAddress("ContextDataGramInfoCloseReason",&ContextDataGramInfoCloseReason);
   fChain->SetBranchAddress("ContextGemScalersElapsed",&ContextGemScalersElapsed);
   fChain->SetBranchAddress("ContextGemScalersLivetime",&ContextGemScalersLivetime);
   fChain->SetBranchAddress("ContextGemScalersPrescaled",&ContextGemScalersPrescaled);
   fChain->SetBranchAddress("ContextGemScalersDiscarded",&ContextGemScalersDiscarded);
   fChain->SetBranchAddress("ContextGemScalersSequence",&ContextGemScalersSequence);
   fChain->SetBranchAddress("ContextGemScalersDeadzone",&ContextGemScalersDeadzone);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentIncomplete",&ContextLsfTimeTimeToneCurrentIncomplete);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentTimeSecs",&ContextLsfTimeTimeToneCurrentTimeSecs);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentFlywheeling",&ContextLsfTimeTimeToneCurrentFlywheeling);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentFlagsValid",&ContextLsfTimeTimeToneCurrentFlagsValid);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentMissingGps",&ContextLsfTimeTimeToneCurrentMissingGps);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentMissingCpuPps",&ContextLsfTimeTimeToneCurrentMissingCpuPps);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentMissingLatPps",&ContextLsfTimeTimeToneCurrentMissingLatPps);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentMissingTimeTone",&ContextLsfTimeTimeToneCurrentMissingTimeTone);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentGemTimeHacks",&ContextLsfTimeTimeToneCurrentGemTimeHacks);
   fChain->SetBranchAddress("ContextLsfTimeTimeToneCurrentGemTimeTicks",&ContextLsfTimeTimeToneCurrentGemTimeTicks);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousIncomplete",&ContextLsfTimeTimeTonePreviousIncomplete);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousTimeSecs",&ContextLsfTimeTimeTonePreviousTimeSecs);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousFlywheeling",&ContextLsfTimeTimeTonePreviousFlywheeling);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousFlagsValid",&ContextLsfTimeTimeTonePreviousFlagsValid);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousMissingGps",&ContextLsfTimeTimeTonePreviousMissingGps);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousMissingCpuPps",&ContextLsfTimeTimeTonePreviousMissingCpuPps);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousMissingLatPps",&ContextLsfTimeTimeTonePreviousMissingLatPps);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousMissingTimeTone",&ContextLsfTimeTimeTonePreviousMissingTimeTone);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousGemTimeHacks",&ContextLsfTimeTimeTonePreviousGemTimeHacks);
   fChain->SetBranchAddress("ContextLsfTimeTimeTonePreviousGemTimeTicks",&ContextLsfTimeTimeTonePreviousGemTimeTicks);
   fChain->SetBranchAddress("ContextLsfTimeTimeTicks",&ContextLsfTimeTimeTicks);
   fChain->SetBranchAddress("ContextLsfTimeHackHacks",&ContextLsfTimeHackHacks);
   fChain->SetBranchAddress("ContextLsfTimeHackTicks",&ContextLsfTimeHackTicks);
   fChain->SetBranchAddress("ContextRunType",&ContextRunType);
   fChain->SetBranchAddress("GemConditionsWord",&GemConditionsWord);
   fChain->SetBranchAddress("GemTkrVector",GemTkrVector);
   fChain->SetBranchAddress("GemRoiVector",GemRoiVector);
   fChain->SetBranchAddress("GemCalLeVector",GemCalLeVector);
   fChain->SetBranchAddress("GemCalHeVector",GemCalHeVector);
   fChain->SetBranchAddress("GemCnoVector",GemCnoVector);
   fChain->SetBranchAddress("GemLiveTime",&GemLiveTime);
   fChain->SetBranchAddress("GemTriggerTime",&GemTriggerTime);
   fChain->SetBranchAddress("GemDeltaEventTime",&GemDeltaEventTime);
   fChain->SetBranchAddress("GemOnePpsSeconds",&GemOnePpsSeconds);
   fChain->SetBranchAddress("GemOnePpsTime",&GemOnePpsTime);
   fChain->SetBranchAddress("GemPrescaled",&GemPrescaled);
   fChain->SetBranchAddress("GemDiscarded",&GemDiscarded);
   fChain->SetBranchAddress("GemCondArrivalTimeWord",&GemCondArrivalTimeWord);
   fChain->SetBranchAddress("GemCondArrivalTimeExt",&GemCondArrivalTimeExt);
   fChain->SetBranchAddress("GemCondArrivalTimeCno",&GemCondArrivalTimeCno);
   fChain->SetBranchAddress("GemCondArrivalTimeCalLe",&GemCondArrivalTimeCalLe);
   fChain->SetBranchAddress("GemCondArrivalTimeCalHe",&GemCondArrivalTimeCalHe);
   fChain->SetBranchAddress("GemCondArrivalTimeTkr",&GemCondArrivalTimeTkr);
   fChain->SetBranchAddress("GemCondArrivalTimeRoi",&GemCondArrivalTimeRoi);
   fChain->SetBranchAddress("GemDeltaWindowOpenTime",&GemDeltaWindowOpenTime);
   fChain->SetBranchAddress("GemDeadZone",&GemDeadZone);
   fChain->SetBranchAddress("GemAcdTilesXzp",&GemAcdTilesXzp);
   fChain->SetBranchAddress("GemAcdTilesXzm",&GemAcdTilesXzm);
   fChain->SetBranchAddress("GemAcdTilesYzp",&GemAcdTilesYzp);
   fChain->SetBranchAddress("GemAcdTilesYzm",&GemAcdTilesYzm);
   fChain->SetBranchAddress("GemAcdTilesXy",&GemAcdTilesXy);
   fChain->SetBranchAddress("GemAcdTilesRbn",&GemAcdTilesRbn);
   fChain->SetBranchAddress("GemAcdTilesNa",&GemAcdTilesNa);
   fChain->SetBranchAddress("DigiTriRowBits",DigiTriRowBits);
   fChain->SetBranchAddress("TrgReqTriRowBits",TrgReqTriRowBits);
   fChain->SetBranchAddress("TkrReq",TkrReq);
   fChain->SetBranchAddress("TkrTp",TkrTp);
   fChain->SetBranchAddress("CalReq",CalReq);
   fChain->SetBranchAddress("CalTp",CalTp);
   fChain->SetBranchAddress("DiagLength",DiagLength);
   fChain->SetBranchAddress("TemLength",TemLength);
   fChain->SetBranchAddress("GemLength",&GemLength);
   fChain->SetBranchAddress("OswLength",&OswLength);
   fChain->SetBranchAddress("AemLength",&AemLength);
   fChain->SetBranchAddress("ErrLength",ErrLength);
   fChain->SetBranchAddress("AcdNumDigis",&AcdNumDigis);
   fChain->SetBranchAddress("AcdPha",AcdPha);
   fChain->SetBranchAddress("AcdHitMap",AcdHitMap);
   fChain->SetBranchAddress("AcdRange",AcdRange);
   fChain->SetBranchAddress("AcdOddParityError",AcdOddParityError);
   fChain->SetBranchAddress("AcdHeaderParityError",AcdHeaderParityError);
   fChain->SetBranchAddress("AcdLowDisc",AcdLowDisc);
   fChain->SetBranchAddress("Acd10Ids",Acd10Ids);
   fChain->SetBranchAddress("AcdTileNumber",AcdTileNumber);
   fChain->SetBranchAddress("AcdMCEnergy",AcdMCEnergy);
   fChain->SetBranchAddress("AcdNaPha",AcdNaPha);
   fChain->SetBranchAddress("AcdNaHitMap",AcdNaHitMap);
   fChain->SetBranchAddress("AcdNaRange",AcdNaRange);
   fChain->SetBranchAddress("AcdNaOddParityError",AcdNaOddParityError);
   fChain->SetBranchAddress("AcdNaHeaderParityError",AcdNaHeaderParityError);
   fChain->SetBranchAddress("AcdNaLowDisc",AcdNaLowDisc);
   fChain->SetBranchAddress("AcdTileMCEnergy",&AcdTileMCEnergy);
   fChain->SetBranchAddress("AcdDoca",&AcdDoca);
   fChain->SetBranchAddress("AcdTileCount",&AcdTileCount);
   fChain->SetBranchAddress("AcdActiveDist",&AcdActiveDist);
   fChain->SetBranchAddress("AcdMinDocaId",&AcdMinDocaId);
   fChain->SetBranchAddress("AcdRibbonMCEnergy",&AcdRibbonMCEnergy);
   fChain->SetBranchAddress("AcdRibbonCount",&AcdRibbonCount);
   fChain->SetBranchAddress("AcdRibbonActiveDist",&AcdRibbonActiveDist);
   fChain->SetBranchAddress("AcdMaxActiveDistId",&AcdMaxActiveDistId);
   fChain->SetBranchAddress("AcdRibbonActiveDistId",&AcdRibbonActiveDistId);
   fChain->SetBranchAddress("AcdCornerDoca",&AcdCornerDoca);
   fChain->SetBranchAddress("AcdNumTkrIntSec",&AcdNumTkrIntSec);
   fChain->SetBranchAddress("AcdTkrIntSecTileId",AcdTkrIntSecTileId);
   fChain->SetBranchAddress("AcdTkrIntSecTkrIndex",AcdTkrIntSecTkrIndex);
   fChain->SetBranchAddress("AcdTkrIntSecGlobalX",AcdTkrIntSecGlobalX);
   fChain->SetBranchAddress("AcdTkrIntSecGlobalY",AcdTkrIntSecGlobalY);
   fChain->SetBranchAddress("AcdTkrIntSecGlobalZ",AcdTkrIntSecGlobalZ);
   fChain->SetBranchAddress("AcdTkrIntSecLocalX",AcdTkrIntSecLocalX);
   fChain->SetBranchAddress("AcdTkrIntSecLocalY",AcdTkrIntSecLocalY);
   fChain->SetBranchAddress("AcdTkrIntSecLocalXXCov",AcdTkrIntSecLocalXXCov);
   fChain->SetBranchAddress("AcdTkrIntSecLocalYYCov",AcdTkrIntSecLocalYYCov);
   fChain->SetBranchAddress("AcdTkrIntSecLocalXYCov",AcdTkrIntSecLocalXYCov);
   fChain->SetBranchAddress("AcdTkrIntSecArcLengthToIntSec",AcdTkrIntSecArcLengthToIntSec);
   fChain->SetBranchAddress("AcdTkrIntSecPathLengthInTile",AcdTkrIntSecPathLengthInTile);
   fChain->SetBranchAddress("AcdTkrIntSecTileHit",AcdTkrIntSecTileHit);
   fChain->SetBranchAddress("AcdMips",AcdMips);
   fChain->SetBranchAddress("AcdMipsPha",AcdMipsPha);
   fChain->SetBranchAddress("AcdMipsFlag",AcdMipsFlag);
   fChain->SetBranchAddress("AcdMipsMax",&AcdMipsMax);
   fChain->SetBranchAddress("AcdMipsMaxTileID",&AcdMipsMaxTileID);
   fChain->SetBranchAddress("AcdMipsMaxPmt",&AcdMipsMaxPmt);
   fChain->SetBranchAddress("AcdMipsSum",&AcdMipsSum);
   fChain->SetBranchAddress("AcdPocaDoca",AcdPocaDoca);
   fChain->SetBranchAddress("AcdPocaDocaErr",AcdPocaDocaErr);
   fChain->SetBranchAddress("AcdPocaDocaRegion",AcdPocaDocaRegion);
   fChain->SetBranchAddress("AcdPocaX",AcdPocaX);
   fChain->SetBranchAddress("AcdPocaY",AcdPocaY);
   fChain->SetBranchAddress("AcdPocaZ",AcdPocaZ);
   fChain->SetBranchAddress("AcdPocaDirX",AcdPocaDirX);
   fChain->SetBranchAddress("AcdPocaDirY",AcdPocaDirY);
   fChain->SetBranchAddress("AcdPocaDirZ",AcdPocaDirZ);
   fChain->SetBranchAddress("AcdPocaTileID",AcdPocaTileID);
   fChain->SetBranchAddress("AcdPocaTrackID",AcdPocaTrackID);
   fChain->SetBranchAddress("AcdPocaNbrTrack1",&AcdPocaNbrTrack1);
   fChain->SetBranchAddress("AcdPocaNbrTrack2",&AcdPocaNbrTrack2);
   fChain->SetBranchAddress("AcdGapPocaDoca",AcdGapPocaDoca);
   fChain->SetBranchAddress("AcdGapPocaTileID",AcdGapPocaTileID);
   fChain->SetBranchAddress("AcdGapPocaTrackID",AcdGapPocaTrackID);
   fChain->SetBranchAddress("AcdGapPocaNbrTrack1",&AcdGapPocaNbrTrack1);
   fChain->SetBranchAddress("AcdGapPocaNbrTrack2",&AcdGapPocaNbrTrack2);
   fChain->SetBranchAddress("AcdTkrPointX",AcdTkrPointX);
   fChain->SetBranchAddress("AcdTkrPointY",AcdTkrPointY);
   fChain->SetBranchAddress("AcdTkrPointZ",AcdTkrPointZ);
   fChain->SetBranchAddress("AcdTkrPointFace",AcdTkrPointFace);
   fChain->SetBranchAddress("CCSDSTime",&CCSDSTime);
   fChain->SetBranchAddress("CCSDSapID",&CCSDSapID);
   fChain->SetBranchAddress("CCSDSscID",&CCSDSscID);
   Notify();
}

Bool_t SvacEvent::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_RunID = fChain->GetBranch("RunID");
   b_EventID = fChain->GetBranch("EventID");
   b_EventSize = fChain->GetBranch("EventSize");
   b_EventFlags = fChain->GetBranch("EventFlags");
   b_EvtTime = fChain->GetBranch("EvtTime");
   b_EvtSecond = fChain->GetBranch("EvtSecond");
   b_EvtNanoSecond = fChain->GetBranch("EvtNanoSecond");
   b_EvtUpperTime = fChain->GetBranch("EvtUpperTime");
   b_EvtLowerTime = fChain->GetBranch("EvtLowerTime");
   b_EvtTimeSeconds = fChain->GetBranch("EvtTimeSeconds");
   b_EvtTicks = fChain->GetBranch("EvtTicks");
   b_EvtSummary = fChain->GetBranch("EvtSummary");
   b_EvtMCLiveTime = fChain->GetBranch("EvtMCLiveTime");
   b_EventBadEventSequence = fChain->GetBranch("EventBadEventSequence");
   b_EventBadTkrRecon = fChain->GetBranch("EventBadTkrRecon");
   b_EventPacketError = fChain->GetBranch("EventPacketError");
   b_EventTemError = fChain->GetBranch("EventTemError");
   b_EventTrgParityError = fChain->GetBranch("EventTrgParityError");
   b_EventBadLdfStatus = fChain->GetBranch("EventBadLdfStatus");
   b_EventGtrcPhase = fChain->GetBranch("EventGtrcPhase");
   b_EventGtfePhase = fChain->GetBranch("EventGtfePhase");
   b_EventGtccFifo = fChain->GetBranch("EventGtccFifo");
   b_EventGtccHdrParity = fChain->GetBranch("EventGtccHdrParity");
   b_EventGtccWcParity = fChain->GetBranch("EventGtccWcParity");
   b_EventGtrcSummary = fChain->GetBranch("EventGtrcSummary");
   b_EventGtccDataParity = fChain->GetBranch("EventGtccDataParity");
   b_EventGtccTimeout = fChain->GetBranch("EventGtccTimeout");
   b_EventGcccError = fChain->GetBranch("EventGcccError");
   b_EventGtccError = fChain->GetBranch("EventGtccError");
   b_EventPhaseError = fChain->GetBranch("EventPhaseError");
   b_EventTimeoutError = fChain->GetBranch("EventTimeoutError");
   b_EventReadout4 = fChain->GetBranch("EventReadout4");
   b_EventZeroSuppress = fChain->GetBranch("EventZeroSuppress");
   b_EventMarker = fChain->GetBranch("EventMarker");
   b_EventCalStrobe = fChain->GetBranch("EventCalStrobe");
   b_EventTag = fChain->GetBranch("EventTag");
   b_EventTACK = fChain->GetBranch("EventTACK");
   b_McSeqNo = fChain->GetBranch("McSeqNo");
   b_McId = fChain->GetBranch("McId");
   b_McTotalEnergy = fChain->GetBranch("McTotalEnergy");
   b_McX0 = fChain->GetBranch("McX0");
   b_McY0 = fChain->GetBranch("McY0");
   b_McZ0 = fChain->GetBranch("McZ0");
   b_McXDir = fChain->GetBranch("McXDir");
   b_McYDir = fChain->GetBranch("McYDir");
   b_McZDir = fChain->GetBranch("McZDir");
   b_McConvPointX = fChain->GetBranch("McConvPointX");
   b_McConvPointY = fChain->GetBranch("McConvPointY");
   b_McConvPointZ = fChain->GetBranch("McConvPointZ");
   b_McCalEneSum = fChain->GetBranch("McCalEneSum");
   b_McTkr1Ene = fChain->GetBranch("McTkr1Ene");
   b_McTkr2Ene = fChain->GetBranch("McTkr2Ene");
   b_McConvAngle = fChain->GetBranch("McConvAngle");
   b_TkrNumDigis = fChain->GetBranch("TkrNumDigis");
   b_TkrNumStrips = fChain->GetBranch("TkrNumStrips");
   b_tot = fChain->GetBranch("tot");
   b_totCorrL = fChain->GetBranch("totCorrL");
   b_totCorrQ = fChain->GetBranch("totCorrQ");
   b_TkrDepositEne = fChain->GetBranch("TkrDepositEne");
   b_TkrNumClusters = fChain->GetBranch("TkrNumClusters");
   b_TkrNumTracks = fChain->GetBranch("TkrNumTracks");
   b_TkrNumVertices = fChain->GetBranch("TkrNumVertices");
   b_TkrTotalHits = fChain->GetBranch("TkrTotalHits");
   b_TkrTotalClusters = fChain->GetBranch("TkrTotalClusters");
   b_Tkr1NumHits = fChain->GetBranch("Tkr1NumHits");
   b_Tkr2NumHits = fChain->GetBranch("Tkr2NumHits");
   b_Tkr1Chisq = fChain->GetBranch("Tkr1Chisq");
   b_Tkr2Chisq = fChain->GetBranch("Tkr2Chisq");
   b_Tkr1ChisqS = fChain->GetBranch("Tkr1ChisqS");
   b_Tkr2ChisqS = fChain->GetBranch("Tkr2ChisqS");
   b_Tkr1Rms = fChain->GetBranch("Tkr1Rms");
   b_Tkr2Rms = fChain->GetBranch("Tkr2Rms");
   b_Tkr1KalThetaMs = fChain->GetBranch("Tkr1KalThetaMs");
   b_Tkr1Ka2ThetaMs = fChain->GetBranch("Tkr2KalThetaMs");
   b_Tkr1KalEne = fChain->GetBranch("Tkr1KalEne");
   b_Tkr2KalEne = fChain->GetBranch("Tkr2KalEne");
   b_Tkr1EndPos = fChain->GetBranch("Tkr1EndPos");
   b_Tkr2EndPos = fChain->GetBranch("Tkr2EndPos");
   b_Tkr1EndDir = fChain->GetBranch("Tkr1EndDir");
   b_Tkr2EndDir = fChain->GetBranch("Tkr2EndDir");
   b_TkrTopTot = fChain->GetBranch("TkrTopTot");
   b_Tkr1ConvTot = fChain->GetBranch("Tkr1ConvTot");
   b_VtxX0 = fChain->GetBranch("VtxX0");
   b_VtxY0 = fChain->GetBranch("VtxY0");
   b_VtxZ0 = fChain->GetBranch("VtxZ0");
   b_VtxXDir = fChain->GetBranch("VtxXDir");
   b_VtxYDir = fChain->GetBranch("VtxYDir");
   b_VtxZDir = fChain->GetBranch("VtxZDir");
   b_Vtx1Energy = fChain->GetBranch("Vtx1Energy");
   b_Vtx1NumTkrs = fChain->GetBranch("Vtx1NumTkrs");
   b_CalEneSum = fChain->GetBranch("CalEneSum");
   b_CalXEcentr = fChain->GetBranch("CalXEcentr");
   b_CalYEcentr = fChain->GetBranch("CalYEcentr");
   b_CalZEcentr = fChain->GetBranch("CalZEcentr");
   b_CalXtalEne = fChain->GetBranch("CalXtalEne");
   b_CalMaxEne = fChain->GetBranch("CalMaxEne");
   b_CalNumHit = fChain->GetBranch("CalNumHit");
   b_CalXtalPos = fChain->GetBranch("CalXtalPos");
   b_CalMipNum = fChain->GetBranch("CalMipNum");
   b_CalMip1Pos = fChain->GetBranch("CalMip1Pos");
   b_CalMip1Dir = fChain->GetBranch("CalMip1Dir");
   b_CalMip1Chi2 = fChain->GetBranch("CalMip1Chi2");
   b_CalMip1D2edge = fChain->GetBranch("CalMip1D2edge");
   b_CalMip1ArcLen = fChain->GetBranch("CalMip1ArcLen");
   b_CalMip1Ecor = fChain->GetBranch("CalMip1Ecor");
   b_CalMip1EcorRms = fChain->GetBranch("CalMip1EcorRms");
   b_CalMip1Erm = fChain->GetBranch("CalMip1Erm");
   b_CalMip2Pos = fChain->GetBranch("CalMip2Pos");
   b_CalMip2Dir = fChain->GetBranch("CalMip2Dir");
   b_CalMip2Chi2 = fChain->GetBranch("CalMip2Chi2");
   b_CalMip2D2edge = fChain->GetBranch("CalMip2D2edge");
   b_CalMip2ArcLen = fChain->GetBranch("CalMip2ArcLen");
   b_CalMip2Ecor = fChain->GetBranch("CalMip2Ecor");
   b_CalMip2EcorRms = fChain->GetBranch("CalMip2EcorRms");
   b_CalMip2Erm = fChain->GetBranch("CalMip2Erm");
   b_GltWord = fChain->GetBranch("GltWord");
   b_ContextRunInfoPlatform = fChain->GetBranch("ContextRunInfoPlatform");
   b_ContextRunInfoDataOrigin = fChain->GetBranch("ContextRunInfoDataOrigin");
   b_ContextRunInfoID = fChain->GetBranch("ContextRunInfoID");
   b_ContextRunInfoStartTime = fChain->GetBranch("ContextRunInfoStartTime");
   b_ContextDataGramInfoModeChanges = fChain->GetBranch("ContextDataGramInfoModeChanges");
   b_ContextDataGramInfoDatagrams = fChain->GetBranch("ContextDataGramInfoDatagrams");
   b_ContextDataGramInfoOpenAction = fChain->GetBranch("ContextDataGramInfoOpenAction");
   b_ContextDataGramInfoOpenReason = fChain->GetBranch("ContextDataGramInfoOpenReason");
   b_ContextDataGramInfoCrate = fChain->GetBranch("ContextDataGramInfoCrate");
   b_ContextDataGramInfoMode = fChain->GetBranch("ContextDataGramInfoMode");
   b_ContextDataGramInfoCloseAction = fChain->GetBranch("ContextDataGramInfoCloseAction");
   b_ContextDataGramInfoCloseReason = fChain->GetBranch("ContextDataGramInfoCloseReason");
   b_ContextGemScalersElapsed = fChain->GetBranch("ContextGemScalersElapsed");
   b_ContextGemScalersLivetime = fChain->GetBranch("ContextGemScalersLivetime");
   b_ContextGemScalersPrescaled = fChain->GetBranch("ContextGemScalersPrescaled");
   b_ContextGemScalersDiscarded = fChain->GetBranch("ContextGemScalersDiscarded");
   b_ContextGemScalersSequence = fChain->GetBranch("ContextGemScalersSequence");
   b_ContextGemScalersDeadzone = fChain->GetBranch("ContextGemScalersDeadzone");
   b_ContextLsfTimeTimeToneCurrentIncomplete = fChain->GetBranch("ContextLsfTimeTimeToneCurrentIncomplete");
   b_ContextLsfTimeTimeToneCurrentTimeSecs = fChain->GetBranch("ContextLsfTimeTimeToneCurrentTimeSecs");
   b_ContextLsfTimeTimeToneCurrentFlywheeling = fChain->GetBranch("ContextLsfTimeTimeToneCurrentFlywheeling");
   b_ContextLsfTimeTimeToneCurrentFlagsValid = fChain->GetBranch("ContextLsfTimeTimeToneCurrentFlagsValid");
   b_ContextLsfTimeTimeToneCurrentMissingGps = fChain->GetBranch("ContextLsfTimeTimeToneCurrentMissingGps");
   b_ContextLsfTimeTimeToneCurrentMissingCpuPps = fChain->GetBranch("ContextLsfTimeTimeToneCurrentMissingCpuPps");
   b_ContextLsfTimeTimeToneCurrentMissingLatPps = fChain->GetBranch("ContextLsfTimeTimeToneCurrentMissingLatPps");
   b_ContextLsfTimeTimeToneCurrentMissingTimeTone = fChain->GetBranch("ContextLsfTimeTimeToneCurrentMissingTimeTone");
   b_ContextLsfTimeTimeToneCurrentGemTimeHacks = fChain->GetBranch("ContextLsfTimeTimeToneCurrentGemTimeHacks");
   b_ContextLsfTimeTimeToneCurrentGemTimeTicks = fChain->GetBranch("ContextLsfTimeTimeToneCurrentGemTimeTicks");
   b_ContextLsfTimeTimeTonePreviousIncomplete = fChain->GetBranch("ContextLsfTimeTimeTonePreviousIncomplete");
   b_ContextLsfTimeTimeTonePreviousTimeSecs = fChain->GetBranch("ContextLsfTimeTimeTonePreviousTimeSecs");
   b_ContextLsfTimeTimeTonePreviousFlywheeling = fChain->GetBranch("ContextLsfTimeTimeTonePreviousFlywheeling");
   b_ContextLsfTimeTimeTonePreviousFlagsValid = fChain->GetBranch("ContextLsfTimeTimeTonePreviousFlagsValid");
   b_ContextLsfTimeTimeTonePreviousMissingGps = fChain->GetBranch("ContextLsfTimeTimeTonePreviousMissingGps");
   b_ContextLsfTimeTimeTonePreviousMissingCpuPps = fChain->GetBranch("ContextLsfTimeTimeTonePreviousMissingCpuPps");
   b_ContextLsfTimeTimeTonePreviousMissingLatPps = fChain->GetBranch("ContextLsfTimeTimeTonePreviousMissingLatPps");
   b_ContextLsfTimeTimeTonePreviousMissingTimeTone = fChain->GetBranch("ContextLsfTimeTimeTonePreviousMissingTimeTone");
   b_ContextLsfTimeTimeTonePreviousGemTimeHacks = fChain->GetBranch("ContextLsfTimeTimeTonePreviousGemTimeHacks");
   b_ContextLsfTimeTimeTonePreviousGemTimeTicks = fChain->GetBranch("ContextLsfTimeTimeTonePreviousGemTimeTicks");
   b_ContextLsfTimeTimeTicks = fChain->GetBranch("ContextLsfTimeTimeTicks");
   b_ContextLsfTimeHackHacks = fChain->GetBranch("ContextLsfTimeHackHacks");
   b_ContextLsfTimeHackTicks = fChain->GetBranch("ContextLsfTimeHackTicks");
   b_ContextRunType = fChain->GetBranch("ContextRunType");
   b_GemConditionsWord = fChain->GetBranch("GemConditionsWord");
   b_GemTkrVector = fChain->GetBranch("GemTkrVector");
   b_GemRoiVector = fChain->GetBranch("GemRoiVector");
   b_GemCalLeVector = fChain->GetBranch("GemCalLeVector");
   b_GemCalHeVector = fChain->GetBranch("GemCalHeVector");
   b_GemCnoVector = fChain->GetBranch("GemCnoVector");
   b_GemLiveTime = fChain->GetBranch("GemLiveTime");
   b_GemTriggerTime = fChain->GetBranch("GemTriggerTime");
   b_GemDeltaEventTime = fChain->GetBranch("GemDeltaEventTime");
   b_GemOnePpsSeconds = fChain->GetBranch("GemOnePpsSeconds");
   b_GemOnePpsTime = fChain->GetBranch("GemOnePpsTime");
   b_GemPrescaled = fChain->GetBranch("GemPrescaled");
   b_GemDiscarded = fChain->GetBranch("GemDiscarded");
   b_GemCondArrivalTimeWord = fChain->GetBranch("GemCondArrivalTimeWord");
   b_GemCondArrivalTimeExt = fChain->GetBranch("GemCondArrivalTimeExt");
   b_GemCondArrivalTimeCno = fChain->GetBranch("GemCondArrivalTimeCno");
   b_GemCondArrivalTimeCalLe = fChain->GetBranch("GemCondArrivalTimeCalLe");
   b_GemCondArrivalTimeCalHe = fChain->GetBranch("GemCondArrivalTimeCalHe");
   b_GemCondArrivalTimeTkr = fChain->GetBranch("GemCondArrivalTimeTkr");
   b_GemCondArrivalTimeRoi = fChain->GetBranch("GemCondArrivalTimeRoi");
   b_GemDeltaWindowOpenTime = fChain->GetBranch("GemDeltaWindowOpenTime");
   b_GemDeadZone = fChain->GetBranch("GemDeadZone");
   b_GemAcdTilesXzp = fChain->GetBranch("GemAcdTilesXzp");
   b_GemAcdTilesXzm = fChain->GetBranch("GemAcdTilesXzm");
   b_GemAcdTilesYzp = fChain->GetBranch("GemAcdTilesYzp");
   b_GemAcdTilesYzm = fChain->GetBranch("GemAcdTilesYzm");
   b_GemAcdTilesXy = fChain->GetBranch("GemAcdTilesXy");
   b_GemAcdTilesRbn = fChain->GetBranch("GemAcdTilesRbn");
   b_GemAcdTilesNa = fChain->GetBranch("GemAcdTilesNa");
   b_DigiTriRowBits = fChain->GetBranch("DigiTriRowBits");
   b_TrgReqTriRowBits = fChain->GetBranch("TrgReqTriRowBits");
   b_TkrReq = fChain->GetBranch("TkrReq");
   b_TkrTp = fChain->GetBranch("TkrTp");
   b_CalReq = fChain->GetBranch("CalReq");
   b_CalTp = fChain->GetBranch("CalTp");
   b_DiagLength = fChain->GetBranch("DiagLength");
   b_TemLength = fChain->GetBranch("TemLength");
   b_GemLength = fChain->GetBranch("GemLength");
   b_OswLength = fChain->GetBranch("OswLength");
   b_AemLength = fChain->GetBranch("AemLength");
   b_ErrLength = fChain->GetBranch("ErrLength");
   b_AcdNumDigis = fChain->GetBranch("AcdNumDigis");
   b_AcdPha = fChain->GetBranch("AcdPha");
   b_AcdHitMap = fChain->GetBranch("AcdHitMap");
   b_AcdRange = fChain->GetBranch("AcdRange");
   b_AcdOddParityError = fChain->GetBranch("AcdOddParityError");
   b_AcdHeaderParityError = fChain->GetBranch("AcdHeaderParityError");
   b_AcdLowDisc = fChain->GetBranch("AcdLowDisc");
   b_Acd10Ids = fChain->GetBranch("Acd10Ids");
   b_AcdTileNumber = fChain->GetBranch("AcdTileNumber");
   b_AcdMCEnergy = fChain->GetBranch("AcdMCEnergy");
   b_AcdNaPha = fChain->GetBranch("AcdNaPha");
   b_AcdNaHitMap = fChain->GetBranch("AcdNaHitMap");
   b_AcdNaRange = fChain->GetBranch("AcdNaRange");
   b_AcdNaOddParityError = fChain->GetBranch("AcdNaOddParityError");
   b_AcdNaHeaderParityError = fChain->GetBranch("AcdNaHeaderParityError");
   b_AcdNaLowDisc = fChain->GetBranch("AcdNaLowDisc");
   b_AcdTileMCEnergy = fChain->GetBranch("AcdTileMCEnergy");
   b_AcdDoca = fChain->GetBranch("AcdDoca");
   b_AcdTileCount = fChain->GetBranch("AcdTileCount");
   b_AcdActiveDist = fChain->GetBranch("AcdActiveDist");
   b_AcdMinDocaId = fChain->GetBranch("AcdMinDocaId");
   b_AcdRibbonMCEnergy = fChain->GetBranch("AcdRibbonMCEnergy");
   b_AcdRibbonCount = fChain->GetBranch("AcdRibbonCount");
   b_AcdRibbonActiveDist = fChain->GetBranch("AcdRibbonActiveDist");
   b_AcdMaxActiveDistId = fChain->GetBranch("AcdMaxActiveDistId");
   b_AcdRibbonActiveDistId = fChain->GetBranch("AcdRibbonActiveDistId");
   b_AcdCornerDoca = fChain->GetBranch("AcdCornerDoca");
   b_AcdNumTkrIntSec = fChain->GetBranch("AcdNumTkrIntSec");
   b_AcdTkrIntSecTileId = fChain->GetBranch("AcdTkrIntSecTileId");
   b_AcdTkrIntSecTkrIndex = fChain->GetBranch("AcdTkrIntSecTkrIndex");
   b_AcdTkrIntSecGlobalX = fChain->GetBranch("AcdTkrIntSecGlobalX");
   b_AcdTkrIntSecGlobalY = fChain->GetBranch("AcdTkrIntSecGlobalY");
   b_AcdTkrIntSecGlobalZ = fChain->GetBranch("AcdTkrIntSecGlobalZ");
   b_AcdTkrIntSecLocalX = fChain->GetBranch("AcdTkrIntSecLocalX");
   b_AcdTkrIntSecLocalY = fChain->GetBranch("AcdTkrIntSecLocalY");
   b_AcdTkrIntSecLocalXXCov = fChain->GetBranch("AcdTkrIntSecLocalXXCov");
   b_AcdTkrIntSecLocalYYCov = fChain->GetBranch("AcdTkrIntSecLocalYYCov");
   b_AcdTkrIntSecLocalXYCov = fChain->GetBranch("AcdTkrIntSecLocalXYCov");
   b_AcdTkrIntSecArcLengthToIntSec = fChain->GetBranch("AcdTkrIntSecArcLengthToIntSec");
   b_AcdTkrIntSecPathLengthInTile = fChain->GetBranch("AcdTkrIntSecPathLengthInTile");
   b_AcdTkrIntSecTileHit = fChain->GetBranch("AcdTkrIntSecTileHit");
   b_AcdMips = fChain->GetBranch("AcdMips");
   b_AcdMipsPha = fChain->GetBranch("AcdMipsPha");
   b_AcdMipsFlag = fChain->GetBranch("AcdMipsFlag");
   b_AcdMipsMax = fChain->GetBranch("AcdMipsMax");
   b_AcdMipsMaxTileID = fChain->GetBranch("AcdMipsMaxTileID");
   b_AcdMipsMaxPmt = fChain->GetBranch("AcdMipsMaxPmt");
   b_AcdMipsSum = fChain->GetBranch("AcdMipsSum");
   b_AcdPocaDoca = fChain->GetBranch("AcdPocaDoca");
   b_AcdPocaDocaErr = fChain->GetBranch("AcdPocaDocaErr");
   b_AcdPocaDocaRegion = fChain->GetBranch("AcdPocaDocaRegion");
   b_AcdPocaX = fChain->GetBranch("AcdPocaX");
   b_AcdPocaY = fChain->GetBranch("AcdPocaY");
   b_AcdPocaZ = fChain->GetBranch("AcdPocaZ");
   b_AcdPocaDirX = fChain->GetBranch("AcdPocaDirX");
   b_AcdPocaDirY = fChain->GetBranch("AcdPocaDirY");
   b_AcdPocaDirZ = fChain->GetBranch("AcdPocaDirZ");
   b_AcdPocaTileID = fChain->GetBranch("AcdPocaTileID");
   b_AcdPocaTrackID = fChain->GetBranch("AcdPocaTrackID");
   b_AcdPocaNbrTrack1 = fChain->GetBranch("AcdPocaNbrTrack1");
   b_AcdPocaNbrTrack2 = fChain->GetBranch("AcdPocaNbrTrack2");
   b_AcdGapPocaDoca = fChain->GetBranch("AcdGapPocaDoca");
   b_AcdGapPocaTileID = fChain->GetBranch("AcdGapPocaTileID");
   b_AcdGapPocaTrackID = fChain->GetBranch("AcdGapPocaTrackID");
   b_AcdGapPocaNbrTrack1 = fChain->GetBranch("AcdGapPocaNbrTrack1");
   b_AcdGapPocaNbrTrack2 = fChain->GetBranch("AcdGapPocaNbrTrack2");
   b_AcdTkrPointX = fChain->GetBranch("AcdTkrPointX");
   b_AcdTkrPointY = fChain->GetBranch("AcdTkrPointY");
   b_AcdTkrPointZ = fChain->GetBranch("AcdTkrPointZ");
   b_AcdTkrPointFace = fChain->GetBranch("AcdTkrPointFace");
   b_CCSDSTime = fChain->GetBranch("CCSDSTime");
   b_CCSDSapID = fChain->GetBranch("CCSDSapID");
   b_CCSDSscID = fChain->GetBranch("CCSDSscID");

   return kTRUE;
}

void SvacEvent::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SvacEvent::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SvacEvent_cxx
