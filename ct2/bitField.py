## @file bitField.py
## @brief Read specified bits from integers as (smaller) integers.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Read specified bits from integers as (smaller) integers.

"""

#
class subField:

    """@brief Read specified bits from integers as (smaller) integers.

    subField(low, high)
    subField(spec)

    @param low An integer, giving the number of the lowest-order bit (starting
    from 0) to be included in the field.

    @param high An integer, giving the highest-order bit to be included in the
    field.  This is unpythonic, but these specifications are also used as
    documentation for nonprogrammers.  May also be None, in which case there
    is no upper limit.

    @param spec A string, consisting of either:@n
    a single integer, which will be the entire field;@n
    '*', in which case the argument will be return unmolested;@n
    a hyphenated range, 'low-high'.  Either limit may be '*', which is
    equivalent to 0 (for low) or None (for high).

    @return Instances are callable with integer argument, and will return the
    specified subfield.

    """

    #
    def __init__(self, *args):
        # UNPYTHONIC: high is the last bit that's in (not the first that's out)
        if len(args) == 1:
            low, high = parseField(args[0])
        elif len(args) == 2:
            low, high = args
        else:
            raise ValueError

        # self.low is the first bit tht's in
        self.low = low
        
        # self.high is 2**(first bit that's out)
        if high is None:
            self.high = 0
        else:
            self.high = 2 ** (high + 1)
            pass
        return

    #
    def __call__(self, field):
        if self.high:
            field = field % self.high
            pass
        field = field >> self.low
        return field

    pass


#
def parseField(field):
    """@brief Parse arguments to bitField constructor into canaonical form"""
    limits = field.split('-')
    nlim = len(limits)
    if nlim < 1 or nlim > 2:
        raise ValueError
    if nlim == 1:
        limit = limits[0]
        if limit == '*' or limit == '':
            return 0, None
        else:
            limit = int(limit, 0)
            return limit, limit
        pass
    if limits[0] == '*':
        limits[0] = 0
    else:
        limits[0] = int(limits[0], 0)
        pass
    if limits[1] == '*':
        limits[1] = None
        pass
    if limits[1] is not None:
        limits[1] = int(limits[1], 0)
        pass
            
    return limits
