"""@brief Configuration.

@author W. Focke <focke@slac.stanford.edu>
"""

import os
from os import path, environ

L1Version = "1.6"
installRoot = "/afs/slac.stanford.edu/g/glast/ground/PipelineConfig/SC/L1Pipeline"
L1ProcROOT = path.join(installRoot, L1Version)
#L1ProcROOT = '/nfs/farm/g/glast/u33/wai/pipeline_tests/svac/L1Pipeline'
#L1ProcROOT = '/nfs/slac/g/svac/focke/cvs/L1Pipeline'
LATCalibRoot = '/afs/slac/g/glast/ground/releases/calibrations'
#L1Cmt = path.join(installRoot, 'builds')
L1Cmt = '/nfs/slac/g/svac/focke/builds'

L1Disk = '/nfs/farm/g/glast/u40/L1'
#L1Disk = '/nfs/slac/g/svac/focke/L1'
#L1Disk = '/nfs/farm/g/glast/u33/wai/pipeline_tests/L1'
#L1Disk = 'L1DISK'
L1Dir = path.join(L1Disk, 'rootData')

afsStage = "/afs/slac/g/glast/ground/PipelineStaging"

maxCpu = 1000

#maxCrumbSize = 48000 # SVAC pipeline uses this
#maxCrumbSize = 250   # tiny
maxCrumbSize = 6353   # ~.5Hr on tori.  Also about half of medium q limit

glastRoot = '/afs/slac.stanford.edu/g/glast'
groundRoot = os.path.join(glastRoot, 'ground')
glastSetup = os.path.join(groundRoot, 'scripts', 'group.sh')
#
cmtConfig = 'rh9_gcc32opt'
#
glastExt = os.path.join(groundRoot, 'GLAST_EXT', cmtConfig)
#
releaseDir = os.path.join(groundRoot, 'releases', 'volume12')
glastVersion = 'v7r0913p11'
releaseName = 'EngineeringModel'
gleamPackage = 'LatIntegration'
#
glastName = '-'.join((releaseName, glastVersion))
glastLocation = path.join(releaseDir, glastName)
gleam = path.join(glastLocation, 'bin', gleamPackage)
cmtScript = path.join(glastLocation, releaseName, glastVersion, 'cmt',
                         'setup.sh') # do we need this?
cmtPath = ':'.join((glastLocation, L1Cmt))
environ['CMTPATH'] = cmtPath
#
digiOptions = path.join(L1ProcROOT, 'digi.jobOpt')
reconOptions = path.join(L1ProcROOT, 'recon.jobOpt')

rootSys = path.join(glastExt, 'ROOT/v5.10.00/root')
haddRootSys = path.join(glastExt, 'ROOT/v5.13.1/root')
hadd = path.join(glastExt, haddRootSys, 'bin', 'hadd')


packages = {
    'TestReport': {
        'repository': 'svac',
        'version': 'v3r6p41',
        },
    'EngineeringModelRoot': {
        'repository': 'svac',
        'version': 'v3r0p3',
        },
    'pipelineDatasets': {
        'repository': 'users/richard',
        'version': 'v0r3',
        },
    }

# fill in standard values for standard packages
for packName in packages:
    package = packages[packName]
    packages[packName]['root'] = os.path.join(L1Cmt, packName, package['version'])
    package['bin'] = os.path.join(package['root'], cmtConfig)
    package['cmtDir'] = os.path.join(package['root'], 'cmt')
    package['setup'] = os.path.join(package['cmtDir'], 'setup.sh')
    package['checkOutName'] = os.path.join(package['repository'], packName)
    continue

# add nonstandard package info
packages['TestReport']['app'] = os.path.join(packages['TestReport']['bin'], 'TestReport.exe')
packages['TestReport']['mergeApp'] = os.path.join(packages['TestReport']['bin'], 'MergeHistFiles.exe')
packages['EngineeringModelRoot']['app'] = os.path.join(packages['EngineeringModelRoot']['bin'], 'RunRootAnalyzer.exe')


apps = {
    'digi': gleam,
    'digiMon': packages['TestReport']['app'],
    'recon': gleam,
    'reconMon': packages['TestReport']['app'],
    'reportMerge': packages['TestReport']['mergeApp'],
    'svacTuple': packages['EngineeringModelRoot']['app'],
    }


ST="/nfs/farm/g/glast/u09/builds/rh9_gcc32opt/ScienceTools/ScienceTools-v7r6p1"
PFILES="."

joiner = '*'

rootPath = os.path.join(rootSys, 'lib')
pythonPath = rootPath
libraryPath = ':'.join((os.path.join(L1Cmt, 'lib'), \
                        os.path.join(glastLocation, 'lib'), \
                        rootPath))

# LSF stuff
allocationGroup = 'glastdata'
#
quickQueue = 'express'
reconQueue = 'medium'
standardQueue = 'glastdataq'

if __name__ == "__main__":
    print L1Dir
    print reconApp
    
