## @file syncExternal.py
## @brief Synchronize event streams from different sources.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Synchronize event streams from different sources.

"""

try:
    import numarray as num
except:
    try:
        import Numeric as num
    except:
        raise ImportError, "Can't import numarray or Numeric!"

default_guess = 50e-9

#
def sync(these, those, rate=default_guess):
    return
