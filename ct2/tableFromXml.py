## @file tableFromXml.py
## @brief make multidimensional tables from XML
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief make multidimensional tables from XML

"""

import ndDict

#
class xTableGen:
    """@brief Create multidimensional tables from XML.

    """

    #
    def __init__(self, doc, path):
        self.doc = doc
        self.path = path
        tags = self.path.split('/')
        # remove empty components
        tags = [tag for tag in tags if tag]
        nodeTags = tags[:-1]
        leafTag = tags[-1]
        items = [((), self.doc)]
        print 'items', items
        for tag in nodeTags:
            items = addNext(items, tag)
            print 'items', items
            pass
        self.data = ndDict.ndDict(dim=len(nodeTags), empty='Absent')
        for coord, element in items:
            self.data[coord] = getLast(element, leafTag)
        return
    
    pass



#
def addNext(items, tag):
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
def getLast(element, tag):
    print element, tag
    child = element.getElementsByTagName(tag)[0]
    value = child.childNodes[0].data
    return value
