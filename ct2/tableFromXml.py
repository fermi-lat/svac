## @file tableFromXml.py
## @brief make multidimensional tables from XML
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief make multidimensional tables from XML

"""

import ndDict
import ndTable
import util

import jobOptions

#
class xTableGen:
    """@brief Create multidimensional tables from XML.

    """

    #
    def __init__(self, doc, path):
        self.doc = doc
        self.path = path
        location, register, subField = parseReg(path)
        items = [((), self.doc)]
        for tag in location:
            items = addPathStep(items, tag)
            pass
        self.data = ndDict.ndDict(dim=len(location), empty=jobOptions.absent)
        for coord, element in items:
            regVal = getRegister(element, register)
            tabVal = subField(regVal)
            self.data[coord] = tabVal
        return

    #
    def table(self):
        array, labels = self.data.table()
        table = ndTable.ndTable(array, labels, 'foo')
        return table
    
    pass



#
def addPathStep(items, tag):
    newItems = []
    for coord, element in items:
        children = element.getElementsByTagName(tag)
        for child in children:
            id = child.getAttribute('ID') or 0
            newCoord = coord + (int(id),)
            newItems.append((newCoord, child))
            pass
        pass
    return newItems


#
def getRegister(element, tag):
    child = element.getElementsByTagName(tag)[0]
    value = child.childNodes[0].data
    value = int(value, 0)
    return value


#
def parseReg(regStr):
    tags = regStr.split('/')
    tags = [tag for tag in tags if tag] # remove empty components
    location = tags[:-1]
    RF = tags[-1].split(':')
    register = RF[0]
    lRF = len(RF)
    if lRF == 1:
        subField = util.subField('*')
    elif lRF == 2:
        subField = util.subField(RF[1])
    elif lRF > 2:
        raise ValueError, "Register specification %s contains more than 1 bitField." % tags[-1]
    return location, register, subField
