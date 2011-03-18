#include "Monitor/RFun.h"
//#include "configData/db/LatcDBImplOld.h"
#include "AcdPedProxy.h"
#include "AcdPeds.h"
#include "CalPedProxy.h"
#include "CalPeds.h"
#include "commonRootData/idents/AcdId.h"
#include "digiRootData/DigiEvent.h"

#include <map>
#include <vector>
#include <list>
#include <string>


// for the tokenizer
#include "facilities/Util.h"

const float RFun::acdped(unsigned int timestamp,int garc,int gafe){
  const AcdPeds* peds=AcdPedProxy::getAcdPeds(timestamp);
  return peds->mean(garc,gafe);
}

const float RFun::acdpedGemId(unsigned int timestamp, unsigned int gemid, int pmt){
  unsigned int pmt_type(pmt);
  unsigned int garc = 10000000;
  unsigned int gafe = 10000000;

  if(gemid>103 || gemid>88 && gemid<96)
    return -1;

  // get tile id
                          
  unsigned int tileindex= AcdId::tileFromGemIndex(gemid);
  
  if(pmt_type==0){
    AcdId::convertToGarcGafe( tileindex, AcdDigi::A, garc, gafe );
  }else if(pmt_type==1){
    AcdId::convertToGarcGafe( tileindex, AcdDigi::B, garc, gafe );
  }else{
    std::cout << "Pmt type " << pmt_type  << "  is not a valid one 0,1." << std::endl
	      << "Aborting... " << std::endl;
    assert(0);
  }
   
  return acdped(timestamp, garc, gafe);
}

/*
int RFun::engine(int i,unsigned key){
  m_tcf->updateKey(key);
  return m_tcf->lut()->engineNumber(i);
}
int RFun::enginecounter(int i,unsigned key,int engine){
  m_tcf->updateKey(key);
  int eng= m_tcf->lut()->engineNumber(i);
  if (eng==engine)return 1;
  else return 0;
}
*/
int RFun::iden(int i ){
  return i;
}

#ifndef oldROOT
const float RFun::calped(unsigned int timestamp,int tower,int callayer, int calcolumn, int calend, int calrange){
  const CalPeds* peds=CalPedProxy::getCalPeds(timestamp);
  return peds->mean(tower,callayer,calcolumn,calend,calrange);
}
const float RFun::calpedwidth(unsigned int timestamp,int tower,int callayer, int calcolumn, int calend, int calrange){
  const CalPeds* peds=CalPedProxy::getCalPeds(timestamp);
  return peds->width(tower,callayer,calcolumn,calend,calrange);
}
#endif

double RFun::computemean_with_outlierscut(const ULong64_t invector[], 
					  const UInt_t vecdim,
					  const double rmstailcut)
{
  double mean(0.0),rms(0.0), cleanmean(0.0), cleanrms(0.0);
  unsigned usefulcomponents(0);

  // check for stupidity
  if(vecdim<1 || rmstailcut <=0)
    {
      std::cout 
	<< "RFun::computemean_with_outlierscut(const UShort_t invector[], " 
	<< "const UInt_t vecdim,const double rmstailcut) : ERROR" <<std::endl
	<< "vecdim or rmstailcut outside logical range: vecdim >=1; rmstailcut >0" 
	<< std::endl;
      assert(0);
    }

  // compute mean and rms
  for(UInt_t i=0;i<vecdim;i++)
    {
      mean+=invector[i];
      rms+=invector[i]*invector[i];
    }
  mean/=double(vecdim);
  rms/=double(vecdim);
  rms -= mean*mean;
  rms /= double(vecdim);
  rms = rms > 0. ? sqrt(rms) : 0.;

  // compute mean and rms without outliers

  for(UInt_t i=0;i<vecdim;i++)
    {
      if(fabs(mean-invector[i])<rmstailcut*rms){
	cleanmean+=invector[i];
	cleanrms+=invector[i]*invector[i];
	usefulcomponents++;
      }
    }
  cleanmean/=double(usefulcomponents);
  cleanrms/=double(usefulcomponents);
  cleanrms -= cleanmean*cleanmean;
  cleanrms /= double(usefulcomponents);
  cleanrms = cleanrms > 0. ? sqrt(cleanrms) : 0.;


  // tmp
  std::cout << std::endl << "Print results of RFun::computemean_with_outlierscut" << std::endl
	    << "Original mean,rms: " << mean << ", " << rms << std::endl
	    << "Corrected mean,rms: " << cleanmean << ", " << cleanrms << std::endl << std::endl;

  // endtmp

  return cleanmean;
}


double RFun::computeratio(Short_t signal1, float ped1, 
			  Short_t signal2, float ped2,
			  Short_t MinSignal)
{
  double sig1 = double(signal1)-double(ped1);
  double sig2 = double(signal2)-double(ped2);
  
  double ratio = -1; // silly value returned in case signals are not large enough to 
  // compute a sensible ratio. 

  // Check minimum signla required
  if(sig1 < MinSignal || sig2 < MinSignal || signal1 >= 4095 || signal2 >= 4095)
    return ratio;
  else
    ratio = sig1/sig2;

 

  return ratio;
}

double RFun::computeratio_v2(Short_t signal1, float ped1, float MinSignal1,
			     Short_t signal2, float ped2,
			     Short_t MinSignal2)
{
  double sig1 = double(signal1)-double(ped1);
  double sig2 = double(signal2)-double(ped2);
  
  double ratio = -1; // silly value returned in case signals are not large enough to 
  // compute a sensible ratio. 

  // Check minimum signla required
  if(sig1 < MinSignal1 || sig2 < MinSignal2 || signal1 >= 4095 || signal2 >= 4095)
    return ratio;
  else
    ratio = sig1/sig2;

 

  return ratio;
}



