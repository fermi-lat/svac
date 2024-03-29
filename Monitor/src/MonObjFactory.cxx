// This class creates the objects that get the input values out of the digi/reco trees.
// Martin Kocian, SLAC, 2/1/07
// Code written for GLAST
//
// M.E.M.: removed all merit/recon/svac variables in preparation for Pass8 
// TODO: comment out from push_back function all merit/recon/svac variables
//
// Last updated with object timestamp by user kocian on Tue Feb 27 23:48:45 2007
// Last updated with object Gem_elapsed by user kocian on Fri Mar  9 19:50:55 2007
// Last updated with object calxtalene by user kocian on Fri Mar  9 20:38:36 2007
// Last updated with object condsummary by user kocian on Fri Mar  9 22:53:38 2007
// Last updated with object configkey1852 by user kocian on Fri Mar 30 18:25:24 2007
// Last updated with object TkrTriggerCounter by user dpaneque on Fri Apr  6 01:33:49 2007
// Last updated with object TkrTriggerTower by user dpaneque on Fri Apr  6 01:40:01 2007
// Last updated with object TkrHitsTowerPlane by user dpaneque on Fri Apr  6 01:40:59 2007
// Last updated with object ToT_Counter by user dpaneque on Fri Apr  6 01:42:22 2007
// Last updated with object ToT_0_Counter by user dpaneque on Fri Apr  6 01:42:54 2007
// Last updated with object ToT_250 by user dpaneque on Fri Apr  6 01:43:25 2007
// Last updated with object ToT_M250 by user dpaneque on Fri Apr  6 01:44:13 2007
// Last updated with object IsTkrDigi by user dpaneque on Fri Apr 13 18:40:42 2007
// Last updated with object ToT_con0 by user dpaneque on Fri Apr 13 18:42:53 2007
// Last updated with object ToT_con1 by user dpaneque on Fri Apr 13 18:44:21 2007
// Last updated with object CalEnergyRaw by user dpaneque on Wed Apr 18 18:28:31 2007
// Last updated with object LivetimeLast by user dpaneque on Fri Apr 27 01:39:12 2007
// Last updated with object DeadZoneLast by user dpaneque on Fri Apr 27 01:42:06 2007
// Last updated with object DiscardedLast by user dpaneque on Fri Apr 27 01:43:54 2007
// Last updated with object PrescaledLast by user dpaneque on Fri Apr 27 01:45:05 2007
// Last updated with object ElapsedLast by user dpaneque on Fri Apr 27 01:46:29 2007
// Last updated with object digitimestamp by user kocian on Fri Apr 20 18:17:48 2007
// Last updated with object filterstatus_hi by user kocian on Fri Apr 20 19:52:10 2007
// Last updated with object CalLoTriggerTower by user kocian on Fri Apr 20 20:12:05 2007
// Last updated with object CalHiTriggerTower by user kocian on Fri Apr 20 20:14:22 2007
// Last updated with object calxtalmaxtower by user kocian on Fri Apr 20 23:42:44 2007
// Last updated with object ntkrdigis by user kocian on Mon Apr 23 17:13:41 2007
// Last updated with object HFC by user kocian on Mon May 14 20:21:34 2007
// Last updated with object acdpha by user kocian on Sat May 26 18:13:04 2007
// Last updated with object numvetotiles by user kocian on Mon May 28 00:10:38 2007
// Last updated with object AcdGemVeto_AcdTile by user dpaneque on Mon Jun  4 22:34:02 2007
// Last updated with object AcdGemROI_Tower by user dpaneque on Mon Jun  4 22:59:56 2007
// Last updated with object AcdGemCNO_GARC by user dpaneque on Mon Jun  4 23:09:49 2007
// Last updated with object CalXHit_TowerCalLayerCalColumn by user dpaneque on Mon Jun  4 23:37:34 2007
// Last updated with object AcdHit_AcdTile by user dpaneque on Tue Jun  5 00:25:53 2007
// Last updated with object AcdPmtA_OverThreshold_AcdTile by user dpaneque on Tue Jun  5 00:41:02 2007
// Last updated with object AcdPmtB_OverThreshold_AcdTile by user dpaneque on Tue Jun  5 00:42:05 2007
// Last updated with object AcdVetoA_AcdTile by user dpaneque on Tue Jun  5 00:43:35 2007
// Last updated with object AcdVetoB_AcdTile by user dpaneque on Tue Jun  5 00:44:35 2007
// Last updated with object AcdPha_PmtA_AcdTile by user dpaneque on Tue Jun  5 01:11:11 2007
// Last updated with object AcdPha_PmtB_AcdTile by user dpaneque on Tue Jun  5 01:12:23 2007
// Last updated with object xoverthresh by user kocian on Thu May 31 20:39:26 2007
// Last updated with object condarrcallo by user kocian on Thu May 31 22:59:44 2007
// Last updated with object condarrcalhi by user kocian on Thu May 31 23:00:27 2007
// Last updated with object CalXHit_TowerCalLayer by user dpaneque on Thu Jun 28 23:07:31 2007
// Last updated with object ReconNumTracks by user dpaneque on Fri Jun 29 03:03:51 2007
// Last updated with object ReconDirXYZ by user dpaneque on Fri Jun 29 03:05:08 2007
// Last updated with object ReconVertexPosXYZ by user dpaneque on Fri Jun 29 03:06:54 2007
// Last updated with object ReconEnergy_TowerCalLayer by user dpaneque on Fri Jun 29 03:40:27 2007
// Last updated with object condarrtkr by user dpaneque on Sun Jul  1 00:36:38 2007
// Last updated with object condarrcno by user dpaneque on Sun Jul  1 00:37:40 2007
// Last updated with object condarrroi by user dpaneque on Sun Jul  1 00:38:14 2007
// Last updated with object DiscardedDelta by user dpaneque on Sun Jul  1 02:05:05 2007
// Last updated with object DeadZoneDelta by user dpaneque on Sun Jul  1 02:07:07 2007
// Last updated with object timestampdouble by user dpaneque on Fri Jul 20 01:17:49 2007
// Last updated with object ReconEnergy_TowerCalLayerCalColumn by user dpaneque on Sun Jul 22 23:45:43 2007
// Last updated with object ReconEnergy_TowerCalLayerCalColumnCalXFace by user dpaneque on Mon Jul 23 02:25:22 2007
// Last updated with object Tick20MHzDeviation by user dpaneque on Fri Aug 17 19:07:09 2007
// Last updated with object CalXAdc_TowerCalLayerCalColumnFaceRange by user dpaneque on Fri Aug 17 22:14:39 2007
// Last updated with object Range4 by user dpaneque on Tue Aug 21 23:20:51 2007
// Last updated with object CalXtalFaceSignal by user dpaneque on Thu Aug 23 18:28:31 2007
// Last updated with object CalReadoutRange by user dpaneque on Sun Aug 26 17:38:54 2007
// Last updated with object OBFStatus by user dpaneque on Wed Sep 26 01:24:44 2007
// Last updated with object AcdPhaMips_PmtA_AcdTile by user dpaneque on Wed Sep 26 03:52:14 2007
// Last updated with object AcdPhaMips_PmtB_AcdTile by user dpaneque on Wed Sep 26 03:52:50 2007
// Last updated with object Sequence by user dpaneque on Wed Sep 26 22:12:04 2007
// Last updated with object FilterBits by user dpaneque on Thu Sep 27 18:08:37 2007
// Last updated with object PrescaledDelta by user dpaneque on Fri Sep 28 18:41:04 2007
// Last updated with object GltWord by user dpaneque on Sat Sep 29 01:03:08 2007
// Last updated with object FT1ZenithTheta by user dpaneque on Sat Sep 29 01:08:22 2007
// Last updated with object CTBBestnergyProb by user dpaneque on Sat Sep 29 01:10:45 2007
// Last updated with object CTBCORE by user dpaneque on Sat Sep 29 01:11:28 2007
// Last updated with object DeltaEventTime by user dpaneque on Wed Oct  3 00:27:24 2007
// Last updated with object DeltaWindowOpen by user dpaneque on Wed Oct  3 00:33:15 2007
// Last updated with object DeltaEventTimeManual by user dpaneque on Mon Oct  8 19:35:18 2007
// Last updated with object TriggerEngine by user dpaneque on Mon Oct  8 20:00:57 2007
// Last updated with object CrateNumber by user dpaneque on Wed Oct 31 01:51:55 2007
// Last updated with object AcdVetoA_OR_B_AcdTile by user dpaneque on Wed Oct 31 19:29:40 2007
// Last updated with object AcdSingleHit by user dpaneque on Wed Oct 31 22:24:42 2007
// Last updated with object AcdSingleVeto_AcdTile by user dpaneque on Wed Oct 31 22:39:07 2007
// Last updated with object DatagramInfo by user dpaneque on Mon Dec 17 21:08:27 2007
// Last updated with object DeltaEvtID by user dpaneque on Tue Dec 18 02:30:41 2007
// Last updated with object Delta_CCSDSTime_EvtTime by user dpaneque on Tue Dec 18 02:35:26 2007
// Last updated with object NewSecond by user dpaneque on Tue Dec 18 04:51:28 2007
// Last updated with object AcdSignalInfo_PMTAcdTilePha by user dpaneque on Sat Jan  5 20:52:15 2008
// Last updated with object AcdHit_PmtGarcGafe by user dpaneque on Sun Jan  6 01:23:23 2008
// Last updated with object AcdVeto_PmtGarcGafe by user dpaneque on Sun Jan  6 01:24:10 2008
// Last updated with object AcdVeto_GafeGarc by user dpaneque on Sun Jan  6 02:11:06 2008
// Last updated with object AcdHit_GafeGarc by user dpaneque on Sun Jan  6 02:11:29 2008
// Last updated with object AcdPhaMipAngleCorrected_PmtExtrapolatedAcdTile by user dpaneque on Sun Jan  6 19:10:52 2008
// Last updated with object AcdPha_PmtIdPmtRangeAcdTile by user dpaneque on Sun Jan  6 22:42:24 2008
// Last updated with object AcdGlobalPos_NotMatchedTrack_FacePosXYZ by user dpaneque on Mon Jan  7 17:34:37 2008
// Last updated with object AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ by user dpaneque on Mon Jan  7 18:35:28 2008
// Last updated, REMOVING object "MonInput_ReconEnergy_TowerCalLayerCalColumnCalXFace" by user dpaneque on Wed Jan 16 2008 (manual entry)
// Last updated with object ZeroSuppress by user dpaneque on Thu Jan 24 19:13:42 2008
// Last updated with object FastMon_TkrHits by user dpaneque on Tue Feb 26 05:10:44 2008
// Last updated with object fastmontimestampdouble by user dpaneque on Tue Feb 26 05:19:54 2008
// Last updated with object FastMon_TkrHits_TowerPlane by user dpaneque on Tue Feb 26 05:59:16 2008
// Last updated with object FastMon_condsummary by user dpaneque on Tue Feb 26 06:01:21 2008
// Last updated with object FastMon_geomagnetic_InvariantLatitude by user dpaneque on Tue Feb 26 20:48:29 2008
// Last updated with object FastMon_geomagnetic_InvariantLambda by user bregeon on Thu Feb 28 11:08:45 2008
// Last updated with object FastMon_geomagnetic_InvariantRadius by user bregeon on Thu Feb 28 11:19:50 2008
// Last updated with object FastMon_spacecraft_latitude by user bregeon on Thu Feb 28 11:28:10 2008
// Last updated with object FastMon_spacecraft_longitude by user bregeon on Thu Feb 28 11:31:56 2008
// Last updated with object FastMon_spacecraft_altitude by user bregeon on Thu Feb 28 11:34:52 2008
// Last updated with object FastMon_geomagnetic_cutoff by user bregeon on Thu Feb 28 11:38:31 2008
// Last updated with object FastMon_geomagnetic_bb0 by user bregeon on Thu Feb 28 11:40:11 2008
// Last updated with object FastMon_geomagnetic_McIlwainL by user bregeon on Thu Feb 28 11:41:53 2008
// Last updated with object FastMon_Acd_Tile_Count by user bregeon on Thu Feb 28 14:08:11 2008
// Last updated with object FastMon_Cal_Tower_Count by user bregeon on Thu Feb 28 14:18:58 2008
// Last updated with object FastMon_TkrHits_TowerPlaneGTFE by user bregeon on Thu Feb 28 14:49:55 2008
// Last updated with object FastMon_CalLogEndRangeHit by user bregeon on Fri Feb 29 14:20:59 2008
// Last updated with object AcdVetoA_AcdTileDigiId by user dpaneque on Sat Mar  1 22:58:58 2008
// Last updated with object AcdVetoB_AcdTileDigiId by user dpaneque on Sat Mar  1 23:00:10 2008
// Last updated with object TkrTwrEdge by user dpaneque on Wed Mar 12 23:29:00 2008
// Last updated with object Tkr1TwrGap by user dpaneque on Wed Mar 12 23:29:50 2008
// Last updated with object Tkr1LATEdge by user dpaneque on Wed Mar 12 23:31:08 2008
// Last updated with object TkrSurplusHCInside by user dpaneque on Wed Mar 12 23:36:20 2008
// Last updated with object TkrThinHits by user dpaneque on Wed Mar 12 23:39:38 2008
// Last updated with object TkrThickHits by user dpaneque on Wed Mar 12 23:40:25 2008
// Last updated with object TkrBlankHits by user dpaneque on Wed Mar 12 23:41:07 2008
// Last updated with object TkrSurplusHitRatio by user dpaneque on Thu Mar 13 00:20:43 2008
// Last updated with object CalEnergyRaw by user dpaneque on Thu Mar 13 00:37:58 2008
// Last updated with object CalEnergyCorr by user dpaneque on Thu Mar 13 00:38:31 2008
// Last updated with object CalCsIRLn by user dpaneque on Thu Mar 13 00:39:11 2008
// Last updated with object CalTwrEdgeCntr by user dpaneque on Thu Mar 13 00:41:09 2008
// Last updated with object CalTrackAngle by user dpaneque on Thu Mar 13 00:42:08 2008
// Last updated with object CalTransRms by user dpaneque on Thu Mar 13 00:43:03 2008
// Last updated with object FT1Energy by user dpaneque on Thu Mar 13 01:03:40 2008
// Last updated with object FT1Theta by user dpaneque on Thu Mar 13 01:04:31 2008
// Last updated with object FT1Phi by user dpaneque on Thu Mar 13 01:05:06 2008
// Last updated with object GltGemSummary by user dpaneque on Thu Mar 13 01:08:29 2008
// Last updated with object FT1ZenithTheta by user dpaneque on Thu Mar 13 01:11:09 2008
// Last updated with object FT1EarthAzimuth by user dpaneque on Thu Mar 13 01:11:46 2008
// Last updated with object Tkr1KalEne by user dpaneque on Wed Mar 19 03:21:57 2008
// Last updated with object Tkr1KalThetaMS by user dpaneque on Wed Mar 19 03:23:17 2008
// Last updated with object FastMon_meta_context_open_mode by user bregeon on Wed Apr  9 10:04:23 2008
// Last updated with object FastMon_meta_context_open_modechanges by user bregeon on Thu Apr 10 14:16:26 2008
// Last updated with object PtMcIlwainB by user dpaneque on Fri Apr 18 02:44:04 2008
// Last updated with object PtMcIlwainL by user dpaneque on Fri Apr 18 02:44:28 2008
// Last updated with object PtLat by user dpaneque on Fri Apr 18 02:44:51 2008
// Last updated with object PtLon by user dpaneque on Fri Apr 18 02:45:24 2008
// Last updated with object PtMagLat by user dpaneque on Fri Apr 18 02:45:47 2008
// Last updated with object EvtEventId by user dpaneque on Tue Apr 22 03:56:45 2008
// Last updated with object CurrentORPreviousTimeToneMissing by user dpaneque on Thu Apr 24 16:33:12 2008
// Last updated with object FastMon_spacecraft_zra by user bregeon on Thu Apr 24 15:00:35 2008
// Last updated with object FastMon_spacecraft_zdec by user bregeon on Thu Apr 24 15:01:17 2008
// Last updated with object FastMon_spacecraft_pitch by user bregeon on Thu Apr 24 15:20:28 2008
// Last updated with object FastMon_spacecraft_roll by user bregeon on Thu Apr 24 15:21:31 2008
// Last updated with object FastMon_spacecraft_yaw by user bregeon on Thu Apr 24 15:21:55 2008
// Last updated with object sourceGps by user dpaneque on Thu Apr 24 23:26:12 2008
// Last updated with object FastMon_new_second by user bregeon on Fri May  2 09:24:08 2008
// Last updated with object FastMon_meta_context_current_source_gps by user bregeon on Fri May  2 09:26:32 2008
// Last updated with object trackermontimestamp by user dpaneque on Wed May 14 23:59:23 2008
// Last updated with object firstRunId by user dpaneque on Thu May 15 00:06:09 2008
// Last updated with object lastRunId by user dpaneque on Thu May 15 00:06:53 2008
// Last updated with object endTime by user dpaneque on Thu May 15 05:07:35 2008
// Last updated with object DataTransferId by user dpaneque on Fri May 16 01:13:45 2008
// Last updated with object TOT_Peak_TowerPlane by user dpaneque on Fri May 16 01:24:02 2008
// Last updated with object TOT_LWidth by user dpaneque on Fri May 16 04:51:31 2008
// Last updated with object TOT_GSigma by user dpaneque on Fri May 16 04:52:01 2008
// Last updated with object TOT_Entries by user dpaneque on Fri May 16 04:52:24 2008
// Last updated with object TOT_PeakError by user dpaneque on Fri May 16 04:52:48 2008
// Last updated with object TOT_LWidthError by user dpaneque on Fri May 16 04:53:08 2008
// Last updated with object TOT_GSigmaError by user dpaneque on Fri May 16 04:53:25 2008
// Last updated with object TOT_FitProb by user dpaneque on Fri May 16 04:53:41 2008
// Last updated with object TOT_FracLowTOT by user dpaneque on Fri May 16 04:54:00 2008
// Last updated with object layerEff by user dpaneque on Fri May 16 04:54:21 2008
// Last updated with object layerEff_err by user dpaneque on Fri May 16 04:54:48 2008
// Last updated with object towerEff by user dpaneque on Fri May 16 04:55:16 2008
// Last updated with object towerEff_err by user dpaneque on Fri May 16 04:55:34 2008
// Last updated with object trigEff by user dpaneque on Fri May 16 04:55:52 2008
// Last updated with object trigEff_err by user dpaneque on Fri May 16 04:56:20 2008
// Last updated with object layerdXY by user dpaneque on Fri May 16 04:56:39 2008
// Last updated with object layerdXY_err by user dpaneque on Fri May 16 04:56:58 2008
// Last updated with object layerOcc by user dpaneque on Fri May 16 04:57:23 2008
// Last updated with object stripOcc by user dpaneque on Fri May 16 04:57:38 2008
// Last updated with object fracSat by user dpaneque on Fri May 16 04:57:57 2008
// Last updated with object FastMon_meta_LATC_master by user bregeon on Sat May 17 12:23:23 2008
// Last updated with object FastMon_evt_data_transfer_id by user bregeon on Sat May 17 12:29:02 2008
// Last updated with object FswFilters by user dpaneque on Sat May 24 21:39:00 2008
// Last updated with object GemPrescale by user dpaneque on Sat May 24 21:46:05 2008
// Last updated with object DGNGemPrescale by user dpaneque on Sat May 24 21:47:37 2008
// Last updated with object FswFilters_GammaBits by user dpaneque on Sun May 25 23:31:55 2008
// Last updated with object CurrentTimeToneMissing by user dpaneque on Tue Jun 24 01:15:42 2008
// Last updated with object PtSCzenith by user dpaneque on Tue Jul  1 01:21:11 2008
// Last updated with object EventSizeInBytes by user dpaneque on Tue Jul  1 02:33:38 2008
// Last updated with object FastMon_spacecraft_rock by user bregeon on Fri Jul  4 00:56:59 2008
// Last updated with object FastMon_spacecraft_xra by user bregeon on Fri Jul  4 00:57:25 2008
// Last updated with object FastMon_spacecraft_xdec by user bregeon on Fri Jul  4 00:57:53 2008
// Last updated with object FastMon_spacecraft_earthlimb by user bregeon on Fri Jul  4 00:58:27 2008
// Last updated with object FastMon_spacecraft_earthlimb_fov by user bregeon on Fri Jul  4 00:58:47 2008
// Last updated with object FastMon_spacecraft_zgalL by user bregeon on Sun Jul 13 03:20:52 2008
// Last updated with object FastMon_spacecraft_zgalB by user bregeon on Sun Jul 13 03:21:35 2008
// Last updated with object GrbXDir by user dpaneque on Thu Jul 17 21:27:49 2008
// Last updated with object GrbYDir by user dpaneque on Thu Jul 17 21:28:31 2008
// Last updated with object GrbZDir by user dpaneque on Thu Jul 17 21:29:13 2008
// Last updated with object FswGamState by user dpaneque on Thu Jul 17 22:24:13 2008
// Last updated with object MootKey by user dpaneque on Thu Jul 17 22:33:04 2008
// Last updated with object CondSummary5bits by user dpaneque on Fri Jul 18 19:14:49 2008
// Last updated with object L1TTriggerWord5bits by user dpaneque on Fri Jul 18 19:17:08 2008
// Last updated with object CalXtalAdcPed by user dpaneque on Mon Aug 11 04:39:31 2008
// Last updated with object CalXtalAdcRng by user dpaneque on Mon Aug 11 04:41:33 2008
// Last updated with object FswFiltersLeaked by user dpaneque on Mon Aug 11 16:24:57 2008
// Last updated with object FswGAMMAEnergyInLeus by user dpaneque on Mon Aug 11 16:37:56 2008
// Last updated with object CompressedEventSizeInBytes by user dpaneque on Mon Aug 11 18:04:30 2008
// Last updated with object CompressionLevel by user dpaneque on Mon Aug 11 18:05:27 2008
// Last updated with object FastMon_spacecraft_orbit_mode by user bregeon on Mon Aug 25 10:01:09 2008
// Last updated with object FastMon_spacecraft_orbit_inSAA by user bregeon on Mon Aug 25 10:01:56 2008
// Last updated with object FastMon_error_summary by user bregeon on Mon Aug 25 14:46:04 2008
// Last updated with object TkrNumTracks by user dpaneque on Fri Sep 12 00:06:29 2008
// Last updated with object CalMIPRatio by user dpaneque on Fri Sep 12 00:39:02 2008
// Last updated with object TemBug by user dpaneque on Fri Mar 27 19:50:54 2009
// Last updated with object FastMon_spacecraft_distance_to_saa by user bregeon on Wed Aug  5 13:14:06 2009
// Last updated with object GoodEvent by user bregeon on Tue Jan 12 15:14:48 2010
// Last updated with object fracSat_err by user lbaldini on Thu Jan 14 18:31:31 2010
// Last updated with object layerOcc_err by user lbaldini on Fri Jan 15 11:25:13 2010
// Last updated with object stripOcc_err by user lbaldini on Fri Jan 15 13:01:16 2010
// Last updated with object FT1Ra by user dpaneque on Tue Jul  5 12:00:04 2011
// Last updated with object FT1Dec by user dpaneque on Tue Jul  5 12:01:02 2011
// Last updated with object Acd2CornerDoca by user lbaldini on Tue Feb  3 13:11:20 2015
// Last updated with object Acd2TileCount by user lbaldini on Tue Feb  3 13:34:07 2015
// Last updated with object Acd2RibbonCount by user lbaldini on Tue Feb  3 13:35:09 2015
// Last updated with object Acd2RibbonActDist by user lbaldini on Tue Feb  3 13:36:48 2015
// Last updated with object Acd2RibbonEnergy by user lbaldini on Tue Feb  3 13:37:40 2015
// Last updated with object Acd2Tkr1TileActDist by user maldera on Mon Apr 20 13:15:04 2015
#include "merit/MonInput_Acd2Tkr1TileActDist.h"

