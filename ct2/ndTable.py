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
class ndDict(dict):
    """@brief A multidimensional dictionary."""


    #
    def __init__(self, empty=None):
        """@brief Create a new empty mulitdiensional dict.

        @param empty The default value for empty cells.

        """
        
        self.empty = empty
        dict.__init__(self)


    #
    def __getitem__(self, key):
        
        pass


    #
    def __setitem__(self, key, value):
        
        pass
    
