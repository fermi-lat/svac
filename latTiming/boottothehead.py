#!/usr/bin/env python

import os, sys

# try:
#     import numarray as num
# except ImportError:
#     import Numeric as num

# if num.__name__ == 'numarray':
#     try:
#         import numarray.fft as fft
#     except ImportError:
#         import FFT2 as fft
# else:
#     import FFT as fft
import Numeric as num
import FFT as fft

import cfitsio

import Model, histogram, stats, tableio
#import qdfits

## configuration
nanoscale = 1e9 # cycles/s of the nano clock
nanogran = 50. # bins/s of the nano clock

#cyclescale = 16e6 # wrong!
#cyclescale = 2.**24 # also wrong
cyclescale = 1 / 60e-9 # cycles/s and bins/s of the cycle clock
upperscale = 2.**32

nominal_ratio = 50.0 # nominal value of nanoscale/cyclescale

clockerror = 0 # Do we calculate uncertainties in the clock ratio?

histbins = 204
histextra = 0.01

#shorttime = 0.003 # Make short separation histogram below here
shorttime = 0.0005 # Make short separation histogram below here
peakcut = 0.002 # Anything below here is assumed to be in the 1.7ms peaks

psd_lc_bins = 2 ** 24 # big FFT
psd_display_bins = 2 ** 10 # rebin PSD to display this many bins

lcbins = 2 ** 9 # display light curve with this many bins

psd_peak = 525.0, 650.0 # should be a peak in the PSD in this range
psd_cut = 2.0 # split between lo and hi frequency PSD
## end config


## get input and output names
infile = sys.argv[1]

if len(sys.argv) > 2:
    outroot = sys.argv[2]
else:
    outroot = os.path.basename(infile)
    outroot = outroot.split('.')[0]

errfile = outroot + '_err.qdp'
widefile = outroot + '_wide.qdp'
narrowfile = outroot + '_narrow.qdp'
lcfile = outroot + '_lc.qdp'
hipsdfile = outroot + '_hipsd.qdp'
peakfile = outroot + '_pkpsd.qdp'
lopsdfile = outroot + '_lopsd.qdp'
longfile = outroot + '_long.qdp'
shortfile = outroot + '_short.qdp'
longpsdfile = outroot + '_longpsd.qdp'
beforefile = outroot + '_before.qdp'

aside = sys.stderr


def edges(lo, hi, bins=histbins, extra=histextra):
    extra = (hi - lo) * histextra
    bottom = lo - extra
    top = hi + extra
    delta = float(top - bottom) / histbins
    epsilon = delta / 2
    edges = num.arange(bottom, top+epsilon, delta)
    return edges


def txttimes(timefile):
    """This works on ASCII files with columns containing
    seconds, nanoseconds, upper and lower
    dumped from the FITS files."""
    
    try:
        reader = timefile.readlines
    except AttributeError:
        reader = open(timefile).readlines

    lines = reader()
    nlines = len(lines)
    ncols = len(lines[0].split())

    data = num.zeros((nlines, ncols), num.Float64)

    for iline in xrange(len(lines)):
        data[iline] = map(float, lines[iline].split())

    data = num.transpose(data)
    return data


def fitstimes(infile):
    EVT_HDU = 2
    SEC_COL = 4
    NAN_COL = 5
    UPP_COL = 6
    LOW_COL = 7

    four_gib = 2.0 ** 32

    status, fptr = cfitsio.fits_open_file(infile, cfitsio.READONLY)
    status, hdu = cfitsio.fits_movabs_hdu(fptr, EVT_HDU)

    status, nrows = cfitsio.fits_get_num_rows(fptr)

    data = num.zeros((4, nrows), num.Float64)

    status, data[0] = cfitsio.fits_read_col_uint(fptr, SEC_COL, 1, 1, nrows)
    status, data[1] = cfitsio.fits_read_col_uint(fptr, NAN_COL, 1, 1, nrows)
    status, data[2] = cfitsio.fits_read_col_uint(fptr, UPP_COL, 1, 1, nrows)
    status, data[3] = cfitsio.fits_read_col_uint(fptr, LOW_COL, 1, 1, nrows)

    status = cfitsio.fits_close_file(fptr)

    # data were unsigned, but Numeric thought they were signed, so fix it.
    # No telling what will happen if you're not running this on Linux/Intel.
    data += four_gib * (data < 0)

    return data


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


