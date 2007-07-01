#ifndef RFun_h
#define RFun_h

//#include "configData/db/TrgConfigDB.h"
#include <vector>
#include "TBranchProxy.h"
#include "TBranchProxyDirector.h"
#include "TBranchProxyTemplate.h"




class RFun{
 public:
  RFun(){};
  static const float acdped(unsigned int timestamp,int garc, int gafe);
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
  static unsigned loopovertowerANDcallayers_double(ROOT::TArray2Proxy<Double_t, 8>& invector);
#else
  static unsigned loopovertowerANDtkrplanes(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 36> >&);
  static unsigned loopovertowerANDcallayers(ROOT::TArrayProxy<ROOT::TArrayType<UShort_t, 8> >&);
  static unsigned loopovertowerANDcallayers_double(ROOT::TArrayProxy<ROOT::TArrayType<Double_t, 8> >&);
#endif





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
  
  
  static double computemean_with_outlierscut(const ULong64_t invector[], 
					     const UInt_t vecdim, 
					     const double rmstailcut);
  

  // END of Acd/Tracker/Cal related functions
  // Trigger related functions
  static Double_t oneTriggerTower(ROOT::TArrayBoolProxy& invector);
  // Test functions
  static std::vector<double> testfun();
  static std::vector<double> vecfun(ROOT::TArrayUShortProxy vec);
  static unsigned gethitsinemptytowerTEST(double isemptytower, int twr,
				      const UShort_t TkrHitsTowerPlane[36]);
  static int testrunonceformulaoutput(std::vector<double>);
  // end test functions


  // Functions to be deleted (obsolete)
  
  // end of functions to be deleted


 private:
  static int m_boundarytwr[16][8]; // boundary towers for all towers
  static bool m_boundarytwrdefined;
  //static TrgConfigDB* m_tcf;

  // test data members
  static UInt_t m_doprintUpToN;
  static UInt_t m_evtcounter;
  // end test data members
  
};

#endif
