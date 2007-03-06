//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  6 11:38:51 2007 by ROOT version 5.10/00
// from TTree MeritTuple/Glast tuple
// found on file: /nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/recon/recon-v3r9p1_077014005_merit_merit.root
//////////////////////////////////////////////////////////

#ifndef MeritEvent_h
#define MeritEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>

class MeritEvent: public TObject{
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Float_t         McSourceId;
   Float_t         McNumIncident;
   Float_t         McId;
   Float_t         McCharge;
   Float_t         McEnergy;
   Float_t         McLogEnergy;
   Float_t         McEFrac;
   Float_t         McOpenAngle;
   Float_t         McTkrExitEne;
   Float_t         McX0;
   Float_t         McY0;
   Float_t         McZ0;
   Float_t         McXDir;
   Float_t         McYDir;
   Float_t         McZDir;
   Float_t         McXErr;
   Float_t         McYErr;
   Float_t         McZErr;
   Float_t         McXDirErr;
   Float_t         McYDirErr;
   Float_t         McZDirErr;
   Float_t         McDirErr;
   Float_t         McTkr1DirErr;
   Float_t         McTkr2DirErr;
   Float_t         GltWord;
   Float_t         GltGemSummary;
   Float_t         GltEventFlags;
   Float_t         GltTower;
   Float_t         GltXTower;
   Float_t         GltYTower;
   Float_t         GltLayer;
   Float_t         GltTotal;
   Float_t         GltNumTowers;
   Float_t         GltType;
   Float_t         GltMoment;
   Float_t         GltZDir;
   Float_t         TkrNumTracks;
   Float_t         TkrSumKalEne;
   Float_t         TkrSumConEne;
   Float_t         TkrEnergy;
   Float_t         TkrEnergyCorr;
   Float_t         TkrHDCount;
   Float_t         TkrTotalHits;
   Float_t         TkrThinHits;
   Float_t         TkrThickHits;
   Float_t         TkrBlankHits;
   Float_t         TkrRadLength;
   Float_t         TkrTwrEdge;
   Float_t         TkrTrackLength;
   Float_t         TkrSurplusHCInside;
   Float_t         TkrSurplusHitRatio;
   Float_t         TkrUpstreamHC;
   Float_t         TkrDispersion;
   Float_t         Tkr1Chisq;
   Float_t         Tkr1FirstChisq;
   Float_t         Tkr1Hits;
   Float_t         Tkr1FirstHits;
   Float_t         Tkr1FirstLayer;
   Float_t         Tkr1LastLayer;
   Float_t         Tkr1DifHits;
   Float_t         Tkr1Gaps;
   Float_t         Tkr1FirstGapPlane;
   Float_t         Tkr1XGap;
   Float_t         Tkr1YGap;
   Float_t         Tkr1FirstGaps;
   Float_t         Tkr1Qual;
   Float_t         Tkr1Type;
   Float_t         Tkr1TwrEdge;
   Float_t         Tkr1PrjTwrEdge;
   Float_t         Tkr1DieEdge;
   Float_t         Tkr1TwrGap;
   Float_t         Tkr1KalEne;
   Float_t         Tkr1ConEne;
   Float_t         Tkr1KalThetaMS;
   Float_t         Tkr1XDir;
   Float_t         Tkr1YDir;
   Float_t         Tkr1ZDir;
   Float_t         Tkr1Phi;
   Float_t         Tkr1Theta;
   Float_t         Tkr1X0;
   Float_t         Tkr1Y0;
   Float_t         Tkr1Z0;
   Float_t         Tkr1ThetaErr;
   Float_t         Tkr1PhiErr;
   Float_t         Tkr1ErrAsym;
   Float_t         Tkr1CovDet;
   Float_t         Tkr1SXX;
   Float_t         Tkr1SXY;
   Float_t         Tkr1SYY;
   Float_t         Tkr1ToTFirst;
   Float_t         Tkr1ToTAve;
   Float_t         Tkr1ToTTrAve;
   Float_t         Tkr1ToTAsym;
   Float_t         Tkr1ChisqAsym;
   Float_t         Tkr1SSDVeto;
   Float_t         Tkr1CoreHC;
   Float_t         Tkr1LATEdge;
   Float_t         Tkr2Chisq;
   Float_t         Tkr2FirstChisq;
   Float_t         Tkr2Hits;
   Float_t         Tkr2FirstHits;
   Float_t         Tkr2FirstLayer;
   Float_t         Tkr2LastLayer;
   Float_t         Tkr2DifHits;
   Float_t         Tkr2Gaps;
   Float_t         Tkr2FirstGaps;
   Float_t         Tkr2Qual;
   Float_t         Tkr2Type;
   Float_t         Tkr2TwrEdge;
   Float_t         Tkr2PrjTwrEdge;
   Float_t         Tkr2DieEdge;
   Float_t         Tkr2KalEne;
   Float_t         Tkr2ConEne;
   Float_t         Tkr2KalThetaMS;
   Float_t         Tkr2XDir;
   Float_t         Tkr2YDir;
   Float_t         Tkr2ZDir;
   Float_t         Tkr2Phi;
   Float_t         Tkr2Theta;
   Float_t         Tkr2X0;
   Float_t         Tkr2Y0;
   Float_t         Tkr2Z0;
   Float_t         Tkr2TkrAngle;
   Float_t         Tkr2TkrHDoca;
   Float_t         VtxXDir;
   Float_t         VtxYDir;
   Float_t         VtxZDir;
   Float_t         VtxPhi;
   Float_t         VtxTheta;
   Float_t         VtxThetaErr;
   Float_t         VtxPhiErr;
   Float_t         VtxSXX;
   Float_t         VtxSXY;
   Float_t         VtxSYY;
   Float_t         VtxX0;
   Float_t         VtxY0;
   Float_t         VtxZ0;
   Float_t         VtxAngle;
   Float_t         VtxDOCA;
   Float_t         VtxHeadSep;
   Float_t         VtxStatus;
   Float_t         VtxQuality;
   Float_t         VtxChisq;
   Float_t         VtxS1;
   Float_t         VtxS2;
   Float_t         VtxAddedRL;
   Float_t         CalEnergyRaw;
   Float_t         CalEnergyCorr;
   Float_t         CalLeakCorr;
   Float_t         CalEdgeCorr;
   Float_t         CalTotalCorr;
   Float_t         CalCsIRLn;
   Float_t         CalTotRLn;
   Float_t         CalCntRLn;
   Float_t         CalLATRLn;
   Float_t         CalDeadTotRat;
   Float_t         CalDeadCntRat;
   Float_t         CalTPred;
   Float_t         CalDeltaT;
   Float_t         CalGapFraction;
   Float_t         CalTwrEdgeCntr;
   Float_t         CalTwrEdge;
   Float_t         CalLATEdge;
   Float_t         CalEdgeEnergy;
   Float_t         CalTrackDoca;
   Float_t         CalTrackAngle;
   Float_t         CalTrackSep;
   Float_t         CalELayer0;
   Float_t         CalELayer1;
   Float_t         CalELayer2;
   Float_t         CalELayer3;
   Float_t         CalELayer4;
   Float_t         CalELayer5;
   Float_t         CalELayer6;
   Float_t         CalELayer7;
   Float_t         CalLyr0Ratio;
   Float_t         CalLyr7Ratio;
   Float_t         CalBkHalfRatio;
   Float_t         CalXtalsTrunc;
   Float_t         CalXtalRatio;
   Float_t         CalXtalMaxEne;
   Float_t         CalTransRms;
   Float_t         CalLongRms;
   Float_t         CalLRmsAsym;
   Float_t         CalMIPDiff;
   Float_t         CalMIPRatio;
   Float_t         CalXEcntr;
   Float_t         CalYEcntr;
   Float_t         CalZEcntr;
   Float_t         CalXDir;
   Float_t         CalYDir;
   Float_t         CalZDir;
   Float_t         CalX0;
   Float_t         CalY0;
   Float_t         CalTrkXtalRms;
   Float_t         CalTrkXtalRmsE;
   Float_t         CalTrkXtalRmsTrunc;
   Float_t         CalTrkXtalRmsETrunc;
   Float_t         CalCfpEnergy;
   Float_t         CalCfpChiSq;
   Float_t         CalCfpEffRLn;
   Float_t         CalLllEnergy;
   Float_t         CalLllEneErr;
   Float_t         CalTklEnergy;
   Float_t         CalTklEneErr;
   Float_t         CalLkHdEnergy;
   Float_t         CalLkHdEneErr;
   Float_t         CalRmsLayerE;
   Float_t         CalRmsLayerEBack;
   Int_t           CalNLayersRmsBack;
   Float_t         CalEAveBack;
   Float_t         CalLayer0Ratio;
   Float_t         AcdTotalEnergy;
   Float_t         AcdRibbonEnergy;
   Float_t         AcdRibbonCount;
   Float_t         AcdTileCount;
   Float_t         AcdDoca;
   Float_t         AcdDocaTileEnergy;
   Float_t         AcdActiveDist;
   Float_t         AcdActiveDist3D;
   Float_t         AcdActDistTileEnergy;
   Float_t         AcdGammaDoca;
   Float_t         AcdCornerDoca;
   Float_t         AcdTkrRibbonDist;
   Float_t         AcdTkr1RibbonDist;
   Float_t         AcdActDistTop;
   Float_t         AcdActDistSideRow0;
   Float_t         AcdActDistSideRow1;
   Float_t         AcdActDistSideRow2;
   Float_t         AcdActDist3DTop;
   Float_t         AcdActDist3DSideRow0;
   Float_t         AcdActDist3DSideRow1;
   Float_t         AcdActDist3DSideRow2;
   Float_t         AcdNoTop;
   Float_t         AcdNoSideRow0;
   Float_t         AcdNoSideRow1;
   Float_t         AcdNoSideRow2;
   Float_t         AcdNoSideRow3;
   Float_t         AcdRibbonActDist;
   Float_t         AcdTkrHitsCountTop;
   Float_t         AcdTkrHitsCountR0;
   Float_t         AcdTkrHitsCountR1;
   Float_t         AcdTkrHitsCountR2;
   Float_t         AcdTkrHitsCountR3;
   UInt_t          EvtRun;
   UInt_t          EvtEventId;
   Double_t        EvtElapsedTime;
   Float_t         EvtLiveTime;
   Float_t         EvtEnergyCorr;
   Float_t         EvtEnergyRaw;
   Float_t         EvtDeltaEoE;
   Float_t         EvtCalEdgeAngle;
   Float_t         EvtTkrEdgeAngle;
   Float_t         EvtLogEnergy;
   Float_t         EvtTkr1EFrac;
   Float_t         EvtVtxKin;
   Float_t         EvtVtxEAngle;
   Float_t         EvtTkrComptonRatio;
   Float_t         EvtETkrComptonRatio;
   Float_t         EvtPSFModel;
   Float_t         EvtETkr1Chisq;
   Float_t         EvtETkr1FirstChisq;
   Float_t         EvtETkr1Qual;
   Float_t         EvtTkr1PSFMdRat;
   Float_t         EvtECalXtalRatio;
   Float_t         EvtECalXtalTrunc;
   Float_t         EvtECalTrackDoca;
   Float_t         EvtECalTrackSep;
   Float_t         EvtECalTransRms;
   Float_t         EvtECalLongRms;
   Float_t         EvtECalLRmsAsym;
   Float_t         EvtECalTrackAngle;
   Float_t         EvtEVtxAngle;
   Float_t         EvtEVtxDoca;
   Float_t         CalMipNum;
   Float_t         CalMipX0;
   Float_t         CalMipY0;
   Float_t         CalMipZ0;
   Float_t         CalMipXDir;
   Float_t         CalMipYDir;
   Float_t         CalMipZDir;
   Float_t         CalMipD2edge;
   Float_t         CalMipArcLen;
   Float_t         CalMipEcor;
   Float_t         CalMipEcorRms;
   Float_t         CalMipChi2;
   Float_t         CalMipErm;
   Double_t        FilterStatus_HI;
   Double_t        FilterStatus_LO;
   Double_t        FilterAlgStatus;
   Double_t        FilterAngSep;
   Float_t         CTBAcdLowerTileCount;
   Float_t         CTBAcdUpperTileCount;
   Float_t         CTBBestDeltaEoE;
   Float_t         CTBBestEnergy;
   Float_t         CTBBestEnergyProb;
   Float_t         CTBBestEnergyRatio;
   Float_t         CTBBestLogEnergy;
   Float_t         CTBBestPSFerr;
   Float_t         CTBBestXDir;
   Float_t         CTBBestYDir;
   Float_t         CTBBestZDir;
   Float_t         CTBCORE;
   Float_t         CTBCalDocaAngle;
   Float_t         CTBCalFrontBackRatio;
   Float_t         CTBCalMaxXtalRatio;
   Float_t         CTBCalTransTCCD;
   Float_t         CTBDiffCalDOCACalXtalRms;
   Float_t         CTBGAM;
   Float_t         CTBLastLayerProb;
   Float_t         CTBLkhdEnergyRatio;
   Float_t         CTBParamProb;
   Float_t         CTBProfEnergyRatio;
   Float_t         CTBProfileProb;
   Float_t         CTBSecondaryCTBGAM;
   Float_t         CTBSummedCTBGAM;
   Float_t         CTBTkrCoreCalDoca;
   Float_t         CTBTkrEnergyFrac;
   Float_t         CTBTkrLATEdge;
   Float_t         CTBTkrSHRCalAngle;
   Float_t         CTBTrackerProb;
   Float_t         CTBVTX;
   Float_t         CTBVtxTkr1Angle;
   Float_t         CTBminCTBGAM;
   UInt_t          FT1EventId;
   Float_t         FT1Energy;
   Float_t         FT1Theta;
   Float_t         FT1Phi;
   Float_t         FT1Ra;
   Float_t         FT1Dec;
   Float_t         FT1L;
   Float_t         FT1B;
   Float_t         FT1ZenithTheta;
   Float_t         FT1EarthAzimuth;
   Float_t         FT1ConvPointX;
   Float_t         FT1ConvPointY;
   Float_t         FT1ConvPointZ;
   Float_t         FT1ConvLayer;
   Float_t         FT1Livetime;

