#!/nfs/farm/g/glast/u05/GLAST_EXT/rh9_gcc32opt/python/2.5.1/bin/python2.5
#!/usr/local/bin/python

"""usage: setupRecon.py digiFile chunkJobs reconChunks meritChunks calChunks keepers junkDirs task runId"""

import math
import os
import re
import shutil
import sys

#print >> sys.stderr, "Exiting to prevent recon of giant ETE1a muon run."
#sys.exit(1)

import ROOT

import chunkSize
import eLogDB
import geometry
import reconPM
import timeLog

print >> sys.stderr, "%s: svacPlRoot=[%s]" % \
      (sys.argv[0], os.environ['svacPlRoot'])

timeLogger = timeLog.timeLog()

ROOT.gSystem.Load('libcommonRootData.so')
ROOT.gSystem.Load('libdigiRootData.so')
ROOT.gSystem.Load('libreconRootData.so')

if len(sys.argv) == 10:
    digiFileName, \
        chunkJobs, reconChunks, meritChunks, calChunks, keepers, junkDirs, \
        task, runId \
        = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

shellFile = os.environ['reconOneScript']

workDir, chunkJobBase = os.path.split(chunkJobs)
#workDir = os.getcwd()
#stageDir = os.environ['reconStageDir']
stageDir = os.path.join(os.environ['reconStageDir'], runId)
os.environ['runStageDir'] = stageDir
if not os.path.isdir(stageDir):
    print >> sys.stderr, 'Making dir [%s]' % stageDir
    os.makedirs(stageDir)
    pass

# put .htaccess file in working directory to prevent HTTP downloads of 
# ROOT files
shutil.copyfile(os.environ['htAccess'], os.path.join(workDir, '.htaccess'))

# make an empty badChunks file (it will be ignored) so we don't run into
# problems from junk left over from previous runs of this run.
workDir, jobBase = os.path.split(chunkJobs)
badChunkBase = '%s_%s_badChunks_text.txt' % (task, runId)
badChunkFile = os.path.join(workDir, badChunkBase)
open(badChunkFile, 'w')

inDir = '$inDir'
procDir = '$procDir'

digiBase = os.path.basename(digiFileName)
digiWorkFile = os.path.join(inDir, digiBase)


numEventsPerFile = chunkSize.chunkSize(runId)
#print >> sys.stderr, "Particle type is %s, using chunk size %s." % (particleType, numEventsPerFile)

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
    print >> sys.stderr, "This run has %d towers, using geometry file %s." % \
          (nTwr, geoFile)
    pass

joHead = \
"""#include "$GLEAMROOT/src/jobOptions/pipeline/readigi_runrecon.txt"
CalibDataSvc.CalibInstrumentName = "%(instrumentType)s";
GlastDetSvc.xmlfile = "%(geoFile)s";
digiRootReaderAlg.digiRootFileList = { "%(digiRootFile)s" };
GlastDetSvc.xmlfile = "$(XMLGEODBSROOT)/xml/latAssembly/latAssemblySegVols.xml";
NtupleMaker.Members = {"AnalysisNtupleAlg","ClassifyAlg","FT1Alg","ObfCoordsAlg"};
AcdCalibSvc.FlavorHighRange     = "ideal";
AcdCalibSvc.FlavorCoherentNoise = "ideal";
GcrReconAlg.HFC_Or_TriggerEng4 = "HFC";
""" % \
{
    'instrumentType': instrumentType,
    'geoFile': geoFile,
    'digiRootFile': digiWorkFile,
    }
# figure out particle type
particleType = eLogDB.query(runId, 'particletype')
if particleType == 'Photons':
    joHead += '#include "$LATINTEGRATIONROOT/src/jobOptions/pipeline/VDG.txt"\n'
    pass

testName = eLogDB.query(runId, 'TESTNAME')
calibFlavors = {'LAT-71x': 'vanilla-muongain'}
for test, flavor in calibFlavors.items():
    if re.search(test, testName):
        joHead += 'CalibDataSvc.CalibFlavorList += {"vanilla-muongain"};\nCalCalibSvc.DefaultFlavor = "vanilla";\nCalCalibSvc.DefaultFlavor = "%s";\n' % flavor
        #joHead += 'TkrCalibSvc.DefaultFlavor = "%s";\n' % flavor
        pass
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
resStr = '-R "scratch > %s && %s"' % (scratchSize, os.environ['chunkArch'])

jobs = []
joFiles = []
reconFiles = []
meritFiles = []
calFiles = []
logFiles = []
directories = []
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
    directories.append(chunkStage)

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

    # use exec so we don't have nChunk shells sitting around waiting for
    # bsub to complete, but we still get the convenience of os.system
    # instead of the fiddliness of os.spawn*
    cmd = 'exec bsub -K -q %s -G %s %s -o %s %s %s %s %s' % \
          (os.environ['chunkQueue'], os.environ['batchgroup'], resStr, \
           logFile, shellFile, joFile, digiFileName, chunkStage)
    print >> sys.stderr, "Prparing command [%s]" % cmd
    jobs.append(cmd)
    pass
directories.append(stageDir)

# Now we have to write out a bunch of lists.

reconPM.writeLines(chunkJobs, jobs)

reconPM.writeLines(reconChunks, reconFiles)
reconPM.writeLines(meritChunks, meritFiles)
reconPM.writeLines(calChunks, calFiles)

keepFiles = logFiles + joFiles
reconPM.writeLines(keepers, keepFiles)

reconPM.writeLines(junkDirs, directories)

