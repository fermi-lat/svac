#ifndef TkrTot_Header
#define TkrTot_Header

#include "OracleTable.h"

struct TkrTot : public OracleTable{

  long m_id; // is a oracle sequence number
  long m_tkrIndexId; 
  int m_strip;
  float m_p0;
  float m_p1;
  float m_p2;
  float m_chi2;

  TkrTot(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
