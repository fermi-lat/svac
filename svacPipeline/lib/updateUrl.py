#! /usr/local/bin/python

"""Usage: updateUrl.py runId urlKey targetFile [dataRoot]

urlKey must be one of (configReportUrl, digiReportUrl, reconReportUrl,
digiRootFile, reconRootFile, meritRootFile, svacRootFile, calRootFile).

targetFile is the file that will be pointed to.

dataRoot is the root directory for the run tree on the FTP server
(defaults to environment variable rootUrl).

"""

import sys
import os

print >> sys.stderr, "%s: svacPlRoot=[%s]" % \
      (sys.argv[0], os.environ['svacPlRoot'])

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
    rootDataDir = None
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
print >> sys.stderr, targetFile
path = targetFile.split('/')
print >> sys.stderr, path
runIndex = path.index(runId)
del path[:runIndex]
if urlKey in reportPages:
    # This is a report, we've gotta replace the tarball with the web page
    # And serve the page thru HTTP
    path[-1] = reportPages[urlKey]
    defaultRootDir = os.environ['rootUrl']
else:
    # not a report, serve it thru FTP
    defaultRootDir = os.environ['rootFtp']
    pass
path = os.path.join(*path)
print >> sys.stderr, path
if not rootDataDir:
    rootDataDir = defaultRootDir
    
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
