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
    def applyCut(self, tcut, infile, outfile,
                 validTrees=("Digi", "Mc", "Recon", "MeritTuple", "Output")):
        digifile = ROOT.TFile(infile)
        for treename in validTrees:
            digi = digifile.Get(treename)
            if digi is not None:
                break
        if digi is None:
            raise RuntimeError, "Valid tree not found in " + infile

        my_cut = ROOT.TCut(tcut)
        self.tree.Draw(">>eList", my_cut)
        evtList = ROOT.gDirectory.Get("eList")

        newfile = ROOT.TFile(outfile, "recreate")
        newtree = digi.CloneTree(0)

        nentries = evtList.GetN()
        for i in xrange(nentries):
            j = evtList.GetEntry(i)
            digi.GetEntry(j)
            newtree.Fill()

        newtree.Write()
        newfile.Write()
        newfile.Close()
        return TTreeWrapper(treename, outfile)
    def __len__(self):
        return self.nrows
    def __getattr__(self, attrname):
        return getattr(self.tree, attrname)

if __name__ == '__main__':
    import time
    from svac_analysis import RootNTuple

#    infile = '140001338_svac.root'
#    tree = 'Output'
    infile = "merit.root"
    tree = "MeritTuple"

# Some timing studies.
    start = time.clock()
    svac = TTreeWrapper(tree, infile)

# fill a list
    x = []  
    for item in svac:
        x.append(item.Event_ID)
    print "cpu time to fill a list using pyRoot: ", time.clock() - start

# one could also use a list comprehension
#    x = [item.Event_ID for item in svac]

# RootNTuple using hippo is faster for large data sets
    start = time.clock()
    nt = RootNTuple(infile, tree)
    x = nt.getColumn('Event_ID')
    print "cpu time using hippo: ", time.clock() - start

# Apply a filter:
    foo = svac.applyCut("Event_ID < 50", infile, 'foo.root')

    print "Some output after applying the cut 'Event_ID < 50': "
    for item in foo:
        print item.Event_ID, item.EvtEnergySumOpt
