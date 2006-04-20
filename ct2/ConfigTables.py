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

#
def getLatcFiles(doc):
    secNodes = {}
    fileNode = doc.getElementsByTagName('latcFiles')[0]
    for node in fileNode.childNodes:
        if node.nodeType == node.ELEMENT_NODE:
            name = str(node.nodeName)
            value = str(node.childNodes[0].nodeValue)
            secNodes[name] = value
            pass
        pass
    return secNodes

# read in the config data
try:
    print >> sys.stderr, "Reading file %s." % snapFile
    doc = md.parse(snapFile)
except:
    print >> sys.stderr, "Snapshot file %s is missing, unreadable, or invalid." % snapFile
    sys.exit(1)
    pass

# select LATTE or LICOS mode
for node in doc.childNodes:
    if node.nodeType != doc.COMMENT_NODE:
        topNode = node
        break
    pass
jobOptions.mode = jobOptions.modes[topNode.tagName]
print >> sys.stderr, "Running in %s mode." % jobOptions.mode

inFiles = [snapFile]

if jobOptions.mode is jobOptions.latteMode:
    jobOptions.toLatte()

elif jobOptions.mode is jobOptions.licosMode:
    docs = {}
    sectionFiles = []
    sections = getLatcFiles(doc)
    for section in sections:
        fileBase = sections[section]
        fileName = os.path.join(inDir, fileBase)
        sectionFiles.append(fileName)
        print >> sys.stderr, "Reading file %s." % fileName
        docs[section] = md.parse(fileName)
        pass
    inFiles += sectionFiles
    
else:
    print >> sys.stderr, "Bad mode %s." % jobOptions.mode
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

if jobOptions.mode is jobOptions.latteMode:
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

if jobOptions.mode is jobOptions.licosMode:
    output.addChild(r"""These data were parsed from LATC input.
    As such, they reflect intended, rather than actual, register values.
    <br/>
    <br/>
    LICOS support is currently somewhere between rudimentary and broken.<br/>
    Any registers configured by broadcast are either missing or 'Absent'.
    """)
    pass

if jobOptions.mode is jobOptions.latteMode:
    globalDoc = doc
    gemDoc = theLat
    temDoc = theLat
    arcDoc = theLat
    afeDoc = theLat
    cfeDoc = theLat
    tfeDoc = theLat
elif jobOptions.mode is jobOptions.licosMode:
    globalDoc = docs['bcast']
    gemDoc = docs['bcast']
    try:
        temDoc = docs['TEM']
    except KeyError:
        temDoc = docs['bcast']
        pass
    try:
        arcDoc = docs['ARC']
    except KeyError:
        temDoc = docs['bcast']
        pass
    try:
        afeDoc = docs['AFE']
    except KeyError:
        temDoc = docs['bcast']
        pass
    try:
        cfeDoc = docs['CFE']
    except KeyError:
        temDoc = docs['bcast']
        pass
    try:
        tfeDoc = docs['TFE']
    except KeyError:
        temDoc = docs['bcast']
        pass
else:
    raise AssertionError, "Can't get here!"
    pass
    
# make tables ############################################
print >> sys.stderr, "Processing globals."
output.addChildren(configParser.globalStuff(globalDoc))
output.addChild(html.Element("HR"))
output.addChild(html.Element("HR"))
output.addChild("\n")

if jobOptions.mode is jobOptions.latteMode:
    print >> sys.stderr, "Processing GEM."
    output.addChildren(configParser.gemStuff(gemDoc))
    output.addChild(html.Element("HR"))
    output.addChild(html.Element("HR"))
    output.addChild("\n")

if configParser.hasTem(temDoc):
    print >> sys.stderr, "Processing TEMs."
    output.addChildren(configParser.perTem(temDoc))
    output.addChild(html.Element("HR"))
    output.addChild(html.Element("HR"))
    output.addChild("\n")
    pass

if jobOptions.mode is jobOptions.latteMode:
    print >> sys.stderr, "Processing delays."
    output.addChildren(configParser.delays(theLat))
    output.addChild("\n")
    output.addChild(html.Element("HR"))
    output.addChild(html.Element("HR"))
    output.addChild("\n")

if configParser.hasAcd(afeDoc):
    print >> sys.stderr, "Processing ACD."
    output.addChildren(configParser.acdStuff(arcDoc, afeDoc))
    pass

if configParser.hasCal(cfeDoc):
    print >> sys.stderr, "Processing CAL FEs."
    output.addChildren(configParser.calFeReg(cfeDoc))
    output.addChild(html.Element("HR"))
    output.addChild(html.Element("HR"))
    output.addChild("\n")
    pass

if configParser.hasTkr(tfeDoc) and jobOptions.mode is jobOptions.latteMode:
    print >> sys.stderr, "Processing TRCs."
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

    print >> sys.stderr, "Processing TFEs."
    output.addChildren(configParser.tkrFeReg(tfeDoc))
    output.addChild(html.Element("HR"))
    output.addChild("\n")

    pass

finish()
