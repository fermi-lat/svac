#!usr/local/bin/python

"""usage: recon.py digiFile reconFile meritFile tarFile task runId"""

import math
import os
import sys

import eLogDB
import runMany

#from ROOT import TFile, TTree, TChain
#from ROOT import *
import ROOT
#from reconPM import getFileChunks
import reconPM

def subJob(arg):
    result = os.system('bsub ' + arg)
    return result

ROOT.gSystem.Load('libcommonRootData.so')
ROOT.gSystem.Load('libdigiRootData.so')

if len(sys.argv) == 7:
    digiFileName, reconFileName, meritFileName, tarFile, task, runId = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

shellFile = os.environ['reconOneScript']

treeName = 'Digi'
numEventsPerFile = 500
chunks = reconPM.getFileChunks(digiFileName, treeName, numEventsPerFile)

print chunks

workDir, reconFileBase = os.path.split(reconFileName)


# figure out particle type
particleType = eLog.query(runId, 'particletype')

# figure out instrument type, # of towers
tkrSerNos = eLog.parseSerNo(eLog.query(runId, 'tkr_ser_no'))
calSerNos = eLog.parseSerNo(eLog.query(runId, 'cal_ser_no'))

nTwr = len(tkrSerNos)

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

schemaFile = eLog.query(runId, 'SCHEMACONFIGFILE')

tkrOnly = False
calOnly = False

if re.search('grid', schemaFile):
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
    geoFile = reconLib.geometries[nTwr]
    pass
if ! geoFile:
    print >> sys.stderr "No geometry for %d towers!\n" % nTwr
    sys.exit(1)
else:
    print >> sys.stderr "This run has %d towers, using geometry file %s.\n" % (nTwr, geoFile)
    pass

# TODO:
#  create JO files for number of chunks, setting initial runs and # events
#  submit jobs

joHead = \
       """#include "$LATINTEGRATIONROOT/src/jobOptions/pipeline/readigi_runrecon.txt"
       CalibDataSvc.CalibInstrumentName = "%(instrumentType)s";
       GlastDetSvc.xmlfile = "%(geoFile)s";
       digiRootReaderAlg.digiRootFile = "%(digiRootFile)s";
       """ % \
{
    'instrumentType': instrumentType,
    'geoFile': geoFile,
    'digiRootFile': digiRootFile,
    }
if em:
    joHead += '#include "\$LATINTEGRATIONROOT/src/jobOptions/pipeline/VDG.txt"'
    pass
if tkrOnly:
    joHead += 'CalCalibSvc.DefaultFlavor = "ideal";'
elif calOnly:
    joHead += 'TkrCalibAlg.calibFlavor = "ideal";'
    pass


# make a nice printf-style format for printing ranges of event numbers
lastEvent = chunks[-1][-1]
lastEvent = max(lastEvent, 2)
nDigits = int(math.ceil(math.log10(lastEvent)))
oneFormat = '\%0.%dd' % nDigits
cFormat oneFormat + '-' + oneFormat

jobs = []
joFiles = []
reconFiles = []
meritFiles = []
logFiles = []
for iChunk, chunk in enumerate(chunks):
    first, last = chunk

    cTag = cFormat % (first, last)

    joFile = '%s_%s_%s_text.jobOpt' % (task, runId, cTag)
    joFiles.appen(joFile)
    joFile = os.path.join(workDir, joFile)

    numEvents = last - first + 1
    joEvents = \
             """RootIoSvc.StartingIndex = %d;
             RootIoSvc.EvtMax = %d;
             """ % \
    (first, numEvents)
    joData = joHead + joEvents

    reconFile = '%s_%s_%s_RECON.root' % (task, runId, cTag)
    reconFile = os.path.join(workDir, reconFile)
    reconFiles.append(reconFile)
    joData += 'reconRootWriterAlg.reconRootFile = "%s";' % reconFile
    
    meritFile = '%s_%s_%s_MERIT.root' % (task, runId, cTag)
    meritFile = os.path.join(workDir, meritFile)
    meritFiles.append(meritFile)
    joData += 'RootTupleSvc.filename = "%s";' % meritFile

    logFile = '%s_%s_%s.log' % (task, runId, cTag)
    logFiles.append(logFile)
    logFile = os.path.join(workDir, logFile)
    
    print 'c = ', c[0], c[1], " numEvents= ", numEvents

    # at this point one would edit template JO file and add lines for first
    # event index and # events. Possibly define environment variables for
    # input, output files.
    # cmd would be modified to run Gleam and give the correct JO file as arg.

    open(joFile, 'w').write(joData)

    cmd = 'bsub -K -q %s -o %s %s %s' % (queue, logFile, shellFile, joFile)
    print cmd
    jobs.append(cmd)

os.system("date")

results = runMany.pollManyResult(subJob, [(x,) for x in jobs])

os.system("date")
print "rc from batch jobs ", results

# should check rc here to see if all went well.

from reconPM import concatenateFiles

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
rcMerit = reconPM.concatenateFiles(meritFileName, 'MERIT', 'MeritTuple')
if rcMerit:
    print >> sys.stderr, "Failed to create merit file %s!" % meritFileName
    sys.exit(1)
else:
    print >> sys.stderr, "Created merit file %s."  % meritFileName
    pass
rcRecon = reconPM.concatenateFiles(reconFileName, 'RECON', 'Recon')
if rcRecon:
    print >> sys.stderr, "Failed to create recon file %s!" % reconFileName
    sys.exit(1)
else:
    print >> sys.stderr, "Created recon file %s."  % reconFileName
    pass
    
# tar up log and JO files
listFile = 'files.list'
keepFiles = logFiles + joFiles
lfp = open(listFile, 'w')
for kf in keepFiles:
    lfp.write('%s\n' % kf)
    pass
lfp.close()
command = 'gtar cf %s -T %s' % (tarFile, listFile)
status = os.system(command)
if status:
    print >> sys.stderr, 'Failed to write tarfile %s!' % tarFile
    sys.exit(1)
    pass

# get rid of chunk files
trash = reconFiles + meritFiles
for junkFile in trash:
    os.unlink(junkFile)
    pass
