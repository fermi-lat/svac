#!/afs/slac/g/glast/isoc/flightOps/rhel3_gcc32/ISOC_PROD/bin/shisoc python2.5

"""@brief Boilerplate

@author W. Focke <focke@slac.stanford.edu>
"""

import os
import sys
import traceback

import config

import GPLinit

import fileNames
import pipeline
import registerPrep
import stageFiles
import variables


moduleTable = {
    # 'processName': ('moduleName', 'functionName', ['cleanupName']),
    # no entry required if process, module, func are the same and no cleanup
    'acdPedsAlarm': ('alarmHandler', 'alarmHandler'),
    'acdPedsLogger': ('alarmLogger', 'alarmLogger'),
    'calGainsAlarm': ('alarmHandler', 'alarmHandler'),
    'calGainsLogger': ('alarmLogger', 'alarmLogger'),
    'calPedsAlarm': ('alarmHandler', 'alarmHandler'),
    'calPedsLogger': ('alarmLogger', 'alarmLogger'),
    'calHist': ('runStrip', 'runStrip'),
    'calHistAlarm': ('alarmHandler', 'alarmHandler'),
    'calHistLogger': ('alarmLogger', 'alarmLogger'),
    'calTrend': ('runStrip', 'runStrip'),
    'diffRspFT1': ('diffRsp', 'diffRsp'),
    'digitization': ('digitize', 'digitize'),
    'digitizationLci': ('digitize', 'digitize'),
    'digiHist': ('runStrip', 'runStrip'),
    'digiHistAlarm': ('alarmHandler', 'alarmHandler'),
    'digiHistLci': ('runStrip', 'runStrip'),
    'digiHistLogger': ('alarmLogger', 'alarmLogger'),
    'digiTrend': ('runStrip', 'runStrip'),
    'digiTrendAlarm': ('alarmHandler', 'alarmHandler'),
    'digiTrendLogger': ('alarmLogger', 'alarmLogger'),
    'electronMerit': ('filterMerit', 'electronMerit'),
    'fastMonErrorAlarm': ('alarmHandler', 'alarmHandler'),
    'fastMonErrorLogger': ('alarmLogger', 'alarmLogger'),
    'fastMonHist': ('fastMon', 'fastMon'),
    'fastMonHistAlarm': ('alarmHandler', 'alarmHandler'),
    'fastMonHistLogger': ('alarmLogger', 'alarmLogger'),
    'fastMonHistLci': ('fastMon', 'fastMon'),
    'fastMonTrend': ('runStrip', 'runStrip'),
    'fastMonTrendAlarm': ('alarmHandler', 'alarmHandler'),
    'fastMonTrendLogger': ('alarmLogger', 'alarmLogger'),
    'fastMonTuple': ('fastMon', 'fastMon'),
    'fastMonTupleLci': ('fastMon', 'fastMon'),
    'findChunks': ('findChunks', 'findChunks', 'cleanup'),
    'findChunksLci': ('findChunks', 'findChunks', 'cleanup'),
    'makeLS1': ('makeFT1', 'makeFT1'),
    'mergeCalCrumbs': ('mergeStuff', 'merge'),
    'mergeCalChunks': ('mergeStuff', 'merge'),
    'mergeCalTrend': ('mergeStuff', 'merge'),
    'mergeFastMonError': ('mergeStuff', 'merge'),
    'mergeFastMonErrorLci': ('mergeStuff', 'merge'),
    'mergeFastMonHist': ('mergeStuff', 'merge'),
    'mergeFastMonHistLci': ('mergeStuff', 'merge'),
    'mergeFastMonTrend': ('mergeStuff', 'merge'),
    'mergeFastMonTuple': ('mergeStuff', 'merge'),
    'mergeFastMonTupleLci': ('mergeStuff', 'merge'),
    'mergeFT1': ('mergeStuff', 'merge'),
    'mergeDigi': ('mergeStuff', 'merge'),
    'mergeDigiLci': ('mergeStuff', 'merge'),
    'mergeDigiHist': ('mergeStuff', 'merge'),
    'mergeDigiHistLci': ('mergeStuff', 'merge'),
    'mergeDigiTrend': ('mergeStuff', 'merge'),
    'mergeGcrCrumbs': ('mergeStuff', 'merge'),
    'mergeGcrChunks': ('mergeStuff', 'merge'),
    'mergeMeritCrumbs': ('mergeStuff', 'merge'),
    'mergeMeritChunks': ('mergeStuff', 'merge'),
    'mergeMeritTrend': ('mergeStuff', 'merge'),
    'mergeReconCrumbs': ('mergeStuff', 'merge'),
    'mergeReconChunks': ('mergeStuff', 'merge'),
    'mergeReconHist': ('mergeStuff', 'merge'),
    'mergeReconTrend': ('mergeStuff', 'merge'),
    'mergeSvacChunks': ('mergeStuff', 'merge'),
    'mergeTkrAnalysis': ('mergeStuff', 'merge'),
    'meritHist': ('runStrip', 'runStrip'),
    'meritHistAlarm': ('alarmHandler', 'alarmHandler'),
    'meritHistLogger': ('alarmLogger', 'alarmLogger'),
    'meritTrend': ('runStrip', 'runStrip'),
    'meritTrendAlarm': ('alarmHandler', 'alarmHandler'),
    'meritTrendLogger': ('alarmLogger', 'alarmLogger'),
    'reconHist': ('runStrip', 'runStrip'),
    'reconHistAlarm': ('alarmHandler', 'alarmHandler'),
    'reconHistLogger': ('alarmLogger', 'alarmLogger'),
    'reconTrend': ('runStrip', 'runStrip'),
    'reconTrendAlarm': ('alarmHandler', 'alarmHandler'),
    'reconTrendLogger': ('alarmLogger', 'alarmLogger'),
    'svacTuple': ('makeSvac', 'svacTuple'),
    'tkrAnalysis': ('tkrRootAnalysis', 'tkrAnalysis'),
    'tkrTrend': ('runStrip', 'runStrip'),
    'tkrTrendAlarm': ('alarmHandler', 'alarmHandler'),
    'tkrTrendLogger': ('alarmLogger', 'alarmLogger'),
    'verifyErrorAlarm': ('alarmHandler', 'alarmHandler'),
    'verifyErrorLogger': ('alarmLogger', 'alarmLogger'),
    'verifyErrorAlarmComp': ('alarmHandler', 'alarmHandler'),
    'verifyErrorLoggerComp': ('alarmLogger', 'alarmLogger'),
    'verifyFt1ErrorAlarm': ('alarmHandler', 'alarmHandler'),
    'verifyFt1ErrorLogger': ('alarmLogger', 'alarmLogger'),
    'verifyFt2ErrorAlarm': ('alarmHandler', 'alarmHandler'),
    'verifyFt2ErrorLogger': ('alarmLogger', 'alarmLogger'),
    'verifyMeritErrorAlarm': ('alarmHandler', 'alarmHandler'),
    'verifyMeritErrorLogger': ('alarmLogger', 'alarmLogger'),
    }

