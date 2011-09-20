#!/afs/slac/g/glast/isoc/flightOps/rhel3_gcc32/ISOC_PROD/bin/shisoc --add-env=oracle11 python2.5

import os
import sys

if __name__ == "__main__":
    print >> sys.stderr, "This module is not supported as main script"
    sys.exit(1)

import config

import fileNames
import meritFiles
import runner

def gtSelect(files, inFileTypes, outFileTypes, workDir, **args):
    status = 0

    inFileType = inFileTypes[0]
    ft2FileType = inFileTypes[1]
    assert len(outFileTypes) == 1
    outFileType = outFileTypes[0]

    stagedInFile = files[inFileType]
    stagedFt2File = files[ft2FileType]
    stagedOutFile = files[outFileType]

    stSetup = config.stSetup
    selectapp = os.path.join(config.stExeDir, 'gtselect')
    timeapp = os.path.join(config.stExeDir, 'gtmktime')

    eventClass = config.gtSelectClass[outFileType]

    timeFilter = 'LIVETIME>0'
    evtFilter = 'evclass=%(eventClass)s' % locals() 

    instDir = config.ST
    glastExt = config.glastExtSCons

    cmd = '''
    cd %(workDir)s
    export INST_DIR=%(instDir)s
    export GLAST_EXT=%(glastExt)s
    source %(stSetup)s
    %(selectapp)s infile=%(stagedInFile)s %(evtFilter)s emin=0 emax=0 zmax=180 outfile=FT1_tmp.fit
    echo gtselect done, now working on gtmktime
    %(timeapp)s overwrite=yes roicut=no scfile=%(stagedFt2File)s filter="%(timeFilter)s" evfile=FT1_tmp.fit outFile=%(stagedOutFile)s
    ''' % locals()

    status = runner.run(cmd)
    return status
