
#include "MonValue_t.h"
#include "TTree.h"
#include "TTreeResult.h"
#include "TTreeRow.h"
#include <iostream>

const std::vector<std::string> MonValue::queryTree(TTree* tree){
  TTreeResult* res;
  res=(TTreeResult*)tree->Query(m_formula.c_str(),m_cut.c_str(),"",tree->GetEntriesFast()-1);
  std::vector<std::string> rv;
  if(res){
    TTreeRow* obj=(TTreeRow*)res->Next();
    while (obj){
      rv.push_back(std::string(obj->GetField(0)));
      obj->Delete();
      obj=(TTreeRow*)res->Next();
    }
  }
  return rv;
}
