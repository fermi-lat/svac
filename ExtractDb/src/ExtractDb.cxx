#include <sstream>
#include <algorithm>
#include <time.h>
#include <stdexcept>
#include "ExtractDb.h"
#include "TPad.h"
#include "TROOT.h"
#include "ToString.h"
#include "ToNumber.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

ExtractDb::ExtractDb() : m_rootF(0), m_tree(0),
			 m_db("slac_tcp", "GLAST_CAL", "9square#")
{
    // initialize ROOT if not already done
  if(gROOT == 0) {
    static TROOT gRoot("RootAnalyzer", "RootAnalyzer");
  }

  assert(sizeof(unsigned int) == 4);
  assert(sizeof(double) == 8);
}

ExtractDb::~ExtractDb() 
{
  TDirectory* saveDir = gDirectory;

  if(m_rootF) {
    m_rootF->cd();
    m_rootF->Write(0, TObject::kOverwrite);
    m_rootF->Close();
  }

  saveDir->cd();

  // note since root will automatically deletes newly created object such as
  // histograms and trees, we don't delete them manually
}

void ExtractDb::makeRootTree()
{
  m_tree = new TTree("hk", "house keeping data");

  m_tree->Branch("time", &(m_ntuple.m_time), "time/i");
  m_tree->Branch("name", (char*) (m_ntuple.m_name), "name/C");
  m_tree->Branch("value", &(m_ntuple.m_value), "value/D");
}

void ExtractDb::fillRootTree()
{
  string sql("select v.usecs, d.Mnem, length(d.Mnem), v.value from v2HkVALfields v, v2HkTLMfields d where d.Id = v.IdTLM and v.usecs > ");
  sql += ToString(m_startTime);
  sql += " and v.usecs < ";
  sql += ToString(m_endTime);
  sql += " and (";

  for(vector<string>::const_iterator itr = m_hkVars.begin(); 
      itr != m_hkVars.end(); ++itr) {
    sql += " d.Mnem = '";
    sql += *itr;
    sql += "' or ";
  }

  // get rid of final "or" in the query string
  sql = sql.substr(0, sql.length()-4);
  sql += ')';

  cout << sql << endl;

  try {
    OCIStmt* stmtH = m_db.prepareStatement(sql.c_str());

    m_db.defineUIntByPos(stmtH, &(m_ntuple.m_time), 1);
    m_db.defineStringByPos(stmtH, (char*) (m_ntuple.m_name), 
			   m_ntuple.MAXLEN, 2);
    int len;
    m_db.defineIntByPos(stmtH, &len, 3);
    m_db.defineDoubleByPos(stmtH, &(m_ntuple.m_value), 4);

    m_db.executeStatement(stmtH, 0);

    while(m_db.fetchNextRow(stmtH)) {
      m_ntuple.m_name[len] = '\0';
      //  m_ntuple.print();
      m_tree->Fill();
    }
  }
  catch(OCIException& e) {
    cout << e.what() << endl;
  }
}

void ExtractDb::parseOptionFile(const char* f)
{
  ifstream optF(f);
  string line;

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  string temp;
  parseLine(temp, line);
  m_rootF = new TFile(temp.c_str(), "RECREATE");
  if(m_rootF->IsZombie()) {
    throw std::runtime_error("output root file can not be openned");
  }
  cout << "output root file: " << temp << endl;

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(temp, line);
  m_startTime = ToULong(temp);
  cout << "start time of house keeping data to be extracted " << ctime((time_t*) (&m_startTime)) << endl;

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(temp, line);
  m_endTime = ToULong(temp);
  cout << "end time of house keeping data to be extracted " << ctime((time_t*) (&m_endTime)) << endl;

  while( getline(optF, line) ) {
    if(skipLine(line)) continue;
    parseLine(temp, line);   
    m_hkVars.push_back(temp);
  }
}

void ExtractDb::parseLine(vector<string>& strs, const string& line)
{
  std::istringstream stream(line);
  string temp;
  while(stream >> temp) {
    strs.push_back(temp);
  }
}

void ExtractDb::parseLine(string& str, const string& line)
{
  std::istringstream stream(line);
  stream >> str;
}

bool ExtractDb::skipLine(const string& line)
{
  //skip a blank line
  std::istringstream stream(line);
  bool blank = true;
  string temp;
  while(stream >> temp) {
    blank = false;
  }

  if(blank) return true;

  // skip a comment line
  if(line.size() >= 2 && line[0] == '/' && line[1] == '/') {
    return true;
  }
  else {
    return false;
  }
}
