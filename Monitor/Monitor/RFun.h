#ifndef RFun_h
#define RFun_h

//#include "configData/db/TrgConfigDB.h"
#include <vector>
#include <map>
#include "TBranchProxy.h"
#include "TBranchProxyDirector.h"
#include "TBranchProxyTemplate.h"
#include "TMath.h"



class RFun{
 public:
  RFun(){};
#ifndef oldROOT
  static const float calped(unsigned int timestamp,int tower,int callayer, int calcolumn, int calend, int calrange);
  static const float calpedwidth(unsigned int timestamp,int tower,int callayer, int calcolumn, int calend, int calrange);
#endif
  static const float acdped(unsigned int timestamp,int garc, int gafe);
  static const float acdpedGemId(unsigned int timestamp, unsigned int gemid, int pmttype);
  static int engine(int i,unsigned key);
  static int enginecounter(int i,unsigned key, int engine);
  static int iden(int i);


  // Acd/Tracker/Cal Related functions

  static unsigned getconsecutiveplaneshit(const UShort_t invector[36]);
  static unsigned getplaneshit(const UShort_t invector[36]);
  static std::vector<double> getemptytowers(ROOT::TArrayBoolProxy& invector);
  //static std::vector<double> getemptytowers(const UShort_t invector[16]);
  static void initboundarytowers();


  static unsigned gethitsinemptytower(double isemptytower, 
				      const UShort_t TkrHitsTowerPlane[36]);

  static unsigned loopovertkrplanes(const UShort_t invector[]);
  
 
#ifdef oldROOT
  static unsigned loopovertowerANDtkrplanes(ROOT::TArray2Proxy<UShort_t, 36>& TkrHitsTowerPlane);
  static unsigned loopovertowerANDcallayers(ROOT::TArray2Proxy<UShort_t, 8>& invector);
  static Double_t loopovertowerANDcallayers_float(ROOT::TArray2Proxy<Float_t, 8>& invector);
  static Double_t loopovercallayersANDcalcolumns_float(ROOT::TArray2Proxy<Float_t, 12>& invector);
#else
  static unsigned loopovertowerANDtkrplanes(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 36> >&);
  static unsigned loopovertowerANDcallayers(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 8> >&);
  static Double_t loopovertowerANDcallayers_float(ROOT::TArrayProxy<ROOT::TArrayType<Float_t, 8> >&);
  // static Double_t loopovercallayersANDcalcolumns_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 12> >&);
  static Double_t loopovercallayersANDcalcolumns_float(const Float_t [8][12]);
#endif


  // I guess this only work for hte root versions 5.14g and later

  static Double_t loopovercalcolumns_float(const Float_t [12]);
  static Double_t loopovertowerANDcallayersANDcalcolumns_float(ROOT::TArrayProxy<ROOT::TMultiArrayType<ROOT::TArrayType<Float_t, 12>, 8> >&);

  
  // Functions to be removed, since Xfaces will be combined in the reconstruction processes, 
  // and should not be combined in the monitoring code.
  /*
  static Double_t loopoverTowerANDcallayersANDcalcolumnsANDXfaces_float(ROOT::TArrayProxy<ROOT::TMultiArrayType<ROOT::TMultiArrayType<ROOT::TArrayType<Float_t,2>, 12>, 8> >&);
  

  static Double_t loopovercallayersANDcalcolumnsANDXfaces_float(const Float_t [8][12][2]);
  static Double_t loopovercalcolumnsANDXfaces_float(const Float_t [12][2]);
  static Double_t loopoverXfaces_float(const Float_t [2]);
  */

  // end of functions that only work with root versions 5.14g and later

  static unsigned loopovercallayers(const UShort_t invector[]);


  static unsigned loopovercalcolumns(const UShort_t invector[]);
  //  static unsigned loopovercallayersANDcalcolumns(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 12> >&);
  static unsigned loopovercallayersANDcalcolumns(const UShort_t[8][12]);

#ifndef oldROOT
  static unsigned loopovertowersANDcallayersANDcalcolumns(ROOT::TArrayProxy<ROOT::TMultiArrayType<ROOT::TArrayType<UShort_t, 12>, 8> >& invector);
#endif


  static unsigned loopovergarc(const UShort_t invector[]);
  
  static unsigned loopoveracdtiles(const UShort_t invector[]);
  static unsigned loopoveracdtilesbool(ROOT::TArrayBoolProxy& invector);
  
  static unsigned loopoverengine(const UShort_t invector[]);
  static unsigned loopoveracdface(const UShort_t invector[]);
  static unsigned loopoveracdrow(const UShort_t invector[]);
  static unsigned loopoveracdcolumn(const UShort_t invector[]);
  static unsigned loopoveracdpmt(const UShort_t invector[]);
  static unsigned loopovergafe(const UShort_t invector[]);

  
  static unsigned loopoveronedimvect(const UShort_t invector[], UInt_t vectdim);
  static unsigned loopoveronedimvectbool(ROOT::TArrayBoolProxy& invector, UInt_t vectdim);

  static unsigned istherenonzerocomponent(const UShort_t invector[], const Int_t vectordim);
  
