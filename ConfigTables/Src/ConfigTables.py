#!/nfs/slac/g/svac/local/bin/python

"""Usage:
ConfigTables.py runNumber schema snapshot tarBall

"""

import glob
import os
import sys
import xml.dom.minidom as md

import html
import htmlTable as table
import temUtil
import util
import xmlUtil

import joboptions


if len(sys.argv) == 5:
    runNumber, schemaFile, snapFile, tarBall = sys.argv[1:]
else:
    print __doc__
    sys.exit(1)
    pass

destDir = os.path.dirname(tarBall) or '.'
tarFile = os.path.basename(tarBall)

schemaTag = "schema"

#inDir = os.path.join(joboptions.runDir, runNumber)
#snapFile = util.findSnapshot(inDir)
#schemaFile = util.findSchema(inDir)


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

    outputFileName = os.path.join(destDir, joboptions.outFile)

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

    sys.exit(0)
    return


output = html.Page("Configuration for run %s" % runNumber)

output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild("\n")

output.addChild(r"""Created by ConfigTables version %s from files:<br/>
snapshot: %s<br/>
schema: %s<br/>
""" % (joboptions.version, snapFile, schemaFile))

# parse the schema
try:
    schema = md.parse(schemaFile)
except:
    output.addChild("Schema file %s is missing, unreadable, or invalid.\n" %
                    schemaFile)
    finish()
schemas = schema.getElementsByTagName(joboptions.schemaTag)
if len(schemas) != 1:
    output.addChild("Schema file %s does not contain exactly 1 schema.\n" %
                    schemaFile)
    finish()
schema = schemas[0]

shapes = {}
indices = {}
for tag in joboptions.shapeTags:
    maxShape = joboptions.maxShape[tag]
    elements = schema.getElementsByTagName(tag)
    if len(elements) == 0:
        shape = range(maxShape)
    else:
        shape = util.scalar(elements)
        shape = shape.getAttribute("ID")
        shape = util.uncompressSequence(shape)
        pass
    newShape = []
    for index in shape:
        if index < maxShape:
            newShape.append(index)
            pass
        pass
    shape = newShape
    shape.sort()
    indices[tag] = shape
    shape = len(shape)
    shapes[tag] = shape
    pass

# parse the config data
try:
    doc = md.parse(snapFile)
except:
    output.addChild("Snapshot file %s is missing, unreadable, or invalid.\n" %
                    snapFile)
    finish()
    
# get stuff from CAL front ends
# and make tables of it
for registerTag in joboptions.calTags:
    elements = doc.getElementsByTagName(registerTag)
    container = util.contain(elements, shapes)

    output.addChild("\n")
    output.addChild(html.Element("HR"))
    output.addChild("\n")

    registerLabel = temUtil.registerMap[registerTag]
    output.addChild(html.Heading(registerLabel, 2))

    for jtem, tem in enumerate(container):
        sides = []
        for iside, side in enumerate(tem):
            #output.addChild(html.Element("HR"))
            #output.addChild("\n")

            sideLabel = temUtil.cccSideMap[iside]
            title = "%s for Tower %d side %s" % (registerLabel, jtem, sideLabel)
            yLen = len(side)
            xLen = len(side[0])
            yLab = map(repr, temUtil.cccLayerMap[iside][:yLen])
            xLab = map(repr, range(xLen))
            hTable = table.twoDTable(side, title, ("crystal", "layer"), (xLab, yLab))
            #output.addChild(hTable)        
            #output.addChild("\n")
            sides.append(hTable)
            pass
        hTable = html.nWay(sides, joboptions.width)
        output.addChild(hTable)
        pass
    pass


#get TKR CSRs
gtccs = doc.getElementsByTagName("GTCC")
tCsrs = []
for gtcc in gtccs:
    tCsrs.extend(gtcc.getElementsByTagName("csr"))
    pass
tCsrs = util.contain(tCsrs, shapes, blank=-1)

subField = util.SubField(7, 13)
nRead = util.superMap(subField, tCsrs)

#get TKR modes
gtrcs = doc.getElementsByTagName("GTRC")
modes = []
for gtrc in gtrcs:
    modes.extend(gtrc.getElementsByTagName("mode"))
modes = util.contain(modes, shapes)

nTrc = shapes["GTRC"]

# calc split points
splits = []
for jtem in range(len(tCsrs)):
    sides = []
    for left, right in temUtil.tccLRMap:
        layers = []
        for jlayer in range(nTrc):
            split = util.getSplit(nRead[jtem][left][jlayer],
                                  nRead[jtem][right][jlayer],
                                  modes[jtem][left][jlayer],
                                  modes[jtem][right][jlayer])
            layers.append(split)
            pass
        sides.append(layers)
        pass
    splits.append(sides)
    pass

# build split point table
tkrLayers = 2 * nTrc
layers = range(tkrLayers)
array = [layers]
labels = ["Layer"]
for jtem, tem in enumerate(splits):
    for view in ("X", "Y"):
        row = []
        for layer in layers:
            side, trc = temUtil.trcLayerMap[view][layer]
            row.append(tem[side][trc])
            pass
        array.append(row)
        labels.append("Tower %s %s" % (jtem, view))
        pass
    pass
array = util.transpose(array)
array.reverse()

output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild("\n")

splitLabel = "Tracker Split Points"
output.addChild(html.Heading(splitLabel, 2))

splitCaption = splitLabel + " (Left:Right)"
hTable = table.oneDTable(array, splitCaption, labels)
output.addChild(hTable)

output.addChild("\n")


finish()
