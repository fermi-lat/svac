#!/nfs/slac/g/svac/local/bin/python

"""Usage:
ConfigTables.py runNumber schema snapshot tarBall

"""

import os
import sys
import xml.dom.minidom as md

import html
import htmlTable as table

import configParser

import jobOptions


if len(sys.argv) == 5:
    runNumber, schemaFile, snapFile, tarBall = sys.argv[1:]
else:
    print __doc__
    sys.exit(1)
    pass

destDir = os.path.dirname(tarBall) or '.'
tarFile = os.path.basename(tarBall)

def finish():
    # put out the output
    # nasty globals
    try:
        os.stat(destDir)
    except OSError:
        try:
            os.makedirs(destDir)
        except:
            print "Couldn't create directory [%s]." % destDir
            sys.exit(2)

    outputFileName = os.path.join(destDir, jobOptions.outFile)

    try:
        outputFile = file(outputFileName, "w")
    except:
        print "Couldn't create file [%s]." % outputFileName
        sys.exit(3)

    outStr = str(output)
    outputFile.write(outStr)
    outputFile.close()

    # tar up the output directory
    os.system("cd %s ; tar -c -f - --exclude %s . | gzip -c > %s" %
              (destDir, tarFile, tarFile))

    # sys.exit(0)
    return

output = html.Page("Configuration for run %s" % runNumber)

output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild("\n")

output.addChild(r"""Created by ConfigTables version %s from files:<br/>
snapshot: %s<br/>
schema: %s<br/>
""" % (jobOptions.version, snapFile, schemaFile))

output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild("\n")


# read in the config data
try:
    doc = md.parse(snapFile)
except:
    output.addChild("Snapshot file %s is missing, unreadable, or invalid.\n" %
                    snapFile)
    finish()

# make tables
output.addChildren(configParser.globalStuff(doc))
output.addChildren(configParser.tkrSplits(doc))
output.addChildren(configParser.calFeReg(doc))
output.addChildren(configParser.delays(doc))

finish()
