#ifndef OracleDbSvc_XinChen
#define OracleDbSvc_XinChen

#include <string>
#include "IOracleDbSvc.h"

class OCIWrapper;

class OracleDbSvc : public Service, virtual public IOracleDbSvc {

public:

  OracleDbSvc(const std::string& name, ISvcLocator* s1);

  StatusCode queryInterface(const IID& riid, void**ppvIF);

  virtual StatusCode initialize();
  
  virtual StatusCode finalize();

  OCIWrapper* getOracleDb() { return m_db; }
  const char*  getOracleTimeFmt() { return m_dateFormat.c_str(); }

private:

  OCIWrapper* m_db;
  std::string m_dbName;
  std::string m_userName;
  std::string m_passWord;
  std::string m_dateFormat;
};

#endif