double RFun::getChannelEnergyHighest(ROOT::TArrayProxy<ROOT::TMultiArrayType<ROOT::TMultiArrayType<ROOT::TArrayType<Float_t,2>, 12>, 8> >& invector, int Level, int Energy)
{

  if(Level <0 || Level > 16*8*12*2)
    {
      std::cout << " RFun::getChannelEnergyHighest" << std::endl
		<< " LEvel is larger than 3072 or negative" << std::endl
		<< "Aborting" << std::endl;
      assert(0);
    }


  // tmp
  /*
  std::cout << " RFun::getChannelEnergyHighest: call with arguments: " << std::endl
	    << "Level, Energy" << Level << "\t" << Energy << std::endl;
  */
  // endtmp


  typedef std::map<int,float> MapEnergyChannel;
  MapEnergyChannel data;  
  std::list<float> EnergyList;
  std::vector<float> EnergySorted;

  int listpos(0);
  for (UShort_t itower = 0; itower <16; itower++){
    for (UShort_t ilayer = 0; ilayer < 8; ilayer++){
      for (UShort_t icolumn = 0; icolumn < 12; icolumn++){
	for (UShort_t iface = 0; iface < 2; iface++){
	  EnergyList.push_back(invector[itower][ilayer][icolumn][iface]);
	  listpos = itower*8*12*2 + ilayer*12*2 + icolumn*2 + iface;
	  data[listpos] = invector[itower][ilayer][icolumn][iface];
	}
      }
    }
  }

  EnergyList.sort();
  EnergyList.reverse();
  for (std::list<float>::iterator it=EnergyList.begin();it!=EnergyList.end();it++)
    EnergySorted.push_back(*it);

  // print info
  /*
  if(!Level){
    std::cout << "RFun::getChannelEnergyHighest: First = " <<  EnergySorted[0] << std::endl;
    std::cout << "RFun::getChannelEnergyHighest : second = " <<  EnergySorted[1] << std::endl;
    std::cout << "RFun::getChannelEnergyHighest : third = " <<  EnergySorted[2] << std::endl;
  }
  */

  if(Energy)
    return EnergySorted[Level];
  else{
    // search for the channel with the Energy in LEvel position

    // tmp
    // Print the entire energy map 
    /*
    if(!Level){
      std::cout << " RFun::getChannelEnergyHighest: Energy Map: " << std::endl
		<< "Channel number          Energy" << std::endl;
      for(MapEnergyChannel::const_iterator it=data.begin();it!=data.end();it++)
	{
	  if(it->second > 0.01)
	    std::cout << it->first << "\t" << it->second << std::endl;
	}
    }
    */
    // end tmp


    for(MapEnergyChannel::const_iterator it=data.begin();it!=data.end();it++)
      {
	if(it->second == EnergySorted[Level]){
	  /*
	  if(1){
	    std::cout << "PosHighest == " << it->first 
		      << "  Energy Highest = " << it->second << std::endl;
	  }
	  */
	  return it->first;
	}
      }
  }
  return -1;
}


unsigned RFun::getplaneshit(const UShort_t invector[36])
{
 unsigned n_planeshit(0);
 for (unsigned iplane = 0; iplane < 36; iplane++)
   {
     if(invector[iplane]>0)
	n_planeshit++;
   }
 return n_planeshit;
}


unsigned RFun::getconsecutiveplaneshit(const UShort_t invector[36])
{
  unsigned n_consecutiveplaneshit(0),maxhits(0);
  for (unsigned iplane = 0; iplane < 36; iplane++)
    {
      if(invector[iplane]>0)
	n_consecutiveplaneshit++;
      else
	{
	  if(maxhits<n_consecutiveplaneshit)
	    maxhits=n_consecutiveplaneshit;
	  n_consecutiveplaneshit=0;
	}
    }
  
  if(maxhits<n_consecutiveplaneshit)
    maxhits=n_consecutiveplaneshit;

  return  maxhits;
}

Double_t RFun::oneTriggerTower(ROOT::TArrayBoolProxy& invector){
  Double_t retval=-1;
  for (int i=0;i<16;i++){
    if (invector[i]){
      if (retval>-1){
	retval=0;
	break;
      }else{
	retval=i;
      }
    }
  }
  return retval;
} 
    



unsigned RFun::gethitsinemptytower(double isemptytower,
				   const UShort_t TkrHitsTowerPlane[36])
{

  if(!isemptytower)
    return 0;
 
  // compute total number of hits in tower using 
  // vector TkrHitsTowerPlane for this tower
  
  unsigned hitscounter(0);
  for(unsigned iplane =0;iplane<36;iplane++)
      hitscounter += TkrHitsTowerPlane[iplane];
  
  return hitscounter;
  
}




//unsigned RFun::loopovertowerANDtkrplanes(const UShort_t invector[16][36])
#ifdef oldROOT
unsigned RFun::loopovertowerANDtkrplanes(ROOT::TArray2Proxy<UShort_t, 36>& invector)
#else
unsigned RFun::loopovertowerANDtkrplanes(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 36> >& invector)
#endif

{
  unsigned n_counter(0);
  for (UShort_t itower = 0; itower < 16; itower++){
    for (UShort_t iplane = 0; iplane < 36; iplane++)
      n_counter += invector[itower][iplane];
  }
  return n_counter;

}






//unsigned RFun::loopovertowerANDtkrplanes(const UShort_t invector[16][36])
#ifdef oldROOT
unsigned RFun::loopovertowerANDcallayers(ROOT::TArray2Proxy<UShort_t, 8>& invector)
#else
unsigned RFun::loopovertowerANDcallayers(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 8> >& invector)
#endif

{
  unsigned n_counter(0);
  for (UShort_t itower = 0; itower < 16; itower++){
    for (UShort_t icallayer = 0; icallayer < 8; icallayer++)
      n_counter += invector[itower][icallayer];
  }
  return n_counter;

}



