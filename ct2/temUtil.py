## @file temUtil.py
## @brief Code that knows about the TEM.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Code that knows about the TEM.

"""

#
def getSplit(nLeft, nRight, leftTfes, rightTfes):
    "Ugly hardcoded constants."
    nTfe = 24
    badMagic = 63
    if nLeft == badMagic and nRight == badMagic:
        return "Absent"
    if nLeft + nRight > nTfe:
        return "Error"
    leftTfes = leftTfes[:nLeft]
    firstRight = nTfe - nRight
    rightTfes = rightTfes[firstRight:]
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

