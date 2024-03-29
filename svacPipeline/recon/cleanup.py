#!/usr/local/bin/python

"""usage: cleanup.py keepers, junkDirs, tarFile"""

import os
import sys
import tarfile

import chunkSize
import eLogDB
import geometry
import reconPM
import runMany
import timeLog

print >> sys.stderr, "%s: svacPlRoot=[%s]" % \
      (sys.argv[0], os.environ['svacPlRoot'])

timeLogger = timeLog.timeLog()

if len(sys.argv) == 4:
    keepers, junkDirs, tarFile = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit(1)
    pass

keepFiles = reconPM.readLines(keepers)
directories = reconPM.readLines(junkDirs)

# tar up log and JO files
print >> sys.stderr, "Making tarball..."
tfp = tarfile.open(tarFile, mode='w:gz')
for keeper in keepFiles:
    try:
        tfp.add(keeper)
    except OSError:
        print >> sys.stderr, "Log file %s missing!" % keeper
        pass
    pass
tfp.close()

# get rid of the staging directory(s)
# (if it's not empty, something is wrong)
print >> sys.stderr, "Removing staging dirs..."
for directory in directories:
    print >> sys.stderr, "Removing directory [%s]" % directory
    if 'svacTestMode' in os.environ and int(os.environ['svacTestMode']):
        print >> sys.stderr, "Test mode, not removing."
    else:
        os.rmdir(directory)
        pass
    pass

timeLogger()