   // List of branches
   TBranch        *b_McSourceId;   //!
   TBranch        *b_McNumIncident;   //!
   TBranch        *b_McId;   //!
   TBranch        *b_McCharge;   //!
   TBranch        *b_McEnergy;   //!
   TBranch        *b_McLogEnergy;   //!
   TBranch        *b_McEFrac;   //!
   TBranch        *b_McOpenAngle;   //!
   TBranch        *b_McTkrExitEne;   //!
   TBranch        *b_McX0;   //!
   TBranch        *b_McY0;   //!
   TBranch        *b_McZ0;   //!
   TBranch        *b_McXDir;   //!
   TBranch        *b_McYDir;   //!
   TBranch        *b_McZDir;   //!
   TBranch        *b_McXErr;   //!
   TBranch        *b_McYErr;   //!
   TBranch        *b_McZErr;   //!
   TBranch        *b_McXDirErr;   //!
   TBranch        *b_McYDirErr;   //!
   TBranch        *b_McZDirErr;   //!
   TBranch        *b_McDirErr;   //!
   TBranch        *b_McTkr1DirErr;   //!
   TBranch        *b_McTkr2DirErr;   //!
   TBranch        *b_GltWord;   //!
   TBranch        *b_GltGemSummary;   //!
   TBranch        *b_GltEventFlags;   //!
   TBranch        *b_GltTower;   //!
   TBranch        *b_GltXTower;   //!
   TBranch        *b_GltYTower;   //!
   TBranch        *b_GltLayer;   //!
   TBranch        *b_GltTotal;   //!
   TBranch        *b_GltNumTowers;   //!
   TBranch        *b_GltType;   //!
   TBranch        *b_GltMoment;   //!
   TBranch        *b_GltZDir;   //!
   TBranch        *b_TkrNumTracks;   //!
   TBranch        *b_TkrSumKalEne;   //!
   TBranch        *b_TkrSumConEne;   //!
   TBranch        *b_TkrEnergy;   //!
   TBranch        *b_TkrEnergyCorr;   //!
   TBranch        *b_TkrHDCount;   //!
   TBranch        *b_TkrTotalHits;   //!
   TBranch        *b_TkrThinHits;   //!
   TBranch        *b_TkrThickHits;   //!
   TBranch        *b_TkrBlankHits;   //!
   TBranch        *b_TkrRadLength;   //!
   TBranch        *b_TkrTwrEdge;   //!
   TBranch        *b_TkrTrackLength;   //!
   TBranch        *b_TkrSurplusHCInside;   //!
   TBranch        *b_TkrSurplusHitRatio;   //!
   TBranch        *b_TkrUpstreamHC;   //!
   TBranch        *b_TkrDispersion;   //!
   TBranch        *b_Tkr1Chisq;   //!
   TBranch        *b_Tkr1FirstChisq;   //!
   TBranch        *b_Tkr1Hits;   //!
   TBranch        *b_Tkr1FirstHits;   //!
   TBranch        *b_Tkr1FirstLayer;   //!
   TBranch        *b_Tkr1LastLayer;   //!
   TBranch        *b_Tkr1DifHits;   //!
   TBranch        *b_Tkr1Gaps;   //!
   TBranch        *b_Tkr1FirstGapPlane;   //!
   TBranch        *b_Tkr1XGap;   //!
   TBranch        *b_Tkr1YGap;   //!
   TBranch        *b_Tkr1FirstGaps;   //!
   TBranch        *b_Tkr1Qual;   //!
   TBranch        *b_Tkr1Type;   //!
   TBranch        *b_Tkr1TwrEdge;   //!
   TBranch        *b_Tkr1PrjTwrEdge;   //!
   TBranch        *b_Tkr1DieEdge;   //!
   TBranch        *b_Tkr1TwrGap;   //!
   TBranch        *b_Tkr1KalEne;   //!
   TBranch        *b_Tkr1ConEne;   //!
   TBranch        *b_Tkr1KalThetaMS;   //!
   TBranch        *b_Tkr1XDir;   //!
   TBranch        *b_Tkr1YDir;   //!
   TBranch        *b_Tkr1ZDir;   //!
   TBranch        *b_Tkr1Phi;   //!
   TBranch        *b_Tkr1Theta;   //!
   TBranch        *b_Tkr1X0;   //!
   TBranch        *b_Tkr1Y0;   //!
   TBranch        *b_Tkr1Z0;   //!
   TBranch        *b_Tkr1ThetaErr;   //!
   TBranch        *b_Tkr1PhiErr;   //!
   TBranch        *b_Tkr1ErrAsym;   //!
   TBranch        *b_Tkr1CovDet;   //!
   TBranch        *b_Tkr1SXX;   //!
   TBranch        *b_Tkr1SXY;   //!
   TBranch        *b_Tkr1SYY;   //!
   TBranch        *b_Tkr1ToTFirst;   //!
   TBranch        *b_Tkr1ToTAve;   //!
   TBranch        *b_Tkr1ToTTrAve;   //!
   TBranch        *b_Tkr1ToTAsym;   //!
   TBranch        *b_Tkr1ChisqAsym;   //!
   TBranch        *b_Tkr1SSDVeto;   //!
   TBranch        *b_Tkr1CoreHC;   //!
   TBranch        *b_Tkr1LATEdge;   //!
   TBranch        *b_Tkr2Chisq;   //!
   TBranch        *b_Tkr2FirstChisq;   //!
   TBranch        *b_Tkr2Hits;   //!
   TBranch        *b_Tkr2FirstHits;   //!
   TBranch        *b_Tkr2FirstLayer;   //!
   TBranch        *b_Tkr2LastLayer;   //!
   TBranch        *b_Tkr2DifHits;   //!
   TBranch        *b_Tkr2Gaps;   //!
   TBranch        *b_Tkr2FirstGaps;   //!
   TBranch        *b_Tkr2Qual;   //!
   TBranch        *b_Tkr2Type;   //!
   TBranch        *b_Tkr2TwrEdge;   //!
   TBranch        *b_Tkr2PrjTwrEdge;   //!
   TBranch        *b_Tkr2DieEdge;   //!
   TBranch        *b_Tkr2KalEne;   //!
   TBranch        *b_Tkr2ConEne;   //!
   TBranch        *b_Tkr2KalThetaMS;   //!
   TBranch        *b_Tkr2XDir;   //!
   TBranch        *b_Tkr2YDir;   //!
   TBranch        *b_Tkr2ZDir;   //!
   TBranch        *b_Tkr2Phi;   //!
   TBranch        *b_Tkr2Theta;   //!
   TBranch        *b_Tkr2X0;   //!
   TBranch        *b_Tkr2Y0;   //!
   TBranch        *b_Tkr2Z0;   //!
   TBranch        *b_Tkr2TkrAngle;   //!
   TBranch        *b_Tkr2TkrHDoca;   //!
   TBranch        *b_VtxXDir;   //!
   TBranch        *b_VtxYDir;   //!
   TBranch        *b_VtxZDir;   //!
   TBranch        *b_VtxPhi;   //!
   TBranch        *b_VtxTheta;   //!
   TBranch        *b_VtxThetaErr;   //!
   TBranch        *b_VtxPhiErr;   //!
   TBranch        *b_VtxSXX;   //!
   TBranch        *b_VtxSXY;   //!
   TBranch        *b_VtxSYY;   //!
   TBranch        *b_VtxX0;   //!
   TBranch        *b_VtxY0;   //!
   TBranch        *b_VtxZ0;   //!
   TBranch        *b_VtxAngle;   //!
   TBranch        *b_VtxDOCA;   //!
   TBranch        *b_VtxHeadSep;   //!
   TBranch        *b_VtxStatus;   //!
   TBranch        *b_VtxQuality;   //!
   TBranch        *b_VtxChisq;   //!
   TBranch        *b_VtxS1;   //!
   TBranch        *b_VtxS2;   //!
   TBranch        *b_VtxAddedRL;   //!
   TBranch        *b_CalEnergyRaw;   //!
   TBranch        *b_CalEnergyCorr;   //!
   TBranch        *b_CalLeakCorr;   //!
   TBranch        *b_CalEdgeCorr;   //!
   TBranch        *b_CalTotalCorr;   //!
   TBranch        *b_CalCsIRLn;   //!
   TBranch        *b_CalTotRLn;   //!
   TBranch        *b_CalCntRLn;   //!
   TBranch        *b_CalLATRLn;   //!
   TBranch        *b_CalDeadTotRat;   //!
   TBranch        *b_CalDeadCntRat;   //!
   TBranch        *b_CalTPred;   //!
   TBranch        *b_CalDeltaT;   //!
   TBranch        *b_CalGapFraction;   //!
   TBranch        *b_CalTwrEdgeCntr;   //!
   TBranch        *b_CalTwrEdge;   //!
   TBranch        *b_CalLATEdge;   //!
   TBranch        *b_CalEdgeEnergy;   //!
   TBranch        *b_CalTrackDoca;   //!
   TBranch        *b_CalTrackAngle;   //!
   TBranch        *b_CalTrackSep;   //!
   TBranch        *b_CalELayer0;   //!
   TBranch        *b_CalELayer1;   //!
   TBranch        *b_CalELayer2;   //!
   TBranch        *b_CalELayer3;   //!
   TBranch        *b_CalELayer4;   //!
   TBranch        *b_CalELayer5;   //!
   TBranch        *b_CalELayer6;   //!
   TBranch        *b_CalELayer7;   //!
   TBranch        *b_CalLyr0Ratio;   //!
   TBranch        *b_CalLyr7Ratio;   //!
   TBranch        *b_CalBkHalfRatio;   //!
   TBranch        *b_CalXtalsTrunc;   //!
   TBranch        *b_CalXtalRatio;   //!
   TBranch        *b_CalXtalMaxEne;   //!
   TBranch        *b_CalTransRms;   //!
   TBranch        *b_CalLongRms;   //!
   TBranch        *b_CalLRmsAsym;   //!
   TBranch        *b_CalMIPDiff;   //!
   TBranch        *b_CalMIPRatio;   //!
   TBranch        *b_CalXEcntr;   //!
   TBranch        *b_CalYEcntr;   //!
   TBranch        *b_CalZEcntr;   //!
   TBranch        *b_CalXDir;   //!
   TBranch        *b_CalYDir;   //!
   TBranch        *b_CalZDir;   //!
   TBranch        *b_CalX0;   //!
   TBranch        *b_CalY0;   //!
   TBranch        *b_CalTrkXtalRms;   //!
   TBranch        *b_CalTrkXtalRmsE;   //!
   TBranch        *b_CalTrkXtalRmsTrunc;   //!
   TBranch        *b_CalTrkXtalRmsETrunc;   //!
   TBranch        *b_CalCfpEnergy;   //!
   TBranch        *b_CalCfpChiSq;   //!
   TBranch        *b_CalCfpEffRLn;   //!
   TBranch        *b_CalLllEnergy;   //!
   TBranch        *b_CalLllEneErr;   //!
   TBranch        *b_CalTklEnergy;   //!
   TBranch        *b_CalTklEneErr;   //!
   TBranch        *b_CalLkHdEnergy;   //!
   TBranch        *b_CalLkHdEneErr;   //!
   TBranch        *b_CalRmsLayerE;   //!
   TBranch        *b_CalRmsLayerEBack;   //!
   TBranch        *b_CalNLayersRmsBack;   //!
   TBranch        *b_CalEAveBack;   //!
   TBranch        *b_CalLayer0Ratio;   //!
   TBranch        *b_AcdTotalEnergy;   //!
   TBranch        *b_AcdRibbonEnergy;   //!
   TBranch        *b_AcdRibbonCount;   //!
   TBranch        *b_AcdTileCount;   //!
   TBranch        *b_AcdDoca;   //!
   TBranch        *b_AcdDocaTileEnergy;   //!
   TBranch        *b_AcdActiveDist;   //!
   TBranch        *b_AcdActiveDist3D;   //!
   TBranch        *b_AcdActDistTileEnergy;   //!
   TBranch        *b_AcdGammaDoca;   //!
   TBranch        *b_AcdCornerDoca;   //!
   TBranch        *b_AcdTkrRibbonDist;   //!
   TBranch        *b_AcdTkr1RibbonDist;   //!
   TBranch        *b_AcdActDistTop;   //!
   TBranch        *b_AcdActDistSideRow0;   //!
   TBranch        *b_AcdActDistSideRow1;   //!
   TBranch        *b_AcdActDistSideRow2;   //!
   TBranch        *b_AcdActDist3DTop;   //!
   TBranch        *b_AcdActDist3DSideRow0;   //!
   TBranch        *b_AcdActDist3DSideRow1;   //!
   TBranch        *b_AcdActDist3DSideRow2;   //!
   TBranch        *b_AcdNoTop;   //!
   TBranch        *b_AcdNoSideRow0;   //!
   TBranch        *b_AcdNoSideRow1;   //!
   TBranch        *b_AcdNoSideRow2;   //!
   TBranch        *b_AcdNoSideRow3;   //!
   TBranch        *b_AcdRibbonActDist;   //!
   TBranch        *b_AcdTkrHitsCountTop;   //!
   TBranch        *b_AcdTkrHitsCountR0;   //!
   TBranch        *b_AcdTkrHitsCountR1;   //!
   TBranch        *b_AcdTkrHitsCountR2;   //!
   TBranch        *b_AcdTkrHitsCountR3;   //!
   TBranch        *b_EvtRun;   //!
   TBranch        *b_EvtEventId;   //!
   TBranch        *b_EvtElapsedTime;   //!
   TBranch        *b_EvtLiveTime;   //!
   TBranch        *b_EvtEnergyCorr;   //!
   TBranch        *b_EvtEnergyRaw;   //!
   TBranch        *b_EvtDeltaEoE;   //!
   TBranch        *b_EvtCalEdgeAngle;   //!
   TBranch        *b_EvtTkrEdgeAngle;   //!
   TBranch        *b_EvtLogEnergy;   //!
   TBranch        *b_EvtTkr1EFrac;   //!
   TBranch        *b_EvtVtxKin;   //!
   TBranch        *b_EvtVtxEAngle;   //!
   TBranch        *b_EvtTkrComptonRatio;   //!
   TBranch        *b_EvtETkrComptonRatio;   //!
   TBranch        *b_EvtPSFModel;   //!
   TBranch        *b_EvtETkr1Chisq;   //!
   TBranch        *b_EvtETkr1FirstChisq;   //!
   TBranch        *b_EvtETkr1Qual;   //!
   TBranch        *b_EvtTkr1PSFMdRat;   //!
   TBranch        *b_EvtECalXtalRatio;   //!
   TBranch        *b_EvtECalXtalTrunc;   //!
   TBranch        *b_EvtECalTrackDoca;   //!
   TBranch        *b_EvtECalTrackSep;   //!
   TBranch        *b_EvtECalTransRms;   //!
   TBranch        *b_EvtECalLongRms;   //!
   TBranch        *b_EvtECalLRmsAsym;   //!
   TBranch        *b_EvtECalTrackAngle;   //!
   TBranch        *b_EvtEVtxAngle;   //!
   TBranch        *b_EvtEVtxDoca;   //!
   TBranch        *b_CalMipNum;   //!
   TBranch        *b_CalMipX0;   //!
   TBranch        *b_CalMipY0;   //!
   TBranch        *b_CalMipZ0;   //!
   TBranch        *b_CalMipXDir;   //!
   TBranch        *b_CalMipYDir;   //!
   TBranch        *b_CalMipZDir;   //!
   TBranch        *b_CalMipD2edge;   //!
   TBranch        *b_CalMipArcLen;   //!
   TBranch        *b_CalMipEcor;   //!
   TBranch        *b_CalMipEcorRms;   //!
   TBranch        *b_CalMipChi2;   //!
   TBranch        *b_CalMipErm;   //!
   TBranch        *b_FilterStatus_HI;   //!
   TBranch        *b_FilterStatus_LO;   //!
   TBranch        *b_FilterAlgStatus;   //!
   TBranch        *b_FilterAngSep;   //!
   TBranch        *b_CTBAcdLowerTileCount;   //!
   TBranch        *b_CTBAcdUpperTileCount;   //!
   TBranch        *b_CTBBestDeltaEoE;   //!
   TBranch        *b_CTBBestEnergy;   //!
   TBranch        *b_CTBBestEnergyProb;   //!
   TBranch        *b_CTBBestEnergyRatio;   //!
   TBranch        *b_CTBBestLogEnergy;   //!
   TBranch        *b_CTBBestPSFerr;   //!
   TBranch        *b_CTBBestXDir;   //!
   TBranch        *b_CTBBestYDir;   //!
   TBranch        *b_CTBBestZDir;   //!
   TBranch        *b_CTBCORE;   //!
   TBranch        *b_CTBCalDocaAngle;   //!
   TBranch        *b_CTBCalFrontBackRatio;   //!
   TBranch        *b_CTBCalMaxXtalRatio;   //!
   TBranch        *b_CTBCalTransTCCD;   //!
   TBranch        *b_CTBDiffCalDOCACalXtalRms;   //!
   TBranch        *b_CTBGAM;   //!
   TBranch        *b_CTBLastLayerProb;   //!
   TBranch        *b_CTBLkhdEnergyRatio;   //!
   TBranch        *b_CTBParamProb;   //!
   TBranch        *b_CTBProfEnergyRatio;   //!
   TBranch        *b_CTBProfileProb;   //!
   TBranch        *b_CTBSecondaryCTBGAM;   //!
   TBranch        *b_CTBSummedCTBGAM;   //!
   TBranch        *b_CTBTkrCoreCalDoca;   //!
   TBranch        *b_CTBTkrEnergyFrac;   //!
   TBranch        *b_CTBTkrLATEdge;   //!
   TBranch        *b_CTBTkrSHRCalAngle;   //!
   TBranch        *b_CTBTrackerProb;   //!
   TBranch        *b_CTBVTX;   //!
   TBranch        *b_CTBVtxTkr1Angle;   //!
   TBranch        *b_CTBminCTBGAM;   //!
   TBranch        *b_FT1EventId;   //!
   TBranch        *b_FT1Energy;   //!
   TBranch        *b_FT1Theta;   //!
   TBranch        *b_FT1Phi;   //!
   TBranch        *b_FT1Ra;   //!
   TBranch        *b_FT1Dec;   //!
   TBranch        *b_FT1L;   //!
   TBranch        *b_FT1B;   //!
   TBranch        *b_FT1ZenithTheta;   //!
   TBranch        *b_FT1EarthAzimuth;   //!
   TBranch        *b_FT1ConvPointX;   //!
   TBranch        *b_FT1ConvPointY;   //!
   TBranch        *b_FT1ConvPointZ;   //!
   TBranch        *b_FT1ConvLayer;   //!
   TBranch        *b_FT1Livetime;   //!

