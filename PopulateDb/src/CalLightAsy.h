#ifndef CalLightAsy_Header
#define CalLightAsy_Header

#include "OracleTable.h"

struct CalLightAsy : public OracleTable{

  long m_id; // is a oracle sequence number
  long m_calIndexId;
  int m_face;
  int m_range; 
  float m_slope;

  CalLightAsy(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