def filter(events, cut):
    delta = events[1:] - events[:-1]
    mask = delta < cut
    short = num.nonzero(mask) + 1
    short = num.take(events, short)
    long = num.nonzero(num.logical_not(mask)) + 1
    long = num.take(events, long)
    return long, short


## read some data
aside.write("Reading data from %s ... " % infile)

# # FITS from cvfits
# Never mind, cvfits didn't work.
# infp = qdfits.QDFits(infile)
# nanos = infp.getColumn(1, 0)
# cycles = infp.getColumn(1,1)

# # ASCII from txtdmp
# seconds, nanoseconds, upper, lower = txttimes(infile)

# digiFITS
seconds, nanoseconds, upper, lower = fitstimes(infile)

nanos = (seconds - seconds[0]) * nanoscale + nanoseconds
cycles = (upper - upper[0]) * upperscale + lower

#nanos -= nanos[0]
#cycles -= cycles[0]

aside.write("ok\n")


## compare seconds/nanos & upper/lower
aside.write("Comparing timebases ... ")

aside.write("calibrating ... ")
# We don't know the true clock speed well enough for a proper comparison,
# so we must measure their ratio.  Do a least-squares fit, treating the
# less-accurate one as a linear function of the more-accurate.

# Reference both to times in their middle.  This should make the linear and
# constant terms of the model uncorrelated, and the offset between the two
# time streams is random anyway.
tnano = nanos - stats.average(nanos)
tcycle = cycles - stats.average(cycles)

def lin((offset, ratio), time):
    othertime = offset + ratio * time
    return othertime

startparm = [0.0, nominal_ratio]
sigma = nanoscale / nanogran
model = Model.Model(lin, startparm, tcycle, tnano, sigma)
endparm, stat, covar = model.fit()
# find a better error estimate so we can find uncertainties
ndof = len(tcycle) - len(startparm)
sigrat = num.sqrt(stat / ndof)
sigma /= sigrat
model.sigma = sigma
endparm, stat, covar = model.fit()
offset, ratio = endparm
aside.write("errors ... ")
if clockerror:
    deltarat = model.uncertain((1,))[0] # slow!
else:
    deltarat = num.sqrt(covar[1, 1])
    deltarat = (-deltarat, deltarat)

# take difference
tcycle = model()
error = (tcycle - tnano) /  nanoscale

# make a histogram
mine = num.minimum.reduce(error)
maxe = num.maximum.reduce(error)
binner = histogram.Histogram(edges(mine, maxe), normwidth=0, normtot=0)

# put data in it
binner.add(error)

# get answers out
cen = binner.centers
hist, err = binner.getvalue()

# put them in a file
ofp = open(errfile, 'w')
ofp.write("read serr 2\nerr off\nline step\n")
ofp.write("! Data taken from %s\n" % infile)
ofp.write("! Clock ratio = %.17g +%.7g/%.7g\n" %
          (ratio, deltarat[1], deltarat[0]))
ofp.write("! tnano sigma = %.17g\n" % sigma)
ofp.write("! Minimum error = %.17g, maximum = %.17g\n" % (mine, maxe))
ofp.write("label top Time Error Distribution\n")
ofp.write("label x Event Separation (s)\n")
ofp.write("label y Events / bin\n")
tableio.writetable((cen, hist, err), ofp)
ofp.close()

aside.write("ok\n")


## histogram waiting times, from the more accurate timebase
aside.write("Checking waiting times ... ")

wtimes = (cycles[1:] - cycles[:-1]) / cyclescale

inpeak = howmany(wtimes < peakcut)
pctpeak = 100.0 * inpeak / len(wtimes)

mint = num.minimum.reduce(wtimes)
maxt = num.maximum.reduce(wtimes)

# make a histogram at long times
aside.write("long ... ")
binner = histogram.Histogram(edges(mint, maxt), normwidth=0, normtot=0)
binner.add(wtimes)
cen = binner.centers
hist, err = binner.getvalue()
ofp = open(widefile, 'w')
ofp.write("read serr 2\nerr off\nline step\nlog y\n")
ofp.write("! Data taken from %s\n" % infile)
ofp.write("! Minimum waiting time = %.17g, maximum = %.17g\n" % (mint, maxt))
ofp.write("label top Long Waiting Time Distribution\n")
ofp.write("label x Event Separation (s)\n")
ofp.write("label y Events / bin\n")
tableio.writetable((cen, hist, err), ofp)
ofp.close()

