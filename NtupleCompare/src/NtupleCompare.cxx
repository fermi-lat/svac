#include <sstream>
#include <algorithm>
#include "NtupleCompare.h"
#include "TPad.h"
#include "TROOT.h"
#include "ToString.h"
#include "ToNumber.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"
#include "NR.h"

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

NtupleCompare::NtupleCompare()
{
    // initialize ROOT if not already done
  if(gROOT == 0) {
    static TROOT gRoot("RootAnalyzer", "RootAnalyzer");
  }

  m_meritChain1 = new TChain("MeritTuple");
  m_meritChain2 = new TChain("MeritTuple");
  m_svacChain1 = new TChain("Output");
  m_svacChain2 = new TChain("Output");
}

NtupleCompare::~NtupleCompare()
{
  // note since root will automatically deletes newly created object such as
  // histograms and trees, we don't delete them manually
}

void NtupleCompare::parseOptionFile(const char* f)
{
  ifstream optF(f);
  string line;

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  string temp;
  parseLine(temp, line);
  m_nEvents = ToInt(temp);
  cout << "no. of events requested to be processed: " << m_nEvents << endl;

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(m_outputDir, line);
  cout << "output dir: " << m_outputDir << endl;

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(m_prefix, line);
  cout << "prefix: " << m_prefix << endl;

  temp = m_outputDir + m_prefix;
  temp += "_report.doxygen";
  cout << "output doxygen file: " << temp << endl;
  m_report.open(temp.c_str());

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(m_meritFiles1, line);

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(m_svacFiles1, line);

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(m_meritFiles2, line);

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(m_svacFiles2, line);

  while( getline(optF, line) ) {
    if(!skipLine(line)) break;
  }
  parseLine(m_variables, line);

  while( getline(optF, line) ) {
    if(skipLine(line)) continue;
    m_cuts.push_back(line);
  }
}

void NtupleCompare::parseLine(vector<string>& strs, const string& line)
{
  std::istringstream stream(line);
  string temp;
  while(stream >> temp) {
    strs.push_back(temp);
  }
}

void NtupleCompare::parseLine(string& str, const string& line)
{
  std::istringstream stream(line);
  stream >> str;
}

bool NtupleCompare::skipLine(const string& line)
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

void NtupleCompare::generateReport()
{
  writeHeader();

  m_report << "@section purpose Purpose" << endl;
  m_report << "This report contains results of K-S tests on variables contained in two sets of merit root files" << endl;

  m_report << "@section summary Summary" << endl;

  m_report << "First set of merit files: " << endl << endl;
  cout << "First set of merit files: " << endl;
  for(vector<string>::const_iterator itr = m_meritFiles1.begin(); 
      itr != m_meritFiles1.end(); ++itr) {
    m_report << "@li " << *itr << endl;
    cout << *itr << endl;
  }
  m_report << endl << "First set of svac files: " << endl << endl;
  cout << "First set of svac files: " << endl;
  for(vector<string>::const_iterator itr = m_svacFiles1.begin(); 
      itr != m_svacFiles1.end(); ++itr) {
    m_report << "@li " << *itr << endl;
    cout << *itr << endl;
  }

  m_report  << endl << "Second set of merit files: " << endl;
  cout << "Second set of merit files: " << endl;
  for(vector<string>::const_iterator itr = m_meritFiles2.begin(); 
      itr != m_meritFiles2.end(); ++itr) {
    m_report << "@li " << *itr << endl;
    cout << *itr << endl;
  }
  m_report << endl << "Second set of svac files: " << endl << endl;
  cout << "Second set of svac files: " << endl;
  for(vector<string>::const_iterator itr = m_svacFiles2.begin(); 
      itr != m_svacFiles2.end(); ++itr) {
    m_report << "@li " << *itr << endl;
    cout << *itr << endl;
  }

  m_report  << endl << "Variables compared: " << endl;
  cout << "Variables compared: " << endl;
  for(vector<string>::const_iterator itr = m_variables.begin(); 
      itr != m_variables.end(); ++itr) {
    m_report << "@li " << *itr << endl;
    cout << *itr << endl;
  }
  m_ksProbs.reserve(m_variables.size());

  m_report << endl << "Cuts: " << endl << endl;
  cout << "Cuts: " << endl;
  for(vector<string>::const_iterator itr = m_cuts.begin(); 
      itr != m_cuts.end(); ++itr) {
    m_report << "@li " << *itr << endl;
    cout << *itr << endl;
  }

  m_report << "@section ksResults Results of KS tests" << endl;
  printKsProbTable(); 

  // produce plots for each compared variables
  int size = m_variables.size();
  for(int i = 0; i != size; ++i) {
    string file(m_prefix);
    file += "_";
    file += m_variables[i];
    convertSpecialCharacter(file);
    PlotAttribute att(file.c_str(), m_variables[i].c_str(), 
		      m_variables[i].c_str(), 0);
    producePlot(m_hists1[i], m_hists2[i], att);
    insertPlot(att);
  }

  writeTail(); 
}

