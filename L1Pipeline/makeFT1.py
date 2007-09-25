#!/afs/slac/g/glast/isoc/flightOps/rhel3_gcc32/ISOC_PROD/bin/shisoc python2.5

import os
import sys

import config

import GPLinit

import fileNames
import runner
import stageFiles
#import pipeline
import registerPrep

files = fileNames.setup(os.environ['DOWNLINK_ID'], os.environ['RUNID'])

staged = stageFiles.StageSet()

if staged.setupOK:
    workDir = staged.stageDir
else:
    workDir = files['dirs']['run']
    pass

app = config.apps['makeFT1']

stagedMeritFile = staged.stageIn(files['run']['merit'])
realFt1File = files['run']['ft1']
stagedFt1File = staged.stageOut(realFt1File)

cmd = '''
cd %(workDir)s
%(app)s rootFile=%(stagedMeritFile)s fitsFile=%(stagedFt1File)s TCuts=DEFAULT event_classifier="Pass5_Classifier" tstart=100000000 tstop=300000000
''' % locals()

status = runner.run(cmd)

status |= staged.finish()

os.symlink(os.path.basename(realFt1File), files['run']['ft1Export'])

fileType = 'FT1'
registerPrep.prep(fileType, realFt1File)

sys.exit(status)
