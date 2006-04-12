#!/usr/bin/env python
#!/nfs/slac/g/svac/local/bin/python -O

"""Usage:
ConfigTables.py runNumber snapshot tarBall

"""

import os
import sys
import time
import xml.dom.minidom as md

import html
import htmlTable as table

import configParser

import jobOptions


if len(sys.argv) == 4:
    runNumber, snapFile, tarBall = sys.argv[1:]
else:
    print __doc__
    sys.exit(1)
    pass

# insert command line options in jobOptions
# might make a dump of jobOptions for the records
jobOptions.runNumber = runNumber
jobOptions.snapFile = snapFile
jobOptions.tarBall = tarBall

inDir = os.path.dirname(snapFile)
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
        raise
        sys.exit(3)


    outStr = str(output)
    outputFile.write(outStr)
    outputFile.close()

    # tar up the output directory
    os.system("cd %s ; gtar -c -f - --exclude %s . | gzip -c > %s" %
              (destDir, tarFile, tarFile))

    sys.exit(0)
    return

# read in the config data
try:
    doc = md.parse(snapFile)
except:
    output.addChild("Snapshot file %s is missing, unreadable, or invalid.\n" %
                    snapFile)
    finish()
    pass

# select LATTE or LICOS mode
for node in doc.childNodes:
    if node.nodeType != doc.COMMENT_NODE:
        topNode = node
        break
    pass
mode = jobOptions.modes[topNode.tagName]
print >> sys.stderr, "Running in %s mode." % mode

inFiles = [snapFile]
if mode is jobOptions.licosMode:
    docs = {}
    sectionFiles = []
    for section in jobOptions.latcBcast:
        fileBase = doc.getElementsByTagName(section)[0].childNodes[0].nodeValue
        fileName = os.path.join(inDir, fileBase)
        sectionFiles.append(fileName)
        docs[section] = md.parse(fileName)
        pass
    inFiles += sectionFiles
elif mode is jobOptions.latteMode:
    jobOptions.toLatte()
else:
    print >> sys.stderr, "Bad mode %s." % mode
    sys.exit(1)
    pass

# Make a header ############################################
output = html.Page("Configuration for run %s" % runNumber)

output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild("\n")

lines=["Created by ConfigTables version %s from files:" % \
       jobOptions.version]
lines += inFiles
output.addChild('<br/>\n'.join(lines))

output.addChild("<br/>\n" + time.asctime() + "\n")

output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild(html.Element("HR"))
output.addChild("\n")

if mode is jobOptions.latteMode:
    # quit semigracefully if we don't have eactly one LAT
    lats = doc.getElementsByTagName('GLAT')
    nLats = len(lats)
    if nLats != 1:
        if nLats == 0:
            output.addChild("There's no LAT in this snapshot!")
        else:
            output.addChild("There's too many LATs in this snapshot!")
            pass
        finish()
        pass
    theLat = lats[0]
    pass

if mode is jobOptions.licosMode:
    output.addChild("Sorry, LICOS support is currently rudimentary.")
    finish()
    pass

# make tables ############################################
output.addChildren(configParser.globalStuff(doc))
output.addChild(html.Element("HR"))
output.addChild(html.Element("HR"))
output.addChild("\n")
output.addChildren(configParser.gemStuff(theLat))
output.addChild(html.Element("HR"))
output.addChild(html.Element("HR"))
output.addChild("\n")
if configParser.hasTem(theLat):
    output.addChildren(configParser.perTem(theLat))
    output.addChild(html.Element("HR"))
    output.addChild(html.Element("HR"))
    output.addChild("\n")
    pass
output.addChildren(configParser.delays(theLat))
output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild(html.Element("HR"))
output.addChild("\n")

if configParser.hasAcd(theLat):
    output.addChildren(configParser.acdStuff(theLat))
    pass

if configParser.hasCal(theLat):
    output.addChildren(configParser.calFeReg(theLat))
    output.addChild(html.Element("HR"))
    output.addChild(html.Element("HR"))
    output.addChild("\n")
    pass

if configParser.hasTkr(theLat):
    output.addChildren(configParser.perGtrc(theLat))
    output.addChild(html.Element("HR"))
    output.addChild(html.Element("HR"))
    output.addChild("\n")

    # # This is broken, and the functionality is provided by
    # # including nread and mode tables
    # output.addChildren(configParser.tkrSplits(theLat))
    # output.addChild(html.Element("HR"))
    # output.addChild(html.Element("HR"))
    # output.addChild("\n")

    output.addChildren(configParser.tkrFeReg(theLat))
    output.addChild(html.Element("HR"))
    output.addChild("\n")

    pass

finish()
