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
stageDir = os.environ['reconStageDir']

# figure out particle type
particleType = eLogDB.query(runId, 'particletype')

numEventsPerFile = chunkSize.chunkSize(particleType)
print >> sys.stderr, "Particle type is %s, using chunk size %s." % (particleType, numEventsPerFile)

treeName = 'Digi'
chunks = reconPM.getFileChunks(digiFileName, treeName, numEventsPerFile)

print >> sys.stderr, chunks

# figure out instrument type, # of towers
tkrSerNos = eLogDB.parseSerNo(eLogDB.query(runId, 'tkr_ser_no'))
calSerNos = eLogDB.parseSerNo(eLogDB.query(runId, 'cal_ser_no'))

nTwr = max(len(tkrSerNos), len(calSerNos))

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

if re.search('grid', schemaFile, re.IGNORECASE):
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
    instrumentType = ''
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
    'digiRootFile': digiFileName,
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

    reconFile = '%s_%s_%s_RECON.root' % (task, runId, cTag)
    reconFile = os.path.join(stageDir, reconFile)
    reconFiles.append(reconFile)
    joData += 'reconRootWriterAlg.reconRootFile = "%s";\n' % reconFile
    
    meritFile = '%s_%s_%s_merit.root' % (task, runId, cTag)
    meritFile = os.path.join(stageDir, meritFile)
    meritFiles.append(meritFile)
    joData += 'RootTupleSvc.filename = "%s";\n' % meritFile

    calFile = '%s_%s_%s_calTuple.root' % (task, runId, cTag)
    calFile = os.path.join(stageDir, calFile)
    calFiles.append(calFile)
    joData += 'CalXtalRecAlg.tupleFilename = "%s";\n' % calFile

    logFile = '%s_%s_%s.log' % (task, runId, cTag)
    logFiles.append(logFile)
    logFile = os.path.join(workDir, logFile)
    
    open(joFile, 'w').write(joData)

    # use exec so we don't have nChunk shells sitting around waiting for bsub to complete
    # but we still get the convenience of os.system instead of the fiddliness of os.spawn*
    cmd = 'exec bsub -K -q %s -G %s -o %s %s %s' % \
          (os.environ['chunkQueue'], os.environ['batchgroup'], \
           logFile, shellFile, joFile)
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
print >> sys.stderr, "Combining cal files into %s" % calFileName
timeLogger()
#rcCal = reconPM.concatenateFiles(calFileName, calFiles, 'CalXtalRecTuple')
rcCal = reconPM.concatenateFiles(calFileName, calFiles, 'CalTuple')
timeLogger()
if rcCal:
    print >> sys.stderr, "Failed to create cal file %s!" % calFileName
    sys.exit(1)
else:
    print >> sys.stderr, "Created cal file %s."  % calFileName
    pass

print >> sys.stderr, "Combining merit files into %s" % meritFileName
timeLogger()
rcMerit = reconPM.concatenateFiles(meritFileName, meritFiles, 'MeritTuple')
timeLogger()
if rcMerit:
    print >> sys.stderr, "Failed to create merit file %s!" % meritFileName
    sys.exit(1)
else:
    print >> sys.stderr, "Created merit file %s."  % meritFileName
    pass

print >> sys.stderr, "Combining recon files into %s" % reconFileName
timeLogger()
rcRecon = reconPM.concatenateFiles(reconFileName, reconFiles, 'Recon')
timeLogger()
if rcRecon:
    print >> sys.stderr, "Failed to create recon file %s!" % reconFileName
    sys.exit(1)
else:
    print >> sys.stderr, "Created recon file %s."  % reconFileName
    pass

# tar up log and JO files
keepFiles = logFiles + joFiles
tfp = tarfile.open(tarFile, mode='w:gz')
for keeper in keepFiles:
    tfp.add(keeper)
    pass
tfp.close()

# get rid of chunk files
trash = reconFiles + meritFiles + calFiles
for junkFile in trash:
    os.unlink(junkFile)
    pass

timeLogger()
