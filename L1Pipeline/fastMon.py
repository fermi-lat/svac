import os
import re
import sys

if __name__ == "__main__":
    print >> sys.stderr, "This module is not supported as main script"
    sys.exit(1)

import config

import pipeline
import runner


def fastMon(files, idArgs, workDir, staged, **args):
    status = 0

    dlId, runId, chunkId, crumbId = idArgs

    package = config.packages['FastMon']

    reportType = os.environ['reportType']
    if reportType == 'fastMonTuple':
        inFile = files['event']
        errorFile = files['fastMonError']
        realM7File = os.path.join(os.environ['DOWNLINK_RAWDIR'], 'magic7_%s.txt' % dlId) 
        m7File = staged.stageIn(realM7File)
        tupleFile = files['fastMonTuple']
        saaDef = package['saaDefinition']
        varArgs = '-o %(tupleFile)s -e %(errorFile)s -m %(m7File)s -s %(saaDef)s' % locals()
        app = config.apps['fastMonTuple']
    elif reportType == 'fastMonHist':
        inFile = files['fastMonTuple']
        histFile = files['fastMonHist']
        varArgs = '-o %(histFile)s' % locals()
        app = config.apps['fastMonHist']
        pass

    os.environ.update(package['env'])

    dmRoot = config.L1Build

    extra = package['extraSetup']

    dataSource = os.environ['DATASOURCE']
    if dataSource in ['LCI']:
        optionTag = 'fastMonLci'
    elif dataSource in ['LPA', 'MC']:
        optionTag = 'fastMon'
    else:
        print >> sys.stderr, 'Bad DATASOURCE %s' % dataSource
        status = 1
        pass
    configFile = config.monitorOptions[optionTag]

    igrfExport = config.igrfExport

    #special settings to deal with the lack of a 64 bits ISOC env 
    python = sys.executable
    override_rootPath = '/afs/slac/package/lsf/curr/lib:/afs/slac.stanford.edu/g/glast/ground/GLAST_EXT/redhat5-i686-32bit-gcc41/ROOT/v5.26.00a-gl6/gcc41/lib' 
    L1home = config.L1ProcROOT
    commonPath = os.path.join(dmRoot,'Common','python')
    igrfPath = os.path.join(dmRoot,'IGRF','python')
    #end of the special settings section. This is terribly ugly

    cmd = '''
    cd %(workDir)s
    export DATAMONITORING_ROOT=%(dmRoot)s
    export FAST_MON_DIR=%(workDir)s
    %(igrfExport)s
    export LD_LIBRARY_PATH=""
    export PYTHONPATH=""
    %(extra)s
    export LD_LIBRARY_PATH=%(override_rootPath)s:${LD_LIBRARY_PATH}
    export PYTHONPATH=%(L1home)s:%(override_rootPath)s:%(commonPath)s:%(igrfPath)s:${PYTHONPATH}:%(workDir)s
    %(python)s %(app)s -c %(configFile)s %(varArgs)s %(inFile)s
    ''' % locals()

    if not status: status |= runner.run(cmd)

    return status
