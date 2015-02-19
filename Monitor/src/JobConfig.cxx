// header file
#include "JobConfig.h"

// stl
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
#include <cassert>

// ROOT io
#include "TSystem.h"
#include "TChain.h"

// xml and file parsing
#include "xmlBase/IFile.h"
#include "facilities/Util.h"

std::map<std::string,std::list<std::vector<float> > > JobConfig::m_NormFactors;
std::map<std::string, std::vector<float> > JobConfig::m_EarthLimbCorrFactors;
std::map<std::string, std::vector<float> > JobConfig::m_LongitudeCorr;
std::string JobConfig::m_normfactascii("");

JobConfig::JobConfig(const char* appName, const char* desc)
  :m_theApp(appName),
   m_description(desc),
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
   m_calChain(0),
   m_fastmonChain(0),
   m_trackermonChain(0),
   m_datatype("Normal"),
   m_WriteintreeToDisk(false),
   m_tmpdir("./")
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
  if (m_fastmonChain) delete m_fastmonChain;
  if (m_trackermonChain) delete m_trackermonChain;
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
       << "\tINPUT" << endl
       << "\t   -r <reconFiles>   : comma seperated list of recon ROOT files" << endl
       << "\t   -d <digiFiles>    : comma seperated list of digi ROOT files" << endl
       << "\t   -y <McFiles>      : comma seperated list of mc ROOT files" << endl
       << "\t   -S <svacFiles>    : comma seperated list of svac ROOT files" << endl
       << "\t   -m <meritFiles>   : comma seperated list of merit ROOT files" << endl 
       << "\t   -a <calFiles>     : comma seperated list of cal ROOT files" << endl 
       << "\t   -f <fastmonFiles> : comma seperated list of fastmon ROOT files" << endl 
       << "\t   -k <trackermonFiles> : comma seperated list of trackermon ROOT files" << endl 
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
       << "\t   -u <dir>          : Directory where to store the intermediate tree. Default is ./ . "
       << endl
       << "\t   -z                : Write intermediate tree to disk" << endl
       << "\t   -e                : Filename with normalization factors" << endl
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
  while ( (opt = getopt(argn, argc, "ho:t:d:r:y:S:m:a:f:k:j:c:e:g:n:s:b:w:u:pqz")) != EOF ) {
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
    case 'z':
      m_WriteintreeToDisk = true;
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
    case 'f':   // Merit files
      m_inputFastMonFileStr += string(optarg);
      m_inputFastMonFileStr += ',';
      break;
    case 'k':   // Merit files
      m_inputTrackerMonFileStr += string(optarg);
      m_inputTrackerMonFileStr += ',';
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
    case 'e': // file with Normfactors
      m_normfactascii = string(optarg);
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
    case 'u':
      m_tmpdir = string(optarg);
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
  std::cout << "Data type : " << m_datatype.c_str() << std::endl;

  // Set ascii file that will be used to normalize rates
  if(m_normfactascii.size() >2) {
    std::cout << "Ascii file used to normalize rates: " << m_normfactascii.c_str() << std::endl;
  
    if(m_NormFactors.size() <1) { // Norm factors have not been loaded yet
      std::cout << "Loading Norm factors from file " << std::endl
	        << m_normfactascii << std::endl;  
      int b = JobConfig::LoadNormFactors();
      if(b) {
	std::cerr << "JobConfig::NormalizeRate:ERROR" << std::endl 
		  << "Norm factors could not be loaded " << std::endl
	          << "Therefore, Rates cannot be normalized. ABORTING..." << std::endl;
	assert(0);
      }
    }
    //PrintNormFactorsMap();
  } 

  // tmp dir to store intermediate tree
  if (m_tmpdir!=""&& m_tmpdir[m_tmpdir.length()-1]!='/')m_tmpdir+="/";

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

   // fastmon files
  if (myFile && myFile->contains("parameters","fastmonFileList")) {
    m_inputFastMonFileStr += myFile->getString("parameters", "fastmonFileList");
  }
  
  if ( m_inputFastMonFileStr != "" ) {
    cout << "Input fastmon files:" << endl;
    m_fastmonChain = makeChain("IsocDataTree",m_inputFastMonFileStr);
  }  


    // trackermon files
  if (myFile && myFile->contains("parameters","trackermonFileList")) {
    m_inputTrackerMonFileStr += myFile->getString("parameters", "trackermonFileList");
  }
  
  if ( m_inputTrackerMonFileStr != "" ) {
    cout << "Input trackermon files:" << endl;
    m_trackermonChain = makeChain("tkrMonitor",m_inputTrackerMonFileStr);
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

Bool_t JobConfig::checkFastMon() const {
  if ( m_fastmonChain == 0 ) {
    std::cerr << "This job requires fastmon ROOT files as input." << std::endl
	      << "\tuse -f <file> option to specify them." << std::endl
	      << std::endl;
    return kFALSE;
  }
  return kTRUE;
}


Bool_t JobConfig::checkTrackerMon() const {
  if ( m_trackermonChain == 0 ) {
    std::cerr << "This job requires trackermon ROOT files as input." << std::endl
	      << "\tuse -k <file> option to specify them." << std::endl
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

// function that reads the norm factors from ascii file and fills the map RFun::NormFactors
int JobConfig::LoadNormFactors()
{
  // open file
  if(m_normfactascii.size()<2)
    {
      std::cerr << "JobConfig::LoadNormFactors:ERROR" << std::endl
		<< "m_normfactascii.size()<2 " << std::endl
		<< "Exiting function returning 1" << std::endl;
      return 1;
    }

  // std::cout << "Opening Norm file " << m_normfactascii.c_str() << std::endl;
  std::ifstream inputFile(m_normfactascii.c_str());
  if ( ! inputFile.good() ) {
    std::cerr << "JobConfig::LoadNormFactors:ERROR" << std::endl 
	      << "Problems opening file " <<  m_normfactascii.c_str() << std::endl
	      << "Exiting function returning 2" << std::endl;
    return 2;
  }

  // ok, we can start filling object static std::map<std::string,std::vector> m_NormFactors;
  std::string ratename;
  float refrate[2]; //value and error (will be put as last components of vector ratelineinfo)
  std::vector<float> ratelineinfo;
  std::list<std::vector<float> > listofnormfactors;
  int newrate = 0; //1 for yes
  int ingestdata = 0; //1 for yes
  float tmpval = 0.0;

  // initialize
  refrate[0] = -2;
  refrate[1] = -2;
   
  // grab one line
  const int bufSize(1000); char buffer[bufSize];
  inputFile.getline(buffer,bufSize);
  while ( ! inputFile.eof() ) {
    // ignore comment lines (start with '#')
    if ( buffer[0] == '#' ) {
      inputFile.getline(buffer,bufSize);
      continue;
    }

     // tokenize the line, make sure that there are 5 tokens
    std::string inputLine(buffer);

    std::vector <std::string> tokens;
    facilities::Util::stringTokenize(inputLine, "\t :", tokens);

    // ignore blank lines
    if ( tokens.size() == 0 ) {
      inputFile.getline(buffer,bufSize);
      continue;
    }
    
    // get rate name
    if(tokens[0] == "RateName"){
      newrate = 1;
      ratename =tokens[1];
      inputFile.getline(buffer,bufSize);
      continue;
    }


    // get rate overall ref value (last components of vector ratelineinfo)
    if(newrate && tokens[0] == "RefRateVal"){
      // get ref value and error (separated by +/-)
      std::string val;
      std::string val_err;
      std::string::size_type pos = tokens[1].find("+/-");
      float fval;
      float fval_err;
      if(pos < tokens[1].size()){ // There is value  related error
	val = tokens[1].substr(0,pos);
	val_err = tokens[1].substr(pos+3,tokens[1].size());
	fval = atof(val.c_str());
	fval_err = atof(val_err.c_str());
	refrate[0] = fval;
	refrate[1] = fval_err;
	inputFile.getline(buffer,bufSize);
	continue;
      }
      else
	{
	  std::cerr << "JobConfig::LoadNormFactors:ERROR" << std::endl 
		    << "The sign +/- was not found in " << tokens[3].c_str() << std::endl
		    << "Ref value and error for rate could not be properly retrieved" << std::endl
		    << "Exiting function returning 3" << std::endl;
	  return 3;
	}
    }

    // get tag name
    if(tokens[0] == "EarthLimbCorr"){
      unsigned int nparams=atoi(tokens[1].c_str());
      // read first line with formula
      inputFile.getline(buffer,bufSize);
      // start reading parameters
      for(int unsigned it = 1; it<nparams;it++){
	    // read line and tokenize it
        inputFile.getline(buffer,bufSize);
        std::string inputLine(buffer);
        std::vector <std::string> tokens;
	    facilities::Util::stringTokenize(inputLine, "\t :", tokens);
	    std::string val;
	    std::string val_err;
	    std::string::size_type pos = tokens[1].find("+/-");
	    float fval=0.;
	    float fval_err=0.;
	    if(pos < tokens[1].size()){ // There is value  related error
	  	  val = tokens[1].substr(0,pos);
		  val_err = tokens[1].substr(pos+3,tokens[1].size());
		  fval = atof(val.c_str());
		  fval_err = atof(val_err.c_str());
		  m_EarthLimbCorrFactors[ratename].push_back(fval);
		  }
	    }
      	
      inputFile.getline(buffer,bufSize);
      continue;
    }

    // get tag name
    if(tokens[0] == "LongitudeCorr"){
      unsigned int nparams=atoi(tokens[1].c_str());
      // read first line with formula -- not used
      inputFile.getline(buffer,bufSize);
      // start reading parameters
      for(int unsigned it = 1; it<nparams;it++){
	  // read line and tokenize it
          inputFile.getline(buffer,bufSize);
          std::string inputLine(buffer);
          std::vector <std::string> tokens;
	  facilities::Util::stringTokenize(inputLine, "\t :", tokens);
	  std::string val;
	  std::string val_err;
	  std::string::size_type pos = tokens[1].find("+/-");
	  float fval=0.;
	  float fval_err=0.;
	  if(pos < tokens[1].size()){ // There is value  related error
		val = tokens[1].substr(0,pos);
		val_err = tokens[1].substr(pos+3,tokens[1].size());
		fval = atof(val.c_str());
		fval_err = atof(val_err.c_str());
		m_LongitudeCorr[ratename].push_back(fval);
		}
	  }
      	
      inputFile.getline(buffer,bufSize);
      continue;
    }

    // New rate
    if(ingestdata == 0 && newrate && refrate[0] > -2 && tokens[0] == "Start"){
      ingestdata = 1;
      listofnormfactors.clear(); // prepare for new data ingestion
      inputFile.getline(buffer,bufSize);
      continue;
    }

    if(ingestdata && tokens[0] == "End"){
      // End of info for this rate. 
      
      // Fill map 
      m_NormFactors[ratename] = listofnormfactors;
      
      // initialize stuff for the next event
      newrate = 0;
      ingestdata = 0;
      listofnormfactors.clear();
      ratename = "";
      refrate[0] = -2;
      refrate[1] = -2;
      inputFile.getline(buffer,bufSize);
      continue;
    }

    if(ingestdata)
      {
	if(tokens.size() != 4){
	  std::cerr << "JobConfig::LoadNormFactors:ERROR" << std::endl 
		    << "tokens.size() != 4 when ingesting data " << std::endl
		    << "Normfactor map could not be filled" << std::endl;

	  std::cout << "Line with poblems is the following one: " << std::endl;
	  for(int unsigned it = 0; it<tokens.size();it++){
	    std::cout << tokens[it].c_str() << "\t";
	  }
	  std::cout  << std::endl;
	  std::cout << "Exiting function returning 4" << std::endl;
	  return 4;	  
	}
	
	for(int unsigned it = 0; it<4;it++){
	  tmpval = atof(tokens[it].c_str());
	  ratelineinfo.push_back(tmpval);
	}
	// last components are teh ref rate and error
	ratelineinfo.push_back(refrate[0]);
	ratelineinfo.push_back(refrate[1]);
	
	// fill one event in the list of norm factors
	listofnormfactors.push_back(ratelineinfo);
	
	// clean vector for next event
	ratelineinfo.clear();
      }

    // ok, on to the next line
    inputFile.getline(buffer,bufSize);
  }

  return 0;
}

void JobConfig::PrintNormFactorsMap()
{
  if(m_NormFactors.size()<1)
    return;
  
  std::cout << std::endl << "JobConfig::PrintNormFactorsMap" << std::endl;
  std::cout << "Size of map is " << m_NormFactors.size() << std::endl;

  for(std::map<std::string,std::list<std::vector<float> > >::const_iterator itr=m_NormFactors.begin();
      itr != m_NormFactors.end();itr++){
    
    std::cout << "RateName: " << itr->first.c_str() <<std::endl;
    for(std::list<std::vector<float> > ::const_iterator itr2=itr->second.begin();
      itr2 != itr->second.end();itr2++){
      for(unsigned int icomp = 0; icomp < (*itr2).size();icomp++)
	{
	  std::cout << (*itr2)[icomp] << "\t\t";
	}
      std::cout << std::endl;
    }
    // Done with this rate
    std::cout << std::endl << std::endl;
  }
}
 
