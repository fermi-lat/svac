#ifndef TKRIndex_Header
#define TKRIndex_Header

#include "OracleTable.h"

struct TkrIndex : public OracleTable {

  long m_id; // is a oracle sequence number
  long m_calDesId; 
  int m_tkrInstId;

  TkrIndex(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