//unsigned RFun::loopovertowerANDtkrplanes(const UShort_t invector[16][36])
#ifdef oldROOT
Double_t RFun::loopovertowerANDcallayers_float(ROOT::TArray2Proxy<Float_t, 8>& invector)
#else
Double_t RFun::loopovertowerANDcallayers_float(ROOT::TArrayProxy<ROOT::TArrayType<Float_t, 8> >& invector)
#endif

{
  Double_t val(-1.0);
  for (UShort_t itower = 0; itower < 16; itower++){
    for (UShort_t icallayer = 0; icallayer < 8; icallayer++){
      if(invector[itower][icallayer] >= 0){
	if(val<0)
	  val = invector[itower][icallayer];
	else
	  val += invector[itower][icallayer];
      }
    }
  }
  return val;
}

#ifdef oldROOT
Double_t  RFun::loopovercallayersANDcalcolumns_float(ROOT::TArray2Proxy<Float_t, 12>& invector)
#else
  //Double_t  RFun::loopovercallayersANDcalcolumns_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 12> >& invector)
Double_t RFun::loopovercallayersANDcalcolumns_float(const Float_t invector[8][12] )
#endif
{

 Double_t val(-1.0);
  for (UShort_t icallayer = 0; icallayer < 8; icallayer++){
    for (UShort_t icalcolumn = 0; icalcolumn < 12; icalcolumn++){
      if(invector[icallayer][icalcolumn] >= 0){
	if(val<0)
	  val = invector[icallayer][icalcolumn];
	else
	  val += invector[icallayer][icalcolumn];
      }
    }
  }
  return val;
}


Double_t RFun::loopovertowerANDcallayersANDcalcolumns_float(ROOT::TArrayProxy<ROOT::TMultiArrayType<ROOT::TArrayType<Float_t, 12>, 8> >& invector)
{
  Double_t val(-1.0);
  for (UShort_t itower = 0; itower < 8; itower++){
    for (UShort_t icallayer = 0; icallayer < 8; icallayer++){
      for (UShort_t icalcolumn = 0; icalcolumn < 12; icalcolumn++){
	if(invector[itower][icallayer][icalcolumn] >= 0){
	  if(val<0)
	    val = invector[itower][icallayer][icalcolumn];
	  else
	    val += invector[itower][icallayer][icalcolumn];
	}
      }
    }
  }
  return val;
}


Double_t RFun::loopovercalcolumns_float(const Float_t invector[12])
{
  Double_t val(-1.0);
  for (UShort_t icalcolumn = 0; icalcolumn < 12; icalcolumn++){
    if(invector[icalcolumn] >= 0){
      if(val<0)
	val = invector[icalcolumn];
      else
	val += invector[icalcolumn];
    }
  }
  
  return val;
}


unsigned RFun::loopovertkrplanes(const UShort_t invector[])
{
  return loopoveronedimvect(invector,36);
}



unsigned RFun::loopovercallayers(const UShort_t invector[])
{
  return loopoveronedimvect(invector,8);
}

unsigned RFun::loopovercallayersANDcalcolumns(const UShort_t invector[8][12])
//unsigned RFun::loopovercallayersANDcalcolumns(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 12> >& invector)
{
  unsigned n_counter(0);
  for (UShort_t ilayer = 0; ilayer < 8; ilayer++){
    for (UShort_t icolumn = 0; icolumn < 12; icolumn++)
      n_counter += invector[ilayer][icolumn];
  }
  return n_counter;
}


//unsigned RFun::loopovertowersANDcallayersANDcalcolumns(const UShort_t invector[16][8][12])
#ifndef oldROOT
unsigned RFun::loopovertowersANDcallayersANDcalcolumns(ROOT::TArrayProxy<ROOT::TMultiArrayType<ROOT::TArrayType<UShort_t, 12>, 8> >& invector)
{
  unsigned n_counter(0);
  for (UShort_t itower = 0; itower <16; itower++){
    for (UShort_t ilayer = 0; ilayer < 8; ilayer++){
      for (UShort_t icolumn = 0; icolumn < 12; icolumn++)
	n_counter += invector[itower][ilayer][icolumn];
    }
  }
  return n_counter;

}
#endif

unsigned RFun::loopovercalcolumns(const UShort_t invector[])
{
  return loopoveronedimvect(invector,12);
}

unsigned RFun::loopovergarc(const UShort_t invector[])
{
  return loopoveronedimvect(invector,12);
}

unsigned RFun::loopoveracdtiles(const UShort_t invector[])
{
  return loopoveronedimvect(invector,128);
}


unsigned RFun::loopoverengine(const UShort_t invector[])
{
  return loopoveronedimvect(invector,16);
}

unsigned RFun::loopoveracdface(const UShort_t invector[])
{
  return loopoveronedimvect(invector,5);
}

unsigned RFun::loopoveracdrow(const UShort_t invector[])
{
  return loopoveronedimvect(invector,5);
}

unsigned RFun::loopoveracdcolumn(const UShort_t invector[])
{
  return loopoveronedimvect(invector,5);
}

unsigned RFun::loopoveracdpmt(const UShort_t invector[])
{
  return loopoveronedimvect(invector,2);
}

unsigned RFun::loopovergafe(const UShort_t invector[])
{
  return loopoveronedimvect(invector,18);
}

 



unsigned RFun::loopoveronedimvect(const UShort_t invector[], UInt_t vectdim)
{
  unsigned n_counter(0);
  for (UInt_t i = 0; i < vectdim; i++)
    n_counter += invector[i];
  return n_counter;
}


unsigned RFun::loopoveracdtilesbool(ROOT::TArrayBoolProxy& invector)
{
  return loopoveronedimvectbool(invector,128);
}



unsigned RFun::loopoveronedimvectbool(ROOT::TArrayBoolProxy& invector, UInt_t vectdim)
{
  unsigned n_counter(0);
  for (UInt_t i = 0; i < vectdim; i++)
    n_counter += invector[i];
  return n_counter;
}



