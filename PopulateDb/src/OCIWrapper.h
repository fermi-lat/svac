#ifndef OCIWrapper_XinChen
#define OCIWrapper_XinChen

#include <exception>
#include <string>
#include "oci.h"

class OCIException : public std::exception {

 public:

  OCIException(const char* msg) throw() : m_errMsg(msg) { }
  ~OCIException() throw() { }

  virtual const char* what() const throw() { return m_errMsg.c_str(); }

 private:

  std::string m_errMsg;
};

class OCIWrapper {

 public:

  OCIWrapper(const char* dbName, const char* uName, const char* passWd);
  ~OCIWrapper();

  OCIStmt* prepareStatement(const char* sql);

  void bindIntVariable(OCIStmt* stmtHandle, const char* varName, void* var);

  void bindFloatVariable(OCIStmt* stmtHandle, const char* varName, void* var);

  void bindStringVariable(OCIStmt* stmtHandle, const char* varName, 
			  const char* var);

  void defineIntByPos(OCIStmt* stmtHandle, int* pInt, int pos);

  void defineLongByPos(OCIStmt* stmtHandle, long* pInt, int pos);

  void fetchNextRow(OCIStmt* stmtHandle);

  // times is no. of times the statement will be executed for NON-SELECT
  // statement.
  // For SELECT statement, normally times = 0 which will retrieve all rows
  void executeStatement(OCIStmt* stmtHandle, int times=1);

  void getNextSeqNo(const char* seqName, long* seqNo);

  void freeStmtH(OCIStmt* stmtH);

 private:

  bool checkErr(OCIError* errHandle, sword status);

  OCIEnv* m_envHandle;

  // a flag: true means there were errors in this connection, need to roll back
  bool m_error;

  sword m_status;

  OCIError* m_errHandle;

  OCISvcCtx* m_svcCtxHandle;

  std::string m_errMsg;
};

#endif
