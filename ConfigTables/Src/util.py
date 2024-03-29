
import glob
import operator
import os
import re
import sys
import types

import xmlUtil


def maxLen(array):
    array = flatten(array)
    lengths = map(len, array)
    longest = max(lengths)
    return longest

def superMap(func, args, depth=sys.maxint):
    if depth == 0 or not isSequence(args):
        return func(args)
    depth -= 1
    ret = []
    for arg in args:
        ret.append(superMap(func, arg, depth))
    return ret

def isSequence(arg):
    if (hasattr(arg, "__getitem__") or \
       hasattr(arg, "__iter__")) and \
       not isinstance(arg, types.StringType):
        return True
    else:
        return False

def scalar(val):
    if len(val) != 1:
        message = r"""The programmer expected the following list:
%r
to have exactly 1 member.  While he anticipated the possibility that it might
not, and checked for that condition, he didn't actually DO anything about it.
        """ % val
        raise ValueError, message
    else:
        val = val[0]
    return val

def flatten(array, depth=sys.maxint):
    if depth == 0 or \
       isinstance(array, types.StringType) or \
       not isSequence(array):
        return [array]
    depth -= 1
    ret = []
    for item in array:
        ret.extend(flatten(item, depth))
    return ret
    

def getShape(seq):
    """Return the shape (in the Numeric sense) of a nested sequence or mapping.

    """

    if isinstance(seq, types.StringType):
        return []
    try:
        myLen = len(seq)
    except TypeError:
        return []
    except AttributeError:
        return []

    try:
        subseq = seq.values()
    except AttributeError:
        subseq = seq

    childShapes = map(getShape, subseq)
    for test in childShapes[1:]:
        if test != childShapes[0]:
            raise ValueError, "Argument is not rectangular."

    shape = childShapes[0]
    shape.insert(0, myLen)
    return shape


def transpose(array):
    shape = getShape(array)
    shape.reverse()
    new = mkEmpty(shape)
    for irow in range(shape[1]):
        for icol in range(shape[0]):
            new[icol][irow] = array[irow][icol]
            pass
        pass
    return new


def getLabels(seq):
    """Return "axis labels" for a nested mapping.

    """

    try:
        myLabels = seq.keys()
    except AttributeError:
        return []
    myLabels.sort()

    childLabels = []
    for child in myLabels:
        childLabels.append(getLabels(seq[child]))
    for test in childLabels[1:]:
        if test != childLabels[0]:
            raise ValueError, "Labels of children do not match."
        
    labels = [myLabels]
    if childLabels:
        labels.extend(childLabels[0])

    return labels
    

def mkEmpty(shape, blank=0):
    if len(shape) == 0:
        empty = []
    elif len(shape) == 1:
        empty = [blank] * shape[0]
    else:
        empty = map(lambda x: mkEmpty(x, blank=blank), [shape[1:]] * shape[0])
    return empty


def parseRange(idStr):
    ranges = idStr.split(",")
    ends = map(lambda x:x.split("-"), ranges)
    return ends

def uncompressSequence(seqStr, sepChar=","):
  l = []
  s = seqStr.split(sepChar)
  for x in s:
    x = x.strip()
    p = x.find("-")
    if p == -1:
      if x == "*":
        l.append(255)
      else:
        l.append(int(x))
    else:
      fNum = int(x[0:p])
      tNum = int(x[p+1:])
      l += range(fNum, tNum+1)
  return l


class SubField:

    def __init__(self, low, high):
        self.low = low
        self.high = 2 ** high

    def __call__(self, field):
        field = field % self.high
        field = field >> self.low
        return field


def getSplit(nLeft, nRight, leftTfes, rightTfes):
    "Ugly hardcoded constants."
    #print nLeft, nRight
    #print leftTfes
    #print rightTfes
    nTfe = 24
    badMagic = 63
    if nLeft == badMagic and nRight == badMagic:
        return "Absent"
    if nLeft + nRight > nTfe:
        return "Error"
    leftTfes = leftTfes[:nLeft]
    #print leftTfes
    firstRight = nTfe - nRight
    rightTfes = rightTfes[firstRight:]
    #print rightTfes
    if nLeft:
        if leftTfes[-1] != 1:
            return "Error"
        for lefty in leftTfes[:-1]:
            if lefty != 0:
                return "Error"
    if nRight:
        if rightTfes[0] != 3:
            return "Error"
        for righty in rightTfes[1:]:
            if righty != 2:
                return "Error"
    return "%s:%s" % (nLeft, nRight)

topTag = "GLAT"
attr = "ID"
def getRegisters(elements, topTag=topTag, attr=attr):
    """@brief Find path to, and coordinates of, a set of XML elements.

    @param elements A sequence of XML elements.

    @param topTag The 'root' tag.  Parents of the elements will be found until
    this tagName is reached.  Optional, default is 'GLAT'.

    @param attr The attribute of parents used to generate coordinates.
    Optional, default is 'ID'.

    @return A tuple containing:
    @li A list of element, coordinate pairs.
    @li The path from topTag to the elements.

    """
    
    all = []
    #elements = doc.getElementsByTagName(tag)
    if len(elements) == 0:
        return [], []
    for element in elements:
        node = element
        path = []
        tagPath = []
        while True:
            parent = node.parentNode
            parTag = parent.tagName
            if parTag == topTag:
                break
            path.append(xmlUtil.getId(parent))
            tagPath.append(parTag)
            node = parent
        path.reverse()
        tagPath.reverse()
        all.append((element, path))
    return all, tagPath


def putVal(container, value, path):
    """@brief Assign a value to a cell in a nested sequence.

    @param container The nested sequence.

    @param value The value to put in the cell.

    @param path The coordinates of the cell to be filled.

    @return None.

    """
    
    for index in path[:-1]:
        container = container[index]
    container[path[-1]] = value
    return


def contain(elements, shapes, blank=0):
    """@brief Put integer values of XML elements into a nested sequence.

    @param elements A sequence of XML elements.

    @param shapes A dict with keys that are tagNames and values that are the
    expected number of elements or parents with that tagName.  This is used to
    set the dimensions of the containing sequence.

    @param blank The default value to put in cells for which there is no
    element.  Optional, default is 0.

    @return A nested sequence containing the integer values of the elements.

    """
    
    elements, tags = getRegisters(elements)

    shape = []
    for tag in tags:
        shape.append(shapes[tag])
        pass
    container = mkEmpty(shape, blank)


    for element, path in elements:
        putVal(container, xmlUtil.intVal(element), path)
        pass
    
    return container


def printArray(array):
    for row in array:
        print row
        pass
    return


