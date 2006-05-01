import math
import sys
import os


def getFileEvents(fileName, treeName='Digi'):

    from ROOT import TFile, TTree, TChain

    file = TFile(fileName)
    tree = file.Get(treeName)

    numEntries = tree.GetEntries()

    return numEntries


def getFileChunks(fileName, treeName='Digi', maxNumEventsPerFile=1500):

    numEntries = getFileEvents(fileName, treeName)

    if numEntries <= 0:
        raise ValueError, "Digi file %s is empty!" % fileName

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


def concatenate_prune(outputFileName, fileNames, treeName):

    from ROOT import TChain, gSystem
    
    c = TChain(treeName)
    c.SetMaxTreeSize(500000000000)

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

def concatenate_hadd(outputFileName, fileNames, treeName):

    fmt = '${SVAC_GLAST_EXT}/ROOT/v4.02.00/root/bin/hadd -f %s' % outputFileName
    fmt += ' %s' * len(fileNames)
    cmd = fmt % tuple(fileNames)

    retCode = os.system(cmd)

    return retCode

concatenateFiles = concatenate_hadd

def reserveSize(digiFile):
    # This is (about) the size of the output files for one chunk.
    chunkSize = 1.1e8
    digiSize = os.stat(digiFile).st_size
    size = digiSize + chunkSize
    # this should give GB, with one digit past the decimal.
    size = math.ceil(size / 1e8) / 10.0
    size = '%.1f' % size
    return size

def submitBatch(shellName):

    return
