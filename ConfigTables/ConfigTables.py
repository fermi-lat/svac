#!/usr/bin/env python
#!/nfs/slac/g/svac/local/bin/python

import glob
import os
import sys
import xml.dom.minidom as md

import html
import table
import temUtil
import util
import xmlUtil

import joboptions


if len(sys.argv) >= 2:
    runNumber = sys.argv[1]
else:
    print "You must supply a run number."
    sys.exit(1)
    pass


schemaTag = "schema"

inDir = os.path.join(joboptions.runDir, runNumber)

# inPat = os.path.join(inDir, joboptions.snapshotPrefix + "*" + joboptions.exten)
# snapshots = glob.glob(inPat)
# if len(snapshots) != 1:
#     print "Run directory %s does not have exactly 1 'before' snapshot." % inDir
#     sys.exit(1)
# inFile = snapshots[0]

# schemaFile = os.path.join(inDir, joboptions.schemaFile)

inFile = util.findSnapshot(inDir)
schemaFile = util.findSchema(inDir)

# parse the schema
schema = md.parse(schemaFile)
schemas = schema.getElementsByTagName(joboptions.schemaTag)
if len(schemas) != 1:
    print "Schema file %s does not have exactly 1 schema." % schemaFile
    sys.exit(42)
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
    #while True:
    #    try:
    #        shape.remove(joboptions.broadcast)
    #    except ValueError:
    #        break
    #    pass
    newShape = []
    print tag, shape
    for index in shape:
        if index < maxShape:
            newShape.append(index)
            pass
        pass
    shape = newShape
    print tag, shape
    shape.sort()
    indices[tag] = shape
    shape = len(shape)
    shapes[tag] = shape
    pass

# parse the config data
doc = md.parse(inFile)

output = html.Page("Configuration for run %s" % runNumber)

output.addChild("\n")
output.addChild(html.Element("HR"))
output.addChild("\n")

output.addChild(r"""Created from files:<br/>
snapshot: %s<br/>
schema: %s<br/>
""" % (inFile, schemaFile))

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
            hTable = table.htmlTable(side, title, ("crystal", "layer"), (xLab, yLab))
            #output.addChild(hTable)        
            #output.addChild("\n")
            sides.append(hTable)
            pass
        hTable = html.nWay(sides, joboptions.width)
        output.addChild(hTable)
        pass
    pass


# #get CAL CSRs
# gcccs = doc.getElementsByTagName("GCCC")
# cCsrs = []
# for gccc in gcccs:
#     cCsrs.extend(gccc.getElementsByTagName("csr"))
#     pass
# cCsrs = util.contain(cCsrs, shapes)

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
modes = doc.getElementsByTagName("mode")
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




# put out the output
destDir = os.path.join(joboptions.outDir, runNumber, joboptions.reportDir)
try:
    os.stat(destDir)
except OSError:
    try:
        os.makedirs(destDir)
    except:
        print "Couldn't create directory %s." % destDir
        sys.exit(2)
outputFileName = os.path.join(destDir, joboptions.outFile)

try:
    outputFile = file(outputFileName, "w")
except:
    print "Couldn't create file %s." % outputFileName
    sys.exit(3)

output = str(output)
outputFile.write(output)
outputFile.close()
