## @file ndTable.py
## @brief Multidimensional tables
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief Multdimensional tables.

"""


#
class ndTable:
    """@brief Multdimensional tables.

    """


    #
    def __init__(self, seq=None, shape=None, empty=None):
        """@brief Create a table.

        @param seq

        @param shape 
        
        @param empty The value to put in unfilled cells.
        Default is None.

        @return The new table.

        """

        

    pass


#
def parseKey(key):
    theRest = None
    if isinstance(key, tuple):
        if len(key) > 1:
            theRest = key[1:]
        key = key[0]
    return key, theRest



#
class ndDict(dict):
    """@brief A multidimensional dictionary.
    Returns a default value for getitem on nonexistent keys.

    """


    #
    def __init__(self, empty=None):
        """@brief Create a new empty mulitdiensional dict.

        @param empty The default value for empty cells.

        """
        
        self.empty = empty
        dict.__init__(self)


    #
    def __getitem__(self, key):
        myKey, theRest = parseKey(key)
        if myKey not in self:
            return self.empty
        next = dict.__getitem__(self, myKey)
        if theRest is None:
            return next
        else:
            return next[theRest]
        

    #
    def __setitem__(self, key, value):
        myKey, theRest = parseKey(key)
        if theRest is None:
            dict.__setitem__(self, myKey, value)
        else:
            if myKey not in self:
                dict.__setitem__(self, myKey, ndDict(empty=self.empty))
            next = dict.__getitem__(self, myKey)
            next[theRest] = value
        return