// Last updated with object Acd2TotalTileEnergy by user lbaldini on Tue Feb  3 14:27:00 2015
// Last updated with object WP8BestEnergy by user lbaldini on Tue Feb  3 15:14:15 2015
// Last updated with object WP8CTBestEnergyProb by user lbaldini on Tue Feb  3 15:15:12 2015
// Last updated with object WP8CTPSFCore by user lbaldini on Tue Feb  3 15:16:11 2015
// Last updated with object WP8BestZDir by user lbaldini on Tue Feb  3 15:16:41 2015
// Last updated with object DQMEventClass by user bregeon on Thu Feb  5 15:25:16 2015
// Last updated with object DQMEventType by user bregeon on Thu Feb  5 15:25:59 2015
// Last updated with object Acd2TileActDist3D by user maldera on Mon Apr 20 11:49:49 2015
// Last updated with object Acd2TileActDistEnergy by user maldera on Mon Apr 20 12:13:49 2015
// Last updated with object Acd2Tkr1TileActDistEnergy by user maldera on Mon Apr 20 12:50:31 2015
#include "merit/MonInput_Acd2Tkr1TileActDistEnergy.h"
#include "merit/MonInput_Acd2TileActDistEnergy.h"
#include "merit/MonInput_Acd2TileActDist3D.h"
#include "merit/MonInput_DQMEventType.h"
#include "merit/MonInput_DQMEventClass.h"
#include "merit/MonInput_WP8BestZDir.h"
#include "merit/MonInput_WP8CTPSFCore.h"
#include "merit/MonInput_WP8CTBestEnergyProb.h"
#include "merit/MonInput_WP8BestEnergy.h"
#include "merit/MonInput_Acd2TotalTileEnergy.h"
#include "merit/MonInput_Acd2RibbonEnergy.h"
#include "merit/MonInput_Acd2RibbonActDist.h"
#include "merit/MonInput_Acd2RibbonCount.h"
#include "merit/MonInput_Acd2TileCount.h"
#include "merit/MonInput_Acd2CornerDoca.h"
#include "merit/MonInput_FT1Dec.h"
#include "merit/MonInput_FT1Ra.h"
#include "trackermon/MonInput_stripOcc_err.h"
#include "trackermon/MonInput_layerOcc_err.h"
#include "trackermon/MonInput_fracSat_err.h"
#include "digi/MonInput_GoodEvent.h"
#include "fastmon/MonInput_FastMon_spacecraft_distance_to_saa.h"
#include "digi/MonInput_TemBug.h"
#include "merit/MonInput_CalMIPRatio.h"
#include "merit/MonInput_TkrNumTracks.h"
#include "fastmon/MonInput_FastMon_error_summary.h"
#include "fastmon/MonInput_FastMon_spacecraft_orbit_inSAA.h"
#include "fastmon/MonInput_FastMon_spacecraft_orbit_mode.h"
#include "digi/MonInput_CompressionLevel.h"
#include "digi/MonInput_CompressedEventSizeInBytes.h"
#include "digi/MonInput_FswGAMMAEnergyInLeus.h"
#include "digi/MonInput_FswFiltersLeaked.h"
#include "cal/MonInput_CalXtalAdcRng.h"
#include "cal/MonInput_CalXtalAdcPed.h"
#include "digi/MonInput_L1TTriggerWord5bits.h"
#include "digi/MonInput_CondSummary5bits.h"
#include "digi/MonInput_MootKey.h"
#include "merit/MonInput_FswGamState.h"
#include "merit/MonInput_GrbZDir.h"
#include "merit/MonInput_GrbYDir.h"
#include "merit/MonInput_GrbXDir.h"
#include "fastmon/MonInput_FastMon_spacecraft_zgalB.h"
#include "fastmon/MonInput_FastMon_spacecraft_zgalL.h"
#include "fastmon/MonInput_FastMon_spacecraft_earthlimb_fov.h"
#include "fastmon/MonInput_FastMon_spacecraft_earthlimb.h"
#include "fastmon/MonInput_FastMon_spacecraft_xdec.h"
#include "fastmon/MonInput_FastMon_spacecraft_xra.h"
#include "fastmon/MonInput_FastMon_spacecraft_rock.h"
#include "digi/MonInput_EventSizeInBytes.h"
#include "merit/MonInput_PtSCzenith.h"
#include "digi/MonInput_CurrentTimeToneMissing.h"
#include "digi/MonInput_FswFilters_GammaBits.h"
#include "digi/MonInput_DGNGemPrescale.h"
#include "digi/MonInput_GemPrescale.h"
#include "digi/MonInput_FswFilters.h"
#include "fastmon/MonInput_FastMon_evt_data_transfer_id.h"
#include "fastmon/MonInput_FastMon_meta_LATC_master.h"
#include "trackermon/MonInput_fracSat.h"
#include "trackermon/MonInput_stripOcc.h"
#include "trackermon/MonInput_layerOcc.h"
#include "trackermon/MonInput_layerdXY_err.h"
#include "trackermon/MonInput_layerdXY.h"
#include "trackermon/MonInput_trigEff_err.h"
#include "trackermon/MonInput_trigEff.h"
#include "trackermon/MonInput_towerEff_err.h"
#include "trackermon/MonInput_towerEff.h"
#include "trackermon/MonInput_layerEff_err.h"
#include "trackermon/MonInput_layerEff.h"
#include "trackermon/MonInput_TOT_FracLowTOT.h"
#include "trackermon/MonInput_TOT_FitProb.h"
#include "trackermon/MonInput_TOT_GSigmaError.h"
#include "trackermon/MonInput_TOT_LWidthError.h"
#include "trackermon/MonInput_TOT_PeakError.h"
#include "trackermon/MonInput_TOT_Entries.h"
#include "trackermon/MonInput_TOT_GSigma.h"
#include "trackermon/MonInput_TOT_LWidth.h"
#include "trackermon/MonInput_TOT_Peak_TowerPlane.h"
#include "digi/MonInput_DataTransferId.h"
#include "trackermon/MonInput_endTime.h"
#include "trackermon/MonInput_lastRunId.h"
#include "trackermon/MonInput_firstRunId.h"
#include "trackermon/MonInput_trackermontimestamp.h"
#include "fastmon/MonInput_FastMon_meta_context_current_source_gps.h"
#include "fastmon/MonInput_FastMon_new_second.h"
#include "digi/MonInput_sourceGps.h"
#include "digi/MonInput_CurrentORPreviousTimeToneMissing.h"
#include "fastmon/MonInput_FastMon_spacecraft_yaw.h"
#include "fastmon/MonInput_FastMon_spacecraft_roll.h"
#include "fastmon/MonInput_FastMon_spacecraft_pitch.h"
#include "fastmon/MonInput_FastMon_spacecraft_zdec.h"
#include "fastmon/MonInput_FastMon_spacecraft_zra.h"
#include "merit/MonInput_EvtEventId.h"
#include "merit/MonInput_PtMagLat.h"
#include "merit/MonInput_PtLon.h"
#include "merit/MonInput_PtLat.h"
#include "merit/MonInput_PtMcIlwainL.h"
#include "merit/MonInput_PtMcIlwainB.h"
#include "fastmon/MonInput_FastMon_meta_context_open_modechanges.h"
#include "fastmon/MonInput_FastMon_meta_context_open_mode.h"
#include "merit/MonInput_Tkr1KalThetaMS.h"
#include "merit/MonInput_Tkr1KalEne.h"
#include "merit/MonInput_FT1EarthAzimuth.h"
#include "merit/MonInput_FT1ZenithTheta.h"
#include "merit/MonInput_GltGemSummary.h"
#include "merit/MonInput_FT1Phi.h"
#include "merit/MonInput_FT1Theta.h"
#include "merit/MonInput_FT1Energy.h"
#include "merit/MonInput_CalTransRms.h"
#include "merit/MonInput_CalTrackAngle.h"
#include "merit/MonInput_CalTwrEdgeCntr.h"
#include "merit/MonInput_CalCsIRLn.h"
#include "merit/MonInput_CalEnergyCorr.h"
#include "merit/MonInput_CalEnergyRaw.h"
#include "merit/MonInput_TkrSurplusHitRatio.h"
#include "merit/MonInput_TkrBlankHits.h"
#include "merit/MonInput_TkrThickHits.h"
#include "merit/MonInput_TkrThinHits.h"
#include "merit/MonInput_TkrSurplusHCInside.h"
#include "merit/MonInput_Tkr1LATEdge.h"
#include "merit/MonInput_Tkr1TwrGap.h"
#include "merit/MonInput_TkrTwrEdge.h"
#include "digi/MonInput_AcdVetoB_AcdTileDigiId.h"
#include "digi/MonInput_AcdVetoA_AcdTileDigiId.h"
#include "fastmon/MonInput_FastMon_CalLogEndRangeHit.h"
#include "fastmon/MonInput_FastMon_TkrHits_TowerPlaneGTFE.h"
#include "fastmon/MonInput_FastMon_Cal_Tower_Count.h"
#include "fastmon/MonInput_FastMon_Acd_Tile_Count.h"
#include "fastmon/MonInput_FastMon_geomagnetic_McIlwainL.h"
#include "fastmon/MonInput_FastMon_geomagnetic_bb0.h"
#include "fastmon/MonInput_FastMon_geomagnetic_cutoff.h"
#include "fastmon/MonInput_FastMon_spacecraft_altitude.h"
#include "fastmon/MonInput_FastMon_spacecraft_longitude.h"
#include "fastmon/MonInput_FastMon_spacecraft_latitude.h"
#include "fastmon/MonInput_FastMon_geomagnetic_InvariantRadius.h"
#include "fastmon/MonInput_FastMon_geomagnetic_InvariantLambda.h"
#include "fastmon/MonInput_FastMon_geomagnetic_InvariantLatitude.h"
#include "fastmon/MonInput_FastMon_condsummary.h"
#include "fastmon/MonInput_FastMon_TkrHits_TowerPlane.h"
#include "fastmon/MonInput_fastmontimestampdouble.h"
#include "fastmon/MonInput_FastMon_TkrHits.h"
#include "digi/MonInput_ZeroSuppress.h"
#include "digi/MonInput_AcdPha_PmtIdPmtRangeAcdTile.h"
#include "recon/MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile.h"
#include "recon/MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ.h"
#include "digi/MonInput_AcdHit_GafeGarc.h"
#include "digi/MonInput_AcdVeto_GafeGarc.h"
#include "digi/MonInput_AcdVeto_PmtGarcGafe.h"
#include "digi/MonInput_AcdHit_PmtGarcGafe.h"
#include "digi/MonInput_NewSecond.h"
#include "digi/MonInput_Delta_CCSDSTime_EvtTime.h"
#include "digi/MonInput_DeltaEvtID.h"
#include "digi/MonInput_DatagramInfo.h"
#include "digi/MonInput_AcdSingleVeto_AcdTile.h"
#include "digi/MonInput_AcdSingleHit.h"
#include "digi/MonInput_AcdVetoA_OR_B_AcdTile.h"
#include "digi/MonInput_CrateNumber.h"
#include "digi/MonInput_TriggerEngine.h"
#include "digi/MonInput_DeltaEventTimeManual.h"
#include "digi/MonInput_DeltaWindowOpen.h"
#include "digi/MonInput_DeltaEventTime.h"
#include "merit/MonInput_FT1ZenithTheta.h"
#include "merit/MonInput_GltWord.h"
#include "digi/MonInput_PrescaledDelta.h"
#include "digi/MonInput_FilterBits.h"
#include "digi/MonInput_Sequence.h"
#include "recon/MonInput_Acd2PhaMips_PmtB_AcdTile.h"
#include "recon/MonInput_Acd2PhaMips_PmtA_AcdTile.h"
#include "digi/MonInput_OBFStatus.h"
#include "digi/MonInput_CalReadoutRange.h"
#include "cal/MonInput_CalXtalFaceSignal.h"
#include "digi/MonInput_Range4.h"
#include "digi/MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange.h"
#include "digi/MonInput_Tick20MHzDeviation.h"
#include "recon/MonInput_ReconEnergy_TowerCalLayerCalColumn.h"
#include "digi/MonInput_timestampdouble.h"
#include "digi/MonInput_DeadZoneDelta.h"
#include "digi/MonInput_DiscardedDelta.h"
#include "digi/MonInput_condarrroi.h"
#include "digi/MonInput_condarrcno.h"
#include "digi/MonInput_condarrtkr.h"
//#include "recon/MonInput_ReconEnergy_TowerCalLayer.h"
#include "recon/MonInput_ReconVertexPosXYZ.h"
#include "recon/MonInput_ReconDirXYZ.h"
#include "recon/MonInput_ReconNumTracks.h"
#include "digi/MonInput_CalXHit_TowerCalLayer.h"
#include "digi/MonInput_AcdPha_PmtB_AcdTile.h"
#include "digi/MonInput_AcdPha_PmtA_AcdTile.h"
#include "digi/MonInput_AcdVetoB_AcdTile.h"
#include "digi/MonInput_AcdVetoA_AcdTile.h"
#include "digi/MonInput_AcdPmtB_OverThreshold_AcdTile.h"
#include "digi/MonInput_AcdPmtA_OverThreshold_AcdTile.h"
#include "digi/MonInput_AcdHit_AcdTile.h"
#include "digi/MonInput_CalXHit_TowerCalLayerCalColumn.h"
#include "digi/MonInput_AcdGemCNO_GARC.h"
#include "digi/MonInput_AcdGemROI_Tower.h"
#include "digi/MonInput_AcdGemVeto_AcdTile.h"
#include "digi/MonInput_condarrcalhi.h"
#include "digi/MonInput_condarrcallo.h"
//#include "recon/MonInput_xoverthresh.h"
#include "digi/MonInput_ElapsedLast.h"
#include "digi/MonInput_PrescaledLast.h"
#include "digi/MonInput_DiscardedLast.h"
#include "digi/MonInput_DeadZoneLast.h"
#include "digi/MonInput_LivetimeLast.h"
#include "merit/MonInput_CalEnergyRaw.h"
#include "digi/MonInput_numvetotiles.h"
#include "digi/MonInput_acdpha.h"
//#include "recon/MonInput_HFC.h"
#include "digi/MonInput_ntkrdigis.h"
//#include "recon/MonInput_calxtalmaxtower.h"
#include "digi/MonInput_CalHiTriggerTower.h"
#include "digi/MonInput_CalLoTriggerTower.h"
#include "digi/MonInput_filterstatus_hi.h"
#include "digi/MonInput_digitimestamp.h"
#include "digi/MonInput_ToT_con1_TowerPlane.h"
#include "digi/MonInput_ToT_con0_TowerPlane.h"
#include "digi/MonInput_IsTkrDigi_TowerPlane.h"
#include "digi/MonInput_TkrHitsTowerPlane.h"
#include "digi/MonInput_TkrTriggerTower.h"
#include "digi/MonInput_configkey1852.h"
#include "digi/MonInput_condsummary.h"
//#include "svac/MonInput_calxtalene.h"
#include "digi/MonInput_Gem_elapsed.h"
#include "digi/MonInput_timestamp.h"
#include "digi/MonInput_nAcd.h"
#include "MonObjFactory.h"

