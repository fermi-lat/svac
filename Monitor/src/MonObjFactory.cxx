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
#include "digi/MonInput_twodimshort.h"
#include "digi/MonInput_onedimshort.h"
#include "digi/MonInput_twodimbool.h"
#include "digi/MonInput_onedimbool.h"
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
  if (s=="onedimbool")
    return new MonInput_onedimbool;
  if (s=="twodimbool")
    return new MonInput_twodimbool;
  if (s=="onedimshort")
    return new MonInput_onedimshort;
  if (s=="twodimshort")
    return new MonInput_twodimshort;
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
  names.push_back("onedimbool");
  names.push_back("twodimbool");
  names.push_back("onedimshort");
  names.push_back("twodimshort");
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
  // another tag used by makeNewMonObject.pl. Do not move or remove.
  for (unsigned int i=0;i<names.size();i++){
    MonInputObject* obj=getMonInputObject(names[i]);
    descriptions[names[i]]["Description"]=obj->getDescription();
    descriptions[names[i]]["Source"]=obj->getInputSource();
    delete obj;
  }
  return descriptions;
}
