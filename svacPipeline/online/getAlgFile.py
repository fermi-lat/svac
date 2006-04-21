#!/usr/local/bin/python

import sys
import xml.dom.minidom as md

rcReport = sys.argv[1]
doc = md.parse(rcReport)

nodes = doc.getElementsByTagName('TestName')
if len(nodes) != 1:
    print >> sys.stderr, "rcReport has no testName node."
    sys.exit(1)
    pass

testName = str(nodes[0].childNodes[0].nodeValue)
chunks = testName.split("_")
algFile = "_".join(chunks[1:])
if len(algFile) == 0:
    print >> sys.stderr, "Can't determine algorithm file."
    sys.exit(1)
    pass
algFile += '.xml'

print algFile