   MeritEvent(TTree *tree=0);
   virtual ~MeritEvent();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MeritEvent_cxx
MeritEvent::MeritEvent(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/recon/recon-v3r9p1_077014005_merit_merit.root");
      if (!f) {
         f = new TFile("/nfs/farm/g/glast/u41/Integration/rootData/077014005/v7r0913p10/recon/recon-v3r9p1_077014005_merit_merit.root");
      }
      tree = (TTree*)gDirectory->Get("MeritTuple");

   }
   Init(tree);
}

MeritEvent::~MeritEvent()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MeritEvent::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MeritEvent::LoadTree(Long64_t entry)
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

void MeritEvent::Init(TTree *tree)
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

   fChain->SetBranchAddress("McSourceId",&McSourceId);
   fChain->SetBranchAddress("McNumIncident",&McNumIncident);
   fChain->SetBranchAddress("McId",&McId);
   fChain->SetBranchAddress("McCharge",&McCharge);
   fChain->SetBranchAddress("McEnergy",&McEnergy);
   fChain->SetBranchAddress("McLogEnergy",&McLogEnergy);
   fChain->SetBranchAddress("McEFrac",&McEFrac);
   fChain->SetBranchAddress("McOpenAngle",&McOpenAngle);
   fChain->SetBranchAddress("McTkrExitEne",&McTkrExitEne);
   fChain->SetBranchAddress("McX0",&McX0);
   fChain->SetBranchAddress("McY0",&McY0);
   fChain->SetBranchAddress("McZ0",&McZ0);
   fChain->SetBranchAddress("McXDir",&McXDir);
   fChain->SetBranchAddress("McYDir",&McYDir);
   fChain->SetBranchAddress("McZDir",&McZDir);
   fChain->SetBranchAddress("McXErr",&McXErr);
   fChain->SetBranchAddress("McYErr",&McYErr);
   fChain->SetBranchAddress("McZErr",&McZErr);
   fChain->SetBranchAddress("McXDirErr",&McXDirErr);
   fChain->SetBranchAddress("McYDirErr",&McYDirErr);
   fChain->SetBranchAddress("McZDirErr",&McZDirErr);
   fChain->SetBranchAddress("McDirErr",&McDirErr);
   fChain->SetBranchAddress("McTkr1DirErr",&McTkr1DirErr);
   fChain->SetBranchAddress("McTkr2DirErr",&McTkr2DirErr);
   fChain->SetBranchAddress("GltWord",&GltWord);
   fChain->SetBranchAddress("GltGemSummary",&GltGemSummary);
   fChain->SetBranchAddress("GltEventFlags",&GltEventFlags);
   fChain->SetBranchAddress("GltTower",&GltTower);
   fChain->SetBranchAddress("GltXTower",&GltXTower);
   fChain->SetBranchAddress("GltYTower",&GltYTower);
   fChain->SetBranchAddress("GltLayer",&GltLayer);
   fChain->SetBranchAddress("GltTotal",&GltTotal);
   fChain->SetBranchAddress("GltNumTowers",&GltNumTowers);
   fChain->SetBranchAddress("GltType",&GltType);
   fChain->SetBranchAddress("GltMoment",&GltMoment);
   fChain->SetBranchAddress("GltZDir",&GltZDir);
   fChain->SetBranchAddress("TkrNumTracks",&TkrNumTracks);
   fChain->SetBranchAddress("TkrSumKalEne",&TkrSumKalEne);
   fChain->SetBranchAddress("TkrSumConEne",&TkrSumConEne);
   fChain->SetBranchAddress("TkrEnergy",&TkrEnergy);
   fChain->SetBranchAddress("TkrEnergyCorr",&TkrEnergyCorr);
   fChain->SetBranchAddress("TkrHDCount",&TkrHDCount);
   fChain->SetBranchAddress("TkrTotalHits",&TkrTotalHits);
   fChain->SetBranchAddress("TkrThinHits",&TkrThinHits);
   fChain->SetBranchAddress("TkrThickHits",&TkrThickHits);
   fChain->SetBranchAddress("TkrBlankHits",&TkrBlankHits);
   fChain->SetBranchAddress("TkrRadLength",&TkrRadLength);
   fChain->SetBranchAddress("TkrTwrEdge",&TkrTwrEdge);
   fChain->SetBranchAddress("TkrTrackLength",&TkrTrackLength);
   fChain->SetBranchAddress("TkrSurplusHCInside",&TkrSurplusHCInside);
   fChain->SetBranchAddress("TkrSurplusHitRatio",&TkrSurplusHitRatio);
   fChain->SetBranchAddress("TkrUpstreamHC",&TkrUpstreamHC);
   fChain->SetBranchAddress("TkrDispersion",&TkrDispersion);
   fChain->SetBranchAddress("Tkr1Chisq",&Tkr1Chisq);
   fChain->SetBranchAddress("Tkr1FirstChisq",&Tkr1FirstChisq);
   fChain->SetBranchAddress("Tkr1Hits",&Tkr1Hits);
   fChain->SetBranchAddress("Tkr1FirstHits",&Tkr1FirstHits);
   fChain->SetBranchAddress("Tkr1FirstLayer",&Tkr1FirstLayer);
   fChain->SetBranchAddress("Tkr1LastLayer",&Tkr1LastLayer);
   fChain->SetBranchAddress("Tkr1DifHits",&Tkr1DifHits);
   fChain->SetBranchAddress("Tkr1Gaps",&Tkr1Gaps);
   fChain->SetBranchAddress("Tkr1FirstGapPlane",&Tkr1FirstGapPlane);
   fChain->SetBranchAddress("Tkr1XGap",&Tkr1XGap);
   fChain->SetBranchAddress("Tkr1YGap",&Tkr1YGap);
   fChain->SetBranchAddress("Tkr1FirstGaps",&Tkr1FirstGaps);
   fChain->SetBranchAddress("Tkr1Qual",&Tkr1Qual);
   fChain->SetBranchAddress("Tkr1Type",&Tkr1Type);
   fChain->SetBranchAddress("Tkr1TwrEdge",&Tkr1TwrEdge);
   fChain->SetBranchAddress("Tkr1PrjTwrEdge",&Tkr1PrjTwrEdge);
   fChain->SetBranchAddress("Tkr1DieEdge",&Tkr1DieEdge);
   fChain->SetBranchAddress("Tkr1TwrGap",&Tkr1TwrGap);
   fChain->SetBranchAddress("Tkr1KalEne",&Tkr1KalEne);
   fChain->SetBranchAddress("Tkr1ConEne",&Tkr1ConEne);
   fChain->SetBranchAddress("Tkr1KalThetaMS",&Tkr1KalThetaMS);
   fChain->SetBranchAddress("Tkr1XDir",&Tkr1XDir);
   fChain->SetBranchAddress("Tkr1YDir",&Tkr1YDir);
   fChain->SetBranchAddress("Tkr1ZDir",&Tkr1ZDir);
   fChain->SetBranchAddress("Tkr1Phi",&Tkr1Phi);
   fChain->SetBranchAddress("Tkr1Theta",&Tkr1Theta);
   fChain->SetBranchAddress("Tkr1X0",&Tkr1X0);
   fChain->SetBranchAddress("Tkr1Y0",&Tkr1Y0);
   fChain->SetBranchAddress("Tkr1Z0",&Tkr1Z0);
   fChain->SetBranchAddress("Tkr1ThetaErr",&Tkr1ThetaErr);
   fChain->SetBranchAddress("Tkr1PhiErr",&Tkr1PhiErr);
   fChain->SetBranchAddress("Tkr1ErrAsym",&Tkr1ErrAsym);
   fChain->SetBranchAddress("Tkr1CovDet",&Tkr1CovDet);
   fChain->SetBranchAddress("Tkr1SXX",&Tkr1SXX);
   fChain->SetBranchAddress("Tkr1SXY",&Tkr1SXY);
   fChain->SetBranchAddress("Tkr1SYY",&Tkr1SYY);
   fChain->SetBranchAddress("Tkr1ToTFirst",&Tkr1ToTFirst);
   fChain->SetBranchAddress("Tkr1ToTAve",&Tkr1ToTAve);
   fChain->SetBranchAddress("Tkr1ToTTrAve",&Tkr1ToTTrAve);
   fChain->SetBranchAddress("Tkr1ToTAsym",&Tkr1ToTAsym);
   fChain->SetBranchAddress("Tkr1ChisqAsym",&Tkr1ChisqAsym);
   fChain->SetBranchAddress("Tkr1SSDVeto",&Tkr1SSDVeto);
   fChain->SetBranchAddress("Tkr1CoreHC",&Tkr1CoreHC);
   fChain->SetBranchAddress("Tkr1LATEdge",&Tkr1LATEdge);
   fChain->SetBranchAddress("Tkr2Chisq",&Tkr2Chisq);
   fChain->SetBranchAddress("Tkr2FirstChisq",&Tkr2FirstChisq);
   fChain->SetBranchAddress("Tkr2Hits",&Tkr2Hits);
   fChain->SetBranchAddress("Tkr2FirstHits",&Tkr2FirstHits);
   fChain->SetBranchAddress("Tkr2FirstLayer",&Tkr2FirstLayer);
   fChain->SetBranchAddress("Tkr2LastLayer",&Tkr2LastLayer);
   fChain->SetBranchAddress("Tkr2DifHits",&Tkr2DifHits);
   fChain->SetBranchAddress("Tkr2Gaps",&Tkr2Gaps);
   fChain->SetBranchAddress("Tkr2FirstGaps",&Tkr2FirstGaps);
   fChain->SetBranchAddress("Tkr2Qual",&Tkr2Qual);
   fChain->SetBranchAddress("Tkr2Type",&Tkr2Type);
   fChain->SetBranchAddress("Tkr2TwrEdge",&Tkr2TwrEdge);
   fChain->SetBranchAddress("Tkr2PrjTwrEdge",&Tkr2PrjTwrEdge);
   fChain->SetBranchAddress("Tkr2DieEdge",&Tkr2DieEdge);
   fChain->SetBranchAddress("Tkr2KalEne",&Tkr2KalEne);
   fChain->SetBranchAddress("Tkr2ConEne",&Tkr2ConEne);
   fChain->SetBranchAddress("Tkr2KalThetaMS",&Tkr2KalThetaMS);
   fChain->SetBranchAddress("Tkr2XDir",&Tkr2XDir);
   fChain->SetBranchAddress("Tkr2YDir",&Tkr2YDir);
   fChain->SetBranchAddress("Tkr2ZDir",&Tkr2ZDir);
   fChain->SetBranchAddress("Tkr2Phi",&Tkr2Phi);
   fChain->SetBranchAddress("Tkr2Theta",&Tkr2Theta);
   fChain->SetBranchAddress("Tkr2X0",&Tkr2X0);
   fChain->SetBranchAddress("Tkr2Y0",&Tkr2Y0);
   fChain->SetBranchAddress("Tkr2Z0",&Tkr2Z0);
   fChain->SetBranchAddress("Tkr2TkrAngle",&Tkr2TkrAngle);
   fChain->SetBranchAddress("Tkr2TkrHDoca",&Tkr2TkrHDoca);
   fChain->SetBranchAddress("VtxXDir",&VtxXDir);
   fChain->SetBranchAddress("VtxYDir",&VtxYDir);
   fChain->SetBranchAddress("VtxZDir",&VtxZDir);
   fChain->SetBranchAddress("VtxPhi",&VtxPhi);
   fChain->SetBranchAddress("VtxTheta",&VtxTheta);
   fChain->SetBranchAddress("VtxThetaErr",&VtxThetaErr);
   fChain->SetBranchAddress("VtxPhiErr",&VtxPhiErr);
   fChain->SetBranchAddress("VtxSXX",&VtxSXX);
   fChain->SetBranchAddress("VtxSXY",&VtxSXY);
   fChain->SetBranchAddress("VtxSYY",&VtxSYY);
   fChain->SetBranchAddress("VtxX0",&VtxX0);
   fChain->SetBranchAddress("VtxY0",&VtxY0);
   fChain->SetBranchAddress("VtxZ0",&VtxZ0);
   fChain->SetBranchAddress("VtxAngle",&VtxAngle);
   fChain->SetBranchAddress("VtxDOCA",&VtxDOCA);
   fChain->SetBranchAddress("VtxHeadSep",&VtxHeadSep);
   fChain->SetBranchAddress("VtxStatus",&VtxStatus);
   fChain->SetBranchAddress("VtxQuality",&VtxQuality);
   fChain->SetBranchAddress("VtxChisq",&VtxChisq);
   fChain->SetBranchAddress("VtxS1",&VtxS1);
   fChain->SetBranchAddress("VtxS2",&VtxS2);
   fChain->SetBranchAddress("VtxAddedRL",&VtxAddedRL);
   fChain->SetBranchAddress("CalEnergyRaw",&CalEnergyRaw);
   fChain->SetBranchAddress("CalEnergyCorr",&CalEnergyCorr);
   fChain->SetBranchAddress("CalLeakCorr",&CalLeakCorr);
   fChain->SetBranchAddress("CalEdgeCorr",&CalEdgeCorr);
   fChain->SetBranchAddress("CalTotalCorr",&CalTotalCorr);
   fChain->SetBranchAddress("CalCsIRLn",&CalCsIRLn);
   fChain->SetBranchAddress("CalTotRLn",&CalTotRLn);
   fChain->SetBranchAddress("CalCntRLn",&CalCntRLn);
   fChain->SetBranchAddress("CalLATRLn",&CalLATRLn);
   fChain->SetBranchAddress("CalDeadTotRat",&CalDeadTotRat);
   fChain->SetBranchAddress("CalDeadCntRat",&CalDeadCntRat);
   fChain->SetBranchAddress("CalTPred",&CalTPred);
   fChain->SetBranchAddress("CalDeltaT",&CalDeltaT);
   fChain->SetBranchAddress("CalGapFraction",&CalGapFraction);
   fChain->SetBranchAddress("CalTwrEdgeCntr",&CalTwrEdgeCntr);
   fChain->SetBranchAddress("CalTwrEdge",&CalTwrEdge);
   fChain->SetBranchAddress("CalLATEdge",&CalLATEdge);
   fChain->SetBranchAddress("CalEdgeEnergy",&CalEdgeEnergy);
   fChain->SetBranchAddress("CalTrackDoca",&CalTrackDoca);
   fChain->SetBranchAddress("CalTrackAngle",&CalTrackAngle);
   fChain->SetBranchAddress("CalTrackSep",&CalTrackSep);
   fChain->SetBranchAddress("CalELayer0",&CalELayer0);
   fChain->SetBranchAddress("CalELayer1",&CalELayer1);
   fChain->SetBranchAddress("CalELayer2",&CalELayer2);
   fChain->SetBranchAddress("CalELayer3",&CalELayer3);
   fChain->SetBranchAddress("CalELayer4",&CalELayer4);
   fChain->SetBranchAddress("CalELayer5",&CalELayer5);
   fChain->SetBranchAddress("CalELayer6",&CalELayer6);
   fChain->SetBranchAddress("CalELayer7",&CalELayer7);
   fChain->SetBranchAddress("CalLyr0Ratio",&CalLyr0Ratio);
   fChain->SetBranchAddress("CalLyr7Ratio",&CalLyr7Ratio);
   fChain->SetBranchAddress("CalBkHalfRatio",&CalBkHalfRatio);
   fChain->SetBranchAddress("CalXtalsTrunc",&CalXtalsTrunc);
   fChain->SetBranchAddress("CalXtalRatio",&CalXtalRatio);
   fChain->SetBranchAddress("CalXtalMaxEne",&CalXtalMaxEne);
   fChain->SetBranchAddress("CalTransRms",&CalTransRms);
   fChain->SetBranchAddress("CalLongRms",&CalLongRms);
   fChain->SetBranchAddress("CalLRmsAsym",&CalLRmsAsym);
   fChain->SetBranchAddress("CalMIPDiff",&CalMIPDiff);
   fChain->SetBranchAddress("CalMIPRatio",&CalMIPRatio);
   fChain->SetBranchAddress("CalXEcntr",&CalXEcntr);
   fChain->SetBranchAddress("CalYEcntr",&CalYEcntr);
   fChain->SetBranchAddress("CalZEcntr",&CalZEcntr);
   fChain->SetBranchAddress("CalXDir",&CalXDir);
   fChain->SetBranchAddress("CalYDir",&CalYDir);
   fChain->SetBranchAddress("CalZDir",&CalZDir);
   fChain->SetBranchAddress("CalX0",&CalX0);
   fChain->SetBranchAddress("CalY0",&CalY0);
   fChain->SetBranchAddress("CalTrkXtalRms",&CalTrkXtalRms);
   fChain->SetBranchAddress("CalTrkXtalRmsE",&CalTrkXtalRmsE);
   fChain->SetBranchAddress("CalTrkXtalRmsTrunc",&CalTrkXtalRmsTrunc);
   fChain->SetBranchAddress("CalTrkXtalRmsETrunc",&CalTrkXtalRmsETrunc);
   fChain->SetBranchAddress("CalCfpEnergy",&CalCfpEnergy);
   fChain->SetBranchAddress("CalCfpChiSq",&CalCfpChiSq);
   fChain->SetBranchAddress("CalCfpEffRLn",&CalCfpEffRLn);
   fChain->SetBranchAddress("CalLllEnergy",&CalLllEnergy);
   fChain->SetBranchAddress("CalLllEneErr",&CalLllEneErr);
   fChain->SetBranchAddress("CalTklEnergy",&CalTklEnergy);
   fChain->SetBranchAddress("CalTklEneErr",&CalTklEneErr);
   fChain->SetBranchAddress("CalLkHdEnergy",&CalLkHdEnergy);
   fChain->SetBranchAddress("CalLkHdEneErr",&CalLkHdEneErr);
   fChain->SetBranchAddress("CalRmsLayerE",&CalRmsLayerE);
   fChain->SetBranchAddress("CalRmsLayerEBack",&CalRmsLayerEBack);
   fChain->SetBranchAddress("CalNLayersRmsBack",&CalNLayersRmsBack);
   fChain->SetBranchAddress("CalEAveBack",&CalEAveBack);
   fChain->SetBranchAddress("CalLayer0Ratio",&CalLayer0Ratio);
   fChain->SetBranchAddress("AcdTotalEnergy",&AcdTotalEnergy);
   fChain->SetBranchAddress("AcdRibbonEnergy",&AcdRibbonEnergy);
   fChain->SetBranchAddress("AcdRibbonCount",&AcdRibbonCount);
   fChain->SetBranchAddress("AcdTileCount",&AcdTileCount);
   fChain->SetBranchAddress("AcdDoca",&AcdDoca);
   fChain->SetBranchAddress("AcdDocaTileEnergy",&AcdDocaTileEnergy);
   fChain->SetBranchAddress("AcdActiveDist",&AcdActiveDist);
   fChain->SetBranchAddress("AcdActiveDist3D",&AcdActiveDist3D);
   fChain->SetBranchAddress("AcdActDistTileEnergy",&AcdActDistTileEnergy);
   fChain->SetBranchAddress("AcdGammaDoca",&AcdGammaDoca);
   fChain->SetBranchAddress("AcdCornerDoca",&AcdCornerDoca);
   fChain->SetBranchAddress("AcdTkrRibbonDist",&AcdTkrRibbonDist);
   fChain->SetBranchAddress("AcdTkr1RibbonDist",&AcdTkr1RibbonDist);
   fChain->SetBranchAddress("AcdActDistTop",&AcdActDistTop);
   fChain->SetBranchAddress("AcdActDistSideRow0",&AcdActDistSideRow0);
   fChain->SetBranchAddress("AcdActDistSideRow1",&AcdActDistSideRow1);
   fChain->SetBranchAddress("AcdActDistSideRow2",&AcdActDistSideRow2);
   fChain->SetBranchAddress("AcdActDist3DTop",&AcdActDist3DTop);
   fChain->SetBranchAddress("AcdActDist3DSideRow0",&AcdActDist3DSideRow0);
   fChain->SetBranchAddress("AcdActDist3DSideRow1",&AcdActDist3DSideRow1);
   fChain->SetBranchAddress("AcdActDist3DSideRow2",&AcdActDist3DSideRow2);
   fChain->SetBranchAddress("AcdNoTop",&AcdNoTop);
   fChain->SetBranchAddress("AcdNoSideRow0",&AcdNoSideRow0);
   fChain->SetBranchAddress("AcdNoSideRow1",&AcdNoSideRow1);
   fChain->SetBranchAddress("AcdNoSideRow2",&AcdNoSideRow2);
   fChain->SetBranchAddress("AcdNoSideRow3",&AcdNoSideRow3);
   fChain->SetBranchAddress("AcdRibbonActDist",&AcdRibbonActDist);
   fChain->SetBranchAddress("AcdTkrHitsCountTop",&AcdTkrHitsCountTop);
   fChain->SetBranchAddress("AcdTkrHitsCountR0",&AcdTkrHitsCountR0);
   fChain->SetBranchAddress("AcdTkrHitsCountR1",&AcdTkrHitsCountR1);
   fChain->SetBranchAddress("AcdTkrHitsCountR2",&AcdTkrHitsCountR2);
   fChain->SetBranchAddress("AcdTkrHitsCountR3",&AcdTkrHitsCountR3);
   fChain->SetBranchAddress("EvtRun",&EvtRun);
   fChain->SetBranchAddress("EvtEventId",&EvtEventId);
   fChain->SetBranchAddress("EvtElapsedTime",&EvtElapsedTime);
   fChain->SetBranchAddress("EvtLiveTime",&EvtLiveTime);
   fChain->SetBranchAddress("EvtEnergyCorr",&EvtEnergyCorr);
   fChain->SetBranchAddress("EvtEnergyRaw",&EvtEnergyRaw);
   fChain->SetBranchAddress("EvtDeltaEoE",&EvtDeltaEoE);
   fChain->SetBranchAddress("EvtCalEdgeAngle",&EvtCalEdgeAngle);
   fChain->SetBranchAddress("EvtTkrEdgeAngle",&EvtTkrEdgeAngle);
   fChain->SetBranchAddress("EvtLogEnergy",&EvtLogEnergy);
   fChain->SetBranchAddress("EvtTkr1EFrac",&EvtTkr1EFrac);
   fChain->SetBranchAddress("EvtVtxKin",&EvtVtxKin);
   fChain->SetBranchAddress("EvtVtxEAngle",&EvtVtxEAngle);
   fChain->SetBranchAddress("EvtTkrComptonRatio",&EvtTkrComptonRatio);
   fChain->SetBranchAddress("EvtETkrComptonRatio",&EvtETkrComptonRatio);
   fChain->SetBranchAddress("EvtPSFModel",&EvtPSFModel);
   fChain->SetBranchAddress("EvtETkr1Chisq",&EvtETkr1Chisq);
   fChain->SetBranchAddress("EvtETkr1FirstChisq",&EvtETkr1FirstChisq);
   fChain->SetBranchAddress("EvtETkr1Qual",&EvtETkr1Qual);
   fChain->SetBranchAddress("EvtTkr1PSFMdRat",&EvtTkr1PSFMdRat);
   fChain->SetBranchAddress("EvtECalXtalRatio",&EvtECalXtalRatio);
   fChain->SetBranchAddress("EvtECalXtalTrunc",&EvtECalXtalTrunc);
   fChain->SetBranchAddress("EvtECalTrackDoca",&EvtECalTrackDoca);
   fChain->SetBranchAddress("EvtECalTrackSep",&EvtECalTrackSep);
   fChain->SetBranchAddress("EvtECalTransRms",&EvtECalTransRms);
   fChain->SetBranchAddress("EvtECalLongRms",&EvtECalLongRms);
   fChain->SetBranchAddress("EvtECalLRmsAsym",&EvtECalLRmsAsym);
   fChain->SetBranchAddress("EvtECalTrackAngle",&EvtECalTrackAngle);
   fChain->SetBranchAddress("EvtEVtxAngle",&EvtEVtxAngle);
   fChain->SetBranchAddress("EvtEVtxDoca",&EvtEVtxDoca);
   fChain->SetBranchAddress("CalMipNum",&CalMipNum);
   fChain->SetBranchAddress("CalMipX0",&CalMipX0);
   fChain->SetBranchAddress("CalMipY0",&CalMipY0);
   fChain->SetBranchAddress("CalMipZ0",&CalMipZ0);
   fChain->SetBranchAddress("CalMipXDir",&CalMipXDir);
   fChain->SetBranchAddress("CalMipYDir",&CalMipYDir);
   fChain->SetBranchAddress("CalMipZDir",&CalMipZDir);
   fChain->SetBranchAddress("CalMipD2edge",&CalMipD2edge);
   fChain->SetBranchAddress("CalMipArcLen",&CalMipArcLen);
   fChain->SetBranchAddress("CalMipEcor",&CalMipEcor);
   fChain->SetBranchAddress("CalMipEcorRms",&CalMipEcorRms);
   fChain->SetBranchAddress("CalMipChi2",&CalMipChi2);
   fChain->SetBranchAddress("CalMipErm",&CalMipErm);
   fChain->SetBranchAddress("FilterStatus_HI",&FilterStatus_HI);
   fChain->SetBranchAddress("FilterStatus_LO",&FilterStatus_LO);
   fChain->SetBranchAddress("FilterAlgStatus",&FilterAlgStatus);
   fChain->SetBranchAddress("FilterAngSep",&FilterAngSep);
   fChain->SetBranchAddress("CTBAcdLowerTileCount",&CTBAcdLowerTileCount);
   fChain->SetBranchAddress("CTBAcdUpperTileCount",&CTBAcdUpperTileCount);
   fChain->SetBranchAddress("CTBBestDeltaEoE",&CTBBestDeltaEoE);
   fChain->SetBranchAddress("CTBBestEnergy",&CTBBestEnergy);
   fChain->SetBranchAddress("CTBBestEnergyProb",&CTBBestEnergyProb);
   fChain->SetBranchAddress("CTBBestEnergyRatio",&CTBBestEnergyRatio);
   fChain->SetBranchAddress("CTBBestLogEnergy",&CTBBestLogEnergy);
   fChain->SetBranchAddress("CTBBestPSFerr",&CTBBestPSFerr);
   fChain->SetBranchAddress("CTBBestXDir",&CTBBestXDir);
   fChain->SetBranchAddress("CTBBestYDir",&CTBBestYDir);
   fChain->SetBranchAddress("CTBBestZDir",&CTBBestZDir);
   fChain->SetBranchAddress("CTBCORE",&CTBCORE);
   fChain->SetBranchAddress("CTBCalDocaAngle",&CTBCalDocaAngle);
   fChain->SetBranchAddress("CTBCalFrontBackRatio",&CTBCalFrontBackRatio);
   fChain->SetBranchAddress("CTBCalMaxXtalRatio",&CTBCalMaxXtalRatio);
   fChain->SetBranchAddress("CTBCalTransTCCD",&CTBCalTransTCCD);
   fChain->SetBranchAddress("CTBDiffCalDOCACalXtalRms",&CTBDiffCalDOCACalXtalRms);
   fChain->SetBranchAddress("CTBGAM",&CTBGAM);
   fChain->SetBranchAddress("CTBLastLayerProb",&CTBLastLayerProb);
   fChain->SetBranchAddress("CTBLkhdEnergyRatio",&CTBLkhdEnergyRatio);
   fChain->SetBranchAddress("CTBParamProb",&CTBParamProb);
   fChain->SetBranchAddress("CTBProfEnergyRatio",&CTBProfEnergyRatio);
   fChain->SetBranchAddress("CTBProfileProb",&CTBProfileProb);
   fChain->SetBranchAddress("CTBSecondaryCTBGAM",&CTBSecondaryCTBGAM);
   fChain->SetBranchAddress("CTBSummedCTBGAM",&CTBSummedCTBGAM);
   fChain->SetBranchAddress("CTBTkrCoreCalDoca",&CTBTkrCoreCalDoca);
   fChain->SetBranchAddress("CTBTkrEnergyFrac",&CTBTkrEnergyFrac);
   fChain->SetBranchAddress("CTBTkrLATEdge",&CTBTkrLATEdge);
   fChain->SetBranchAddress("CTBTkrSHRCalAngle",&CTBTkrSHRCalAngle);
   fChain->SetBranchAddress("CTBTrackerProb",&CTBTrackerProb);
   fChain->SetBranchAddress("CTBVTX",&CTBVTX);
   fChain->SetBranchAddress("CTBVtxTkr1Angle",&CTBVtxTkr1Angle);
   fChain->SetBranchAddress("CTBminCTBGAM",&CTBminCTBGAM);
   fChain->SetBranchAddress("FT1EventId",&FT1EventId);
   fChain->SetBranchAddress("FT1Energy",&FT1Energy);
   fChain->SetBranchAddress("FT1Theta",&FT1Theta);
   fChain->SetBranchAddress("FT1Phi",&FT1Phi);
   fChain->SetBranchAddress("FT1Ra",&FT1Ra);
   fChain->SetBranchAddress("FT1Dec",&FT1Dec);
   fChain->SetBranchAddress("FT1L",&FT1L);
   fChain->SetBranchAddress("FT1B",&FT1B);
   fChain->SetBranchAddress("FT1ZenithTheta",&FT1ZenithTheta);
   fChain->SetBranchAddress("FT1EarthAzimuth",&FT1EarthAzimuth);
   fChain->SetBranchAddress("FT1ConvPointX",&FT1ConvPointX);
   fChain->SetBranchAddress("FT1ConvPointY",&FT1ConvPointY);
   fChain->SetBranchAddress("FT1ConvPointZ",&FT1ConvPointZ);
   fChain->SetBranchAddress("FT1ConvLayer",&FT1ConvLayer);
   fChain->SetBranchAddress("FT1Livetime",&FT1Livetime);
   Notify();
}

