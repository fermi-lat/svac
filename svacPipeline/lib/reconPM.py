def getFileChunks(fileName, treeName='Digi', numEventsPerFile=1500):

    from ROOT import TFile, TTree, TChain

    file = TFile(fileName)
    tree = file.Get(treeName)

    numEntries = tree.GetEntries()

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


def concatenateFiles(outputFileName, fileKind, treeName):

    from ROOT import TChain, gSystem
    
    c = TChain(treeName)
    c.Add('*'+fileKind+'*')

    numChainEntries = c.GetEntries()
    print 'numChainEntries = ', numChainEntries


    gSystem.Load('/u/ey/richard/GLAST/Pipeline/parallel/pipelineDatasets/v0/rh9_gcc32/libpipelineDatasets.so')


    from ROOT import pruneTuple

    pt = pruneTuple(c,outputFileName)
    retCode = pt.prune()

    #print outputFileName, ' created\n'

    return retCode

def submitBatch(shellName):

    return
