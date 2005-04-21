"""
@brief A small class to wrap the row access to a ROOT TTree.
@author J. Chiang <jchiang@slac.stanford.edu>
"""
# $Header$
#

import ROOT

class TTreeWrapper(object):
    """
    Wrap the row access to an ntuple-like TTree.
    """
    def __init__(self, tree, file=None):
        if file is not None:
            # assume we are being passed a tree name and file name
            self.rootfile = ROOT.TFile(file)
            self.tree = self.rootfile.Get(tree)
        else:
            # assume we have a TTree
            self.tree = tree
        self.nrows = int(self.tree.GetEntries())
        names = []
        leaves = self.tree.GetListOfLeaves()
        for item in leaves:
            names.append(item.GetName())
            self.names = tuple(names)
    def __getitem__(self, row):
        result = self.tree.GetEntry(row)
        if result <= 0:
            raise StopIteration
        return self.tree
    def leaves(self):
        return self.names
    def has_leaf(self, value):
        return value in self.names
    def __len__(self):
        return self.nrows
    def __getattr__(self, attrname):
        return getattr(self.tree, attrname)

if __name__ == '__main__':
    import time
    import sys
    sys.path.insert(0, '../svac_scripts/v0/python')
    from svac_analysis import RootNTuple

    infile = '140001338_svac.root'
    tree = 'Output'

# Some timing studies.

    start = time.clock()
    svac = TTreeWrapper(infile, tree)

# fill a list
    x = []  
    for item in svac:
        x.append(item.Event_ID)
    print time.clock() - start

# one could also use a list comprehension
#    x = [item.Event_ID for item in svac]


# RootNTuple using hippo is faster

    start = time.clock()

    nt = RootNTuple(infile, tree)

    x = nt.getColumn('Event_ID')

    print time.clock() - start
