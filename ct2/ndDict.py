## @file ndDict.py
## @brief Multidimensional dictionaries
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief Multdimensional dictionaries.

"""


#
def _mergeLists(*args):
    print "merge", args
    import bisect
    merged = []
    for arg in args:
        for item in arg:
            if item not in merged:
                bisect.insort(merged, item)
    return merged


#
class ndDict(dict):

    #
    def __init__(self, dim=1, empty=None):
        if dim < 1:
            raise ValueError, "Must have positive dimensions."
        self.dim = dim
        self.empty = empty
        dict.__init__(self)
        return

    #
    def __getitem__(self, key):
        print "get", key
        if isinstance(key, tuple):
            keyLen = len(key)
            if keyLen > self.dim:
                raise KeyError, "Too many indices."
            elif keyLen == 1:
                return self._getSimple(key[0])
            elif keyLen == 0:
                return self
            else:
                # delegate
                return self._getSimple(key[0])[key[1:]]
        else:
            return self._getSimple(key)
        return

    #
    def _getSimple(self, key):
        if self.has_key(key):
            value = dict.__getitem__(self, key)
        else:
            value = self.empty
            pass
        return value

    #
    def __setitem__(self, key, value):
        print "set", key
        if isinstance(key, tuple):
            keyLen = len(key)
            if keyLen > self.dim:
                raise KeyError, "Too many indices."
            elif keyLen == 1:
                self._setSimple(key[0], value)
                pass
            else:
                myKey = key[0]
                if self.has_key(myKey):
                    next = dict.__getitem__(self, myKey)
                else:
                    next = self.__class__(empty=self.empty, dim=self.dim-1)
                    self._setSimple(myKey, next)
                    pass
                next[key[1:]] = value
                pass
            pass
        else:
            self._setSimple(key, value)
        return
    
    #
    def _setSimple(self, key, value):
        if self.dim != 1 and \
           (not isinstance(value, self.__class__) or \
            value.dim != self.dim-1):
            raise ValueError, "Can't assign to slices."
        dict.__setitem__(self, key, value)
        return


    #
    def indices(self):
        myInd = self.keys()
        myInd.sort()
        if self.dim == 1:
            return [myInd]
        subDim = self.dim - 1
        indices = []
        for ii in range(subDim):
            indices.append([])
            pass
        for child in self.values():
            cInd = child.indices()
            for ii in range(subDim):
                indices[ii].append(cInd[ii])
                pass
            pass
        for ii in range(subDim):
            indices[ii] = _mergeLists(*indices[ii])
            pass
        indices.insert(0, myInd)
        return indices

    #
    def shape(self):
        indices = self.indices()
        shape = map(len, indices)
        return shape


    #
    def map(self, func):
        print "map", self
        result = self.__class__(dim=self.dim, empty=self.empty)
        for key, arg in self.items():
            if self.dim == 1:
                value = func(arg)
            else:
                value = arg.map(func)
                pass
            result[key] = value
        return result


    #
    def array(self):
        return
    
