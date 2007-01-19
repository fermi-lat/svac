#include "MonDataFiller.h"

#include "TTree.h"

// Attach to a TTree for input
Bool_t MonDataFiller::attachInput(TTree& tree) {

  // turn on needed branches
  for ( std::set<std::string>::const_iterator itr = m_readBranches.begin();
	itr != m_readBranches.end(); itr++ ) {
    tree.SetBranchStatus(itr->c_str(),1);
  }

  return kTRUE;
}

void MonDataFiller::addChild(MonDataFiller& child) { 
  std::map<std::string,MonDataFiller*>::const_iterator itrFind = m_childMap.find(child.name());
  if ( itrFind != m_childMap.end() ) {
    return;
  }
  m_children.push_back(&child);
  m_childMap[child.name()] = &child;
  m_vals.addVal(child.vals());
}

