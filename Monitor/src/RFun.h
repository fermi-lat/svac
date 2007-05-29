#ifndef RFun_h
#define RFun_h

#include "configData/db/TrgConfigDB.h"
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


  // Tracker Related functions

  static unsigned getconsecutiveplaneshit(const UShort_t invector[36]);
  static std::vector<double> getemptytowers(ROOT::TArrayBoolProxy& invector);
  //static std::vector<double> getemptytowers(const UShort_t invector[16]);
  static void initboundarytowers();


  static unsigned gethitsinemptytower(double isemptytower, 
				      const UShort_t TkrHitsTowerPlane[36]);

  static unsigned loopovertkrplanes(const UShort_t invector[36]);
  
  //static unsigned loopovertowerANDtkrplanes(const UShort_t TkrHitsTowerPlane[16][36]);
  static unsigned loopovertowerANDtkrplanes(ROOT::TArray2Proxy<UShort_t, 36>& TkrHitsTowerPlane);

   


  // END of tracker related functions
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
  static TrgConfigDB* m_tcf;

  // test data members
  static UInt_t m_doprintUpToN;
  static UInt_t m_evtcounter;
  // end test data members
  
};

#endif
