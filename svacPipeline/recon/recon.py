#!/usr/local/bin/python

"""usage: recon.py digiFile reconFile meritFile tarFile task runId"""

import math
import os
import re
import sys
import tarfile

import ROOT

import chunkSize
import eLogDB
import geometry
import reconPM
import runMany
import timeLog

timeLogger = timeLog.timeLog()

ROOT.gSystem.Load('libcommonRootData.so')
ROOT.gSystem.Load('libdigiRootData.so')
ROOT.gSystem.Load('libreconRootData.so')

if len(sys.argv) == 8:
    digiFileName, reconFileName, meritFileName, calFileName, tarFile, task, runId = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

shellFile = os.environ['reconOneScript']

workDir, reconFileBase = os.path.split(reconFileName)
#stageDir = os.environ['reconStageDir']
stageDir = os.path.join(os.environ['reconStageDir'], runId)
os.environ['runStageDir'] = stageDir
if not os.path.isdir(stageDir):
    print >> sys.stderr, 'Making dir [%s]' % stageDir
    os.makedirs(stageDir)
    pass

inDir = '$inDir'
procDir = '$procDir'

digiBase = os.path.basename(digiFileName)
digiWorkFile = os.path.join(inDir, digiBase)

# figure out particle type
particleType = eLogDB.query(runId, 'particletype')

numEventsPerFile = chunkSize.chunkSize(particleType)
print >> sys.stderr, "Particle type is %s, using chunk size %s." % (particleType, numEventsPerFile)

treeName = 'Digi'
chunks, numEventsPerFile = \
        reconPM.getFileChunks(digiFileName, treeName, numEventsPerFile)

print >> sys.stderr, chunks

# figure out instrument type, # of towers
tkrSerNos = eLogDB.parseSerNo(eLogDB.query(runId, 'tkr_ser_no'))
calSerNos = eLogDB.parseSerNo(eLogDB.query(runId, 'cal_ser_no'))
dbTwr = int(eLogDB.query(runId, 'NoOfTowers'))

nTwr = max(len(tkrSerNos), len(calSerNos), dbTwr)

if tkrSerNos:
    firstTkr = tkrSerNos[0][0]
    hasTkr = True
else:
    hasTkr = False
    pass
if calSerNos:
    firstCal = calSerNos[0][0]
    hasCal = True
else:
    hasCal = False
    pass

if (hasTkr and re.search('Mini', firstTkr)) or (hasCal and re.search('EM2|Mini', firstCal)):
    em = True
else:
    em = False
    pass

schemaFile = eLogDB.query(runId, 'SCHEMACONFIGFILE')

tkrOnly = False
calOnly = False

fullLatRe = 'grid|lat'
if re.search(fullLatRe, schemaFile, re.IGNORECASE):
    instrumentType = 'LAT'
elif em:
    instrumentType = 'EM'
elif hasTkr and not hasCal:
    instrumentType = firstTkr
    tkrOnly = True
elif hasCal and not hasTkr:
    instrumentType = 'Cal' + firstCal
    calOnly = True
elif hasTkr and hasCal:
    # if we get here, there should be exactly one each of TKR and CAL
    instrumentType = firstTkr + ':Cal' + firstCal
else:
    instrumentType = 'LAT'
    pass

# figure out the geometry
if em:
    geoFile = '$(XMLGEODBSROOT)/xml/em2/em2SegVols.xml'
else:
    geoFile = geometry.geometries[nTwr]
    pass
if not geoFile:
    print >> sys.stderr, "No geometry for %d towers!" % nTwr
    sys.exit(1)
else:
    print >> sys.stderr, "This run has %d towers, using geometry file %s." % (nTwr, geoFile)
    pass

joHead = \
"""#include "$LATINTEGRATIONROOT/src/jobOptions/pipeline/readigi_runrecon.txt"
CalibDataSvc.CalibInstrumentName = "%(instrumentType)s";
GlastDetSvc.xmlfile = "%(geoFile)s";
digiRootReaderAlg.digiRootFile = "%(digiRootFile)s";
""" % \
{
    'instrumentType': instrumentType,
    'geoFile': geoFile,
    'digiRootFile': digiWorkFile,
    }
if particleType == 'Photons':
    joHead += '#include "$LATINTEGRATIONROOT/src/jobOptions/pipeline/VDG.txt"\n'
    pass

# Deal with hardware that we don't expect to have calibrations for.
# Gleam/EM will ask for calibrations for TKR and CAL even if one is absent.
# Set TKR and CAL to ideal if we have EM hardware
if tkrOnly or em:
    # Set CAL to ideal if it is absent.
    joHead += 'CalCalibSvc.DefaultFlavor = "ideal";\n'
if calOnly or em:
    # set TKR to ideal if it is absent.
    joHead += 'TkrCalibAlg.calibFlavor = "ideal";\n'
    pass


# make a nice printf-style format for printing ranges of event numbers sortably
lastEvent = chunks[-1][-1]
lastEvent = max(lastEvent, 2)
nDigits = int(math.ceil(math.log10(lastEvent)))
oneFormat = '%0.' + `nDigits` + 'd'
cFormat = oneFormat + '-' + oneFormat

# Make a resource requirement string to make sure the LSF hosts have enough scratch space
scratchSize = reconPM.reserveSize(digiFileName, numEventsPerFile)
resStr = '-R "scratch > %s"' % scratchSize

