// header file
#include "JobConfig.h"

// stl
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>

// ROOT io
#include "TSystem.h"
#include "TChain.h"

// xml and file parsing
#include "xmlBase/IFile.h"
#include "facilities/Util.h"

JobConfig::JobConfig(const char* appName, const char* desc)
  :m_theApp(appName),
   m_description(desc),
   m_IsMC(0),
   m_optval_n(0),
   m_optval_s(0),
   m_optval_b(10),
   m_compile(false),
   m_dontcompile(false),
   m_digiChain(0),
   m_reconChain(0),
   m_mcChain(0),
   m_svacChain(0),
   m_meritChain(0),
   m_calChain(0)
{

}

JobConfig::~JobConfig() 
{
  if (m_digiChain)delete m_digiChain;
  if (m_reconChain) delete m_reconChain;
  if (m_mcChain) delete m_mcChain;
  if (m_svacChain) delete m_svacChain; 
  if (m_meritChain) delete m_meritChain;
  if (m_calChain) delete m_calChain;
}

void JobConfig::usage() {

  using std::cout;
  using std::cerr;
  using std::endl;
  
  cout << endl
       << m_theApp << endl
       << m_description << endl
       << endl;
  
  cout << "Usage:" << endl
       << "\t" << m_theApp << " -j <configfile>" << endl 
       << endl
       << "\t   <configFile>      : name of xml file with job configuration" << endl
       << endl
       << "\t" << m_theApp << " [options] [input] -o <output>" << endl 
       << endl
       << "\t   -c <monConifg>    : name of the xml file with the monitoring configuration"<<endl
       << endl
       << "\t   -g <htmlFile>    : name of the html output file with the listing of the configuration"<<endl
       << endl
       << "\t   -w <directory>    : location of the directory for the proxies"<<endl
       << endl
       << "\t   -w <directory>    : location of the directory for the proxies"<<endl
       << endl
       << "\tINPUT" << endl
       << "\t   -r <reconFiles>   : comma seperated list of recon ROOT files" << endl
       << "\t   -d <digiFiles>    : comma seperated list of digi ROOT files" << endl
       << "\t   -y <McFiles>      : comma seperated list of mc ROOT files" << endl
       << "\t   -S <svacFiles>    : comma seperated list of svac ROOT files" << endl
       << "\t   -m <meritFiles>   : comma seperated list of merit ROOT files" << endl 
       << "\t   -a <calFiles>     : comma seperated list of cal ROOT files" << endl 
       << "\tNOTE:  Different calibrations jobs take diffenent types of input files" << endl
       << endl
       << "\t   -o <output>       : prefix (path or filename) to add to output files" << endl
       << endl
       << "\tOPTIONS for all jobs" << endl
       << "\t   -h                : print this message" << endl
       << "\t   -q                : Only compile shared libraries but don't run" << endl
       << "\t   -p                : Don't do any run-time compilation, read existing shared libraries" << endl
       << "\t   -n <nEvents>      : run over <nEvents>" << endl
       << "\t   -s <startEvent>   : start with event <startEvent>" << endl
       << "\t   -t <datatype>     : Data type. Currently only MC/Data" << endl
       << endl
       << "\tOPTIONS for specific jobs (will be ignored by other jobs)"  << endl
       << "\t   -b <binSize>         : size of time bins in seconds [10]" << endl   
       << endl;
}
  
