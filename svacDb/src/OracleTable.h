#ifndef OracleTable_Header
#define OracleTable_Header

#include "OCIWrapper.h"

struct OracleTable {

  OracleTable(OCIWrapper* db=0) : m_db(db), m_stmtH(0), m_oracleTimeFmt(0){ }  

  virtual ~OracleTable() { if(m_db) m_db->freeStmtH(m_stmtH); }

  void setDb(OCIWrapper* db) { m_db = db; }

  void setOracleTimeFmt(const char* fmt) { m_oracleTimeFmt = fmt; }
  virtual void prepareFill() = 0;

  void fill() 
  { assert(m_db != 0); m_db->executeStatement(m_stmtH); }

  OCIWrapper* m_db;

  OCIStmt* m_stmtH;

  const char* m_oracleTimeFmt;

};

#endif
