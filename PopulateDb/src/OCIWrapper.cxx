#include <string>
#include <iostream>
#include "OCIWrapper.h"

using namespace std;

OCIWrapper::OCIWrapper(const char* dbName, const char* uName, 
		       const char* passWd) : m_error(false)
{
  OCIEnvCreate(&m_envHandle, OCI_THREADED | OCI_OBJECT, (dvoid*) 0, 0,
	       0, 0, (size_t) 0, (dvoid **) 0);

  m_status = OCIHandleAlloc((dvoid*) m_envHandle, (dvoid**) &m_errHandle, 
			  OCI_HTYPE_ERROR, 0, (dvoid**) 0);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());

  m_status = OCILogon(m_envHandle, m_errHandle, &m_svcCtxHandle, 
		      (text*) uName, strlen(uName), (text*) passWd, 
		      strlen(passWd), (text*) dbName, strlen(dbName));

  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

OCIWrapper::~OCIWrapper()
{
  if(m_error) {
    OCITransRollback(m_svcCtxHandle, m_errHandle, OCI_DEFAULT);
  }

  m_status = OCILogoff(m_svcCtxHandle, m_errHandle);
  if(checkErr(m_errHandle, m_status)) {
    cout << "During OCILogoff, " << m_errMsg << endl;
  }

  // only need to free envHandle, all its child handles will be freed 
  // automatically 
  m_status = OCIHandleFree(m_envHandle, OCI_HTYPE_ENV);
  if(checkErr(m_errHandle, m_status)) {
    cout << "During OCIHandleFree to free enviromental handle, " << m_errMsg
	 << endl;
  }
}

void OCIWrapper::freeStmtH(OCIStmt* stmtH)
{
  m_status = OCIHandleFree(stmtH, OCI_HTYPE_STMT);
  if(checkErr(m_errHandle, m_status)) {
    cout << "During OCIHandleFree to free statement handel, " << m_errMsg 
	 << endl;
  }
}

OCIStmt* OCIWrapper::prepareStatement(const char* sql)
{
  OCIStmt* stmtHandle;
  m_status = OCIHandleAlloc((dvoid*) m_envHandle, (dvoid**) &stmtHandle, 
			    OCI_HTYPE_STMT, 0, (dvoid**) 0);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());

  m_status = OCIStmtPrepare(stmtHandle, m_errHandle, (text*) sql, 
			  strlen(sql), OCI_NTV_SYNTAX, OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());

  return stmtHandle;
}

void OCIWrapper::bindIntVariable(OCIStmt* stmtHandle, const char* varName, 
				 void* var)
{
  OCIBind* bindHandle = 0;
  m_status = OCIBindByName(stmtHandle, &bindHandle, m_errHandle, 
			   (text*) varName, strlen(varName), var, sizeof(int),
			   SQLT_INT, (dvoid*) 0, (ub2*) 0, (ub2*) 0, (ub4) 0, 
			   (ub4*) 0,  OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

void OCIWrapper::bindFloatVariable(OCIStmt* stmtHandle, const char* varName, 
				   void* var)
{
  OCIBind* bindHandle = 0;
  m_status = OCIBindByName(stmtHandle, &bindHandle, m_errHandle, 
			   (text*) varName, strlen(varName), var, 
			   sizeof(float), SQLT_FLT, (dvoid*) 0, (ub2*) 0, 
			   (ub2*) 0, (ub4) 0, (ub4*) 0, OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

void OCIWrapper::bindStringVariable(OCIStmt* stmtHandle, const char* varName, 
				    const char* var)
{
  OCIBind* bindHandle = 0;
  m_status = OCIBindByName(stmtHandle, &bindHandle, m_errHandle, 
			   (text*) varName, strlen(varName), (void*) var, 
			   strlen(var)+1, SQLT_STR, 
			   (dvoid*) 0, (ub2*) 0, 
			   (ub2*) 0, (ub4) 0, (ub4*) 0, OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

void OCIWrapper::defineIntByPos(OCIStmt* stmtHandle, int* pInt, int pos)
{
  OCIDefine* defHandle = 0;
  sb2 dp;
  ub2* rlenp = 0;
  ub2* rcodep = 0;
  m_status = OCIDefineByPos(stmtHandle, &defHandle, m_errHandle, pos, pInt, 
			    sizeof(int), SQLT_INT, &dp, rlenp, rcodep, 
			    OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

void OCIWrapper::defineLongByPos(OCIStmt* stmtHandle, long* pInt, int pos)
{
  OCIDefine* defHandle = 0;
  sb2 dp;
  ub2* rlenp = 0;
  ub2* rcodep = 0;
  m_status = OCIDefineByPos(stmtHandle, &defHandle, m_errHandle, pos, pInt, 
			    sizeof(int), SQLT_INT, &dp, rlenp, rcodep, 
			    OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

void OCIWrapper::executeStatement(OCIStmt* stmtHandle, int times)
{
  m_status = OCIStmtExecute(m_svcCtxHandle, stmtHandle, m_errHandle, times, 0,
			    0, 0, OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

void OCIWrapper::fetchNextRow(OCIStmt* stmtHandle)
{
  m_status = OCIStmtFetch(stmtHandle, m_errHandle, 1, OCI_FETCH_NEXT, 
			    OCI_DEFAULT);
  if(checkErr(m_errHandle, m_status)) throw OCIException(m_errMsg.c_str());
}

void OCIWrapper::getNextSeqNo(const char* seqName, long* seqNo)
{
  string sql = "SELECT ";
  sql += seqName;
  sql += ".NextVal FROM DUAL";

  OCIStmt* stmtH = prepareStatement(sql.c_str());
  defineLongByPos(stmtH, seqNo, 1);
  executeStatement(stmtH);
  freeStmtH(stmtH);
}

bool OCIWrapper::checkErr(OCIError* errHandle, sword status)
{
  text errBuffer[512];
  ub4 bufferLen = sizeof(errBuffer);
  sb4 errCode;

  std::string errStr("OCI Error: ");

  m_error = true;

  switch (status)
    {
    case OCI_SUCCESS:
      m_error = false;
      break;
    case OCI_SUCCESS_WITH_INFO:
      m_errMsg = "OCI Error: OCI_SUCCESS_WITH_INFO";
      return 1;
    case OCI_NEED_DATA:
      m_errMsg = "OCI Error: OCI_NEED_DATA";
      return 1;
    case OCI_NO_DATA:
      m_errMsg = "OCI Error: OCI_NO_DATA";
      return 1;
    case OCI_ERROR:
      OCIErrorGet(errHandle, (ub4) 1, (text*) 0, &errCode, errBuffer, 
		  bufferLen, OCI_HTYPE_ERROR);
       errStr += (char*) errBuffer;
      m_errMsg = errStr;
      return 1;
    case OCI_INVALID_HANDLE:
      m_errMsg = "OCI Error: OCI_INVALID_HANDLE";
      return 1;
    case OCI_STILL_EXECUTING:
      m_errMsg = "OCI Error: OCI_STILL_EXECUTING";
      return 1;
    default:
      return 0;
    }
  return 0;
}