  static int returnnonzerocomponent(ROOT::TArrayUShortProxy& invector, int vectordim);

  
  static double computemean_with_outlierscut(const ULong64_t invector[], 
					     const UInt_t vecdim, 
					     const double rmstailcut);
  

  
  static double computeratio(Short_t signal1, float ped1, 
			     Short_t signal2, float ped2,
			     Short_t MinSignal);


  static double computeratio_v2(Short_t signal1, float ped1, float MinSignal1,
				Short_t signal2, float ped2,
				Short_t MinSignal2);

  // function scans invector (CalXtalFaceSignal[16][8][12][2]) and returns 
  // Either the Energy (Energy =1) or Channel (Energy =0) of the channel with 
  // the highest energy (level =0), or the second highest (level = 1) or the third highest (level = 2) 
  // etc, etc....

  static double getChannelEnergyHighest(ROOT::TArrayProxy<ROOT::TMultiArrayType<ROOT::TMultiArrayType<ROOT::TArrayType<Float_t,2>, 12>, 8> >&, int Level, int Energy);


  // Get cal index [0-3071] corresponding to coordinates tower,layer,column,face. 
  static unsigned GetOveralIndex_TowerCalLayerCalColumnCalFace(int tower, int layer, int column, int face);


  // Update datagram evt counters. If event belongs to a new datagram (for that particular cpuNumber)
  // the function returns the value of the counter and resets it. Otherwise, the function returns -1.

  static int UpdateDatagramEvtCounter(Int_t datagraminfo[2], int cpuNumber);
  static void initdatagramevtcounter();

  // END of Acd/Tracker/Cal related functions
  // Trigger related functions
  static Double_t oneTriggerTower(ROOT::TArrayBoolProxy& invector);

  // Normalization of Rates
  
  static void SetAsciiFileNameWithNormFactors(const char* asciifile){m_normfactascii = asciifile;}

  // function that reads the norm factors from ascii file and fills the map RFun::NormFactors
  static int LoadNormFactors();
  

    // function that returns the Normalized the rates or error in the normalized rate 
// for the rate_type and magnetic info
  // It uses info from RFun::NormFactors. If this object is empty, it will fill it from ascii file

  static Float_t NormalizeRate(char* RateType, Float_t MagneticInfo, 
			       Float_t Rate,  Float_t RateErr, char* RetType);
  // OVerload when Zenith Angle and Longitude are given too
  static Float_t RFun::NormalizeRate(char* RateType, Float_t MagneticInfo,
                 Float_t ZenithAngle, Float_t Longitude,
                 Float_t Rate,  Float_t RateErr, char* RetType);


  static Float_t NormalizeRateVector(char* RateType, Float_t MagneticInfo, 
				     Float_t Rate,  Float_t RateErr, char* RetType,int dim);
  // OVerload when Zenith Angle and Longitude are given too
  static Float_t NormalizeRateVector(char* RateType, Float_t MagneticInfo,
                 Float_t ZenithAngle, Float_t Longitude,
                 Float_t Rate,  Float_t RateErr, char* RetType,int dim);

 
  // 
  static void PrintNormFactorsMap();

  // Fast mon functions

  /* This does not work !! 
  static unsigned loopovertowerANDtkrplanes_int(const Int_t[16][36]);
  static unsigned loopovertkrplanes_int(const Int_t[36]);

  */ 

  // Function to check whether bit is up
  // It returns 1 if bit is set, it returns zero otherwise
  static int IsBitSet(unsigned number, unsigned bitposition);

  // Function to dump the bit map from FT1EventClass variable into a 16-dim vector
  //static std::vector<double> GetVectorWithBitMapFromFT1EventClass(unsigned FT1EventClass);


  // This works !!

  static unsigned loopovertowerANDtkrplanes_int(ROOT::TArrayProxy<ROOT::TArrayType<Int_t, 36> >&);
  static unsigned loopovertkrplanes_int(const Int_t invector[]);
  static Double_t loopovertkrplanes_double(const Double_t invector[]);
  static Double_t loopovertowerANDtkrplanes_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 36> >&);
  static Double_t loopovertowerANDtkrplanes_square_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 36> >&);

    //(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 36> >&);
       
  // end of fastmon functions

  

  // Test functions
  static std::vector<double> testfun();
  static std::vector<double> vecfun(ROOT::TArrayUShortProxy vec);
  static unsigned gethitsinemptytowerTEST(double isemptytower, int twr,
				      const UShort_t TkrHitsTowerPlane[36]);
  static int testrunonceformulaoutput(std::vector<double>);
  // end test functions


  // Functions to be deleted (obsolete)
  
  // end of functions to be deleted


  // public memeber data
  static std::map<std::string,std::list<std::vector<float> > > m_NormFactors;
  static std::map<std::string, std::vector<float> > m_EarthLimbCorrFactors;
  static std::map<std::string, std::vector<float> > m_LongitudeCorr;
  static std::string m_normfactascii;


 private:
  static int m_boundarytwr[16][8]; // boundary towers for all towers
  static bool m_boundarytwrdefined;
  //static TrgConfigDB* m_tcf;

  

  static int m_datagramevtcounter[5];
  static int m_previousdatagramnumber[5];
  static bool makeinitdatagraminfo;
  // test data members
  static UInt_t m_doprintUpToN;
  static UInt_t m_evtcounter;
  // end test data members
  
};

#endif