# make a histogram at short times
aside.write("short ... ")
binner = histogram.Histogram(edges(mint, shorttime), normwidth=0, normtot=0)
binner.add(wtimes)
cen = binner.centers
hist, err = binner.getvalue()
ofp = open(narrowfile, 'w')
ofp.write("read serr 2\nerr off\nline step\nlog y\n")
ofp.write("! Data taken from %s\n" % infile)
ofp.write("! Minimum waiting time = %.17g, maximum = %.17g\n" % (mint, maxt))
ofp.write("! %.3g %% in 1.7ms peaks.\n" % pctpeak)
ofp.write("label top Short Waiting Time Distribution\n")
ofp.write("label x Event Separation (s)\n")
ofp.write("label y Events / bin\n")
tableio.writetable((cen, hist, err), ofp)
ofp.close()

aside.write("ok\n")


## Make a power spectrum
aside.write("Making light curve and PSD ... ")

bintime = cycles - cycles[0]

rate = bintime[-1] / cyclescale / (len(bintime) - 1)

maxbins = bintime[-1]
binfactor = int(maxbins / psd_lc_bins)
last_bin = psd_lc_bins * float(binfactor)
bintime = num.compress(bintime<last_bin, bintime)

nevent = len(bintime)
freqres = cyclescale / last_bin

aside.write("binning ... ")
hedges = num.arange(psd_lc_bins) * float(binfactor)
lcurve = lightcurve(bintime, hedges)
del hedges # It's so big!

aside.write("light curve ... ")
lc_lo, lcerr = rebin(lcurve, lcbins, 0)
lcfactor = float(psd_lc_bins / lcbins) 
binsize = lcfactor * binfactor / cyclescale
lc_lo /= binsize
lcerr /= binsize
lctaxis = num.arange(lcbins) * binsize + binsize / 2

ofp = open(lcfile, 'w')
ofp.write("read serr 2\nline step\nerr off\n")
ofp.write("! Data taken from %s\n" % infile)
ofp.write("! Average rate = %g events/s\n" % rate)
ofp.write("label x Time (s)\n")
ofp.write("label y Event Rate (s\u-1\d)\n")
ofp.write("label top Light Curve\n")
tableio.writetable((lctaxis, lc_lo, lcerr), ofp)
ofp.close()

aside.write("transforming ... ")
psd = fft.real_fft(lcurve)[1:]
del lcurve # It's so big!
psd = psd.real ** 2 + psd.imaginary ** 2
# Leahy norm
psd = psd * (2.0 / nevent)

aside.write("PSD output ... ")
orig_freq = (num.arange(len(psd)) + 1) * freqres

# high-freq display
aside.write("high ... ")
mask = orig_freq > psd_cut
hfpsd = num.compress(mask, psd)
hfpsd, hferr = rebin(hfpsd, psd_display_bins)
hfreq = num.compress(mask, orig_freq)
hfreq, junk = rebin(hfreq, psd_display_bins)
ofp = open(hipsdfile, 'w')
ofp.write("read serr 2\n")
ofp.write("label x Frequency (Hz)\n")
ofp.write("label y Power (Leahy)\n")
ofp.write("label top Power Spectrum\n")
tableio.writetable((hfreq, hfpsd, hferr), ofp)
ofp.close()

# low-freq display
aside.write("low ... ")
mask = orig_freq < psd_cut
lfpsd = num.compress(mask, psd)
lfpsd, lferr = rebin(lfpsd, psd_display_bins)
lfreq = num.compress(mask, orig_freq)
lfreq, junk = rebin(lfreq, psd_display_bins)
ofp = open(lopsdfile, 'w')
ofp.write("read serr 2\nlog x y\nline step\n")
ofp.write("label x Frequency (Hz)\n")
ofp.write("label y Power (Leahy)\n")
ofp.write("label top Power Spectrum\n")
tableio.writetable((lfreq, lfpsd, lferr), ofp)
ofp.close()