Bool_t MeritEvent::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_McSourceId = fChain->GetBranch("McSourceId");
   b_McNumIncident = fChain->GetBranch("McNumIncident");
   b_McId = fChain->GetBranch("McId");
   b_McCharge = fChain->GetBranch("McCharge");
   b_McEnergy = fChain->GetBranch("McEnergy");
   b_McLogEnergy = fChain->GetBranch("McLogEnergy");
   b_McEFrac = fChain->GetBranch("McEFrac");
   b_McOpenAngle = fChain->GetBranch("McOpenAngle");
   b_McTkrExitEne = fChain->GetBranch("McTkrExitEne");
   b_McX0 = fChain->GetBranch("McX0");
   b_McY0 = fChain->GetBranch("McY0");
   b_McZ0 = fChain->GetBranch("McZ0");
   b_McXDir = fChain->GetBranch("McXDir");
   b_McYDir = fChain->GetBranch("McYDir");
   b_McZDir = fChain->GetBranch("McZDir");
   b_McXErr = fChain->GetBranch("McXErr");
   b_McYErr = fChain->GetBranch("McYErr");
   b_McZErr = fChain->GetBranch("McZErr");
   b_McXDirErr = fChain->GetBranch("McXDirErr");
   b_McYDirErr = fChain->GetBranch("McYDirErr");
   b_McZDirErr = fChain->GetBranch("McZDirErr");
   b_McDirErr = fChain->GetBranch("McDirErr");
   b_McTkr1DirErr = fChain->GetBranch("McTkr1DirErr");
   b_McTkr2DirErr = fChain->GetBranch("McTkr2DirErr");
   b_GltWord = fChain->GetBranch("GltWord");
   b_GltGemSummary = fChain->GetBranch("GltGemSummary");
   b_GltEventFlags = fChain->GetBranch("GltEventFlags");
   b_GltTower = fChain->GetBranch("GltTower");
   b_GltXTower = fChain->GetBranch("GltXTower");
   b_GltYTower = fChain->GetBranch("GltYTower");
   b_GltLayer = fChain->GetBranch("GltLayer");
   b_GltTotal = fChain->GetBranch("GltTotal");
   b_GltNumTowers = fChain->GetBranch("GltNumTowers");
   b_GltType = fChain->GetBranch("GltType");
   b_GltMoment = fChain->GetBranch("GltMoment");
   b_GltZDir = fChain->GetBranch("GltZDir");
   b_TkrNumTracks = fChain->GetBranch("TkrNumTracks");
   b_TkrSumKalEne = fChain->GetBranch("TkrSumKalEne");
   b_TkrSumConEne = fChain->GetBranch("TkrSumConEne");
   b_TkrEnergy = fChain->GetBranch("TkrEnergy");
   b_TkrEnergyCorr = fChain->GetBranch("TkrEnergyCorr");
   b_TkrHDCount = fChain->GetBranch("TkrHDCount");
   b_TkrTotalHits = fChain->GetBranch("TkrTotalHits");
   b_TkrThinHits = fChain->GetBranch("TkrThinHits");
   b_TkrThickHits = fChain->GetBranch("TkrThickHits");
   b_TkrBlankHits = fChain->GetBranch("TkrBlankHits");
   b_TkrRadLength = fChain->GetBranch("TkrRadLength");
   b_TkrTwrEdge = fChain->GetBranch("TkrTwrEdge");
   b_TkrTrackLength = fChain->GetBranch("TkrTrackLength");
   b_TkrSurplusHCInside = fChain->GetBranch("TkrSurplusHCInside");
   b_TkrSurplusHitRatio = fChain->GetBranch("TkrSurplusHitRatio");
   b_TkrUpstreamHC = fChain->GetBranch("TkrUpstreamHC");
   b_TkrDispersion = fChain->GetBranch("TkrDispersion");
   b_Tkr1Chisq = fChain->GetBranch("Tkr1Chisq");
   b_Tkr1FirstChisq = fChain->GetBranch("Tkr1FirstChisq");
   b_Tkr1Hits = fChain->GetBranch("Tkr1Hits");
   b_Tkr1FirstHits = fChain->GetBranch("Tkr1FirstHits");
   b_Tkr1FirstLayer = fChain->GetBranch("Tkr1FirstLayer");
   b_Tkr1LastLayer = fChain->GetBranch("Tkr1LastLayer");
   b_Tkr1DifHits = fChain->GetBranch("Tkr1DifHits");
   b_Tkr1Gaps = fChain->GetBranch("Tkr1Gaps");
   b_Tkr1FirstGapPlane = fChain->GetBranch("Tkr1FirstGapPlane");
   b_Tkr1XGap = fChain->GetBranch("Tkr1XGap");
   b_Tkr1YGap = fChain->GetBranch("Tkr1YGap");
   b_Tkr1FirstGaps = fChain->GetBranch("Tkr1FirstGaps");
   b_Tkr1Qual = fChain->GetBranch("Tkr1Qual");
   b_Tkr1Type = fChain->GetBranch("Tkr1Type");
   b_Tkr1TwrEdge = fChain->GetBranch("Tkr1TwrEdge");
   b_Tkr1PrjTwrEdge = fChain->GetBranch("Tkr1PrjTwrEdge");
   b_Tkr1DieEdge = fChain->GetBranch("Tkr1DieEdge");
   b_Tkr1TwrGap = fChain->GetBranch("Tkr1TwrGap");
   b_Tkr1KalEne = fChain->GetBranch("Tkr1KalEne");
   b_Tkr1ConEne = fChain->GetBranch("Tkr1ConEne");
   b_Tkr1KalThetaMS = fChain->GetBranch("Tkr1KalThetaMS");
   b_Tkr1XDir = fChain->GetBranch("Tkr1XDir");
   b_Tkr1YDir = fChain->GetBranch("Tkr1YDir");
   b_Tkr1ZDir = fChain->GetBranch("Tkr1ZDir");
   b_Tkr1Phi = fChain->GetBranch("Tkr1Phi");
   b_Tkr1Theta = fChain->GetBranch("Tkr1Theta");
   b_Tkr1X0 = fChain->GetBranch("Tkr1X0");
   b_Tkr1Y0 = fChain->GetBranch("Tkr1Y0");
   b_Tkr1Z0 = fChain->GetBranch("Tkr1Z0");
   b_Tkr1ThetaErr = fChain->GetBranch("Tkr1ThetaErr");
   b_Tkr1PhiErr = fChain->GetBranch("Tkr1PhiErr");
   b_Tkr1ErrAsym = fChain->GetBranch("Tkr1ErrAsym");
   b_Tkr1CovDet = fChain->GetBranch("Tkr1CovDet");
   b_Tkr1SXX = fChain->GetBranch("Tkr1SXX");
   b_Tkr1SXY = fChain->GetBranch("Tkr1SXY");
   b_Tkr1SYY = fChain->GetBranch("Tkr1SYY");
   b_Tkr1ToTFirst = fChain->GetBranch("Tkr1ToTFirst");
   b_Tkr1ToTAve = fChain->GetBranch("Tkr1ToTAve");
   b_Tkr1ToTTrAve = fChain->GetBranch("Tkr1ToTTrAve");
   b_Tkr1ToTAsym = fChain->GetBranch("Tkr1ToTAsym");
   b_Tkr1ChisqAsym = fChain->GetBranch("Tkr1ChisqAsym");
   b_Tkr1SSDVeto = fChain->GetBranch("Tkr1SSDVeto");
   b_Tkr1CoreHC = fChain->GetBranch("Tkr1CoreHC");
   b_Tkr1LATEdge = fChain->GetBranch("Tkr1LATEdge");
   b_Tkr2Chisq = fChain->GetBranch("Tkr2Chisq");
   b_Tkr2FirstChisq = fChain->GetBranch("Tkr2FirstChisq");
   b_Tkr2Hits = fChain->GetBranch("Tkr2Hits");
   b_Tkr2FirstHits = fChain->GetBranch("Tkr2FirstHits");
   b_Tkr2FirstLayer = fChain->GetBranch("Tkr2FirstLayer");
   b_Tkr2LastLayer = fChain->GetBranch("Tkr2LastLayer");
   b_Tkr2DifHits = fChain->GetBranch("Tkr2DifHits");
   b_Tkr2Gaps = fChain->GetBranch("Tkr2Gaps");
   b_Tkr2FirstGaps = fChain->GetBranch("Tkr2FirstGaps");
   b_Tkr2Qual = fChain->GetBranch("Tkr2Qual");
   b_Tkr2Type = fChain->GetBranch("Tkr2Type");
   b_Tkr2TwrEdge = fChain->GetBranch("Tkr2TwrEdge");
   b_Tkr2PrjTwrEdge = fChain->GetBranch("Tkr2PrjTwrEdge");
   b_Tkr2DieEdge = fChain->GetBranch("Tkr2DieEdge");
   b_Tkr2KalEne = fChain->GetBranch("Tkr2KalEne");
   b_Tkr2ConEne = fChain->GetBranch("Tkr2ConEne");
   b_Tkr2KalThetaMS = fChain->GetBranch("Tkr2KalThetaMS");
   b_Tkr2XDir = fChain->GetBranch("Tkr2XDir");
   b_Tkr2YDir = fChain->GetBranch("Tkr2YDir");
   b_Tkr2ZDir = fChain->GetBranch("Tkr2ZDir");
   b_Tkr2Phi = fChain->GetBranch("Tkr2Phi");
   b_Tkr2Theta = fChain->GetBranch("Tkr2Theta");
   b_Tkr2X0 = fChain->GetBranch("Tkr2X0");
   b_Tkr2Y0 = fChain->GetBranch("Tkr2Y0");
   b_Tkr2Z0 = fChain->GetBranch("Tkr2Z0");
   b_Tkr2TkrAngle = fChain->GetBranch("Tkr2TkrAngle");
   b_Tkr2TkrHDoca = fChain->GetBranch("Tkr2TkrHDoca");
   b_VtxXDir = fChain->GetBranch("VtxXDir");
   b_VtxYDir = fChain->GetBranch("VtxYDir");
   b_VtxZDir = fChain->GetBranch("VtxZDir");
   b_VtxPhi = fChain->GetBranch("VtxPhi");
   b_VtxTheta = fChain->GetBranch("VtxTheta");
   b_VtxThetaErr = fChain->GetBranch("VtxThetaErr");
   b_VtxPhiErr = fChain->GetBranch("VtxPhiErr");
   b_VtxSXX = fChain->GetBranch("VtxSXX");
   b_VtxSXY = fChain->GetBranch("VtxSXY");
   b_VtxSYY = fChain->GetBranch("VtxSYY");
   b_VtxX0 = fChain->GetBranch("VtxX0");
   b_VtxY0 = fChain->GetBranch("VtxY0");
   b_VtxZ0 = fChain->GetBranch("VtxZ0");
   b_VtxAngle = fChain->GetBranch("VtxAngle");
   b_VtxDOCA = fChain->GetBranch("VtxDOCA");
   b_VtxHeadSep = fChain->GetBranch("VtxHeadSep");
   b_VtxStatus = fChain->GetBranch("VtxStatus");
   b_VtxQuality = fChain->GetBranch("VtxQuality");
   b_VtxChisq = fChain->GetBranch("VtxChisq");
   b_VtxS1 = fChain->GetBranch("VtxS1");
   b_VtxS2 = fChain->GetBranch("VtxS2");
   b_VtxAddedRL = fChain->GetBranch("VtxAddedRL");
   b_CalEnergyRaw = fChain->GetBranch("CalEnergyRaw");
   b_CalEnergyCorr = fChain->GetBranch("CalEnergyCorr");
   b_CalLeakCorr = fChain->GetBranch("CalLeakCorr");
   b_CalEdgeCorr = fChain->GetBranch("CalEdgeCorr");
   b_CalTotalCorr = fChain->GetBranch("CalTotalCorr");
   b_CalCsIRLn = fChain->GetBranch("CalCsIRLn");
   b_CalTotRLn = fChain->GetBranch("CalTotRLn");
   b_CalCntRLn = fChain->GetBranch("CalCntRLn");
   b_CalLATRLn = fChain->GetBranch("CalLATRLn");
   b_CalDeadTotRat = fChain->GetBranch("CalDeadTotRat");
   b_CalDeadCntRat = fChain->GetBranch("CalDeadCntRat");
   b_CalTPred = fChain->GetBranch("CalTPred");
   b_CalDeltaT = fChain->GetBranch("CalDeltaT");
   b_CalGapFraction = fChain->GetBranch("CalGapFraction");
   b_CalTwrEdgeCntr = fChain->GetBranch("CalTwrEdgeCntr");
   b_CalTwrEdge = fChain->GetBranch("CalTwrEdge");
   b_CalLATEdge = fChain->GetBranch("CalLATEdge");
   b_CalEdgeEnergy = fChain->GetBranch("CalEdgeEnergy");
   b_CalTrackDoca = fChain->GetBranch("CalTrackDoca");
   b_CalTrackAngle = fChain->GetBranch("CalTrackAngle");
   b_CalTrackSep = fChain->GetBranch("CalTrackSep");
   b_CalELayer0 = fChain->GetBranch("CalELayer0");
   b_CalELayer1 = fChain->GetBranch("CalELayer1");
   b_CalELayer2 = fChain->GetBranch("CalELayer2");
   b_CalELayer3 = fChain->GetBranch("CalELayer3");
   b_CalELayer4 = fChain->GetBranch("CalELayer4");
   b_CalELayer5 = fChain->GetBranch("CalELayer5");
   b_CalELayer6 = fChain->GetBranch("CalELayer6");
   b_CalELayer7 = fChain->GetBranch("CalELayer7");
   b_CalLyr0Ratio = fChain->GetBranch("CalLyr0Ratio");
   b_CalLyr7Ratio = fChain->GetBranch("CalLyr7Ratio");
   b_CalBkHalfRatio = fChain->GetBranch("CalBkHalfRatio");
   b_CalXtalsTrunc = fChain->GetBranch("CalXtalsTrunc");
   b_CalXtalRatio = fChain->GetBranch("CalXtalRatio");
   b_CalXtalMaxEne = fChain->GetBranch("CalXtalMaxEne");
   b_CalTransRms = fChain->GetBranch("CalTransRms");
   b_CalLongRms = fChain->GetBranch("CalLongRms");
   b_CalLRmsAsym = fChain->GetBranch("CalLRmsAsym");
   b_CalMIPDiff = fChain->GetBranch("CalMIPDiff");
   b_CalMIPRatio = fChain->GetBranch("CalMIPRatio");
   b_CalXEcntr = fChain->GetBranch("CalXEcntr");
   b_CalYEcntr = fChain->GetBranch("CalYEcntr");
   b_CalZEcntr = fChain->GetBranch("CalZEcntr");
   b_CalXDir = fChain->GetBranch("CalXDir");
   b_CalYDir = fChain->GetBranch("CalYDir");
   b_CalZDir = fChain->GetBranch("CalZDir");
   b_CalX0 = fChain->GetBranch("CalX0");
   b_CalY0 = fChain->GetBranch("CalY0");
   b_CalTrkXtalRms = fChain->GetBranch("CalTrkXtalRms");
   b_CalTrkXtalRmsE = fChain->GetBranch("CalTrkXtalRmsE");
   b_CalTrkXtalRmsTrunc = fChain->GetBranch("CalTrkXtalRmsTrunc");
   b_CalTrkXtalRmsETrunc = fChain->GetBranch("CalTrkXtalRmsETrunc");
   b_CalCfpEnergy = fChain->GetBranch("CalCfpEnergy");
   b_CalCfpChiSq = fChain->GetBranch("CalCfpChiSq");
   b_CalCfpEffRLn = fChain->GetBranch("CalCfpEffRLn");
   b_CalLllEnergy = fChain->GetBranch("CalLllEnergy");
   b_CalLllEneErr = fChain->GetBranch("CalLllEneErr");
   b_CalTklEnergy = fChain->GetBranch("CalTklEnergy");
   b_CalTklEneErr = fChain->GetBranch("CalTklEneErr");
   b_CalLkHdEnergy = fChain->GetBranch("CalLkHdEnergy");
   b_CalLkHdEneErr = fChain->GetBranch("CalLkHdEneErr");
   b_CalRmsLayerE = fChain->GetBranch("CalRmsLayerE");
   b_CalRmsLayerEBack = fChain->GetBranch("CalRmsLayerEBack");
   b_CalNLayersRmsBack = fChain->GetBranch("CalNLayersRmsBack");
   b_CalEAveBack = fChain->GetBranch("CalEAveBack");
   b_CalLayer0Ratio = fChain->GetBranch("CalLayer0Ratio");
   b_AcdTotalEnergy = fChain->GetBranch("AcdTotalEnergy");
   b_AcdRibbonEnergy = fChain->GetBranch("AcdRibbonEnergy");
   b_AcdRibbonCount = fChain->GetBranch("AcdRibbonCount");
   b_AcdTileCount = fChain->GetBranch("AcdTileCount");
   b_AcdDoca = fChain->GetBranch("AcdDoca");
   b_AcdDocaTileEnergy = fChain->GetBranch("AcdDocaTileEnergy");
   b_AcdActiveDist = fChain->GetBranch("AcdActiveDist");
   b_AcdActiveDist3D = fChain->GetBranch("AcdActiveDist3D");
   b_AcdActDistTileEnergy = fChain->GetBranch("AcdActDistTileEnergy");
   b_AcdGammaDoca = fChain->GetBranch("AcdGammaDoca");
   b_AcdCornerDoca = fChain->GetBranch("AcdCornerDoca");
   b_AcdTkrRibbonDist = fChain->GetBranch("AcdTkrRibbonDist");
   b_AcdTkr1RibbonDist = fChain->GetBranch("AcdTkr1RibbonDist");
   b_AcdActDistTop = fChain->GetBranch("AcdActDistTop");
   b_AcdActDistSideRow0 = fChain->GetBranch("AcdActDistSideRow0");
   b_AcdActDistSideRow1 = fChain->GetBranch("AcdActDistSideRow1");
   b_AcdActDistSideRow2 = fChain->GetBranch("AcdActDistSideRow2");
   b_AcdActDist3DTop = fChain->GetBranch("AcdActDist3DTop");
   b_AcdActDist3DSideRow0 = fChain->GetBranch("AcdActDist3DSideRow0");
   b_AcdActDist3DSideRow1 = fChain->GetBranch("AcdActDist3DSideRow1");
   b_AcdActDist3DSideRow2 = fChain->GetBranch("AcdActDist3DSideRow2");
   b_AcdNoTop = fChain->GetBranch("AcdNoTop");
   b_AcdNoSideRow0 = fChain->GetBranch("AcdNoSideRow0");
   b_AcdNoSideRow1 = fChain->GetBranch("AcdNoSideRow1");
   b_AcdNoSideRow2 = fChain->GetBranch("AcdNoSideRow2");
   b_AcdNoSideRow3 = fChain->GetBranch("AcdNoSideRow3");
   b_AcdRibbonActDist = fChain->GetBranch("AcdRibbonActDist");
   b_AcdTkrHitsCountTop = fChain->GetBranch("AcdTkrHitsCountTop");
   b_AcdTkrHitsCountR0 = fChain->GetBranch("AcdTkrHitsCountR0");
   b_AcdTkrHitsCountR1 = fChain->GetBranch("AcdTkrHitsCountR1");
   b_AcdTkrHitsCountR2 = fChain->GetBranch("AcdTkrHitsCountR2");
   b_AcdTkrHitsCountR3 = fChain->GetBranch("AcdTkrHitsCountR3");
   b_EvtRun = fChain->GetBranch("EvtRun");
   b_EvtEventId = fChain->GetBranch("EvtEventId");
   b_EvtElapsedTime = fChain->GetBranch("EvtElapsedTime");
   b_EvtLiveTime = fChain->GetBranch("EvtLiveTime");
   b_EvtEnergyCorr = fChain->GetBranch("EvtEnergyCorr");
   b_EvtEnergyRaw = fChain->GetBranch("EvtEnergyRaw");
   b_EvtDeltaEoE = fChain->GetBranch("EvtDeltaEoE");
   b_EvtCalEdgeAngle = fChain->GetBranch("EvtCalEdgeAngle");
   b_EvtTkrEdgeAngle = fChain->GetBranch("EvtTkrEdgeAngle");
   b_EvtLogEnergy = fChain->GetBranch("EvtLogEnergy");
   b_EvtTkr1EFrac = fChain->GetBranch("EvtTkr1EFrac");
   b_EvtVtxKin = fChain->GetBranch("EvtVtxKin");
   b_EvtVtxEAngle = fChain->GetBranch("EvtVtxEAngle");
   b_EvtTkrComptonRatio = fChain->GetBranch("EvtTkrComptonRatio");
   b_EvtETkrComptonRatio = fChain->GetBranch("EvtETkrComptonRatio");
   b_EvtPSFModel = fChain->GetBranch("EvtPSFModel");
   b_EvtETkr1Chisq = fChain->GetBranch("EvtETkr1Chisq");
   b_EvtETkr1FirstChisq = fChain->GetBranch("EvtETkr1FirstChisq");
   b_EvtETkr1Qual = fChain->GetBranch("EvtETkr1Qual");
   b_EvtTkr1PSFMdRat = fChain->GetBranch("EvtTkr1PSFMdRat");
   b_EvtECalXtalRatio = fChain->GetBranch("EvtECalXtalRatio");
   b_EvtECalXtalTrunc = fChain->GetBranch("EvtECalXtalTrunc");
   b_EvtECalTrackDoca = fChain->GetBranch("EvtECalTrackDoca");
   b_EvtECalTrackSep = fChain->GetBranch("EvtECalTrackSep");
   b_EvtECalTransRms = fChain->GetBranch("EvtECalTransRms");
   b_EvtECalLongRms = fChain->GetBranch("EvtECalLongRms");
   b_EvtECalLRmsAsym = fChain->GetBranch("EvtECalLRmsAsym");
   b_EvtECalTrackAngle = fChain->GetBranch("EvtECalTrackAngle");
   b_EvtEVtxAngle = fChain->GetBranch("EvtEVtxAngle");
   b_EvtEVtxDoca = fChain->GetBranch("EvtEVtxDoca");
   b_CalMipNum = fChain->GetBranch("CalMipNum");
   b_CalMipX0 = fChain->GetBranch("CalMipX0");
   b_CalMipY0 = fChain->GetBranch("CalMipY0");
   b_CalMipZ0 = fChain->GetBranch("CalMipZ0");
   b_CalMipXDir = fChain->GetBranch("CalMipXDir");
   b_CalMipYDir = fChain->GetBranch("CalMipYDir");
   b_CalMipZDir = fChain->GetBranch("CalMipZDir");
   b_CalMipD2edge = fChain->GetBranch("CalMipD2edge");
   b_CalMipArcLen = fChain->GetBranch("CalMipArcLen");
   b_CalMipEcor = fChain->GetBranch("CalMipEcor");
   b_CalMipEcorRms = fChain->GetBranch("CalMipEcorRms");
   b_CalMipChi2 = fChain->GetBranch("CalMipChi2");
   b_CalMipErm = fChain->GetBranch("CalMipErm");
   b_FilterStatus_HI = fChain->GetBranch("FilterStatus_HI");
   b_FilterStatus_LO = fChain->GetBranch("FilterStatus_LO");
   b_FilterAlgStatus = fChain->GetBranch("FilterAlgStatus");
   b_FilterAngSep = fChain->GetBranch("FilterAngSep");
   b_CTBAcdLowerTileCount = fChain->GetBranch("CTBAcdLowerTileCount");
   b_CTBAcdUpperTileCount = fChain->GetBranch("CTBAcdUpperTileCount");
   b_CTBBestDeltaEoE = fChain->GetBranch("CTBBestDeltaEoE");
   b_CTBBestEnergy = fChain->GetBranch("CTBBestEnergy");
   b_CTBBestEnergyProb = fChain->GetBranch("CTBBestEnergyProb");
   b_CTBBestEnergyRatio = fChain->GetBranch("CTBBestEnergyRatio");
   b_CTBBestLogEnergy = fChain->GetBranch("CTBBestLogEnergy");
   b_CTBBestPSFerr = fChain->GetBranch("CTBBestPSFerr");
   b_CTBBestXDir = fChain->GetBranch("CTBBestXDir");
   b_CTBBestYDir = fChain->GetBranch("CTBBestYDir");
   b_CTBBestZDir = fChain->GetBranch("CTBBestZDir");
   b_CTBCORE = fChain->GetBranch("CTBCORE");
   b_CTBCalDocaAngle = fChain->GetBranch("CTBCalDocaAngle");
   b_CTBCalFrontBackRatio = fChain->GetBranch("CTBCalFrontBackRatio");
   b_CTBCalMaxXtalRatio = fChain->GetBranch("CTBCalMaxXtalRatio");
   b_CTBCalTransTCCD = fChain->GetBranch("CTBCalTransTCCD");
   b_CTBDiffCalDOCACalXtalRms = fChain->GetBranch("CTBDiffCalDOCACalXtalRms");
   b_CTBGAM = fChain->GetBranch("CTBGAM");
   b_CTBLastLayerProb = fChain->GetBranch("CTBLastLayerProb");
   b_CTBLkhdEnergyRatio = fChain->GetBranch("CTBLkhdEnergyRatio");
   b_CTBParamProb = fChain->GetBranch("CTBParamProb");
   b_CTBProfEnergyRatio = fChain->GetBranch("CTBProfEnergyRatio");
   b_CTBProfileProb = fChain->GetBranch("CTBProfileProb");
   b_CTBSecondaryCTBGAM = fChain->GetBranch("CTBSecondaryCTBGAM");
   b_CTBSummedCTBGAM = fChain->GetBranch("CTBSummedCTBGAM");
   b_CTBTkrCoreCalDoca = fChain->GetBranch("CTBTkrCoreCalDoca");
   b_CTBTkrEnergyFrac = fChain->GetBranch("CTBTkrEnergyFrac");
   b_CTBTkrLATEdge = fChain->GetBranch("CTBTkrLATEdge");
   b_CTBTkrSHRCalAngle = fChain->GetBranch("CTBTkrSHRCalAngle");
   b_CTBTrackerProb = fChain->GetBranch("CTBTrackerProb");
   b_CTBVTX = fChain->GetBranch("CTBVTX");
   b_CTBVtxTkr1Angle = fChain->GetBranch("CTBVtxTkr1Angle");
   b_CTBminCTBGAM = fChain->GetBranch("CTBminCTBGAM");
   b_FT1EventId = fChain->GetBranch("FT1EventId");
   b_FT1Energy = fChain->GetBranch("FT1Energy");
   b_FT1Theta = fChain->GetBranch("FT1Theta");
   b_FT1Phi = fChain->GetBranch("FT1Phi");
   b_FT1Ra = fChain->GetBranch("FT1Ra");
   b_FT1Dec = fChain->GetBranch("FT1Dec");
   b_FT1L = fChain->GetBranch("FT1L");
   b_FT1B = fChain->GetBranch("FT1B");
   b_FT1ZenithTheta = fChain->GetBranch("FT1ZenithTheta");
   b_FT1EarthAzimuth = fChain->GetBranch("FT1EarthAzimuth");
   b_FT1ConvPointX = fChain->GetBranch("FT1ConvPointX");
   b_FT1ConvPointY = fChain->GetBranch("FT1ConvPointY");
   b_FT1ConvPointZ = fChain->GetBranch("FT1ConvPointZ");
   b_FT1ConvLayer = fChain->GetBranch("FT1ConvLayer");
   b_FT1Livetime = fChain->GetBranch("FT1Livetime");

   return kTRUE;
}

void MeritEvent::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MeritEvent::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MeritEvent_cxx
