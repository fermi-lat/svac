#!/afs/slac/g/glast/isoc/flightOps/rhel6_gcc44/ISOC_PROD/bin/shisoc python2.6

import os
import sys

import config

import GPLinit

import fileNames
import parseBTI
import runner
import stageFiles
import registerPrep

head, dlId = os.path.split(os.environ['DOWNLINK_RAWDIR'])
if not dlId: head, dlId = os.path.split(head)
runId = os.environ['RUNID']

staged = stageFiles.StageSet(excludeIn=config.excludeIn)
finishOption = config.finishOption
python = config.python

#input file
realDigiTrend = fileNames.fileName('digiTrend', dlId, runId, next=False)
stagedDigiTrend = staged.stageIn(realDigiTrend)
realMeritTrend = fileNames.fileName('meritTrend', dlId, runId, next=False)
stagedMeritTrend = staged.stageIn(realMeritTrend)

#output
realSolarFlareHist = fileNames.fileName('solarFlareHist', dlId, runId, next=True)
solarFlareHist = staged.stageOut(realSolarFlareHist)
realSolarFlareLog = fileNames.fileName('solarFlareLog', dlId, runId, next=True)
solarFlareLog = staged.stageOut(realSolarFlareLog)
realSolarFlarePlot = fileNames.fileName('solarFlarePlot', dlId, runId, next=True)
solarFlarePlot = staged.stageOut(realSolarFlarePlot)

app = config.apps['solarFlares']
workDir = os.path.dirname(solarFlareHist)

cmd = '''
cd %(workDir)s
%(python)s %(app)s %(stagedDigiTrend)s %(stagedMeritTrend)s -r %(solarFlareHist)s -x %(solarFlareLog)s -p %(solarFlarePlot)s
''' % locals()

status = runner.run(cmd)
if status: finishOption = 'wipe'

if not status:
    ranges = parseBTI.getRangesXml(solarFlareLog)
    parseBTI.setRangesVar(ranges)
    pass

status |= staged.finish(finishOption)

if not status: 
    registerPrep.prep('solarFlareHist', realSolarFlareHist)
    registerPrep.prep('solarFlareLog', realSolarFlareLog)
    registerPrep.prep('solarFlarePlot', realSolarFlarePlot)
    pass

sys.exit(status)