void NtupleCompare::convertSpecialCharacter(string& s) 
{
  int size = s.size();
  for(int i = 0; i != size; ++i) {
    if(s[i] == '.' || s[i] == '[' || s[i] == ']' || s[i] == '*' ||
       s[i] == '(' || s[i] == ')') s[i] = '_';
  }
}

void NtupleCompare::writeHeader()
{
  m_report << "/** @mainpage KS Test Report" << endl
	   << "@htmlonly" << endl
	   << "<center>" << endl
	   << "<a href=\"../latex/refman.ps\"> PS file </a> &nbsp" << endl
	   << "<a href=\"../latex/refman.pdf\"> PDF file </a>" << endl 
	   << "</center>" << endl
	   << "@endhtmlonly" << endl
	   << "@author{automatically generated}" << endl << endl;
}

void NtupleCompare::writeTail()
{
  m_report << "*/" << endl;
}

void NtupleCompare::chainFiles()
{
  for(vector<string>::const_iterator itr = m_meritFiles1.begin();
      itr != m_meritFiles1.end(); ++itr) {
    m_meritChain1->Add(itr->c_str());
  }
  for(vector<string>::const_iterator itr = m_svacFiles1.begin();
      itr != m_svacFiles1.end(); ++itr) {
    m_svacChain1->Add(itr->c_str());
  }
  m_meritChain1->AddFriend(m_svacChain1, 0);

  for(vector<string>::const_iterator itr = m_meritFiles2.begin();
      itr != m_meritFiles2.end(); ++itr) {
    m_meritChain2->Add(itr->c_str());
  }
  for(vector<string>::const_iterator itr = m_svacFiles2.begin();
      itr != m_svacFiles2.end(); ++itr) {
    m_svacChain2->Add(itr->c_str());
  }
  m_meritChain2->AddFriend(m_svacChain2, 0);
}

void NtupleCompare::makeHistograms()
{
  string allCuts("1");
  for(vector<string>::const_iterator itr = m_cuts.begin();
      itr != m_cuts.end(); ++itr) {
    allCuts += " && (";
    allCuts += *itr;
    allCuts += ")";
  }

  for(vector<string>::const_iterator itr = m_variables.begin();
      itr != m_variables.end(); ++itr) {

    TCanvas c1;
    string name1(*itr);
    name1 += "_1";
    string draw(*itr);
    draw += ">>";
    draw += "htemp";
    m_meritChain1->Draw(draw.c_str(), allCuts.c_str(), "", m_nEvents);
    int nEvent1 = (int) m_meritChain1->GetSelectedRows();
    Double_t* start1 = m_meritChain1->GetV1();
    vector<float> x1(start1, start1+nEvent1);

    TH1F* h1 = (TH1F*) gPad->GetPrimitive("htemp");
    h1->SetName(name1.c_str());
    h1->SetXTitle(itr->c_str());
    m_hists1.push_back(h1);

    string name2(*itr);
    name2 += "_2";
    draw = *itr;
    draw += ">>";
    draw += "htemp";
    m_meritChain2->Draw(draw.c_str(), allCuts.c_str(), "", m_nEvents);
    int nEvent2 = (int) m_meritChain2->GetSelectedRows();
    Double_t* start2 = m_meritChain2->GetV1();
    vector<float> x2(start2, start2+nEvent2);

    TH1F* h2 = (TH1F*) gPad->GetPrimitive("htemp");
    h2->SetName(name2.c_str());
    h2->SetXTitle(itr->c_str());
    m_hists2.push_back(h2);

    doKsTest(x1, x2);

    // normalize two histograms
    int norm = std::min(nEvent1, nEvent2);
    
    h1->Sumw2();
    h2->Sumw2();
    if(norm < nEvent2) {
      h2->Scale(norm/double(nEvent2));
    }
    else if(norm < nEvent1){
      h1->Scale(norm/double(nEvent1));
    }
    
  }
}

void NtupleCompare::compareVariables()
{
  chainFiles();

  makeHistograms();
}

void NtupleCompare::doKsTest(vector<float>& x1, vector<float>& x2)
{
  float d, prob;
  NR::kstwo(&x1[0], x1.size(), &x2[0], x2.size(), &d, &prob);

  m_ksProbs.push_back(prob);
}

