#ifndef NtupleCompare_Class
#define NtupleCompare_Class

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TChain.h"
#include "TH1F.h"

/**
 * \class NtupleCompare
 * \brief NtupleCompare compare specified vriables in two merit ntuple files
 * \author Xin Chen
 */

class NtupleCompare {
 public:

  NtupleCompare();
  ~NtupleCompare();

  void parseOptionFile(const char* f);

  void compareVariables();

  void generateReport();

 private:

  struct PlotAttribute {
    PlotAttribute::PlotAttribute(const char* file=0, const char* caption=0,
				 const char* label=0, bool yLog=0,
				 float height=10, float width=15, int x=606,
				 int y=410) : 
      m_file(file), m_caption(caption), m_label(label), m_yLog(yLog),
	 m_height(height), m_width(width), m_xPixel(x), m_yPixel(y)
    { 
      m_nColor = 6;
      m_colors[0] = 4; 
      m_colors[1] = 6;
      m_colors[2] = 7;
      m_colors[3] = 5;
      m_colors[4] = 3;
      m_colors[5] = 2;
    }

    void set(const char* file=0, const char* caption=0, const char* label=0, 
	     bool yLog=0, float height=10, float width=15, int x=606, 
	     int y=410)
    {
      m_file = file;
      m_caption = caption;
      m_label = label;
      m_yLog = yLog;
      m_height = height;
      m_width = width;
      m_xPixel = x;
      m_yPixel = y;
      m_nColor = 6;
    }

    /// name of file to be produced, note file type such as ".eps" is not
    /// included 
    const char* m_file;  
    const char* m_caption;
    const char* m_label;
    bool m_yLog;

    /// height and width of a plot in latex
    float m_height;
    float m_width;

    /// height and width in pixel for a gif plot on web
    int m_xPixel, m_yPixel;

    enum PlotType {COLZ, LEGO};
    PlotType m_2dPlotType;

    /// colors used to make a palette for drawing 2D histogram using colz
    int m_nColor;
    int m_colors[6];
  };

  struct TableDef {
    TableDef::TableDef() { }
    TableDef::TableDef(const std::string* table, const char* caption, 
		       const char* label, int nRow, int nCol) :
      m_table(table), m_caption(caption), m_label(label), m_nRow(nRow), 
	 m_nCol(nCol) { }

    const std::string* m_table;
    const char* m_caption;
    const char* m_label;
    int m_nRow;
    int m_nCol;
  };

  /// print table in html format
  void printHtmlTable(const TableDef& r);

  /// print table in latex format
  void printLatexTable(const TableDef& r);

  /// produce a eps file where two compared 1D histograms are superimposed
  void producePlot(TH1F* h1, TH1F* h2, const PlotAttribute& att);

  /// replace special characters in s such as '.' '[' ']' to '_'
  /// since gif and eps file names are produced using ntuple variable names,
  /// there could be special characters which either linux or doxygen or latex
  /// does not like 
  void convertSpecialCharacter(std::string& s);

  /// insert a plot to both latex and html files
  void insertPlot(const PlotAttribute& att);

  /// chain two sets of merit ntuple files
  void chainFiles();

  /// make histograms to be compared
  void makeHistograms();

  /// do ks tests on two sets of histograms
  void doKsTest(std::vector<float>& x1, std::vector<float>& x2);

  /// print results of KS tests
  void printKsProbTable();

  /// skip both empty lines and comment lines
  bool skipLine(const std::string& line);

  void writeHeader();
  void writeTail();

  /// parse a line using space as delimiter, pass out a vector of strings
  void parseLine(std::vector<std::string>& strs, const std::string& line);

  /// assuming there is only one string in the line, this function strips off
  /// preceding and tailing blank spaces
  void parseLine(std::string& str, const std::string& line);

  /// 2 vectors of merit ntuple files to be compared
  std::vector<std::string> m_meritFiles1;
  std::vector<std::string> m_svacFiles1;
  std::vector<std::string> m_meritFiles2;
  std::vector<std::string> m_svacFiles2;

  /// chains of ntuple files to be compared
  TChain* m_meritChain1;
  TChain* m_svacChain1;
  TChain* m_meritChain2;
  TChain* m_svacChain2;

  /// 2 sets of histograms to be compared
  std::vector<TH1F*> m_hists1;
  std::vector<TH1F*> m_hists2;
 
  /// variables to be compared
  std::vector<std::string> m_variables;

  /// cuts to be applied
  std::vector<std::string> m_cuts;

  /// output directory where result ps file occurs
  std::string m_outputDir;

  /// prefix of output file
  std::string m_prefix;

  /// output latex report file
  std::ofstream m_report; 

  /// probabilities from KS tests
  std::vector<double> m_ksProbs;

  /// no. of events requested to be processed, note if the requested number is 
  /// more than no. of events in the root files, only process all events
  /// in the root files of course
  int m_nEvents;
};

#endif