std::vector<double> RFun::getemptytowers(ROOT::TArrayBoolProxy& invector)
//std::vector<double> RFun::getemptytowers(const UShort_t invector[16])
{

  std::vector<double> emptytowers;

  // initialization of boundary towers
  if(!m_boundarytwrdefined)
    RFun::initboundarytowers();


  // tmp printing
  /*
  std::cout << std::endl << "Evt number " << m_evtcounter << std::endl;
  if(m_evtcounter<m_doprintUpToN)
    {
     
      std::cout << std::endl << "Printing towers which trigger" << std::endl;
      for(unsigned itwr = 0;itwr<16;itwr++)
	{
	  std::cout << "Tower id = " << itwr << "; " 
		    << invector[itwr] << std::endl;
	}
      m_evtcounter++;

    }
  */
  // endtmp printing


  // initialize empty tower vector to 1 (all are empty towers)
  for(unsigned itwr = 0;itwr<16;itwr++)
    emptytowers.push_back(1);
    
  // scan over all towers, setting the "empty tower condition" whenver 
  // the tower has a trigger and/or is boundary tower to a tower which had a trigger
  
  for(unsigned itwr = 0;itwr<16;itwr++)
    {
      if(invector[itwr])
	{ // this tower had a trigger
	  emptytowers[itwr] = 0;  
	  for(unsigned j = 0; j<8;j++)
	    {
	      if(m_boundarytwr[itwr][j]>=0)
		emptytowers[m_boundarytwr[itwr][j]] = 0;
	    }
	}
    }

  return emptytowers;
}


unsigned RFun::istherenonzerocomponent(const UShort_t invector[], const Int_t vectordim)
{
  for(UShort_t i=0; i<vectordim;i++){
    if(invector[i]>0.0)
      return 1;
  }
  return 0;
}

// Returns the non zero coponent of a vector (e.g. ReconNumTracks[11], 
// the non-zero component is the number of tracks). 

// IF all components are zero, then it returns -1 

int RFun::returnnonzerocomponent(ROOT::TArrayUShortProxy& invector, int vectordim)
{
  for(int i=0; i<vectordim;i++){
    if(invector[i]>0.0)
      return i;
  }
  return -1;
}


std::vector<double> RFun::testfun(){
  std::vector<double> retvec;
  for (int i=0;i<16;i++)retvec.push_back((double)i);
  return retvec;
}

std::vector<double> RFun::vecfun(ROOT::TArrayUShortProxy vec){
  std::vector<double> retvec;
  for (int i=0;i<3;i++)retvec.push_back(vec[i]);
  return retvec;
}

int RFun::testrunonceformulaoutput(std::vector<double> formulavector)
{
  std::cout << std::endl << "Print output of runonceformula:" << std::endl;
 UShort_t counter = 0;
 for(std::vector<double>::const_iterator itr=formulavector.begin();
     itr != formulavector.end(); itr++)
   {
     std::cout << "Index " << counter << "; " << *itr << std::endl;
     counter++;
   }
 return 1;
}

int RFun::UpdateDatagramEvtCounter(Int_t datagraminfo[2], int cpuNumber)
{

  int numevts = -1;
  // check that cpuNumber given makes sense
  if(cpuNumber < 0 || cpuNumber >4)
    {
      std::cerr<< "RFun::UpdateDatagramEvtCounter: ERROR" << std::endl
	       << "cpuNumber given (=" << cpuNumber <<") is out of bounds [0,4]" << std::endl;
      assert(0);
    }

  // initialize counters if needed
  if(makeinitdatagraminfo)
    RFun::initdatagramevtcounter();

  if(datagraminfo[0] == cpuNumber)
    {// This event belongs to the cpuNumber we are interested in
      // check if evt belongs to the previous datagram number for this cpuNumber.
      // If true, keep adding events
      // If false, update numbers for this event and return the number of events in the previous datagram, 
      // in case this number is different from 0
                            
      if(datagraminfo[1] == m_previousdatagramnumber[cpuNumber])
	m_datagramevtcounter[cpuNumber]++;
      else
	{
	  numevts = int(m_datagramevtcounter[cpuNumber]);
	  m_datagramevtcounter[cpuNumber] = 1; // this event !!
	  m_previousdatagramnumber[cpuNumber] = datagraminfo[1];
	}
    }
  
  return numevts;
}



// Initialization of static data member

//TrgConfigDB* RFun::m_tcf=new TrgConfigDB(new LatcDBImplOld);

int RFun::m_boundarytwr[16][8];
bool RFun::m_boundarytwrdefined = false;
UInt_t RFun::m_doprintUpToN = 5;
UInt_t RFun::m_evtcounter = 0;
int RFun::m_datagramevtcounter[5];
int RFun::m_previousdatagramnumber[5];
bool  RFun::makeinitdatagraminfo = true;

std::map<std::string,std::list<std::vector<float> > > RFun::m_NormFactors;
std::map<std::string, std::vector<float> > RFun::m_EarthLimbCorrFactors;
std::map<std::string, std::vector<float> > RFun::m_LongitudeCorr;
std::string RFun::m_normfactascii;


void RFun::initdatagramevtcounter()
{
  for(UInt_t i=0;i<5;i++){
     m_datagramevtcounter[i] = 0;
     m_previousdatagramnumber[i] = -1;
  }
    makeinitdatagraminfo = false;
}

