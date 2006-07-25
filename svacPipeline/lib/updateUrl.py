#! /afs/slac.stanford.edu/g/glast/applications/python/Python-2.2.2/i386_linux24/bin/python

"""Usage: updateUrl.py runId urlKey targetFile [dataRoot]

urlKey must be one of (configReportUrl, digiReportUrl, reconReportUrl,
digiRootFile, reconRootFile, meritRootFile, svacRootFile, calRootFile).

targetFile is the file that will be pointed to.

dataRoot is the root directory for the run tree on the FTP server
(defaults to environment variable rootUrl).

"""

import sys
import os

reportPages = {"configReportUrl": os.environ['configReportUrl'],
               "digiReportUrl": os.environ['digiReportUrl'],
               "reconReportUrl": os.environ['reconReportUrl'],
               "tkrReportUrl": os.environ['tkrReportUrl'],
               }

goodKeys = ('configReportUrl', 'digiReportUrl', 'reconReportUrl',
            'tkrReportUrl', 
            'digiRootFile', 'reconRootFile', 'meritRootFile', 'svacRootFile',
            'calRootFile',
            )

success = 0
failure = 1

# parse args
nArg = len(sys.argv)
if nArg == 4:
    runId, urlKey, targetFile = sys.argv[1:]
    # used to form ftp URL - default value
    rootDataDir = os.environ['rootUrl']
elif nArg == 5:
    runId, urlKey, targetFile, rootDataDir = sys.argv[1:]    
else:
    print "Wrong number of arguments.\n"
    print __doc__
    sys.exit(failure)

if urlKey not in goodKeys:
    print "Bad urlKey.\n"
    print __doc__
    sys.exit(failure)

# figure out the path to the target file
#path = list(os.path.split(targetFile))
print targetFile
path = targetFile.split('/')
print path
runIndex = path.index(runId)
del path[:runIndex]
if urlKey in reportPages:
    # This is a report, we've gotta replace the tarball with the web page
    path[-1] = reportPages[urlKey]
path = os.path.join(*path)
print path

    
# construct URL string
reportUrl = "%s/%s" % (rootDataDir, path)
    
# update DB
command = "%s '%s' '%s' '%s'" % (os.environ['eLogUpdate'], runId, urlKey, reportUrl)
sys.stderr.write("About to run command [%s]\n" % command)
status = os.system(command)
if status:
    sys.exit(failure)
else:
    sys.exit(success)
    pass
