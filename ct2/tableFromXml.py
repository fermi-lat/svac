## @file tableFromXml.py
## @brief make multidimensional tables from XML
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief make multidimensional tables from XML

"""

import ndDict
import util

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
        print 'items', items
        for tag in location:
            items = addPathStep(items, tag)
            print 'items', items
            pass
        self.data = ndDict.ndDict(dim=len(location), empty='Absent')
        for coord, element in items:
            regVal = getRegister(element, register)
            tabVal = subField(regVal)
            self.data[coord] = tabVal
        return
    
    pass



#
def addPathStep(items, tag):
    newItems = []
    for coord, element in items:
        children = element.getElementsByTagName(tag)
        for child in children:
            id = child.getAttribute('ID')
            newCoord = coord + (int(id),)
            newItems.append((newCoord, child))
            pass
        pass
    return newItems


#
def getRegister(element, tag):
    print element, tag
    child = element.getElementsByTagName(tag)[0]
    value = child.childNodes[0].data
    value = int(value, 0)
    return value


#
def parseReg(regStr):
    tags = regStr.split('/')
    tags = [tag for tag in tags if tag] # remove empty components
    location = tags[:-1]
    register, field = tags[-1].split(':')
    subField = util.subField(field)
    return location, register, subField
