#ifndef IOracleDbSvc_XinChen
#define IOracleDbSvc_XinChen

#include "GaudiKernel/IInterface.h"

class OCIWrapper;

static const InterfaceID IID_IOracleDbSvc("IOracleDbSvc", 1, 0); 

class IOracleDbSvc : virtual public IInterface {

 public:

  static const InterfaceID& interfaceID() { return IID_IOracleDbSvc; }

  virtual OCIWrapper* getOracleDb() = 0;
  virtual const char* getOracleTimeFmt() = 0;

  virtual ~IOracleDbSvc() { }

};


#endif