jobs = []
joFiles = []
reconFiles = []
meritFiles = []
calFiles = []
logFiles = []
for iChunk, chunk in enumerate(chunks):
    # edit template JO file and add lines for first
    # event index and # events.

    first, last = chunk

    cTag = cFormat % (first, last)

    chunkStage = os.path.join(stageDir, cTag)
    if not os.path.isdir(chunkStage):
        print >> sys.stderr, 'Making dir [%s]' % chunkStage
        os.makedirs(chunkStage)
        pass    

    joFile = '%s_%s_%s_text.jobOpt' % (task, runId, cTag)
    joFiles.append(joFile)
    joFile = os.path.join(workDir, joFile)

    numEvents = last - first + 1
    joEvents = \
"""RootIoSvc.StartingIndex = %d;
ApplicationMgr.EvtMax = %d;
""" % \
    (first, numEvents)
    joData = joHead + joEvents

    reconChunkBase = '%s_%s_%s_RECON.root' % (task, runId, cTag)
    reconProcFile = os.path.join(procDir, reconChunkBase)
    reconFile = os.path.join(chunkStage, reconChunkBase)
    reconFiles.append(reconFile)
    joData += 'reconRootWriterAlg.reconRootFile = "%s";\n' % reconProcFile
    
    meritChunkBase = '%s_%s_%s_merit.root' % (task, runId, cTag)
    meritProcFile = os.path.join(procDir, meritChunkBase)
    meritFile = os.path.join(chunkStage, meritChunkBase)
    meritFiles.append(meritFile)
    joData += 'RootTupleSvc.filename = "%s";\n' % meritProcFile

    calChunkBase = '%s_%s_%s_calTuple.root' % (task, runId, cTag)
    calProcFile = os.path.join(procDir, calChunkBase)
    calFile = os.path.join(chunkStage, calChunkBase)
    calFiles.append(calFile)
    joData += 'CalTupleAlg.tupleFilename = "%s";\n' % calProcFile

    logFile = '%s_%s_%s.log' % (task, runId, cTag)
    logFiles.append(logFile)
    logFile = os.path.join(workDir, logFile)
    
    open(joFile, 'w').write(joData)

    # use exec so we don't have nChunk shells sitting around waiting for bsub to complete
    # but we still get the convenience of os.system instead of the fiddliness of os.spawn*
    cmd = 'exec bsub -K -q %s -G %s %s -o %s %s %s %s %s' % \
          (os.environ['chunkQueue'], os.environ['batchgroup'], resStr, \
           logFile, shellFile, joFile, digiFileName, chunkStage)
    print >> sys.stderr, cmd
    jobs.append(cmd)

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
for iJob, rc in enumerate(results):
    status |= rc
    if rc:
        print >> sys.stderr, "Command [%s] failed!" % jobs[iJob]
        pass
    pass
if status:
    print >> sys.stderr, "Job failed."
    sys.exit(1)
    pass

# concat chunk files into final results

reconStage = os.path.join(stageDir, reconFileBase)
print >> sys.stderr, "Combining recon files into %s" % reconStage
timeLogger()
rcRecon = reconPM.concatenate_prune(reconStage, reconFiles, 'Recon')
timeLogger()
if rcRecon:
    print >> sys.stderr, "Failed to create recon file %s!" % reconStage
    sys.exit(1)
else:
    print >> sys.stderr, "Created recon file %s."  % reconStage
    print >> sys.stderr, "Moving recon file to %s." % reconFileName
    timeLogger()
    status = os.system("mv %s %s" % (reconStage, reconFileName))
    if status:
        print >> sys.stderr, "Move failed."
        sys.exit(1)
        pass
    timeLogger()
    pass

calBase = os.path.basename(calFileName)
calStage = os.path.join(stageDir, calBase)
print >> sys.stderr, "Combining cal files into %s" % calStage
timeLogger()
#rcCal = reconPM.concatenateFiles(calStage, calFiles, 'CalXtalRecTuple')
rcCal = reconPM.concatenate_hadd(calStage, calFiles, 'CalTuple')
timeLogger()
if rcCal:
    print >> sys.stderr, "Failed to create cal file %s!" % calStage
    sys.exit(1)
else:
    print >> sys.stderr, "Created cal file %s."  % calStage
    print >> sys.stderr, "Moving cal file to %s." % calFileName
    timeLogger()
    status = os.system("mv %s %s" % (calStage, calFileName))
    if status:
        print >> sys.stderr, "Move failed."
        sys.exit(1)
        pass
    timeLogger()
    pass

meritBase = os.path.basename(meritFileName)
meritStage = os.path.join(stageDir, meritBase)
print >> sys.stderr, "Combining merit files into %s" % meritStage
timeLogger()
rcMerit = reconPM.concatenate_hadd(meritStage, meritFiles, 'MeritTuple')
timeLogger()
if rcMerit:
    print >> sys.stderr, "Failed to create merit file %s!" % meritStage
    sys.exit(1)
else:
    print >> sys.stderr, "Created merit file %s."  % meritStage
    print >> sys.stderr, "Moving merit file to %s." % meritFileName
    timeLogger()
    status = os.system("mv %s %s" % (meritStage, meritFileName))
    if status:
        print >> sys.stderr, "Move failed."
        sys.exit(1)
        pass
    timeLogger()
    pass

# tar up log and JO files
keepFiles = logFiles + joFiles
tfp = tarfile.open(tarFile, mode='w:gz')
for keeper in keepFiles:
    try:
        tfp.add(keeper)
    except OSError:
        print >> sys.stderr, "Log file %s missing!" % keeper
        pass
    pass
tfp.close()

# get rid of chunk files
trash = reconFiles + meritFiles + calFiles
for junkFile in trash:
    os.unlink(junkFile)
    pass
# and the staging directory
# (if it's not empty, something is wrong)
os.rmdir(stageDir)

timeLogger()
