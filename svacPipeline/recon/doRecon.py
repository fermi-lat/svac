#!/usr/local/bin/python

"""usage: doRecon.py chunkJobs taskName runId"""

import os
import sys

import reconPM
import runMany
import timeLog

timeLogger = timeLog.timeLog()

if len(sys.argv) == 4:
    chunkJobs, taskName, runId = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

# If we ran before and some chunks failed, there should be a file containing
# a list of the bad chunks.  If so, use it for input instead of the original
# file listing all chunks.  Due to the ephemeral nature of this file, it cannot
# be registered with pipeline I.  I've given it a name that looks like a
# registered dataset, but really it could be anything, since it is only used
# by this script.
workDir, jobBase = os.path.split(chunkJobs)
badChunkBase = '%s_%s_badChunks_text.txt' % (taskName, runId)
badChunkFile = os.path.join(workDir, badChunkBase)
if os.path.exists(badChunkFile) and \
   os.stat(badChunkFile).st_size > 0:
    chunkFile = badChunkFile
else:
    chunkFile = chunkJobs
    pass

print >> sys.stderr, "Reading chunk jobs from %s" % chunkFile
jobs = reconPM.readLines(chunkFile)

if len(jobs) == 0:
    print >> sys.stderr, "No chunks jobs to run."
    sys.exit(1)
    pass

# run the chunks
os.system("date")
timeLogger()
results = runMany.pollManyResult(os.system, [(x,) for x in jobs])
os.system("date")
timeLogger()
print >> sys.stderr, "rc from batch jobs ", results

# should check rc here to see if all went well.
# ditto on rc's for final success/fail report back to pipeline
status = 0
badJobs = []
for iJob, rc in enumerate(results):
    status |= rc
    if rc:
        print >> sys.stderr, "Command [%s] failed!" % jobs[iJob]
        badJobs.append(jobs[iJob])
        pass
    pass

reconPM.writeLines(badChunkFile, badJobs)

if status:
    print >> sys.stderr, "Job failed."
    sys.exit(1)
    pass

timeLogger()

