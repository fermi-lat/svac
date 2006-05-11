#!/usr/local/bin/python

"""usage: mergeRecon.py reconChunks reconFile runId"""

import os
import sys

import ROOT

import reconPM
import timeLog

timeLogger = timeLog.timeLog()

ROOT.gSystem.Load('libcommonRootData.so')
ROOT.gSystem.Load('libdigiRootData.so')
ROOT.gSystem.Load('libreconRootData.so')

if len(sys.argv) == 4:
    reconChunks, reconFileName, runId = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

reconFiles = reconPM.readLines(reconChunks)

workDir, reconFileBase = os.path.split(reconFileName)
stageDir = os.path.join(os.environ['reconStageDir'], runId)

# concat chunk files into final results

reconStage = os.path.join(stageDir, reconFileBase)
print >> sys.stderr, "Combining recon files into %s" % reconStage
timeLogger()
rcRecon = reconPM.concatenate_prune(reconStage, reconFiles, 'Recon')
timeLogger()
if rcRecon:
    print >> sys.stderr, "Failed to create recon file %s!" % reconStage
    sys.exit(1)
    pass

print >> sys.stderr, "Created recon file %s."  % reconStage
print >> sys.stderr, "Moving recon file to %s." % reconFileName
timeLogger()
status = os.system("mv %s %s" % (reconStage, reconFileName))
if status:
    print >> sys.stderr, "Move failed."
    sys.exit(1)
    pass
timeLogger()

print >> sys.stderr, "Removing chunk files..."
for junkFile in reconFiles:
    try:
        os.unlink(junkFile)
    except OSError:
        print >> sys.stderr, "Can't remove %s" % junkFile
        pass
    pass
timeLogger()


