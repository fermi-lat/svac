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


    #
    def __init__(self, seq=None, shape=None, empty=None):
        """@brief Create a list.

        @param seq

        @param shape 
        
        @param empty The value to put in unfilled cells.
        Default is None.

        @return The new list.

        """

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


    pass