def getFuncs(procName):
    names = moduleTable.get(procName) or (procName, procName)
    modName, mainFunc = names[:2]
    module = __import__(modName)
    function = getattr(module, mainFunc)
    if len(names) > 2:
        clName = names[2]
        cleanupFunc = getattr(module, clName)
    else:
        cleanupFunc = None
        pass
    return function, cleanupFunc


def tryToCall(func, *args, **kwargs):
    print >> sys.stderr, 'About to run %s with args %s, %s' % (func, args, kwargs)
    try:
        status = func(*args, **kwargs)
    except:
        print >> sys.stderr, 'Failed!'
        traceback.print_exc()
        status = 1
        pass
    return status


def finalize(status, args, staged, cleanupFunc=None):
    args['status'] = status
    if cleanupFunc is not None: status |= cleanupFunc(**args)
    
    if status:
        finishOption = 'wipe'
    else:
        finishOption = config.finishOption
        pass
    status |= staged.finish(finishOption)
    
    sys.exit(status)
    return


def main():
    status = 0

    procName = pipeline.getProcess()
    # this crashes without cleanup if the module won't compile
    function, cleanupFunc = getFuncs(procName)

    head, dlId = os.path.split(os.environ['DOWNLINK_RAWDIR'])
    if not dlId: head, dlId = os.path.split(head)
    runId = os.environ.get('RUNID')
    chunkId = os.environ.get('CHUNK_ID')
    crumbId = os.environ.get('CRUMB_ID')
    idArgs = (dlId, runId, chunkId, crumbId)

    idPath = '.'.join((arg for arg in idArgs if arg is not None))

    if runId is None:
        level = 'downlink'
    elif chunkId is None:
        level = 'run'
    elif crumbId is None:
        level = 'chunk'
    else:
        level = 'crumb'
        pass

    for idArg in idArgs[::-1]:
        if idArg is not None:
            piId = idArg
            break
        continue
    pipeline.setVariable('L1_PI_ID', piId)
    piVersion = int(os.environ['PIPELINE_PROCESSINSTANCE'])
    pipeline.setVariable('L1_PI_version', piVersion)

    staged = stageFiles.StageSet(excludeIn=config.excludeIn)
    workDir = staged.stageDir

    runDir = fileNames.fileName(None, dlId, runId)

    files = {}
    args = {}

    inFileTList = os.environ.get('inFileTypes')
    if inFileTList is not None:
        inFileTypes = inFileTList.split(os.sep)
    else:
        inFileTypes = []
        pass
    for fileType in inFileTypes:
        realFile = fileNames.fileName(fileType, *idArgs)
        try:
            files[fileType] = staged.stageIn(realFile)
        except IOError:
            status |= 1
            finalize(status, args, staged, cleanupFunc)
            pass
        continue

    outFileTList = os.environ.get('outFileTypes')
    if outFileTList is not None:
        outFileTypes = outFileTList.split(os.sep)
    else:
        outFileTypes = []
        pass
    for fileType in outFileTypes:
        try:
            version = int(variables.getVar(fileType, 'ver'))
            next = True
        except KeyError:
            version = piVersion
            next = False
            pass
        realFile = fileNames.fileName(fileType, next=next, version=version, *idArgs)
        files[fileType] = staged.stageOut(realFile)
        registerPrep.prep(fileType, realFile)
        continue

    args = {
        'files': files,
        'idArgs': idArgs,
        'idPath': idPath,
        'inFileTypes': inFileTypes,
        'level': level,
        'outFileTypes': outFileTypes,
        'piId': piId,
        'piVersion': piVersion,
        'procName': procName,
        'runDir': runDir,
        'staged': staged,
        'workDir': workDir,
        }

    status |= tryToCall(function, **args)
    print >> sys.stderr, 'Status = %s' % status
    
    finalize(status, args, staged, cleanupFunc)

    return status

if __name__ == '__main__':
    status = main()
    sys.exit(status)