#include <iostream>
#include <cassert>



MonObjFactory::MonObjFactory(){;}
MonInputObject* MonObjFactory::getMonInputObject(string s){
  if(s=="nACD")
    return new MonInput_nAcd;
  if (s=="timestamp")
    return new MonInput_timestamp;

    if (s=="Gem_elapsed")
    return new MonInput_Gem_elapsed;
//  if (s=="calxtalene")
//    return new MonInput_calxtalene;
  if (s=="condsummary")
    return new MonInput_condsummary;
  if (s=="configkey1852")
    return new MonInput_configkey1852;
  if (s=="TkrTriggerTower")
    return new MonInput_TkrTriggerTower;
  if (s=="TkrHitsTowerPlane")
    return new MonInput_TkrHitsTowerPlane;
  if (s=="IsTkrDigi_TowerPlane")
    return new MonInput_IsTkrDigi_TowerPlane;
  if (s=="ToT_con0_TowerPlane")
    return new MonInput_ToT_con0_TowerPlane;
  if (s=="ToT_con1_TowerPlane")
    return new MonInput_ToT_con1_TowerPlane;
  if (s=="CalEnergyRaw")
    return new MonInput_CalEnergyRaw;
  if (s=="LivetimeLast")
    return new MonInput_LivetimeLast;
  if (s=="DeadZoneLast")
    return new MonInput_DeadZoneLast;
  if (s=="DiscardedLast")
    return new MonInput_DiscardedLast;
  if (s=="PrescaledLast")
    return new MonInput_PrescaledLast;
  if (s=="ElapsedLast")
    return new MonInput_ElapsedLast;
  if (s=="digitimestamp")
    return new MonInput_digitimestamp;
  if (s=="filterstatus_hi")
    return new MonInput_filterstatus_hi;
  if (s=="CalLoTriggerTower")
    return new MonInput_CalLoTriggerTower;
  if (s=="CalHiTriggerTower")
    return new MonInput_CalHiTriggerTower;
//  if (s=="calxtalmaxtower")
//    return new MonInput_calxtalmaxtower;
  if (s=="ntkrdigis")
    return new MonInput_ntkrdigis;
//  if (s=="HFC")
//    return new MonInput_HFC;
  if (s=="acdpha")
    return new MonInput_acdpha;
  if (s=="numvetotiles")
    return new MonInput_numvetotiles;
  if (s=="AcdGemVeto_AcdTile")
    return new MonInput_AcdGemVeto_AcdTile;
  if (s=="AcdGemROI_Tower")
    return new MonInput_AcdGemROI_Tower;
  if (s=="AcdGemCNO_GARC")
    return new MonInput_AcdGemCNO_GARC;
  if (s=="CalXHit_TowerCalLayerCalColumn")
    return new MonInput_CalXHit_TowerCalLayerCalColumn;
  if (s=="AcdHit_AcdTile")
    return new MonInput_AcdHit_AcdTile;
  if (s=="AcdPmtA_OverThreshold_AcdTile")
    return new MonInput_AcdPmtA_OverThreshold_AcdTile;
  if (s=="AcdPmtB_OverThreshold_AcdTile")
    return new MonInput_AcdPmtB_OverThreshold_AcdTile;
  if (s=="AcdVetoA_AcdTile")
    return new MonInput_AcdVetoA_AcdTile;
  if (s=="AcdVetoB_AcdTile")
    return new MonInput_AcdVetoB_AcdTile;
  if (s=="AcdPha_PmtA_AcdTile")
    return new MonInput_AcdPha_PmtA_AcdTile;
  if (s=="AcdPha_PmtB_AcdTile")
    return new MonInput_AcdPha_PmtB_AcdTile;
//  if (s=="xoverthresh")
//    return new MonInput_xoverthresh;
  if (s=="condarrcallo")
    return new MonInput_condarrcallo;
  if (s=="condarrcalhi")
    return new MonInput_condarrcalhi;
  if (s=="CalXHit_TowerCalLayer")
    return new MonInput_CalXHit_TowerCalLayer;
  if (s=="ReconNumTracks")
    return new MonInput_ReconNumTracks;
  if (s=="ReconDirXYZ")
    return new MonInput_ReconDirXYZ;
  if (s=="ReconVertexPosXYZ")
    return new MonInput_ReconVertexPosXYZ;
//  if (s=="ReconEnergy_TowerCalLayer")
//    return new MonInput_ReconEnergy_TowerCalLayer;
  if (s=="condarrtkr")
    return new MonInput_condarrtkr;
  if (s=="condarrcno")
    return new MonInput_condarrcno;
  if (s=="condarrroi")
    return new MonInput_condarrroi;
  if (s=="DiscardedDelta")
    return new MonInput_DiscardedDelta;
  if (s=="DeadZoneDelta")
    return new MonInput_DeadZoneDelta;
  if (s=="timestampdouble")
    return new MonInput_timestampdouble;
  if (s=="ReconEnergy_TowerCalLayerCalColumn")
    return new MonInput_ReconEnergy_TowerCalLayerCalColumn;
  if (s=="Tick20MHzDeviation")
    return new MonInput_Tick20MHzDeviation;
  if (s=="CalXAdc_TowerCalLayerCalColumnFaceRange")
    return new MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange;
  if (s=="Range4")
    return new MonInput_Range4;
  if (s=="CalXtalFaceSignal")
    return new MonInput_CalXtalFaceSignal;
  if (s=="CalReadoutRange")
    return new MonInput_CalReadoutRange;
  if (s=="OBFStatus")
    return new MonInput_OBFStatus;
  if (s=="Acd2PhaMips_PmtA_AcdTile")
    return new MonInput_Acd2PhaMips_PmtA_AcdTile;
  if (s=="Acd2PhaMips_PmtB_AcdTile")
    return new MonInput_Acd2PhaMips_PmtB_AcdTile;
  if (s=="Sequence")
    return new MonInput_Sequence;
  if (s=="FilterBits")
    return new MonInput_FilterBits;
  if (s=="PrescaledDelta")
    return new MonInput_PrescaledDelta;
  if (s=="GltWord")
    return new MonInput_GltWord;
  if (s=="FT1ZenithTheta")
    return new MonInput_FT1ZenithTheta;
  if (s=="DeltaEventTime")
    return new MonInput_DeltaEventTime;
  if (s=="DeltaWindowOpen")
    return new MonInput_DeltaWindowOpen;
  if (s=="DeltaEventTimeManual")
    return new MonInput_DeltaEventTimeManual;
  if (s=="TriggerEngine")
    return new MonInput_TriggerEngine;
  if (s=="CrateNumber")
    return new MonInput_CrateNumber;
  if (s=="AcdVetoA_OR_B_AcdTile")
    return new MonInput_AcdVetoA_OR_B_AcdTile;
  if (s=="AcdSingleHit")
    return new MonInput_AcdSingleHit;
  if (s=="AcdSingleVeto_AcdTile")
    return new MonInput_AcdSingleVeto_AcdTile;
  if (s=="DatagramInfo")
    return new MonInput_DatagramInfo;
  if (s=="DeltaEvtID")
    return new MonInput_DeltaEvtID;
  if (s=="Delta_CCSDSTime_EvtTime")
    return new MonInput_Delta_CCSDSTime_EvtTime;
  if (s=="NewSecond")
    return new MonInput_NewSecond;
  if (s=="AcdHit_PmtGarcGafe")
    return new MonInput_AcdHit_PmtGarcGafe;
  if (s=="AcdVeto_PmtGarcGafe")
    return new MonInput_AcdVeto_PmtGarcGafe;
  if (s=="AcdVeto_GafeGarc")
    return new MonInput_AcdVeto_GafeGarc;
  if (s=="AcdHit_GafeGarc")
    return new MonInput_AcdHit_GafeGarc;
  if (s=="Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile")
    return new MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile;
  if (s=="AcdPha_PmtIdPmtRangeAcdTile")
    return new MonInput_AcdPha_PmtIdPmtRangeAcdTile;
//  if (s=="AcdGlobalPos_NotMatchedTrack_FacePosXYZ")
//    return new MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ;
  if (s=="Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ")
    return new MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ;
  if (s=="ZeroSuppress")
    return new MonInput_ZeroSuppress;
  if (s=="FastMon_TkrHits")
    return new MonInput_FastMon_TkrHits;
  if (s=="fastmontimestampdouble")
    return new MonInput_fastmontimestampdouble;
  if (s=="FastMon_TkrHits_TowerPlane")
    return new MonInput_FastMon_TkrHits_TowerPlane;
  if (s=="FastMon_condsummary")
    return new MonInput_FastMon_condsummary;
  if (s=="FastMon_geomagnetic_InvariantLatitude")
    return new MonInput_FastMon_geomagnetic_InvariantLatitude;
  if (s=="FastMon_geomagnetic_InvariantLambda")
    return new MonInput_FastMon_geomagnetic_InvariantLambda;
  if (s=="FastMon_geomagnetic_InvariantRadius")
    return new MonInput_FastMon_geomagnetic_InvariantRadius;
  if (s=="FastMon_spacecraft_latitude")
    return new MonInput_FastMon_spacecraft_latitude;
  if (s=="FastMon_spacecraft_longitude")
    return new MonInput_FastMon_spacecraft_longitude;
  if (s=="FastMon_spacecraft_altitude")
    return new MonInput_FastMon_spacecraft_altitude;
  if (s=="FastMon_geomagnetic_cutoff")
    return new MonInput_FastMon_geomagnetic_cutoff;
  if (s=="FastMon_geomagnetic_bb0")
    return new MonInput_FastMon_geomagnetic_bb0;
  if (s=="FastMon_geomagnetic_McIlwainL")
    return new MonInput_FastMon_geomagnetic_McIlwainL;
  if (s=="FastMon_Acd_Tile_Count")
    return new MonInput_FastMon_Acd_Tile_Count;
  if (s=="FastMon_Cal_Tower_Count")
    return new MonInput_FastMon_Cal_Tower_Count;
  if (s=="FastMon_TkrHits_TowerPlaneGTFE")
    return new MonInput_FastMon_TkrHits_TowerPlaneGTFE;
  if (s=="FastMon_CalLogEndRangeHit")
    return new MonInput_FastMon_CalLogEndRangeHit;
  if (s=="AcdVetoA_AcdTileDigiId")
    return new MonInput_AcdVetoA_AcdTileDigiId;
  if (s=="AcdVetoB_AcdTileDigiId")
    return new MonInput_AcdVetoB_AcdTileDigiId;
  if (s=="TkrTwrEdge")
    return new MonInput_TkrTwrEdge;
  if (s=="Tkr1TwrGap")
    return new MonInput_Tkr1TwrGap;
  if (s=="Tkr1LATEdge")
    return new MonInput_Tkr1LATEdge;
  if (s=="TkrSurplusHCInside")
    return new MonInput_TkrSurplusHCInside;
  if (s=="TkrThinHits")
    return new MonInput_TkrThinHits;
  if (s=="TkrThickHits")
    return new MonInput_TkrThickHits;
  if (s=="TkrBlankHits")
    return new MonInput_TkrBlankHits;
  if (s=="TkrSurplusHitRatio")
    return new MonInput_TkrSurplusHitRatio;
  if (s=="CalEnergyRaw")
    return new MonInput_CalEnergyRaw;
  if (s=="CalEnergyCorr")
    return new MonInput_CalEnergyCorr;
  if (s=="CalCsIRLn")
    return new MonInput_CalCsIRLn;
  if (s=="CalTwrEdgeCntr")
    return new MonInput_CalTwrEdgeCntr;
  if (s=="CalTrackAngle")
    return new MonInput_CalTrackAngle;
  if (s=="CalTransRms")
    return new MonInput_CalTransRms;
  if (s=="FT1Energy")
    return new MonInput_FT1Energy;
  if (s=="FT1Theta")
    return new MonInput_FT1Theta;
  if (s=="FT1Phi")
    return new MonInput_FT1Phi;
  if (s=="GltGemSummary")
    return new MonInput_GltGemSummary;
  if (s=="FT1ZenithTheta")
    return new MonInput_FT1ZenithTheta;
  if (s=="FT1EarthAzimuth")
    return new MonInput_FT1EarthAzimuth;
  if (s=="Tkr1KalEne")
    return new MonInput_Tkr1KalEne;
  if (s=="Tkr1KalThetaMS")
    return new MonInput_Tkr1KalThetaMS;
  if (s=="FastMon_meta_context_open_mode")
    return new MonInput_FastMon_meta_context_open_mode;
  if (s=="FastMon_meta_context_open_modechanges")
    return new MonInput_FastMon_meta_context_open_modechanges;
  if (s=="PtMcIlwainB")
    return new MonInput_PtMcIlwainB;
  if (s=="PtMcIlwainL")
    return new MonInput_PtMcIlwainL;
  if (s=="PtLat")
    return new MonInput_PtLat;
  if (s=="PtLon")
    return new MonInput_PtLon;
  if (s=="PtMagLat")
    return new MonInput_PtMagLat;
  if (s=="EvtEventId")
    return new MonInput_EvtEventId;
  if (s=="CurrentORPreviousTimeToneMissing")
    return new MonInput_CurrentORPreviousTimeToneMissing;
  if (s=="FastMon_spacecraft_zra")
    return new MonInput_FastMon_spacecraft_zra;
  if (s=="FastMon_spacecraft_zdec")
    return new MonInput_FastMon_spacecraft_zdec;
  if (s=="FastMon_spacecraft_pitch")
    return new MonInput_FastMon_spacecraft_pitch;
  if (s=="FastMon_spacecraft_roll")
    return new MonInput_FastMon_spacecraft_roll;
  if (s=="FastMon_spacecraft_yaw")
    return new MonInput_FastMon_spacecraft_yaw;
  if (s=="sourceGps")
    return new MonInput_sourceGps;
  if (s=="FastMon_new_second")
    return new MonInput_FastMon_new_second;
  if (s=="FastMon_meta_context_current_source_gps")
    return new MonInput_FastMon_meta_context_current_source_gps;
  if (s=="trackermontimestamp")
    return new MonInput_trackermontimestamp;
  if (s=="firstRunId")
    return new MonInput_firstRunId;
  if (s=="lastRunId")
    return new MonInput_lastRunId;
  if (s=="endTime")
    return new MonInput_endTime;
  if (s=="DataTransferId")
    return new MonInput_DataTransferId;
  if (s=="TOT_Peak_TowerPlane")
    return new MonInput_TOT_Peak_TowerPlane;
  if (s=="TOT_LWidth_TowerPlane")
    return new MonInput_TOT_LWidth;
  if (s=="TOT_GSigma_TowerPlane")
    return new MonInput_TOT_GSigma;
  if (s=="TOT_Entries_TowerPlane")
    return new MonInput_TOT_Entries;
  if (s=="TOT_PeakError_TowerPlane")
    return new MonInput_TOT_PeakError;
  if (s=="TOT_LWidthError_TowerPlane")
    return new MonInput_TOT_LWidthError;
  if (s=="TOT_GSigmaError_TowerPlane")
    return new MonInput_TOT_GSigmaError;
  if (s=="TOT_FitProb_TowerPlane")
    return new MonInput_TOT_FitProb;
  if (s=="TOT_FracLowTOT_TowerPlane")
    return new MonInput_TOT_FracLowTOT;
  if (s=="layerEff_TowerPlane")
    return new MonInput_layerEff;
  if (s=="layerEff_err_TowerPlane")
    return new MonInput_layerEff_err;
  if (s=="towerEff_Tower")
    return new MonInput_towerEff;
  if (s=="towerEff_err_Tower")
    return new MonInput_towerEff_err;
  if (s=="trigEff_Tower")
    return new MonInput_trigEff;
  if (s=="trigEff_err_Tower")
    return new MonInput_trigEff_err;
  if (s=="layerdXY_TowerPlane")
    return new MonInput_layerdXY;
  if (s=="layerdXY_err_TowerPlane")
    return new MonInput_layerdXY_err;
  if (s=="layerOcc_TowerPlane")
    return new MonInput_layerOcc;
  if (s=="stripOcc_TowerPlane")
    return new MonInput_stripOcc;
  if (s=="fracSat_TowerPlane")
    return new MonInput_fracSat;
  if (s=="FastMon_meta_LATC_master")
    return new MonInput_FastMon_meta_LATC_master;
  if (s=="FastMon_evt_data_transfer_id")
    return new MonInput_FastMon_evt_data_transfer_id;
  if (s=="FswFilters")
    return new MonInput_FswFilters;
  if (s=="GemPrescale")
    return new MonInput_GemPrescale;
  if (s=="DGNGemPrescale")
    return new MonInput_DGNGemPrescale;
  if (s=="FswFilters_GammaBits")
    return new MonInput_FswFilters_GammaBits;
  if (s=="CurrentTimeToneMissing")
    return new MonInput_CurrentTimeToneMissing;
  if (s=="PtSCzenith")
    return new MonInput_PtSCzenith;
  if (s=="EventSizeInBytes")
    return new MonInput_EventSizeInBytes;
  if (s=="FastMon_spacecraft_rock")
    return new MonInput_FastMon_spacecraft_rock;
  if (s=="FastMon_spacecraft_xra")
    return new MonInput_FastMon_spacecraft_xra;
  if (s=="FastMon_spacecraft_xdec")
    return new MonInput_FastMon_spacecraft_xdec;
  if (s=="FastMon_spacecraft_earthlimb")
    return new MonInput_FastMon_spacecraft_earthlimb;
  if (s=="FastMon_spacecraft_earthlimb_fov")
    return new MonInput_FastMon_spacecraft_earthlimb_fov;
  if (s=="FastMon_spacecraft_zgalL")
    return new MonInput_FastMon_spacecraft_zgalL;
  if (s=="FastMon_spacecraft_zgalB")
    return new MonInput_FastMon_spacecraft_zgalB;
  if (s=="GrbXDir")
    return new MonInput_GrbXDir;
  if (s=="GrbYDir")
    return new MonInput_GrbYDir;
  if (s=="GrbZDir")
    return new MonInput_GrbZDir;
  if (s=="FswGamState")
    return new MonInput_FswGamState;
  if (s=="MootKey")
    return new MonInput_MootKey;
  if (s=="CondSummary5bits")
    return new MonInput_CondSummary5bits;
  if (s=="L1TTriggerWord5bits")
    return new MonInput_L1TTriggerWord5bits;
  if (s=="CalXtalAdcPed")
    return new MonInput_CalXtalAdcPed;
  if (s=="CalXtalAdcRng")
    return new MonInput_CalXtalAdcRng;
  if (s=="FswFiltersLeaked")
    return new MonInput_FswFiltersLeaked;
  if (s=="FswGAMMAEnergyInLeus")
    return new MonInput_FswGAMMAEnergyInLeus;
  if (s=="CompressedEventSizeInBytes")
    return new MonInput_CompressedEventSizeInBytes;
  if (s=="CompressionLevel")
    return new MonInput_CompressionLevel;
  if (s=="FastMon_spacecraft_orbit_mode")
    return new MonInput_FastMon_spacecraft_orbit_mode;
  if (s=="FastMon_spacecraft_orbit_inSAA")
    return new MonInput_FastMon_spacecraft_orbit_inSAA;
  if (s=="FastMon_error_summary")
    return new MonInput_FastMon_error_summary;
  if (s=="TkrNumTracks")
    return new MonInput_TkrNumTracks;
  if (s=="CalMIPRatio")
    return new MonInput_CalMIPRatio;
  if (s=="TemBug")
    return new MonInput_TemBug;
  if (s=="FastMon_spacecraft_distance_to_saa")
    return new MonInput_FastMon_spacecraft_distance_to_saa;
  if (s=="GoodEvent")
    return new MonInput_GoodEvent;
  // Modification by lb starting...
  if (s=="fracSat_err_TowerPlane")
    return new MonInput_fracSat_err;
  if (s=="layerOcc_err_TowerPlane")
    return new MonInput_layerOcc_err;
  if (s=="stripOcc_err_TowerPlane")
    return new MonInput_stripOcc_err;
  // Modification by lb ended.
  if (s=="FT1Ra")
    return new MonInput_FT1Ra;
  if (s=="FT1Dec")
    return new MonInput_FT1Dec;
  if (s=="Acd2CornerDoca")
    return new MonInput_Acd2CornerDoca;
  if (s=="Acd2TileCount")
    return new MonInput_Acd2TileCount;
  if (s=="Acd2RibbonCount")
    return new MonInput_Acd2RibbonCount;
  if (s=="Acd2RibbonActDist")
    return new MonInput_Acd2RibbonActDist;
  if (s=="Acd2RibbonEnergy")
    return new MonInput_Acd2RibbonEnergy;
   if (s=="Acd2TotalTileEnergy")
    return new MonInput_Acd2TotalTileEnergy;
  if (s=="WP8BestEnergy")
    return new MonInput_WP8BestEnergy;
  if (s=="WP8CTBestEnergyProb")
    return new MonInput_WP8CTBestEnergyProb;
  if (s=="WP8CTPSFCore")
    return new MonInput_WP8CTPSFCore;
  if (s=="WP8BestZDir")
    return new MonInput_WP8BestZDir;
  if (s=="DQMEventClass")
    return new MonInput_DQMEventClass;
  if (s=="DQMEventType")
    return new MonInput_DQMEventType;
  if (s=="Acd2TileActDist3D")
    return new MonInput_Acd2TileActDist3D;
  if (s=="Acd2TileActDistEnergy")
    return new MonInput_Acd2TileActDistEnergy;
  if (s=="Acd2Tkr1TileActDistEnergy")
    return new MonInput_Acd2Tkr1TileActDistEnergy;
  if (s=="Acd2Tkr1TileActDist")
    return new MonInput_Acd2Tkr1TileActDist;
  // This line is a tag for makeNewMonObject.pl. Do not move or remove.
  else{
    std::cout<<"Object "<<s<<" does not exist"<<std::endl;
    assert(0);
  }
}

