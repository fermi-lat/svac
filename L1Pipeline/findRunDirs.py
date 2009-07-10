#!/afs/slac/g/glast/isoc/flightOps/rhel3_gcc32/ISOC_PROD/bin/shisoc --add-env=flightops python2.5

"""@brief Find new run directories.

@author W. Focke <focke@slac.stanford.edu>
"""

import os
import re
import sys
import time

import config

import GPLinit

import chunkTester
import fileNames
import finders
import glastTime
import lsf
import pipeline
import runner
import stageFiles


dlRawDir = os.environ['DOWNLINK_RAWDIR']

# VERYBAD!  Or maybe not.  Embrace it.
head, dlId = os.path.split(os.environ['DOWNLINK_RAWDIR'])
if not dlId: head, dlId = os.path.split(head)

staged = stageFiles.StageSet(excludeIn=config.excludeIn)

runDirs = finders.findRunDirs(dlRawDir)
dataRuns = set(runDirs)
print >> sys.stderr, "Presumed runs:[%s]" % dataRuns

print >> sys.stderr, 'Reading evt headers ...'
startTs = time.time()
chunkKeys = []
chunkLists = {}
for runId, runData in runDirs.items():
    print >> sys.stderr, runId
    runDir = runData['runDir']
    chunkListData = finders.findChunkFiles(runDir)
    print >> sys.stderr, chunkListData
    for chunk in chunkListData.values():
        print >> sys.stderr, chunk
        chunk['headerData'] = chunkTester.readHeader(chunk['chunkFile'])
        continue
    chunkKeys.extend((runId, chunkId) for chunkId in chunkListData)
    chunkLists[runId] = chunkListData
    continue
stopTs = time.time()
delta = stopTs - startTs
print >> sys.stderr, '%s s' % delta

hostLists = lsf.balance(chunkKeys)

for (runId, chunkId), hostList in hostLists:
    chunkLists[runId][chunkId]['hostList'] = hostList
    continue

for runId, chunkListData in chunkLists.items():
    realChunkList = fileNames.fileName('chunkList', dlId, runId)
    # temporarily mangle chunk list name to get around JIRA LONE-67    
    mangledChunkList = fileNames.mangleChunkList(realChunkList)
    stagedChunkList = staged.stageOut(mangledChunkList)
    fileNames.writeList(chunkListData, stagedChunkList)
    continue

runStatuses = dict.fromkeys(dataRuns, config.defaultRunStatus)

# the name of this file is a contract with the halfpipe
retireFile = os.path.join(dlRawDir, 'retired_runs_%s.txt' % dlId)
try:
    retireeStatus = dict(line.split() for line in open(retireFile))
except IOError:
    print >> sys.stderr, "Couldn't open run status file %s, all runs will have default status %s" % (retireFile, config.defaultRunStatus)
    retireeStatus = {}
    pass
retirees = set(retireeStatus)

print >> sys.stderr, "Retiring runs:[%s]" % retirees

runStatuses.update(retireeStatus)

oldRuns = retirees - dataRuns

print >> sys.stderr, "Old runs:[%s]" % oldRuns

# bogus placeholder start and stop times
# Should get from acqsummary DB table
# findChunks does so, and overrides these values for chunks and registration
# makeFT1 looks in ACQSUMMARY
tStartDef = 100000001.0
tStopDef = 300000001.0
start = {}
stop = {}
boundaryFile = os.path.join(dlRawDir, 'event_times_%s.txt' % dlId)
try:
    lines = open(boundaryFile)
except IOError:
    print >> sys.stderr, "Couldn't open run boundary file %s" % boundaryFile
    lines = []
    pass
for line in lines:
    runId, tStart, tStop = line.strip().split()
    start[runId] = glastTime.met(float(tStart))
    stop[runId] = glastTime.met(float(tStop))
    continue

# parse run type
deliveredEvents = {}
heldBackEvents = {}
dataSource = {}
# the name of this file is a contract with the halfpipe
deliveredFile = os.path.join(dlRawDir, 'delivered_events_%s.txt' % dlId)
try:
    dfp = open(deliveredFile)
    for line in dfp:
        runId, delivered, heldBack, source = line.split()
        deliveredEvents[runId] = int(delivered)
        heldBackEvents[runId] = int(heldBack)
        dataSource[runId] = source
        continue
    dfp.close()
except IOError:
    print >> sys.stderr, "Couldn't open delivered event file %s, all runs will have default dataSource %s" % (deliveredFile, config.defaultDataSource)
    pass

# get MOOT keys
mootFile = os.path.join(dlRawDir, 'moot_keys_%s.txt' % dlId)
try:
    mootLines = [line.split() for line in open(mootFile)]
except IOError:
    print >> sys.stderr, "Couldn't open moot mey file %s, all runs will have default key %s, alias %s" % (deliveredFile, config.defaultMootKey, config.defaultMootAlias)
    pass
mootKeys = dict((line[0], line[1]) for line in mootLines)
mootAliases = dict((line[0], line[2]) for line in mootLines)

runNumRe = re.compile('([0-9]+)')
# create up a subStream for each run
for runId in dataRuns | oldRuns:
    source = dataSource.get(runId, config.defaultDataSource)

    mop = runNumRe.search(runId)
    if mop:
        nStr = mop.group(1)
    else:
        print >> sys.stderr, 'runId %s is malformed.' % runId
        nStr = runId[1:]
        pass
    runNumber = '%d' % int(nStr)
    stream = runNumber

    runStatus = runStatuses[runId]
    if runStatus == "INCOMPLETE" and runId in dataRuns:
        newStatus = "WAITING"
        print >> sys.stderr, "%s has data, but status is %s, changing it to %s" % (runId, runStatus, newStatus)
        runStatus = newStatus
        pass
    
    subTask = config.runSubTask[runStatus][source]

    try:
        tStart = start[runId]
        tStop = stop[runId]
    except KeyError:
        tStart = tStartDef
        tStop = tStopDef
        print >> sys.stderr, "Couldn't get tStart, tStop for run %s, using bogus values" % runId
        pass

    mootKey = mootKeys.get(runId, config.defaultMootKey)
    mootAlias = mootAliases.get(runId, config.defaultMootAlias)
    
    args = "RUNID=%(runId)s,runNumber=%(runNumber)s,RUNSTATUS=%(runStatus)s,hpTStart=%(tStart).17g,hpTStop=%(tStop).17g,DATASOURCE=%(source)s,mootKey=%(mootKey)s,mootAlias=%(mootAlias)s" % locals()
    print >> sys.stderr, \
          "Creating stream [%s] of subtask [%s] with args [%s]" % \
          (stream, subTask, args)
    pipeline.createSubStream(subTask, stream, args)
    continue

fileNames.preMakeDirs(dataRuns, dlId)

staged.finish()
