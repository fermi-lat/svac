#!/usr/local/bin/python

"""usage: mergeRecon.py reconChunks digiFile reconStageList runId"""

import os
import sys

import ROOT

import reconPM
import timeLog

print >> sys.stderr, "%s: svacPlRoot=[%s]" % \
      (sys.argv[0], os.environ['svacPlRoot'])

timeLogger = timeLog.timeLog()

ROOT.gSystem.Load('libcommonRootData.so')
ROOT.gSystem.Load('libdigiRootData.so')
ROOT.gSystem.Load('libreconRootData.so')

if len(sys.argv) == 5:
    reconChunks, digiFile, reconStageList, runId = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

reconFiles = reconPM.readLines(reconChunks)
nChunks = len(reconFiles)

if nChunks > 0:
    stageDir = os.path.join(os.environ['reconStageDir'], runId)
    
    # concat chunk files into final results

    # reconStageFile is the merged RECON.root file in the staging area.
    # reconStageList is a text file containing the name of the merged file.
    reconStageFile = os.path.join(stageDir, 'RECON.root')

    expectedEntries = reconPM.getFileEvents(digiFile)
    
    print >> sys.stderr, "Combining recon files into %s" % reconStageFile
    timeLogger()
    rcRecon = reconPM.concatenate_prune(reconStageFile, reconFiles, 'Recon', \
                                        expectedEntries)
    timeLogger()
    if rcRecon:
        print >> sys.stderr, "Failed to create recon file %s!" % reconStageFile
        sys.exit(1)
        pass

    print >> sys.stderr, "Created recon file %s."  % reconStageFile

# # To enable this, uncomment and change the condition on the "if" to 1
# elif nChunks == 1:
#     print >> sys.stderr, "Only one chunk, moving instead of merging."
#     reconStageFile = reconFiles[0]

else:
    print >> sys.stderr, "No chunks, shouldn't get here."
    sys.exit(1)
    pass

reconPM.writeLines(reconStageList, [reconStageFile])
