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
    def __init__(self, data, labels, title):
        """@brief Create a table.

        @param data

        @param labels 
        
        @param title

        @return The new table.

        """

        self.data = data
        self.labels = list(labels)
        self.title = title

        return

    pass

