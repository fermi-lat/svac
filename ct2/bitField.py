## @file bitField.py
## @brief bit fields
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief bit fields

"""


#
class SubField:
    """@brief Extract subfields

    """


    #
    def __init__(self, low, high):
        """@brief Create subfield extractors.

        @param low The low bit of the subfield of interest.
        
        @param high The high bit of the subfield of interest.

        @return A callable obhect that extracts the subfield of interest
        from its argument.

        """

        self.low = low
        self.high = high
        self.highVal = 2 ** high


    #
    def __call__(self, field):
        """@brief Extract the subfield of interest.

        @param field The containing bit field.

        @return The subfield of interest.

        """

        field = field % self.highVal
        field = field >> self.low
        return field

