#ifndef CalIndex_Header
#define CalIndex_Header

#include "OracleTable.h"

struct CalIndex : public OracleTable {

  long m_id; // is a oracle sequence number
  long m_calDesId; 
  int m_calInstId;

  CalIndex(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