# # display around expected peak freq
# aside.write("peak ... ")
# mask = (orig_freq > psd_peak[0]) & (orig_freq < psd_peak[1])
# ppsd = num.compress(mask, psd)
# ppsd, perr = rebin(ppsd, psd_display_bins)
# pfreq = num.compress(mask, orig_freq)
# pfreq, junk = rebin(pfreq, psd_display_bins)
# ofp = open(peakfile, 'w')
# ofp.write("read serr 2\n")
# ofp.write("label x Frequency (Hz)\n")
# ofp.write("label y Power (Leahy)\n")
# ofp.write("label top Power Spectrum\n")
# tableio.writetable((pfreq, ppsd, perr), ofp)
# ofp.close()

aside.write("ok\n")


## look at events in waiting-time peak separately
aside.write("Separating long and short times ... ")
ccut = peakcut * cyclescale
long, short = filter(cycles, ccut)

ldel = long[1:] - long[:-1]
lmin = num.minimum.reduce(ldel)
lmax = num.maximum.reduce(ldel)
hedges = num.exp(edges(num.log(lmin), num.log(lmax)))
binner = histogram.Histogram(hedges)
binner.add(ldel)
cen = binner.centers
hist, err = binner.getvalue()
ofp = open(longfile, 'w')
ofp.write("read serr 2\n")
tableio.writetable((cen, hist, err), ofp)
ofp.close()

sdel = short[1:] - short[:-1]
smin = num.minimum.reduce(sdel)
smax = num.maximum.reduce(sdel)
hedges = num.exp(edges(num.log(smin), num.log(smax)))
binner = histogram.Histogram(hedges)
binner.add(sdel)
cen = binner.centers
hist, err = binner.getvalue()
ofp = open(shortfile, 'w')
ofp.write("read serr 2\n")
tableio.writetable((cen, hist, err), ofp)
ofp.close()

aside.write('ok\n')


## Make a power spectrum of just "long" events
aside.write("Making long event PSD ... ")

bintime = long - long[0]
maxbins = bintime[-1]
binfactor = int(maxbins / psd_lc_bins)
last_bin = psd_lc_bins * float(binfactor)
bintime = num.compress(bintime<last_bin, bintime)

nevent = len(bintime)
freqres = cyclescale / last_bin

aside.write("binning ... ")
hedges = num.arange(psd_lc_bins) * float(binfactor)
lcurve = lightcurve(bintime, hedges)
del hedges # It's so big!

aside.write("transforming ... ")
psd = fft.real_fft(lcurve)[1:]
del lcurve # It's so big!
psd = psd.real ** 2 + psd.imaginary ** 2
# Leahy norm
psd = psd * (2.0 / nevent)

aside.write("PSD output ... ")
orig_freq = (num.arange(len(psd)) + 1) * freqres

# high-freq display
aside.write("high ... ")
mask = orig_freq > psd_cut
hfpsd = num.compress(mask, psd)
hfpsd, hferr = rebin(hfpsd, psd_display_bins)
hfreq = num.compress(mask, orig_freq)
hfreq, junk = rebin(hfreq, psd_display_bins)
ofp = open(longpsdfile, 'w')
ofp.write("read serr 2\n")
ofp.write("label x Frequency (Hz)\n")
ofp.write("label y Power (Leahy)\n")
ofp.write("label top Power Spectrum\n")
tableio.writetable((hfreq, hfpsd, hferr), ofp)
ofp.close()

aside.write('ok\n')



## Look at dist of times before peak events
## compare to dist of times before non-peak events
aside.write("Events before ... ")

mask = wtimes < peakcut
short = num.nonzero(mask)
if not short[0]:
    short = short[1:]
short -= 1
short = num.take(wtimes, short)
smin = num.minimum.reduce(short)
smax = num.maximum.reduce(short)

long = num.nonzero(num.logical_not(mask))
if not long[0]:
    long = long[1:]
long -= 1
long = num.take(wtimes, long)
lmin = num.minimum.reduce(long)
lmax = num.maximum.reduce(long)

emin = min(smin, lmin)
emax = max(smax, lmax)
hedges = edges(emin, emax)

sbin = histogram.Histogram(hedges)
sbin.add(short)
lbin = histogram.Histogram(hedges)
lbin.add(long)

cen = sbin.centers
shist, serr = sbin.getvalue()
lhist, lerr = lbin.getvalue()

ofp = open(beforefile, 'w')
ofp.write("read serr 2 3\n")
tableio.writetable((cen,shist, serr, lhist, lerr), ofp)
ofp.close()

aside.write("ok\n")