Int_t JobConfig::parse(int argn, char** argc) {

  using std::cout;
  using std::cerr;
  using std::endl;
  using std::string;

  char* endPtr;  
  int opt;
  while ( (opt = getopt(argn, argc, "ho:t:d:r:y:S:m:a:j:c:g:n:s:b:w:pq")) != EOF ) {
    switch (opt) {
    case 'h':   // help      
      usage();
      return 1;
    case 'q':   // compile only
      m_compile=true;
      break;
    case 'p':   // don't compile 
      m_dontcompile=true;
      break;
    case 'o':   //  output
      m_outputPrefix = string(optarg);
      break;
    case 'd':   // digi files
      m_inputDigiFileStr += string(optarg);
      m_inputDigiFileStr += ',';
      break;
    case 'r':   // recon files
      m_inputReconFileStr += string(optarg);
      m_inputReconFileStr += ',';
      break;
    case 'y':   // mc files
      m_inputMcFileStr += string(optarg);
      m_inputMcFileStr += ',';
      break;
    case 'S':   // Svac files
      m_inputSvacFileStr += string(optarg);
      m_inputSvacFileStr += ',';
      break;
    case 'm':   // Merit files
      m_inputMeritFileStr += string(optarg);
      m_inputMeritFileStr += ',';
      break;
    case 'a':   // Cal files
      m_inputCalFileStr += string(optarg);
      m_inputCalFileStr += ',';
      break;
    case 'j':   // job option file
      m_jobOptionXmlFile = string(optarg);
      break;
    case 'c':   // monitoring configuration file
      m_configFile = string(optarg);
      break;
    case 'g':   // html configuration file
      m_htmlFile = string(optarg);
      break;
    case 'w':   // shared object directory
      m_sodir = string(optarg);
      break;
    case 'b':   // size of bins
      m_optval_b = strtoul( optarg, &endPtr, 0 );
      break;
    case 'n':   // number of events
      m_optval_n = strtoul( optarg, &endPtr, 0 );
      break;
    case 's':   // start event
      m_optval_s = strtoul( optarg, &endPtr, 0 );
      break;
    case 't':
      m_datatype = string(optarg);
      break;
    case '?':
      usage();
      return 2;
    default:
      cerr << opt << " not parsable..." << endl;
      cerr << "Try " << m_theApp << " -h" << endl;
      return 2;
    }
  }

  if ( argn - optind > 0 ) {
    cerr << m_theApp << " only takes options, not bare arguments" << endl
	 << "Try " << m_theApp << " -h" << endl;
    return 3;
  }

  // parse xml config file if requested
  using xmlBase::IFile;
  IFile* myFile=0;
  if (m_jobOptionXmlFile != ""){
    myFile=new IFile(m_jobOptionXmlFile.c_str()); 

    // output file prefix
    if (myFile->contains("parameters","outputPrefix") && m_outputPrefix == "" ) {
      m_outputPrefix = myFile->getString("parameters", "outputPrefix");
    }
  }
    

  // data type
  if(strstr(m_datatype.c_str(),"MC"))
    {
      m_IsMC = 1;
      std::cout << "Data type: MC" << std::endl;
    }

  // timestamp
  std::time_t theTime = std::time(0);
  const char* timeString = std::ctime(&theTime);

  m_timeStamp = string(timeString);
  m_timeStamp.erase(m_timeStamp.size()-1);

  // digi files
  if (myFile && myFile->contains("parameters","digiFileList")) {
    m_inputDigiFileStr += myFile->getString("parameters", "digiFileList");
  }
  
  if ( m_inputDigiFileStr != "" ) {
    cout << "Input digi files:" << endl;
    m_digiChain = makeChain("Digi",m_inputDigiFileStr);
  }    


  // recon files
  if (myFile && myFile->contains("parameters","reconFileList")) {
    m_inputReconFileStr += myFile->getString("parameters", "reconFileList");
  }

  if ( m_inputReconFileStr != "" ) {
    cout << "Input recon files:" << endl;
    m_reconChain = makeChain("Recon",m_inputReconFileStr);
  }    
  
  // mc files
  if (myFile && myFile->contains("parameters","mcFileList")) {
    m_inputMcFileStr += myFile->getString("parameters", "McFileList");
  }
  
  if ( m_inputMcFileStr != "" ) {
    cout << "Input mc files:" << endl;
    m_mcChain = makeChain("mc",m_inputMcFileStr);
  }    


  // svac files
  if (myFile&& myFile->contains("parameters","svacFileList")) {
    m_inputSvacFileStr += myFile->getString("parameters", "svacFileList");
  }
  
  if ( m_inputSvacFileStr != "" ) {
    cout << "Input svac files:" << endl;
    m_svacChain = makeChain("Output",m_inputSvacFileStr);
  }    

  // merit files
  if (myFile && myFile->contains("parameters","meritFileList")) {
    m_inputMeritFileStr += myFile->getString("parameters", "meritFileList");
  }
  
  if ( m_inputMeritFileStr != "" ) {
    cout << "Input merit files:" << endl;
    m_meritChain = makeChain("MeritTuple",m_inputMeritFileStr);
  }    

  // cal files
  if (myFile && myFile->contains("parameters","calFileList")) {
    m_inputCalFileStr += myFile->getString("parameters", "calFileList");
  }
  
  if ( m_inputCalFileStr != "" ) {
    cout << "Input cal files:" << endl;
    m_calChain = makeChain("CalTuple",m_inputCalFileStr);
  }    
  // html configuration file
  if (myFile && myFile->contains ("parameters","htmlFile")){
    if (m_htmlFile !=""){
      cerr<<"html configuration file defined both in command line and xml file. Exiting..."<<endl;
      return 1;
    }
    m_htmlFile=myFile->getString("parameters","htmlFile");
  }
  // shared libraries directory
  if (myFile && myFile->contains ("parameters","sharedLibDir")){
    if (m_sodir !=""){
      cerr<<"Overriding shared lib directory defined both in xml file."<<endl;
    }
    m_sodir=myFile->getString("parameters","sharedLibDir");
  }
  if (m_sodir!=""&&m_sodir[m_sodir.length()-1]!='/')m_sodir+="/";
  // monitoring configuration file
  if (myFile && myFile->contains ("parameters","configFile")){
    if (m_configFile !=""){
      cerr<<"Monitoring configuration file defined both in command line and xml file. Exiting..."<<endl;
      return 1;
    }
    m_configFile=myFile->getString("parameters","configFile");
  }
  std::cout << "output file prefix: " << m_outputPrefix << std::endl;
  std::cout << "timestamp: " << m_timeStamp << std::endl;

  return 0;
}


