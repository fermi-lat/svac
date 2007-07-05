#include "AcdPedProxy.h"
#include "AcdPedParser.h"
#include "calibUtil/Metadata.h"
using calibUtil::Metadata;

AcdPeds* AcdPedProxy::m_thepeds=0;
Timestamp* AcdPedProxy::m_startvalidity=0;
Timestamp* AcdPedProxy::m_endvalidity=0;

const AcdPeds* AcdPedProxy::getAcdPeds(unsigned int timestamp){
  static const facilities::Timestamp missionStart("2001-1-1 00:00");
  static const unsigned missionSec = (unsigned) missionStart.getClibTime();
  facilities::Timestamp absTime(missionSec + timestamp,0);
  if(m_thepeds!=0 && absTime>=*m_startvalidity && absTime<=*m_endvalidity)return m_thepeds;
  if (m_thepeds==0){
    m_thepeds=new AcdPeds;
  }
  std::cout<<"Timestamp: "<<absTime.getString()<<std::endl;
  unsigned int ser;   Metadata       meta("*", "*", "calib");
  Metadata::eRet ret = meta.findBest(&ser, "ACD_Ped", absTime, Metadata::LEVELProd | Metadata::LEVELDev, "LAT","VANILLA");
  if (ret != Metadata::RETOk) {
    std::cout << "findBest failed with status" << (int) ret << std::endl;
    return 0;
  }
  else if (!ser) {
    std::cout << "Query succeeded; no rows found." << std::endl;
    return 0;
  }
  std::string  fmtVersion;
  std::string dataFmt;
  std::string dataIdent;
  ret = meta.getReadInfo(ser, dataFmt, fmtVersion, dataIdent);
  if (ret == Metadata::RETOk) { 
    unsigned int bpos=dataIdent.find("/");
    unsigned int vsp=dataIdent.find("$(");
    unsigned int vep=dataIdent.find(")");
    std::string var=dataIdent.substr(vsp+2,vep-vsp-2);
    std::string rest=dataIdent.substr(bpos+1,dataIdent.length()-bpos-1);
    std::string fname=getenv(var.c_str());
    if(fname[fname.length()-1]!='/')fname+="/";
    fname+=rest;
    std::cout<<fname<<std::endl;
    AcdPedParser par;
    par.parse(m_thepeds,fname.c_str());
    ret=meta.getInterval(ser,m_startvalidity,m_endvalidity);
    if (ret == Metadata::RETOk) { 
      std::cerr << "ACD pedstals start validity = " << m_startvalidity->getString() << std::endl;
      std::cerr << "ACD pedstals end validity = " << m_endvalidity->getString() << std::endl;
    }else{
      std::cerr<<"No good ACD pedestal interval for time "<<absTime.getString()<<std::endl;
      assert(0);
    }
  }else{
    std::cerr<<"No good ACD pedestals found."<<std::endl;
    assert(0);
  }
  return m_thepeds;
}
