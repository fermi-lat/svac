#!/usr/bin/env python

import os
import re
import sys

import runner

termRe = re.compile('\d{3}$') # how we recognize a terminal directory
numRe = re.compile('^\d{3}(x{3})*$')
verRe = re.compile('^\d+\.\d+$')

defPrefChars = 4

#zipDest = '/nfs/farm/g/glast/u41/L1/logs/DEV/L1Proc/archived'
zipDest = '/nfs/farm/g/glast/u41/L1/logs/PROD/L1Proc/archived'
delivTag = 'deliveries'
runTag = 'runs'
allTags = [delivTag, runTag]

preWash = """find * \( -name '*.gz' -exec gunzip '{}' \; -print \) -o \( \( -name 'core.*' -o -name '*.root' \) -exec rm '{}' \; -print \)"""


def shuffleDirs(topDir):
    head, tail = os.path.split(topDir)
    if head:
        origDir = os.getcwd()
        os.chdir(head)
        pass

    print >> sys.stderr, 'Examining directory %s ...' % topDir
    delivs, runs = getDelivsAndRuns(tail)

    print >> sys.stderr, 'Moving deliveries..'
    delDirs = moveDirs(delivs, delivTag)
    print >> sys.stderr, 'Moving runs..'
    runDirs = moveDirs(runs, runTag)

    # for tmpDir in delDirs: zipOne(tmpDir, delivTag)
    # for tmpDir in runDirs: zipOne(tmpDir, runTag)

    if head: os.chdir(origDir)
    return


def moveDirs(can, head, prefChars=None):
    if prefChars is None: prefChars = defPrefChars

    zippables = set()
    for key, subDirs in can.items():
        middle = key[:prefChars]
        zippable = os.path.join(head, middle)
        zippables.add(zippable)
        front = os.path.join(zippable, key)
        for subDir in subDirs:
            # tail, final = os.path.split(subDir)
            # dest = os.path.join(front, tail)
            # os.makedirs(dest)
            target = os.path.join(front, subDir)
            os.renames(subDir, target)
            continue
        continue
    
    return zippables


def doZip(topDir):
    status = 0
    origDir = os.getcwd()
    os.chdir(topDir)
    zippables = findZippables(topDir)
    for tag, subDirs in zippables.items():
        for subDir in subDirs:
            status |= zipOne(subDir, tag)
            if status: return status
            continue
        continue
    os.chdir(origDir)
    return status


def findZippables(topDir):
    origDir = os.getcwd()
    os.chdir(topDir)
    zippables = {}
    for tag in allTags:
        these = [os.path.join(tag, subDir) for subDir in os.listdir(tag)]
        zippables[tag] = these
        continue
    os.chdir(origDir)
    return zippables


def zipOne(source, tag, unGz=True):
    print >> sys.stderr, 'Zipping %s' % source
    
    status = 0
    
    origDir = os.getcwd()
    os.chdir(source)

    head, tail = os.path.split(source)
    subDir = tail[:2]
    zipName = tail + '.zip'
    zipDir = os.path.join(zipDest, tag, subDir)
    
    try:
        os.makedirs(zipDir)
    except OSError: # Huh.
        os.stat(zipDir) # If this succeeds, the dir was already there.
        pass # And if it doesn't, we're borked anyway.
    
    zipPath = os.path.join(zipDir, zipName)

    if unGz: status |= runner.run(preWash)
    if status: return status

    cmd = "zip -9 -T -r -m %s * -x '*.root' 'core.*'" % zipPath
    status |= runner.run(cmd)
    if status: return status

    os.chdir(origDir)
    os.removedirs(source)
    return


def getDelivsAndRuns(topDir):    
    runs = {}
    delivs = {}

    for head, tails, files in os.walk(topDir):
        term = termRe.search(head)
        if not term: continue # intermediate directory

        comps = head.split(os.sep)
        level = checkLevel(comps)

        if level == 'run': # run directory
            can = runs
        elif level == 'delivery': # delivery-level process
            can = delivs
        else: # delivery directory for a run-or-lower level process
            can = None
            pass
        
        if can is not None:
            del tails[:]
            mils, thous, ones = comps[-3:]
            theId = mils[:3] + thous[:3] + ones
            can.setdefault(theId, []).append(head)
            pass
                
        continue

    return delivs, runs


def checkLevel(comps):
    # There should be either 3 or 6 numeric components at the tail of comps
    # if 6, there should be more than one nonnumeric comp below version level
    # if 3, there could be 1 (in which case it's a delivery-level process),
    # or more (in which case we keep looking)

    nNum = 0
    nAlph = 0
    for comp in comps[::-1]:
        if numRe.match(comp):
            nNum += 1
        elif verRe.match(comp):
            break
        else:
            nAlph += 1
            pass
        continue

    assert (nAlph > 0) and (nNum in (3, 6))

    if nNum == 6:
        assert nAlph > 1
        level = 'run'
    else:
        if nAlph == 1: level = 'delivery'
        else: level = 'intermediate'
        pass
    
    return level


funkTable = {
    'shuffle': shuffleDirs,
    'zip': doZip
    }


def parseArgs():
    from optparse import OptionParser
    parser = OptionParser()

    funks = funkTable.keys()
    funks.sort()

    parser.add_option('-m', '--mode', dest='mode', metavar='MODE',
                      default=None,
                      help='mode (required): one of %s' % funks)
    (options, args) = parser.parse_args()


    if options.mode not in funks:
        print >> sys.stderr, "You have to supply a mode, and it must be one of %s" % funks
        sys.exit(1)
        pass
    
    return options, args


def main():
    options, args = parseArgs()
    funk = funkTable[options.mode]
    for topDir in args:
        funk(topDir)
    return

if __name__ == "__main__":
    main()
    
