#ifndef TkrNoisyChannel_Header
#define TkrNoisyChannel_Header

#include "OracleTable.h"

struct TkrNoisyChannel : public OracleTable{

  long m_id; // is a oracle sequence number
  long m_tkrIndexId; 
  int m_strip;

  TkrNoisyChannel(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
