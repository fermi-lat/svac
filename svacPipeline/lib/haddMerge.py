#!/usr/local/bin/python

"""usage: haddMerge.py chunkFile stageList runId"""

import os
import sys

import reconPM
import timeLog

timeLogger = timeLog.timeLog()

if len(sys.argv) == 4:
    chunkFile, stageList, runId = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

chunks = reconPM.readLines(chunkFile)
nChunks = len(chunks)

if nChunks > 0:
    stageDir = os.path.join(os.environ['reconStageDir'], runId)

    # concat chunk files into final results

    # stageFile is the merged root file in the staging area.
    # stageList is a text file containing the name of the merged file.
    outStage = os.path.join(stageDir, 'mergedTuple.root')

    print >> sys.stderr, "Combining chunk files into %s" % outStage
    timeLogger()
    rcOut = reconPM.concatenate_hadd(outStage, chunks)
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

reconPM.writeLines(stageList, [outStage])
