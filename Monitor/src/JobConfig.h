#ifndef JobConfig_h
#define JobConfig_h 

#include <iostream>

#include "Rtypes.h"
#include <string>

class TChain;

 
class JobConfig {

public :
  
  // Standard c'tor
  JobConfig(const char* appName, const char* desc);

  virtual ~JobConfig();  

  void usage();
  
  Int_t parse(int argn, char** argc);


  
 
  
  inline const std::string& theApp() const { return m_theApp; }
  inline const std::string& path() const { return m_path; }

  inline const std::string& jobOptionXmlFile() const { return m_jobOptionXmlFile; }
  inline const std::string& configFile() const { return m_configFile; }
  inline const std::string& htmlFile() const { return m_htmlFile; }
  inline const std::string& sodir() const { return m_sodir; }
  inline const bool compile() const { return m_compile; }
  inline const bool dontCompile() const { return m_dontcompile; }

  inline const std::string& inputDigiFileStr() const { return m_inputDigiFileStr; }
  inline const std::string& inputReconFileStr() const { return m_inputReconFileStr; }
  inline const std::string& inputMcFileStr() const { return m_inputMcFileStr; }
  inline const std::string& inputSvacFileStr() const { return m_inputSvacFileStr; }
  inline const std::string& inputMeritFileStr() const { return m_inputMeritFileStr; }
  inline const std::string& inputCalFileStr() const { return m_inputCalFileStr; }

  inline const std::string& outputPrefix() const { return m_outputPrefix; }
  inline const std::string& timeStamp() const { return m_timeStamp; }

  inline int optval_n() const { return m_optval_n; }
  inline int optval_s() const { return m_optval_s; }
  inline int optval_b() const { return m_optval_b; }

  inline TChain* digiChain() const { return m_digiChain;}
  inline TChain* reconChain() const { return m_reconChain;}
  inline TChain* calChain() const { return m_calChain;}
  inline TChain* mcChain() const { return m_mcChain;}
  inline TChain* svacChain() const { return m_svacChain;}
  inline TChain* meritChain() const { return m_meritChain;}

  Bool_t checkDigi() const;
  Bool_t checkRecon() const;
  Bool_t checkMc() const;
  Bool_t checkSvac() const;
  Bool_t checkMerit() const;
  Bool_t checkCal() const;

  std::string getDataType(){ return m_datatype;} 
  Bool_t WriteInTreeToDisk() {return m_WriteintreeToDisk;}
  std::string gettmpdir() { return m_tmpdir;}
   
protected:

  TChain* makeChain(const char* name, const std::string& fileString) const;
 
private:

  std::string m_theApp;
  std::string m_description;
  std::string m_path;

  std::string m_jobOptionXmlFile;
  std::string m_configFile;
  std::string m_htmlFile;
  std::string m_sodir;

  std::string m_inputDigiFileStr;
  std::string m_inputReconFileStr;
  std::string m_inputMcFileStr;
  std::string m_inputSvacFileStr;
  std::string m_inputMeritFileStr;
  std::string m_inputCalFileStr;

  std::string m_outputPrefix;
  std::string m_timeStamp;

  int m_optval_n;
  int m_optval_s;
  int m_optval_b;
  bool m_compile;
  bool m_dontcompile;

  TChain* m_digiChain;
  TChain* m_reconChain;
  TChain* m_mcChain;
  TChain* m_svacChain;
  TChain* m_meritChain;
  TChain* m_calChain;
  std::string m_datatype;
  Bool_t m_WriteintreeToDisk;
  std::string m_tmpdir;
};

#endif
