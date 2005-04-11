#! /afs/slac.stanford.edu/g/glast/applications/python/Python-2.2.2/i386_linux24/bin/python

"""Usage: updateUrl.py runId urlKey targetFile [dataRoot]

urlKey must be one of (configReportUrl, digiReportUrl, reconReportUrl,
digiRootFile, reconRootFile, meritRootFile, svacRootFile).

targetFile is the file that will be pointed to.

dataRoot is the root directory for the run tree on the FTP server
(defaults to environment variable rootUrl).

"""

import sys
import os

import DCOracle2

#used to form ftp URL - default value
rootDataDir = os.environ['rootUrl']

reportPages = {"configReportUrl": os.environ['configReportUrl'],
               "digiReportUrl": os.environ['digiReportUrl'],
               "reconReportUrl": os.environ['reconReportUrl'],
               }

goodKeys = ('configReportUrl', 'digiReportUrl', 'reconReportUrl',
            'digiRootFile', 'reconRootFile', 'meritRootFile', 'svacRootFile',
            )

failCode = 1

# parse args
nArg = len(sys.argv)
if nArg == 4:
    runId, urlKey, targetFile = sys.argv[1:]
elif nArg == 5:
    runId, urlKey, targetFile, rootDataDir = sys.argv[1:]    
else:
    print "Wrong number of arguments.\n"
    print __doc__
    sys.exit(failCode)

if urlKey not in goodKeys:
    print "Bad urlKey.\n"
    print __doc__
    sys.exit(failCode)

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

#open connection to oracle database
db = DCOracle2.connect('GLAST_CAL/9square#')
cursor = db.cursor()

# determine whether run is already in the database
sqlStr = 'select * from eLogReport where RunId = %s' % runId
cursor.execute(sqlStr)
result = cursor.fetchone()
if(result == None):
    print 'run %s does not exist in the database, abortted!' % runId
    db.close()
    sys.exit(failCode)
    
# construct URL string
reportUrl = "ftp://ftp-glast.slac.stanford.edu/%s/%s" % \
            (rootDataDir, path)
    
# construct sql string to input data into oracle database.
# in oracle, '' is used to put ' inside a string.
sqlStr = "update eLogReport set %s = '%s' where RunId = %s" % \
         (urlKey, reportUrl, runId)

try:
    cursor.execute(sqlStr)
except:
    (exc_type, exc_value) = sys.exc_info()[:2]

    print sqlStr
    print exc_type
    print exc_value

    db.rollback()
    db.close()
    sys.exit(failCode)
    
# safe to commit
db.commit()
    
#close database
db.close()
