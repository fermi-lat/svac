// This class creates the objects that get the input values out of the digi/reco trees.
// Martin Kocian, SLAC, 2/1/07
// Code written for GLAST
//
// Last updated with object timestamp by user kocian on Tue Feb 27 23:48:45 2007
// Last updated with object acdLowerTileCount by user kocian on Tue Mar  6 21:10:00 2007
// Last updated with object eventid by user kocian on Tue Mar  6 22:51:00 2007
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
// Last updated with object tkrnumtracks by user kocian on Fri Apr 20 20:44:19 2007
// Last updated with object tkr1theta by user kocian on Fri Apr 20 20:46:04 2007
// Last updated with object tkr1hits by user kocian on Fri Apr 20 20:46:47 2007
// Last updated with object calxtalmaxene by user kocian on Fri Apr 20 20:47:47 2007
// Last updated with object gltgemsummary by user kocian on Fri Apr 20 22:06:31 2007
// Last updated with object glttower by user kocian on Fri Apr 20 23:26:52 2007
// Last updated with object gltnumtowers by user kocian on Fri Apr 20 23:27:36 2007
// Last updated with object evtelapsedtime by user kocian on Fri Apr 20 23:38:22 2007
// Last updated with object calxtalmaxtower by user kocian on Fri Apr 20 23:42:44 2007
// Last updated with object Mfilterstatus_hi by user kocian on Sat Apr 21 00:03:41 2007
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
// Last updated with object callayers by user kocian on Wed May 30 18:47:05 2007
// Last updated with object xoverthresh by user kocian on Thu May 31 20:39:26 2007
// Last updated with object condarrcallo by user kocian on Thu May 31 22:59:44 2007
// Last updated with object condarrcalhi by user kocian on Thu May 31 23:00:27 2007
// Last updated with object mcid by user kocian on Fri Jun  1 21:41:01 2007
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
#include "digi/MonInput_timestampdouble.h"
#include "digi/MonInput_DeadZoneDelta.h"
#include "digi/MonInput_DiscardedDelta.h"
#include "digi/MonInput_condarrroi.h"
#include "digi/MonInput_condarrcno.h"
#include "digi/MonInput_condarrtkr.h"
#include "recon/MonInput_ReconEnergy_TowerCalLayer.h"
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
#include "merit/MonInput_mcid.h"
#include "digi/MonInput_condarrcalhi.h"
#include "digi/MonInput_condarrcallo.h"
#include "recon/MonInput_xoverthresh.h"
#include "merit/MonInput_callayers.h"
#include "digi/MonInput_ElapsedLast.h"
#include "digi/MonInput_PrescaledLast.h"
#include "digi/MonInput_DiscardedLast.h"
#include "digi/MonInput_DeadZoneLast.h"
#include "digi/MonInput_LivetimeLast.h"
#include "merit/MonInput_CalEnergyRaw.h"
#include "digi/MonInput_numvetotiles.h"
#include "digi/MonInput_acdpha.h"
#include "recon/MonInput_HFC.h"
#include "digi/MonInput_ntkrdigis.h"
#include "merit/MonInput_Mfilterstatus_hi.h"
#include "recon/MonInput_calxtalmaxtower.h"
#include "merit/MonInput_evtelapsedtime.h"
#include "merit/MonInput_gltnumtowers.h"
#include "merit/MonInput_glttower.h"
#include "merit/MonInput_gltgemsummary.h"
#include "merit/MonInput_calxtalmaxene.h"
#include "merit/MonInput_tkr1hits.h"
#include "merit/MonInput_tkr1theta.h"
#include "merit/MonInput_tkrnumtracks.h"
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
#include "svac/MonInput_calxtalene.h"
#include "digi/MonInput_Gem_elapsed.h"
#include "merit/MonInput_eventid.h"
#include "merit/MonInput_acdLowerTileCount.h"
#include "digi/MonInput_timestamp.h"
#include "digi/MonInput_nAcd.h"
#include "MonObjFactory.h"
#include <iostream>



MonObjFactory::MonObjFactory(){;}
MonInputObject* MonObjFactory::getMonInputObject(string s){
  if(s=="nACD")
    return new MonInput_nAcd;
  if (s=="timestamp")
    return new MonInput_timestamp;
  if (s=="acdLowerTileCount")
    return new MonInput_acdLowerTileCount;
  if (s=="eventid")
    return new MonInput_eventid;
  if (s=="Gem_elapsed")
    return new MonInput_Gem_elapsed;
  if (s=="calxtalene")
    return new MonInput_calxtalene;
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
  if (s=="tkrnumtracks")
    return new MonInput_tkrnumtracks;
  if (s=="tkr1theta")
    return new MonInput_tkr1theta;
  if (s=="tkr1hits")
    return new MonInput_tkr1hits;
  if (s=="calxtalmaxene")
    return new MonInput_calxtalmaxene;
  if (s=="gltgemsummary")
    return new MonInput_gltgemsummary;
  if (s=="glttower")
    return new MonInput_glttower;
  if (s=="gltnumtowers")
    return new MonInput_gltnumtowers;
  if (s=="evtelapsedtime")
    return new MonInput_evtelapsedtime;
  if (s=="calxtalmaxtower")
    return new MonInput_calxtalmaxtower;
  if (s=="Mfilterstatus_hi")
    return new MonInput_Mfilterstatus_hi;
  if (s=="ntkrdigis")
    return new MonInput_ntkrdigis;
  if (s=="HFC")
    return new MonInput_HFC;
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
  if (s=="callayers")
    return new MonInput_callayers;
  if (s=="xoverthresh")
    return new MonInput_xoverthresh;
  if (s=="condarrcallo")
    return new MonInput_condarrcallo;
  if (s=="condarrcalhi")
    return new MonInput_condarrcalhi;
  if (s=="mcid")
    return new MonInput_mcid;
  if (s=="CalXHit_TowerCalLayer")
    return new MonInput_CalXHit_TowerCalLayer;
  if (s=="ReconNumTracks")
    return new MonInput_ReconNumTracks;
  if (s=="ReconDirXYZ")
    return new MonInput_ReconDirXYZ;
  if (s=="ReconVertexPosXYZ")
    return new MonInput_ReconVertexPosXYZ;
  if (s=="ReconEnergy_TowerCalLayer")
    return new MonInput_ReconEnergy_TowerCalLayer;
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
  names.push_back("acdLowerTileCount");
  names.push_back("eventid");
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
  names.push_back("tkrnumtracks");
  names.push_back("tkr1theta");
  names.push_back("tkr1hits");
  names.push_back("calxtalmaxene");
  names.push_back("gltgemsummary");
  names.push_back("glttower");
  names.push_back("gltnumtowers");
  names.push_back("evtelapsedtime");
  names.push_back("calxtalmaxtower");
  names.push_back("Mfilterstatus_hi");
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
  names.push_back("callayers");
  names.push_back("xoverthresh");
  names.push_back("condarrcallo");
  names.push_back("condarrcalhi");
  names.push_back("mcid");
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
  // another tag used by makeNewMonObject.pl. Do not move or remove.
  for (unsigned int i=0;i<names.size();i++){
    MonInputObject* obj=getMonInputObject(names[i]);
    descriptions[names[i]]["Description"]=obj->getDescription();
    descriptions[names[i]]["Source"]=obj->getInputSource();
    delete obj;
  }
  return descriptions;
}