void NtupleCompare::printKsProbTable()
{
  int nRow = m_variables.size() + 1;
  int nCol = 2;
  string table[nRow][nCol];

  table[0][0] = "Variable";
  table[0][1] = "KS Probability";
  for(int i = 1; i != nRow; ++i) {
    table[i][0] = m_variables[i-1];
    table[i][1] = ToString(m_ksProbs[i-1]);
  }

  TableDef t((string*) table, "Probabilities produced by the KS tests. Probability much less than 0.5 means two distributions are incompatible", "ksProbTable", nRow, nCol);

  printHtmlTable(t);
  printLatexTable(t);
}

void NtupleCompare::printHtmlTable(const TableDef& r)
{
  m_report << endl << "@htmlonly" << endl;
  m_report << "<table border=\"1\" width=\"100%\">" << endl;
  m_report << "<caption> " << r.m_caption << " </caption>" << endl;

  for(int i = 0; i != r.m_nRow; ++i) {
    m_report << "  <tr>" << endl;
    for(int j = 0; j != r.m_nCol; ++j) {
      m_report << "    <td> " << r.m_table[i*r.m_nCol+j] 
		  << " </td>" << endl;
    }
    m_report << "  </tr>" << endl;
  }

  m_report << "</table>" << endl;
  m_report << "@endhtmlonly" << endl << endl;
}

void NtupleCompare::printLatexTable(const TableDef& r)
{
  m_report << endl << "@latexonly" << endl;
  m_report << "\\begin{table}[h]" << endl;
  m_report << "\\begin{center}" << endl;
  m_report << "\\caption{" << r.m_caption << "}" << endl;
  m_report << "\\label{" << r.m_label << "}" << endl;

  m_report << "\\begin{tabular}{";
  for(int i = 0; i != r.m_nCol; ++i) {
    m_report << "|c";
  }
  m_report << "|} \\hline" << endl;

  for(int i = 0; i != r.m_nRow; ++i) {
    for(int j = 0; j != r.m_nCol-1; ++j) {
      m_report << r.m_table[i*r.m_nCol+j] << " & ";
    }
    m_report << r.m_table[(i+1)*r.m_nCol-1] << " \\\\ \\hline" << endl;
  }

  m_report << "\\end{tabular}" << endl;
  m_report << "\\end{center}" << endl;
  m_report << "\\end{table}" << endl;
  m_report << "@endlatexonly" << endl << endl;
}

void NtupleCompare::producePlot(TH1F* h1, TH1F* h2, const PlotAttribute& att)
{
  TCanvas c1("c1", "produce eps file", att.m_xPixel, att.m_yPixel);
  gPad->SetBorderMode(0);
  gPad->SetFillColor(10);

  //set to default values
  gStyle->SetTitleH();
  gStyle->SetTitleW();
  gStyle->SetTitleFontSize();
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.16);
  gStyle->SetPalette();

  if(att.m_yLog) gPad->SetLogy();

  h1->SetMarkerStyle(kFullCircle); 
  h1->SetMarkerColor(1);
  h1->Draw();
  h2->SetMarkerStyle(kFullTriangleUp); 
  h2->SetMarkerColor(2);
  h2->Draw("SAME");

  string epsFile(m_outputDir);
  epsFile += "/";
  epsFile += att.m_file;
  epsFile += ".eps";

  c1.SaveAs(epsFile.c_str());

  // ROOT can not produce gif file in the batch mode
  // run pstopnm and ppmtogif to produce gif file

  string pwd = gSystem->WorkingDirectory();
  gSystem->cd(m_outputDir.c_str());

  string cmd1("pstopnm -ppm -xborder 0 -yborder 0 -portrait -nocrop -xsize ");
  cmd1 += ToString(att.m_xPixel);
  cmd1 += " -ysize ";
  cmd1 += ToString(att.m_yPixel);
  cmd1 += " ";
  epsFile = att.m_file;
  epsFile += ".eps";
  cmd1 += epsFile;
  gSystem->Exec(cmd1.c_str());

  string ppmFile(epsFile);
  ppmFile += "001.ppm";
  string gifFile(att.m_file);
  gifFile += ".gif";

  string cmd2("ppmtogif ");
  cmd2 += ppmFile;
  cmd2 += " > ";
  cmd2 += gifFile;
  gSystem->Exec(cmd2.c_str());

  gSystem->cd(pwd.c_str());
}

void NtupleCompare::insertPlot(const PlotAttribute& att)
{
  string gifFile(att.m_file);
  gifFile += ".gif";

  m_report << "@htmlonly <div align=\"center\"> <p><strong>"
	      << att.m_caption << "</strong></p> <img src=\"../" 
	      << gifFile << "\" alt=\"../" << gifFile 
	      << "\"> </div> @endhtmlonly" << endl;
 
  string epsFile(att.m_file);
  epsFile += ".eps";

  m_report << "@image latex " << epsFile << " \"" << att.m_caption << "\" "
	   << "height=" << att.m_height << "cm" << ",width=" 
	   << att.m_width << "cm " << endl << endl;
}