void RFun::initboundarytowers()
{
  // tmp printing
  /*
  std::cout << std::endl 
	    << "Boundary Towers are defined for all towers" << std::endl;
  */
  // end tmp


  // initialize m_boundarytwr vector to -1 (non-existent tower)
  for(unsigned itwr = 0;itwr<16;itwr++)
    {
      for(unsigned j = 0;j<8;j++)
	m_boundarytwr[itwr][j] = -1;
    }

// Definition of the boundary towers

 // define boundary towers for each tower

  // twr0
  m_boundarytwr[0][0] = 1;
  m_boundarytwr[0][1] = 4;
  m_boundarytwr[0][2] = 5;
   // twr1
  m_boundarytwr[1][0] = 0;
  m_boundarytwr[1][1] = 4;
  m_boundarytwr[1][2] = 5;
  m_boundarytwr[1][3] = 6;
  m_boundarytwr[1][4] = 2;
   // twr2
  m_boundarytwr[2][0] = 1;
  m_boundarytwr[2][1] = 5;
  m_boundarytwr[2][2] = 6;
  m_boundarytwr[2][3] = 7;
  m_boundarytwr[2][4] = 3;
  // twr3
  m_boundarytwr[3][0] = 2;
  m_boundarytwr[3][1] = 6;
  m_boundarytwr[3][2] = 7;

  // twr4
  m_boundarytwr[4][0] = 8;
  m_boundarytwr[4][1] = 9;
  m_boundarytwr[4][2] = 5;
  m_boundarytwr[4][3] = 1;
  m_boundarytwr[4][4] = 0;
  // twr5
  m_boundarytwr[5][0] = 8;
  m_boundarytwr[5][1] = 9;
  m_boundarytwr[5][2] = 10;
  m_boundarytwr[5][3] = 6;
  m_boundarytwr[5][4] = 2;
  m_boundarytwr[5][5] = 1;
  m_boundarytwr[5][6] = 0;
  m_boundarytwr[5][7] = 4;

  // twr6
   m_boundarytwr[6][0] = 5;
  m_boundarytwr[6][1] = 9;
  m_boundarytwr[6][2] = 10;
  m_boundarytwr[6][3] = 11;
  m_boundarytwr[6][4] = 7;
  m_boundarytwr[6][5] = 3;
  m_boundarytwr[6][6] = 2;
  m_boundarytwr[6][7] = 1;

  // twr7
  m_boundarytwr[7][0] = 6;
  m_boundarytwr[7][1] = 10;
  m_boundarytwr[7][2] = 11;
  m_boundarytwr[7][3] = 3;
  m_boundarytwr[7][4] = 2;
  // twr8
  m_boundarytwr[8][0] = 12;
  m_boundarytwr[8][1] = 13;
  m_boundarytwr[8][2] = 9;
  m_boundarytwr[8][3] = 5;
  m_boundarytwr[8][4] = 4;
  // twr9
  m_boundarytwr[9][0] = 8;
  m_boundarytwr[9][1] = 12;
  m_boundarytwr[9][2] = 13;
  m_boundarytwr[9][3] = 14;
  m_boundarytwr[9][4] = 10;
  m_boundarytwr[9][5] = 6;
  m_boundarytwr[9][6] = 5;
  m_boundarytwr[9][7] = 4;
  // twr10
  m_boundarytwr[10][0] = 9;
  m_boundarytwr[10][1] = 13;
  m_boundarytwr[10][2] = 14;
  m_boundarytwr[10][3] = 15;
  m_boundarytwr[10][4] = 11;
  m_boundarytwr[10][5] = 7;
  m_boundarytwr[10][6] = 6;
  m_boundarytwr[10][7] = 5;
  // twr11
  m_boundarytwr[11][0] = 10;
  m_boundarytwr[11][1] = 14;
  m_boundarytwr[11][2] = 15;
  m_boundarytwr[11][3] = 7;
  m_boundarytwr[11][4] = 6;
  // twr12
  m_boundarytwr[12][0] = 13;
  m_boundarytwr[12][1] = 9;
  m_boundarytwr[12][2] = 8;
  // twr13
  m_boundarytwr[13][0] = 12;
  m_boundarytwr[13][1] = 14;
  m_boundarytwr[13][2] = 10;
  m_boundarytwr[13][3] = 9;
  m_boundarytwr[13][4] = 8;
  // twr14
  m_boundarytwr[14][0] = 13;
  m_boundarytwr[14][1] = 15;
  m_boundarytwr[14][2] = 11;
  m_boundarytwr[14][3] = 10;
  m_boundarytwr[14][4] = 9;
  // twr15
  m_boundarytwr[15][0] = 14;
  m_boundarytwr[15][1] = 11;
  m_boundarytwr[15][2] = 10;

  m_boundarytwrdefined = true;

}


unsigned RFun::GetOveralIndex_TowerCalLayerCalColumnCalFace(int tower, int layer, int column, int face)
{
  // check that indeces make sense
  if(tower<0 || tower>15){
    std::cout << "RFun::GetOveralIndex_TowerCalLayerCalColumnCalFace: ERROR" << std::endl
	      << "Tower= " << tower << " is out of bounds [0-15] " << std::endl
	      << "Aborting... " << std::endl;
    assert(0);
  }

   if(layer<0 || layer>15){
    std::cout << "RFun::GetOveralIndex_TowerCalLayerCalColumnCalFace: ERROR" << std::endl
	      << "Layer= " << layer << " is out of bounds [0-7] " << std::endl
	      << "Aborting... " << std::endl;
    assert(0);
   }
   
   if(column<0 || column>12){
     std::cout << "RFun::GetOveralIndex_TowerCalLayerCalColumnCalFace: ERROR" << std::endl
	       << "Column= " << column << " is out of bounds [0-11] " << std::endl
	       << "Aborting... " << std::endl;
     assert(0);
   }
    if(face<0 || face>1){
    std::cout << "RFun::GetOveralIndex_TowerCalLayerCalColumnCalFace: ERROR" << std::endl
	      << "Face= " << face << " is out of bounds [0-1] " << std::endl
	      << "Aborting... " << std::endl;
    assert(0);
  }

    unsigned index = tower*8*12*2 + layer*12*2 + column*2 + face;

    return index;
}



// FAST Mon functions



