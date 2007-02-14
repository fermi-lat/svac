import math
import sys
import os


def writeLines(fileName, lines):
    fp = open(fileName, 'w')
    fp.writelines((line + '\n' for line in lines))
    pass

def readLines(fileName):
    lines = [line.strip() for line in open(fileName).readlines()]
    return lines


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
    print >> sys.stderr, "Reduced chunk size from %d to %d" % \
          (maxNumEventsPerFile, numEventsPerFile)

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

        
    return chunks, numEventsPerFile


def concatenate_prune(outputFileName, fileNames, treeName, expectedEntries):

    from ROOT import TChain, gSystem
    
    c = TChain(treeName)
    c.SetMaxTreeSize(500000000000)

    print >> sys.stderr, "Expect %d entries." % expectedEntries

    for name in fileNames:
        print >> sys.stderr, "Adding [%s] " % name
        addCode = c.Add(name, 0)
        if not addCode: # TChain.Add returns 1 for success, 0 for failure
            return 1
        pass
    
    numChainEntries = c.GetEntries()
    print >> sys.stderr, 'numChainEntries = ', numChainEntries
    if numChainEntries != expectedEntries:
        print >> sys.stderr, "Bad # entries after chain creation."
        return 1

    gSystem.Load('libpipelineDatasets.so')


    from ROOT import pruneTuple

    print >> sys.stderr, "Merging..."

    pt = pruneTuple(c, outputFileName)

    # we don't really care if this succeeds or not...
    junk = pt.copyHeader(fileNames[0])

    retCode = pt.prune()

    numChainEntries = getFileEvents(outputFileName, treeName)
    print >> sys.stderr, 'numChainEntries = ', numChainEntries
    if numChainEntries != expectedEntries:
        print >> sys.stderr, "Bad # entries after merge."
        return 1

    #print >> sys.stderr, outputFileName, ' created\n'

    return retCode

def concatenate_hadd(outputFileName, fileNames, \
                     treeName=None, expectedEntries=None):

    fmt = 'LD_LIBRARY_PATH=%s ROOTSYS=%s %s -f %s' % \
          (os.environ['haddLib'], os.environ['haddSys'], \
           os.environ['hadd'], outputFileName)
    fmt += ' %s' * len(fileNames)
    cmd = fmt % tuple(fileNames)
    print >> sys.stderr, 'About to run [%s]' % cmd
    retCode = os.system(cmd)
    return retCode

concatenateFiles = concatenate_hadd

def reserveSize(digiFile, numEventsPerFile):
    # This is (about) the size of the output files for one chunk.
    chunkSize = 1.1e4 * numEventsPerFile
    digiSize = os.stat(digiFile).st_size
    size = digiSize + chunkSize
    # this should give GB, with one digit past the decimal.
    size = math.ceil(size / 1e8) / 10.0
    size = '%.1f' % size
    return size

def submitBatch(shellName):

    return
