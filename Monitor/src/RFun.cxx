#include "Monitor/RFun.h"
//#include "configData/db/LatcDBImplOld.h"
#include "AcdPedProxy.h"
#include "AcdPeds.h"
#include "CalPedProxy.h"
#include "CalPeds.h"
#include <map>

const float RFun::acdped(unsigned int timestamp,int garc,int gafe){
  const AcdPeds* peds=AcdPedProxy::getAcdPeds(timestamp);
  return peds->mean(garc,gafe);
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
  if(sig1 < MinSignal || sig2 < MinSignal)
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