unsigned RFun::loopovertowerANDtkrplanes_int(ROOT::TArrayProxy<ROOT::TArrayType<Int_t, 36> >& invector)
{
  unsigned n_counter(0);
  for (UShort_t itower = 0; itower < 16; itower++){
    for (UShort_t iplane = 0; iplane < 36; iplane++)
      n_counter += invector[itower][iplane];
  }
  return n_counter;
}


unsigned RFun::loopovertkrplanes_int(const Int_t invector[])
{
  unsigned n_counter(0);
  for (UShort_t iplane = 0; iplane < 36; iplane++)
      n_counter += invector[iplane];
  
  return n_counter;
}


Double_t RFun::loopovertkrplanes_double(const Double_t invector[])
{
  Double_t n_counter(0);
  for (UShort_t iplane = 0; iplane < 36; iplane++)
      n_counter += invector[iplane];
  
  return n_counter;

}

Double_t RFun::loopovertowerANDtkrplanes_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 36> >& invector)
{
  Double_t n_counter(0.0);
  for (UShort_t itower = 0; itower < 16; itower++){
    for (UShort_t iplane = 0; iplane < 36; iplane++)
      n_counter += invector[itower][iplane];
  }
  return n_counter;
}

Double_t RFun::loopovertowerANDtkrplanes_square_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 36> >& invector)
{
  Double_t n_counter(0.0);
  for (UShort_t itower = 0; itower < 16; itower++){
    for (UShort_t iplane = 0; iplane < 36; iplane++)
      n_counter += invector[itower][iplane]*invector[itower][iplane];
  }
  return sqrt(n_counter);
}


 // function that reads the norm factors from ascii file and fills the map RFun::NormFactors
int RFun::LoadNormFactors()
{
   // open file

  if(m_normfactascii.size()<2)
    {
      std::cerr << "RFun::LoadNormFactors:ERROR" << std::endl
		<< "m_normfactascii.size()<2 " << std::endl
		<< "Exiting function returning 1" << std::endl;
      return 1;
    }

  // std::cout << "Opening Norm file " << m_normfactascii.c_str() << std::endl;
  
  std::ifstream inputFile(m_normfactascii.c_str());
  if ( ! inputFile.good() ) {
    std::cerr << "RFun::LoadNormFactors:ERROR" << std::endl 
	      << "Problems opening file " <<  m_normfactascii.c_str() << std::endl
	      << "Exiting function returning 2" << std::endl;
    return 2;
  }

  // ok, we can start filling object static std::map<std::string,std::vector> m_NormFactors;
  
  std::string ratename;
  float refrate[2]; //value and error (will be put as last components of vector ratelineinfo)
  std::vector<float> ratelineinfo;
  std::list<std::vector<float> > listofnormfactors;
  int newrate = 0; //1 for yes
  int ingestdata = 0; //1 for yes
  float tmpval = 0.0;


  // initialize
  refrate[0] = -2;
  refrate[1] = -2;
   
  // grab one line
  const int bufSize(1000); char buffer[bufSize];
  inputFile.getline(buffer,bufSize);
  while ( ! inputFile.eof() ) {
    // ignore comment lines (start with '#')
    if ( buffer[0] == '#' ) {
      inputFile.getline(buffer,bufSize);
      continue;
    }

     // tokenize the line, make sure that there are 5 tokens
    std::string inputLine(buffer);

    std::vector <std::string> tokens;
    facilities::Util::stringTokenize(inputLine, "\t :", tokens);

    // ignore blank lines
    if ( tokens.size() == 0 ) {
      inputFile.getline(buffer,bufSize);
      continue;
    }
    
    // get rate name
    if(tokens[0] == "RateName"){
      newrate = 1;
      ratename =tokens[1];
      inputFile.getline(buffer,bufSize);
      continue;
    }


    // get rate overall ref value (last components of vector ratelineinfo)
    if(newrate && tokens[0] == "RefRateVal"){
      // get ref value and error (separated by +/-)
      std::string val;
      std::string val_err;
      std::string::size_type pos = tokens[1].find("+/-");
      float fval;
      float fval_err;
      if(pos < tokens[1].size()){ // There is value  related error
	val = tokens[1].substr(0,pos);
	val_err = tokens[1].substr(pos+3,tokens[1].size());
	fval = atof(val.c_str());
	fval_err = atof(val_err.c_str());
	refrate[0] = fval;
	refrate[1] = fval_err;
	inputFile.getline(buffer,bufSize);
	continue;
      }
      else
	{
	  std::cerr << "RFun::LoadNormFactors:ERROR" << std::endl 
		    << "The sign +/- was not found in " << tokens[3].c_str() << std::endl
		    << "Ref value and error for rate could not be properly retrieved" << std::endl
		    << "Exiting function returning 3" << std::endl;
	  return 3;
	}
    }

    // get tag name
    if(tokens[0] == "EarthLimbCorr"){
      unsigned int nparams=atoi(tokens[1].c_str());
      // read first line with formula
      inputFile.getline(buffer,bufSize);
      // start reading parameters
      for(int unsigned it = 1; it<nparams;it++){
	    // read line and tokenize it
        inputFile.getline(buffer,bufSize);
        std::string inputLine(buffer);
        std::vector <std::string> tokens;
	    facilities::Util::stringTokenize(inputLine, "\t :", tokens);
	    std::string val;
	    std::string val_err;
	    std::string::size_type pos = tokens[1].find("+/-");
	    float fval=0.;
	    float fval_err=0.;
	    if(pos < tokens[1].size()){ // There is value  related error
	  	  val = tokens[1].substr(0,pos);
		  val_err = tokens[1].substr(pos+3,tokens[1].size());
		  fval = atof(val.c_str());
		  fval_err = atof(val_err.c_str());
		  m_EarthLimbCorrFactors[ratename].push_back(fval);
		  }
	    }
      	
      inputFile.getline(buffer,bufSize);
      continue;
    }

    // get tag name
    if(tokens[0] == "LongitudeCorr"){
      unsigned int nparams=atoi(tokens[1].c_str());
      // read first line with formula -- not used
      inputFile.getline(buffer,bufSize);
      // start reading parameters
      for(int unsigned it = 1; it<nparams;it++){
	  // read line and tokenize it
          inputFile.getline(buffer,bufSize);
          std::string inputLine(buffer);
          std::vector <std::string> tokens;
	  facilities::Util::stringTokenize(inputLine, "\t :", tokens);
	  std::string val;
	  std::string val_err;
	  std::string::size_type pos = tokens[1].find("+/-");
	  float fval=0.;
	  float fval_err=0.;
	  if(pos < tokens[1].size()){ // There is value  related error
		val = tokens[1].substr(0,pos);
		val_err = tokens[1].substr(pos+3,tokens[1].size());
		fval = atof(val.c_str());
		fval_err = atof(val_err.c_str());
		m_LongitudeCorr[ratename].push_back(fval);
		}
	  }
      	
      inputFile.getline(buffer,bufSize);
      continue;
    }

    // New rate
    if(ingestdata == 0 && newrate && refrate[0] > -2 && tokens[0] == "Start"){
      ingestdata = 1;
      listofnormfactors.clear(); // prepare for new data ingestion
      inputFile.getline(buffer,bufSize);
      continue;
    }

    if(ingestdata && tokens[0] == "End"){
      // End of info for this rate. 
      
      // Fill map 
      m_NormFactors[ratename] = listofnormfactors;
      
      // initialize stuff for the next event
      newrate = 0;
      ingestdata = 0;
      listofnormfactors.clear();
      ratename = "";
      refrate[0] = -2;
      refrate[1] = -2;
      inputFile.getline(buffer,bufSize);
      continue;
    }


    if(ingestdata)
      {
	if(tokens.size() != 4){
	  std::cerr << "RFun::LoadNormFactors:ERROR" << std::endl 
		    << "tokens.size() != 4 when ingesting data " << std::endl
		    << "Normfactor map could not be filled" << std::endl;

	  std::cout << "Line with poblems is the following one: " << std::endl;
	  for(int unsigned it = 0; it<tokens.size();it++){
	    std::cout << tokens[it].c_str() << "\t";
	  }
	  std::cout  << std::endl;
	  std::cout << "Exiting function returning 4" << std::endl;
	  return 4;	  
	}
	
	for(int unsigned it = 0; it<4;it++){
	  tmpval = atof(tokens[it].c_str());
	  ratelineinfo.push_back(tmpval);
	}
	// last components are teh ref rate and error
	ratelineinfo.push_back(refrate[0]);
	ratelineinfo.push_back(refrate[1]);
	
	// fill one event in the list of norm factors
	listofnormfactors.push_back(ratelineinfo);
	
	// clean vector for next event
	ratelineinfo.clear();
      }



    // ok, on to the next line
    inputFile.getline(buffer,bufSize);
  }

  return 0;
}