bool JobConfig::getIsMC()
{
  //return m_IsMC;
  return 1;
}

TChain* JobConfig::makeChain(const char* name, const std::string& fileString) const {

  TChain* chain(0);
  std::vector <std::string> token;
  facilities::Util::stringTokenize(fileString, ";, ", token);
  unsigned int nFiles = token.size();
  
  for ( unsigned int iFile(0); iFile < nFiles; iFile++ ) {
    if (token[iFile]=="") continue;
    if ( chain == 0 ) chain = new TChain(name);
    chain->Add(token[iFile].c_str());
    std::cout << "   " << iFile+1 << ") " << token[iFile] << std::endl;
  }
  return chain;
}


Bool_t JobConfig::checkDigi() const {
  if ( m_digiChain == 0 ) {
    std::cerr << "This job requires digi ROOT files as input." << std::endl
	      << "\tuse -d <file> option to specify them." << std::endl
	      << std::endl;
    return kFALSE;
  }
  return kTRUE;
}

Bool_t JobConfig::checkRecon() const {
  if ( m_reconChain == 0 ) {
    std::cerr << "This job requires recon ROOT files as input." << std::endl
	      << "\tuse -r <file> option to specify them." << std::endl
	      << std::endl;
    return kFALSE;
  }
  return kTRUE;
}

Bool_t JobConfig::checkMc() const {
  if ( m_mcChain == 0 ) {
    std::cerr << "This job requires mc ROOT files as input." << std::endl
	      << "\tuse -y <file> option to specify them." << std::endl
	      << std::endl;
    return kFALSE;
  }
  return kTRUE;
}

Bool_t JobConfig::checkSvac() const {
  if ( m_svacChain == 0 ) {
    std::cerr << "This job requires svac ROOT files as input." << std::endl
	      << "\tuse -S <file> option to specify them." << std::endl
	      << std::endl;
    return kFALSE;
  }
  return kTRUE;
}

Bool_t JobConfig::checkMerit() const {
  if ( m_meritChain == 0 ) {
    std::cerr << "This job requires merit ROOT files as input." << std::endl
	      << "\tuse -m <file> option to specify them." << std::endl
	      << std::endl;
    return kFALSE;
  }
  return kTRUE;
}

Bool_t JobConfig::checkCal() const {
  if ( m_calChain == 0 ) {
    std::cerr << "This job requires cal ROOT files as input." << std::endl
	      << "\tuse -a <file> option to specify them." << std::endl
	      << std::endl;
    return kFALSE;
  }
  return kTRUE;
}
