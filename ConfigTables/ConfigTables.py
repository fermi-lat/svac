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

inPat = os.path.join(inDir, joboptions.snapshotPrefix + "*" + joboptions.exten)
snapshots = glob.glob(inPat)
if len(snapshots) != 1:
    print "Run directory %s does not have exactly 1 'before' snapshot." % inDir
    sys.exit(1)
inFile = snapshots[0]

schemaFile = os.path.join(inDir, joboptions.schemaFile)


# parse the schema
schema = md.parse(schemaFile)
schemas = schema.getElementsByTagName(joboptions.schemaTag)
if len(schemas) != 1:
    print "Run directory %s does not have exactly 1 schema." % inDir
    sys.exit(2)
schema = schemas[0]

shapes = {}
indices = {}
for tag in joboptions.shapeTags:
    elements = schema.getElementsByTagName(tag)
    shape = util.scalar(elements)
    shape = shape.getAttribute("ID")
    shape = util.uncompressSequence(shape)
    while True:
        try:
            shape.remove(joboptions.broadcast)
        except ValueError:
            break
    shape.sort()
    indices[tag] = shape
    shape = len(shape)
    shapes[tag] = shape
    pass

# parse the config data
doc = md.parse(inFile)

output = html.Element("HTML")
output.addChild("\n")

# get stuff from CAL front ends
# and make tables of it
for registerTag in joboptions.calTags:
    elements = doc.getElementsByTagName(registerTag)
    container = util.contain(elements, shapes)

    for jtem, tem in enumerate(container):
        sides = []
        for iside, side in enumerate(tem):
            #output.addChild(html.Element("HR"))
            #output.addChild("\n")

            sideLabel = temUtil.cccSideMap[iside]
            registerLabel = temUtil.registerMap[registerTag]
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

    output.addChild("\n")
    output.addChild(html.Element("HR"))
    output.addChild("\n")
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

splitCaption = "Tracker Split Points (Left:Right)"
hTable = table.oneDTable(array, splitCaption, labels)
output.addChild(hTable)




# put out the output
output = str(output)
destDir = os.path.join(joboptions.outDir, runNumber, joboptions.reportDir)
outputFile = os.path.join(destDir, joboptions.outFile)
file(outputFile, "w").write(output)

