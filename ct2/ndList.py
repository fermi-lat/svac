## @file ndList.py
## @brief Multidimensional lists
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief Multdimensional lists.

"""


#
class ndList(list):
    """@brief Multdimensional lists.

    """

    super = list


    #
    def __init__(self, seq=None, shape=None, empty=None):
        """@brief Create a list.

        @param seq

        @param shape 
        
        @param empty The value to put in unfilled cells.
        Default is None.

        @return The new list.

        """

        self.super.__init__(self)

        self.shape = list(shape)
        self.empty = empty

        mySize = shape[0]
        childShape = shape[1:]

        if childShape:
            for ic in range(mySize):
                child = self.__class__(shape=childShape, empty=self.empty)
                self.append(child)
                pass
            pass
        else:
            for ic in range(mySize):
                self.append(self.empty)
            pass

        return

    #
    def __getitem__(self, key):
        if isinstance(key, tuple):
            keyLen = len(key)
            if keyLen > len(self.shape):
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
        value = self.super.__getitem__(self, key)
        return value

    #
    def __setitem__(self, key, value):
        if isinstance(key, tuple):
            keyLen = len(key)
            if keyLen > len(self.shape):
                raise KeyError, "Too many indices."
            elif keyLen == 1:
                self._setSimple(key[0], value)
                pass
            else:
                myKey = key[0]
                next = self.super.__getitem__(self, myKey)
                next[key[1:]] = value
                pass
            pass
        else:
            self._setSimple(key, value)
            pass
        return

    #
    def _setSimple(self, key, value):
        if len(self.shape) != 1 and \
           (not isinstance(value, self.__class__) or \
            len(value.shape) != len(self.shape)-1):
            raise ValueError, "Can't assign to slices."
        self.super.__setitem__(self, key, value)
        return

    pass

