## @file unBinnedFT.py
## @brief Fourier transform of an unbinned event list.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Fourier transform of an unbinned event list.

"""

import numarray as num

#
def transform(times, freqs, byPhase=False):
    """Fourier transform of an unbinned event list.

    @arg times The list (or preferably array) of event times.

    @arg freqs The list (or preferably array) of frequencies at which
    the transform is to be evaluated.  Measured in 1/ whatever units
    @a times is expressed in.

    @arg [byPhase] If true, @a freqs contains exp(-2j * pi * frequency)
    instead of frequency.  Improves performance if this is called repeatedly
    with the same frequency grid.

    @ret A complex array of the same shape as @a freqs.

    """

    if byPhase:
        phase = freqs
    else:
        phase = phases(freqs)
        pass
    ift = power.outer(phase, times)
    tft = add.reduce(ift, axis=1)
    return tft

#
def pds(times, freqs):
    phase = phases(freqs)
    segments = []
    pShape = (len(segments),) + phase.shape
    powers = num.zeros(pShape, num.Complex64)
    for iSeg, segment in enumerate(segments):
        tform = transform(segment, phases, byPhase=True)
        segPower = tform.real**2 + tform.imag**2
        powers[iSeg] = segPower
        pass
    power = num.add.reduce(powers) / len(powers)
    dPower = num.sqrt(num.add.reduce((powers - power)**2) / len(powers))
    return power, dPower

#
def phases(freqs):
    omega = 2 * num.pi * num.asarray(freqs)
    phase = exp(-1j * omega)
    return phase

#
def segmentize(times, length):
    segments = []
    return segments