void RFun::PrintNormFactorsMap()
{
  if(m_NormFactors.size()<1)
    return;
  
  std::cout << std::endl << "RFun::PrintNormFactorsMap" << std::endl;
  std::cout << "Size of map is " << m_NormFactors.size() << std::endl;

  for(std::map<std::string,std::list<std::vector<float> > >::const_iterator itr=m_NormFactors.begin();
      itr != m_NormFactors.end();itr++){
    
    std::cout << "RateName: " << itr->first.c_str() <<std::endl;
    for(std::list<std::vector<float> > ::const_iterator itr2=itr->second.begin();
      itr2 != itr->second.end();itr2++){
      for(unsigned int icomp = 0; icomp < (*itr2).size();icomp++)
	{
	  std::cout << (*itr2)[icomp] << "\t\t";
	}
      std::cout << std::endl;
    }
    // Done with this rate
    std::cout << std::endl << std::endl;
  }
}
 

  
  // function that returns the Normalized the rates or error in the normalized rate 
// for the rate_type and magnetic info
  // It uses info from RFun::NormFactors. If this object is empty, it will fill it from ascii file


Float_t RFun::NormalizeRate(char* RateType, Float_t MagneticInfo, 
			    Float_t Rate,  Float_t RateErr, char* RetType)
{


  std::string returntype = RetType;
  
  if(m_NormFactors.size() <1) // Norm factors have not been loaded yet 
    {
      // tmp
      std::cout << "Loading Norm factors from file " << std::endl
		<< m_normfactascii << std::endl;  
      int b = LoadNormFactors();
      if(b)
	{
	  std::cerr << "RFun::NormalizeRate:ERROR" << std::endl 
		    << "Norm factors could not be loaded " << std::endl
		    << "Therefore, Rates cannot be normalized. ABORTING..." << std::endl;
	  assert(0);
	}
    }

  // Check that rate is in map
  //std::cout << "Checking rate name " << std::endl;  
  std::map<std::string,std::list<std::vector<float> > >::const_iterator itr=m_NormFactors.find(RateType);
  if(itr==m_NormFactors.end())
    {
      std::cerr << "RFun::NormalizeRate:ERROR" << std::endl 
		<< "Normalization factors for rate type " << RateType 
		<< " do not exist in file " << m_normfactascii << std::endl
		<< "Therefore, Rates cannot be normalized for this type. " << std::endl
		<< "Aborting..." << std::endl;

      //PrintNormFactorsMap();
      //return -1;
      assert(0);
    }

  // check that the magnetic quantity has a reasonable value (0.5-3 for McIlwainL or 0.5-30 for RigCutoff
  
  if(MagneticInfo<0.5 || MagneticInfo >30)
    {
      std::cout << "RFun::NormalizeRate:WARNING" << std::endl 
		<< "MagneticInfo="<<MagneticInfo << " is out of allowed bounds [0.5-30]"
		<< std::endl 
		<< "Returning -1 (or 0 if return type returntype==NormRateErr" << std::endl;
      if(returntype=="NormRateErr")
	return 0;
      return -1;
    }

  // check that MagInfoVal (RigCutoff or McIlwainL param) is in map
  std::list<std::vector<float> > ::const_iterator itr2=itr->second.begin();
  while(!(MagneticInfo>=(*itr2)[0] && MagneticInfo<= (*itr2)[1]) && itr2 != itr->second.end())
    itr2++;

  if(itr2==itr->second.end()){
    std::cout << "RFun::NormalizeRate:WARNING" << std::endl 
	      << "Normalization factors for rate type " << RateType 
	      << " do not exist in file " << m_normfactascii << std::endl
	      << "for the magnetic quantity with value " << MagneticInfo<< std::endl
	      << "Returning -1 (or 0 if return type returntype==NormRateErr" << std::endl;
    if(returntype=="NormRateErr")
      return 0;
    return -1;
  }


  // Normalize
  


  //NormRate = Rate/NormFactor/RefValue
   /* NormRateErr = Rate*sqrt(pow(norm_err/norm,2)
	 +pow(RateErr/Rate,2)
	 +pow(RefRateErr/RefRate,2));
   */

  Float_t NormRate = -1;
  Float_t NormRateErr = 0;
  if((*itr2)[2]>0 && (*itr2)[4]>0 && Rate>0){ // calculation is possible
    NormRate =  Rate/(*itr2)[2]/(*itr2)[4]; 
    // Commented out by Luca B.---see GDQMQ-340.
    //NormRateErr = NormRate*sqrt(pow((*itr2)[3]/(*itr2)[2],2)
    //				+pow(RateErr/Rate,2)
    //				+pow((*itr2)[5]/(*itr2)[4],2));
    // And here is the replacement, we just pick up the relative error on the original rate.
    NormRateErr = NormRate*(RateErr/Rate);
  }

  Float_t returnval = 0.0;

  if(returntype=="NormRate")
    returnval= NormRate;
  else if(returntype=="NormRateErr")
    returnval= NormRateErr;
  else
    {
      std::cerr << "RFun::NormalizeRate:ERROR" << std::endl
		<< "Return type " << RetType << " is none of the 2 possible values: " << std::endl
		<< "1) NormRate;  2) NormRateErr" << std::endl
		<< "ABORTING..." << std::endl;
      assert(0);      
    }


  return returnval;
}

 // Overload to be able to correct for earth limb in the field of view when the Zenith angle is given
