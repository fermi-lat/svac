## @file temUtil.py
## @brief Code that knows about the TEM.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Code that knows about the TEM.

"""

import jobOptions

#
def getSplit(nLeft, nRight, leftTfes, rightTfes):
    "Ugly hardcoded constants."
    nTfe = 24
    badMagic = jobOptions.absent
    if nLeft == badMagic and nRight == badMagic:
        return jobOptions.absent
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
            pass
    if nRight:
        if rightTfes[0] != 3:
            return "Error"
        for righty in rightTfes[1:]:
            if righty != 2:
                return "Error"
            pass
        pass
    nDead = nTfe - nLeft - nRight
    return "%s:%s:%s" % (nLeft, nDead, nRight)

cccSideMap = ("+X", "+Y", "-X", "-Y")
cccLayerMap = ((0,2,4,6),
               (1,3,5,7),
               (0,2,4,6),
               (1,3,5,7))

crcLayerMap = range(4)

tccLRMap = ((0,1), (3,2), (5,4), (6,7))

tkrSideMap = (('Y', 0), ('X', 0), ('Y', 1), ('X', 1))
tkrLayerMap = [[(x[0], 2*i+x[1]) for i in range(9)] for x in tkrSideMap]