const std::map<std::string, std::map<std::string, std::string> > MonObjFactory::getDescriptions(){
  std::map<std::string, std::map<std::string, std::string> > descriptions;
  std::vector<std::string> names;
  names.push_back("nACD");
  names.push_back("timestamp");
  names.push_back("Gem_elapsed");
  names.push_back("calxtalene");
  names.push_back("condsummary");
  names.push_back("configkey1852");
  //names.push_back("onedimbool");
  //names.push_back("twodimbool");
  //names.push_back("onedimshort");
  //names.push_back("twodimshort");
  names.push_back("TkrTriggerTower");
  names.push_back("TkrHitsTowerPlane");
  names.push_back("IsTkrDigi_TowerPlane");
  names.push_back("ToT_con0_TowerPlane");
  names.push_back("ToT_con1_TowerPlane");
  names.push_back("digitimestamp");
  names.push_back("filterstatus_hi");
  names.push_back("CalLoTriggerTower");
  names.push_back("CalHiTriggerTower");
  names.push_back("calxtalmaxtower");
  names.push_back("ntkrdigis");
  names.push_back("HFC");
  names.push_back("acdpha");
  names.push_back("numvetotiles");
  names.push_back("AcdGemVeto_AcdTile");
  names.push_back("AcdGemROI_Tower");
  names.push_back("AcdGemCNO_GARC");
  names.push_back("CalXHit_TowerCalLayerCalColumn");
  names.push_back("AcdHit_AcdTile");
  names.push_back("AcdPmtA_OverThreshold_AcdTile");
  names.push_back("AcdPmtB_OverThreshold_AcdTile");
  names.push_back("AcdVetoA_AcdTile");
  names.push_back("AcdVetoB_AcdTile");
  names.push_back("AcdPha_PmtA_AcdTile");
  names.push_back("AcdPha_PmtB_AcdTile");
  names.push_back("xoverthresh");
  names.push_back("condarrcallo");
  names.push_back("condarrcalhi");
  names.push_back("CalXHit_TowerCalLayer");
  names.push_back("ReconNumTracks");
  names.push_back("ReconDirXYZ");
  names.push_back("ReconVertexPosXYZ");
  names.push_back("ReconEnergy_TowerCalLayer");
  names.push_back("condarrtkr");
  names.push_back("condarrcno");
  names.push_back("condarrroi");
  names.push_back("GemDiscardedDelta");
  names.push_back("DeadZoneDelta");
  names.push_back("timestampdouble");
  names.push_back("ReconEnergy_TowerCalLayerCalColumn");
  names.push_back("Tick20MHzDeviation");
  names.push_back("CalXAdc_TowerCalLayerCalColumnFaceRange");
  names.push_back("Range4");
  names.push_back("CalXtalFaceSignal");
  names.push_back("CalReadoutRange");
  names.push_back("OBFStatus");
  names.push_back("Acd2PhaMips_PmtA_AcdTile");
  names.push_back("Acd2PhaMips_PmtB_AcdTile");
  names.push_back("Sequence");
  names.push_back("FilterBits");
  names.push_back("PrescaledDelta");
  names.push_back("GltWord");
  names.push_back("FT1ZenithTheta");
  names.push_back("DeltaEventTime");
  names.push_back("DeltaWindowOpen");
  names.push_back("DeltaEventTimeManual");
  names.push_back("TriggerEngine");
  names.push_back("CrateNumber");
  names.push_back("AcdVetoA_OR_B_AcdTile");
  names.push_back("AcdSingleHit");
  names.push_back("AcdSingleVeto_AcdTile");
  names.push_back("DatagramInfo");
  names.push_back("DeltaEvtID");
  names.push_back("Delta_CCSDSTime_EvtTime");
  names.push_back("NewSecond");
  names.push_back("AcdSignalInfo_PMTAcdTilePha");
  names.push_back("AcdHit_PmtGarcGafe");
  names.push_back("AcdVeto_PmtGarcGafe");
  names.push_back("AcdVeto_GafeGarc");
  names.push_back("AcdHit_GafeGarc");
  names.push_back("Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile");
  names.push_back("AcdPha_PmtIdPmtRangeAcdTile");
  names.push_back("AcdGlobalPos_NotMatchedTrack_FacePosXYZ");
  names.push_back("Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ");
  names.push_back("ZeroSuppress");
  names.push_back("FastMon_TkrHits");
  names.push_back("fastmontimestampdouble");
  names.push_back("FastMon_TkrHits_TowerPlane");
  names.push_back("FastMon_condsummary");
  names.push_back("FastMon_geomagnetic_InvariantLatitude");
  names.push_back("FastMon_geomagnetic_InvariantLambda");
  names.push_back("FastMon_geomagnetic_InvariantRadius");
  names.push_back("FastMon_spacecraft_latitude");
  names.push_back("FastMon_spacecraft_longitude");
  names.push_back("FastMon_spacecraft_altitude");
  names.push_back("FastMon_geomagnetic_cutoff");
  names.push_back("FastMon_geomagnetic_bb0");
  names.push_back("FastMon_geomagnetic_McIlwainL");
  names.push_back("FastMon_Acd_Tile_Count");
  names.push_back("FastMon_Cal_Tower_Count");
  names.push_back("FastMon_TkrHits_TowerPlaneGTFE");
  names.push_back("FastMon_CalLogEndRangeHit");
  names.push_back("AcdVetoA_AcdTileDigiId");
  names.push_back("AcdVetoB_AcdTileDigiId");
  names.push_back("TkrTwrEdge");
  names.push_back("Tkr1TwrGap");
  names.push_back("Tkr1LATEdge");
  names.push_back("TkrSurplusHCInside");
  names.push_back("TkrThinHits");
  names.push_back("TkrThickHits");
  names.push_back("TkrBlankHits");
  names.push_back("TkrSurplusHitRatio");
  names.push_back("CalEnergyRaw");
  names.push_back("CalEnergyCorr");
  names.push_back("CalCsIRLn");
  names.push_back("CalTwrEdgeCntr");
  names.push_back("CalTrackAngle");
  names.push_back("CalTransRms");
  names.push_back("FT1Energy");
  names.push_back("FT1Theta");
  names.push_back("FT1Phi");
  names.push_back("GltGemSummary");
  names.push_back("FT1ZenithTheta");
  names.push_back("FT1EarthAzimuth");
  names.push_back("Tkr1KalEne");
  names.push_back("Tkr1KalThetaMS");
  names.push_back("FastMon_meta_context_open_mode");
  names.push_back("FastMon_meta_context_open_modechanges");
  names.push_back("PtMcIlwainB");
  names.push_back("PtMcIlwainL");
  names.push_back("PtLat");
  names.push_back("PtLon");
  names.push_back("PtMagLat");
  names.push_back("EvtEventId");
  names.push_back("CurrentORPreviousTimeToneMissing");
  names.push_back("FastMon_spacecraft_zra");
  names.push_back("FastMon_spacecraft_zdec");
  names.push_back("FastMon_spacecraft_pitch");
  names.push_back("FastMon_spacecraft_roll");
  names.push_back("FastMon_spacecraft_yaw");
  names.push_back("sourceGps");
  names.push_back("FastMon_new_second");
  names.push_back("FastMon_meta_context_current_source_gps");
  names.push_back("trackermontimestamp");
  names.push_back("firstRunId");
  names.push_back("lastRunId");
  names.push_back("endTime");
  names.push_back("DataTransferId");
  names.push_back("TOT_Peak_TowerPlane");
  names.push_back("TOT_LWidth");
  names.push_back("TOT_GSigma");
  names.push_back("TOT_Entries");
  names.push_back("TOT_PeakError");
  names.push_back("TOT_LWidthError");
  names.push_back("TOT_GSigmaError");
  names.push_back("TOT_FitProb");
  names.push_back("TOT_FracLowTOT");
  names.push_back("layerEff");
  names.push_back("layerEff_err");
  names.push_back("towerEff");
  names.push_back("towerEff_err");
  names.push_back("trigEff");
  names.push_back("trigEff_err");
  names.push_back("layerdXY");
  names.push_back("layerdXY_err");
  names.push_back("layerOcc");
  names.push_back("stripOcc");
  names.push_back("fracSat");
  names.push_back("FastMon_meta_LATC_master");
  names.push_back("FastMon_evt_data_transfer_id");
  names.push_back("FswFilters");
  names.push_back("GemPrescale");
  names.push_back("DGNGemPrescale");
  names.push_back("FswFilters_GammaBits");
  names.push_back("MeritObfGamStatus");
  names.push_back("CurrentTimeToneMissing");
  names.push_back("PtSCzenith");
  names.push_back("EventSizeInBytes");
  names.push_back("FastMon_spacecraft_rock");
  names.push_back("FastMon_spacecraft_xra");
  names.push_back("FastMon_spacecraft_xdec");
  names.push_back("FastMon_spacecraft_earthlimb");
  names.push_back("FastMon_spacecraft_earthlimb_fov");
  names.push_back("FastMon_spacecraft_zgalL");
  names.push_back("FastMon_spacecraft_zgalB");
  names.push_back("GrbXDir");
  names.push_back("GrbYDir");
  names.push_back("GrbZDir");
  names.push_back("FswGamState");
  names.push_back("MootKey");
  names.push_back("CondSummary5bits");
  names.push_back("L1TTriggerWord5bits");
  names.push_back("CalXtalAdcPed");
  names.push_back("CalXtalAdcRng");
  names.push_back("FswFiltersLeaked");
  names.push_back("FswGAMMAEnergyInLeus");
  names.push_back("CompressedEventSizeInBytes");
  names.push_back("CompressionLevel");
  names.push_back("FastMon_spacecraft_orbit_mode");
  names.push_back("FastMon_spacecraft_orbit_inSAA");
  names.push_back("FastMon_error_summary");
  names.push_back("TkrNumTracks");
  names.push_back("CalMIPRatio");
  names.push_back("TemBug");
  names.push_back("FastMon_spacecraft_distance_to_saa");
  names.push_back("GoodEvent");
  names.push_back("fracSat_err");
  names.push_back("layerOcc_err");
  names.push_back("stripOcc_err");
  names.push_back("FT1Ra");
  names.push_back("FT1Dec");
  names.push_back("Acd2CornerDoca");
  names.push_back("Acd2TileCount");
  names.push_back("Acd2RibbonCount");
  names.push_back("Acd2RibbonActDist");
  names.push_back("Acd2RibbonEnergy");
  names.push_back("Acd2TotalTileEnergy");
  names.push_back("WP8BestEnergy");
  names.push_back("WP8CTBestEnergyProb");
  names.push_back("WP8CTPSFCore");
  names.push_back("WP8BestZDir");
  names.push_back("DQMEventClass");
  names.push_back("DQMEventType");
  names.push_back("Acd2TileActDist3D");
  names.push_back("Acd2TileActDistEnergy");
  names.push_back("Acd2Tkr1TileActDistEnergy");
  names.push_back("Acd2Tkr1TileActDist");
   // another tag used by makeNewMonObject.pl. Do not move or remove.
  for (unsigned int i=0;i<names.size();i++){
    MonInputObject* obj=getMonInputObject(names[i]);
    descriptions[names[i]]["Description"]=obj->getDescription();
    descriptions[names[i]]["Source"]=obj->getInputSource();
    delete obj;
  }
  return descriptions;
}
