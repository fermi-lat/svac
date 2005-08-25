import math
import sys

def getFileChunks(fileName, treeName='Digi', maxNumEventsPerFile=1500):

    from ROOT import TFile, TTree, TChain

    file = TFile(fileName)
    tree = file.Get(treeName)

    numEntries = tree.GetEntries()

    numChunks = math.ceil(float(numEntries) / maxNumEventsPerFile)
    numEventsPerFile = int(math.ceil(float(numEntries) / numChunks))
    print >> sys.stderr, "Run has %d events." % numEntries
    print >> sys.stderr, "Using %d chunks." % numChunks
    print >> sys.stderr, "Reduced chunk size from %d to %d" % (maxNumEventsPerFile, numEventsPerFile)

    eventStart=0
    eventEnd=-1
    numSeq=0
    chunks = []

    while 1:

        numSeq += 1
        eventEnd += numEventsPerFile
    
        if eventStart+numEventsPerFile >= numEntries: break
        chunks.append([eventStart, eventEnd])
        eventStart = eventEnd + 1

    eventEnd = min(numEntries,eventEnd)
    chunks.append([eventStart, eventEnd])

        
    return chunks


def concatenateFiles(outputFileName, fileNames, treeName):

    from ROOT import TChain, gSystem
    
    c = TChain(treeName)

    for name in fileNames:
        print >> sys.stderr, "Adding [%s] " % name
        c.Add(name)
        pass
    
    numChainEntries = c.GetEntries()
    print >> sys.stderr, 'numChainEntries = ', numChainEntries


    gSystem.Load('libpipelineDatasets.so')


    from ROOT import pruneTuple

    pt = pruneTuple(c,outputFileName)

    # we don't really care if this succeeds or not...
    junk = pt.copyHeader(fileNames[0])

    retCode = pt.prune()

    #print >> sys.stderr, outputFileName, ' created\n'

    return retCode

def submitBatch(shellName):

    return
