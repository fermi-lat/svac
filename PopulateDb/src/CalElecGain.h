#ifndef CalElecGain_Header
#define CalElecGain_Header

#include "OracleTable.h"

struct CalElecGain : public OracleTable{

  long m_id; // is a oracle sequence number
  long m_calIndexId;
  int m_face;
  int m_range; 
  float m_peak;
  float m_width;

  CalElecGain(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
