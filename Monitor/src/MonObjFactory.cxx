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
  // This line is a tag for makeNewMonObject.pl. Do not move or remove.
  else{
    std::cout<<"Object "<<s<<" does not exist"<<std::endl;
    assert(0);
  }
}
