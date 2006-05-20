#!/usr/local/bin/python

"""usage: haddMerge.py chunkFile outFile runId"""

import os
import sys

import reconPM
import timeLog

timeLogger = timeLog.timeLog()

if len(sys.argv) == 4:
    chunkFile, outFileName, runId = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

chunks = reconPM.readLines(chunkFile)
nChunks = len(chunks)

if nChunks > 0:
    workDir, outFileBase = os.path.split(outFileName)
    stageDir = os.path.join(os.environ['reconStageDir'], runId)

    # concat chunk files into final results

    outStage = os.path.join(stageDir, outFileBase)
    print >> sys.stderr, "Combining chunk files into %s" % outStage
    timeLogger()
    rcOut = reconPM.concatenate_hadd(outStage, chunks, 'dummyArg')
    timeLogger()
    if rcOut:
        print >> sys.stderr, "Failed to create file %s!" % outStage
        sys.exit(1)
        pass

    print >> sys.stderr, "Created file %s."  % outStage

# # To enable this, uncomment and change the condition on the "if" to 1
# elif nChunks == 1:
#     print >> sys.stderr, "Only one chunk, moving instead of merging."
#     outStage = chunks[0]

else:
    print >> sys.stderr, "No chunks, shouldn't get here."
    sys.exit(1)
    pass


    
print >> sys.stderr, "Moving file to %s." % outFileName
timeLogger()
status = os.system("%s mv %s %s" % (os.environ['tryAFewTimes'], \
                                    outStage, outFileName))
if status:
    print >> sys.stderr, "Move failed."
    sys.exit(1)
    pass
timeLogger()

print >> sys.stderr, "Removing chunk files..."
for junkFile in chunks:
    try:
        os.unlink(junkFile)
    except OSError:
        print >> sys.stderr, "Can't remove %s" % junkFile
        pass
    pass
timeLogger()


