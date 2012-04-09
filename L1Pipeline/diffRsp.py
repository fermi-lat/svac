#!/afs/slac/g/glast/isoc/flightOps/rhel3_gcc32/ISOC_PROD/bin/shisoc --add-env=oracle11 python2.5

import os
import sys

if __name__ == "__main__":
    print >> sys.stderr, "This module is not supported as main script"
    sys.exit(1)

import config

import runner


def diffRsp(files, inFileTypes, outFileTypes, workDir, **args):
    status = 0

    inFileType = inFileTypes[0]
    ft2FileType = inFileTypes[1]

    assert len(outFileTypes) == 1
    outFileType = outFileTypes[0]

    stSetup = config.stSetup
    app = config.apps['diffRsp']

    stagedInFile = files[inFileType]
    stagedFt2File = files[ft2FileType]
    stagedOutFile = files[outFileType]

    instDir = config.ST
    glastExt = config.glastExt

    tmpFt1File = stagedInFile + '.tmp'
    os.rename(stagedInFile, tmpFt1File)

    cmdHead = '''
    cd %(workDir)s
    export INST_DIR=%(instDir)s
    export GLAST_EXT=%(glastExt)s
    source %(stSetup)s
    ''' % locals()

    for evcls in config.diffRspMap.keys():
        irf = config.diffRspMap[evcls]['irf']
        model = config.diffRspMap[evcls]['model']
        cmdTail = '''%(app)s scfile=%(stagedFt2File)s evfile=%(tmpFt1File)s srcmdl=%(model)s irfs=%(irf)s evclass=%(evcls)s
        ''' % locals()
        cmd = cmdHead + cmdTail
        status |= runner.run(cmd)
        if status: return status
        continue

    os.rename(tmpFt1File, stagedOutFile)

    return status
