#ifndef ExtractDb_Class
#define ExtractDb_Class

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include "TFile.h"
#include "TTree.h"
#include "NtupleDef.h"
#include "OCIWrapper.h"

/**
 * \class ExtractDb
 * \brief ExtractDb extract housekeepinh data from oracle database
 * \author Xin Chen
 */

class ExtractDb {
 public:

  ExtractDb();
  ~ExtractDb();

  void parseOptionFile(const char* f);

  void makeRootTree();

  void fillRootTree();

 private:


  /// skip both empty lines and comment lines
  bool skipLine(const std::string& line);

  /// parse a line using space as delimiter, pass out a vector of strings
  void parseLine(std::vector<std::string>& strs, const std::string& line);

  /// assuming there is only one string in the line, this function strips off
  /// preceding and tailing blank spaces
  void parseLine(std::string& str, const std::string& line);

  /// parse time in a string formatted as: YYYY-MM-DD-HH:MI:SS, return UTC time
  time_t parseStrTime(const char* str) const;

  /// time range of house keeping data to be extracted
  time_t m_startTime;
  time_t m_endTime;

  /// list of variables to be extracted
  std::vector<std::string> m_hkVars;

  /// name of output root file
  TFile* m_rootF;

  /// source id used in the query
  std::string m_sourceId;

  /// name of output root tree
  TTree* m_tree;

  /// C structure used to fill the tree
  NtupleDef m_ntuple;

  OCIWrapper m_db;
};

#endif
