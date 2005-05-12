## @file lightcurve.py
## @brief Create and manipulate lightcurves.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Create and manipulate lightcurves.

"""

def rebin(seq, newlen, avg=1):
    factor = len(seq) / int(newlen)
    factor = max(factor, 1)
    if avg:
        scale = float(factor)
    else:
        scale = 1.0
    keep = newlen * factor
    seq = seq[:keep]
    seq.shape = (-1, factor)
    rebinned = num.add.reduce(seq, -1) / scale
    sig = (seq - rebinned[:, num.NewAxis]) ** 2
    sig = num.add.reduce(sig, -1) / max(factor-1, 1)
    sig = num.sqrt(sig / factor)
    return rebinned, sig


def lightcurve(a, bins):
    n = num.searchsorted(num.sort(a), bins)
    n = num.concatenate([n, [len(a)]])
    return n[1:]-n[:-1]


def howmany(seq):
    seq = num.asarray(seq)
    seq = seq.astype(num.Int32)
    many = num.add.reduce(seq)
    return many

def edges(lo, hi, bins=histbins, extra=histextra):
    extra = (hi - lo) * histextra
    bottom = lo - extra
    top = hi + extra
    delta = float(top - bottom) / histbins
    epsilon = delta / 2
    edges = num.arange(bottom, top+epsilon, delta)
    return edges

