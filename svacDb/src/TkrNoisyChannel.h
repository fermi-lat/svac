#ifndef TkrNoisyChannel_Header
#define TkrNoisyChannel_Header

#include "OracleTable.h"

struct TkrNoisyChannel : public OracleTable{

  long m_tkrNoisyChId; // is a oracle sequence number
  long m_tkrIndexId; 
  int m_strip;
  float m_avgCount;

  TkrNoisyChannel(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
