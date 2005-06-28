## @file linFit.py
## @brief Do linear fits.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Do linear fits.

"""

import numarray as num

import Model


#
def linFit(xx, yy, sigma=None, recenter=False, inverse=False, fancyErrors=False):
    """@brief Do linear fits.

    @arg xx The independent variable.

    @arg yy The dependent variable.

    @arg [recenter] If true, subtract averages from @a xx and @a yy before fitting.
    This make the fitted offset and slope uncorrelated, but the offset is random.
    Default is False.

    @arg [inverse] If true, return 1/slope, and its error, instead of slope.
    Default is False.

    @ret A tuple of fitted offset and slope,
    a tuple of uncertainties on fitted parameters, and
    an array of residuals.

    """

    xx = num.asarray(xx)
    yy = num.asarray(yy)

    sGuess = float(yy[-1] - yy[0]) / (xx[-1] - xx[0])
    if inverse:
        sGuess = 1.0 / sGuess
        funk = invLin
    else:
        funk = linear
        pass

    xBar = avg(xx)
    yBar = avg(yy)
    if recenter:
        xx -= xBar
        yy -= yBar
        oGuess = 0.0
    else:
        oGuess = yBar - sGuess * xBar
        pass

    model = Model.Model(funk, (oGuess, sGuess), xx, yy, sigma)
    (offset, slope), stat, covar = model.fit()

    if fancyErrors:
        offserr, serr = model.uncertain((0, 1))
    else:
        offerr, serr = num.sqrt(num.diagonal(covar))
        pass

    resids = yy - model()
    
    return (offset, slope), (offerr, serr), stat, resids


#
def linear((offset, slope), xx):
    return xx * slope + offset

#
def invLin((offset, rate), xx):
    return xx / rate + offset

#
def avg(xx):
    xx = num.asarray(xx, num.Float64)
    avg = num.add.reduce(xx) / len(xx)
    return avg
