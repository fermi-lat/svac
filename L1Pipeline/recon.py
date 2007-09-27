#!/afs/slac/g/glast/isoc/flightOps/rhel3_gcc32/ISOC_PROD/bin/shisoc python2.5

"""@brief Reconstruct a crumb.

Really most everything has already been set up at this point. This is just
here to handle staging and set JOBOPTIONS.

@author W. Focke <focke@slac.stanford.edu>
"""

import os
import sys

import GPLinit

import config
import fileNames
import runner
import stageFiles

files = fileNames.setup(os.environ['DOWNLINK_ID'], os.environ['RUNID'], \
                        os.environ['CHUNK_ID'], os.environ['CRUMB_ID'])

staged = stageFiles.StageSet()
finishOption = config.finishOption

os.environ['digiChunkFile'] = staged.stageIn(files['chunk']['digi'])
os.environ['fakeFT2File'] = staged.stageIn(files['chunk']['ft2Fake'])
os.environ['reconCrumbFile'] = staged.stageOut(files['crumb']['recon'])
os.environ['meritCrumbFile'] = staged.stageOut(files['crumb']['merit'])
os.environ['calCrumbFile'] = staged.stageOut(files['crumb']['cal'])

datasource = os.environ['DATASOURCE']
if datasource == 'LPA':
    geometry = 'latAssembly/latAssemblySegVols.xml'
elif datasource == 'MC':
    geometry = 'flight/flightSegVols.xml'
    pass
os.environ['gleamGeometry'] = geometry

status = runner.run(config.apps['recon'] + ' ' + config.reconOptions)
if status: finishOption = 'wipe'

status |= staged.finish(finishOption)

sys.exit(status)
