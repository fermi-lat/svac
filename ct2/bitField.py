## @file util.py
## @brief Random useful stuff.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Random useful stuff.

"""

#
class subField:

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
