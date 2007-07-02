#include "Monitor/RFun.h"
//#include "configData/db/LatcDBImplOld.h"
#include "AcdPedProxy.h"
#include "AcdPeds.h"

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
unsigned RFun::loopovertowerANDcallayers_double(ROOT::TArray2Proxy<Double_t, 8>& invector)
#else
unsigned RFun::loopovertowerANDcallayers_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 8> >& invector)
#endif

{
  Double_t val(0.0);
  for (UShort_t itower = 0; itower < 16; itower++){
    for (UShort_t icallayer = 0; icallayer < 8; icallayer++){
      if(invector[itower][icallayer] >= 0)
	val += invector[itower][icallayer];
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


static unsigned RFun::istherenonzerocomponent(const UShort_t invector[], const Int_t vectordim)
{
  for(UShort_t i=0; i<vectordim;i++){
    if(invector[i]>0.0)
      return 1;
  }
  return 0;
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

// Initialization of static data member

//TrgConfigDB* RFun::m_tcf=new TrgConfigDB(new LatcDBImplOld);

int RFun::m_boundarytwr[16][8];
bool RFun::m_boundarytwrdefined = false;
UInt_t RFun::m_doprintUpToN = 5;
UInt_t RFun::m_evtcounter = 0;


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






