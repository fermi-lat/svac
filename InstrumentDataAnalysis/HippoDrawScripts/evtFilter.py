import ROOT

def evtFilter(merit_file, digi_file, tcut, outfile):
    meritfile = ROOT.TFile(merit_file)
    merit = meritfile.Get("MeritTuple")

    if merit is None:  # assume it is an SVAC ntuple
        merit = meritfile.Get("Output")
    if merit is None:  # otherwise throw exception
        raise RuntimeError, ("Input file appears not to be a " +
                             "merit or svac ntuple.")
    
    digifile = ROOT.TFile(digi_file)
    for treename in ("Digi", "Mc", "Recon", "MeritTuple", "Output"):
        digi = digifile.Get(treename)
        if digi is not None:
            break

    my_cut = ROOT.TCut(tcut)
    merit.Draw(">>eList", my_cut)
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

if __name__ == '__main__':
    from TTreeWrapper import TTreeWrapper
    evtFilter('merit.root', 'merit.root', 'Event_ID < 50', 'foo.root')

    newfile = ROOT.TFile('foo.root')
    newtree = newfile.Get('MeritTuple')

    foo = TTreeWrapper(newtree)

    for item in foo:
        print item.Event_ID, item.McEnergy