Float_t RFun::NormalizeRate(char* RateType, Float_t MagneticInfo,
        Float_t ZenithAngle, Float_t Longitude,
        Float_t Rate,  Float_t RateErr, char* RetType)
{
  
  Float_t retValue = NormalizeRate(RateType,MagneticInfo,Rate,RateErr,RetType);
  Float_t corrFact = 1.;
  
  // Correcting for earth limb in the field of view - GDQMQ-330
  std::map<std::string, std::vector<float> >::const_iterator itearth=m_EarthLimbCorrFactors.find(RateType);
  if(itearth==m_EarthLimbCorrFactors.end())
    {
      std::cerr << "RFun::NormalizeRate:ERROR" << std::endl 
		<< "Earth limb correction factors for rate type " << RateType 
		<< " do not exist in file " << m_normfactascii << std::endl;
      assert(0);
    }

  // Formula is [0] + [1]*(x>[3])*(x-[3]) + [2]*(x>[3])*(x-[3])**2
  Float_t p0=0., p1=0., p2=0., p3=0.; 
  p0=(*itearth).second[0];
  p1=(*itearth).second[1];
  p2=(*itearth).second[2];
  p3=(*itearth).second[3];
  corrFact=p0;
  if(ZenithAngle>p3)
    corrFact+= p1*(ZenithAngle-p3) + p2*(ZenithAngle-p3)*(ZenithAngle-p3);
  // If correction factor is too small, give up
  if (corrFact<=0.1)
    corrFact=1.;

  // Correcting for longitude dip
  std::map<std::string, std::vector<float> >::const_iterator itlon=m_LongitudeCorr.find(RateType);
  if(itlon==m_LongitudeCorr.end())
    {
      std::cerr << "RFun::NormalizeRate:ERROR" << std::endl 
		<< "Longitude correction factors for rate type " << RateType 
		<< " do not exist in file " << m_normfactascii << std::endl;
      assert(0);
    }
  //Function : min(1, 1 - [0] + [0]*abs([2]*(x - [1])))
  Float_t lonCorr=1.;
  p0=(*itlon).second[0];
  p1=(*itlon).second[1];
  p2=(*itlon).second[2];
  lonCorr=TMath::Min(1., 1. - p0 + p0*TMath::Abs(p2*(Longitude - p1)));

  // Returning normalized value
  return retValue/(corrFact*lonCorr);
}

// Normalization for vectors
Float_t RFun::NormalizeRateVector(char* RateType, Float_t MagneticInfo, 
				  Float_t Rate,  Float_t RateErr, char* RetType,int dim)
{

  char RateTypeWithDim[100];
  sprintf(RateTypeWithDim,"%s[%d]",RateType,dim);

  return NormalizeRate(RateTypeWithDim,MagneticInfo,Rate,RateErr,RetType);
}

 // Overload when ZenithAngle and Longitude are also available
Float_t RFun::NormalizeRateVector(char* RateType, Float_t MagneticInfo,
        Float_t ZenithAngle, Float_t Longitude,
        Float_t Rate,  Float_t RateErr, char* RetType,int dim)
{

  char RateTypeWithDim[100];
  sprintf(RateTypeWithDim,"%s[%d]",RateType,dim);

  return NormalizeRate(RateTypeWithDim,MagneticInfo,ZenithAngle,Longitude,Rate,RateErr,RetType);
}
