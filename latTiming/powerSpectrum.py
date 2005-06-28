#!/afs/slac/g/ek/bin/python

import os, sys

import numarray as num
import numarray.fft as fft

import Model, histogram, linFit, stats, tableio
#import qdfits

import readColumns

## configuration
nanoscale = 1e9 # cycles/s of the nano clock
nanoGran = 50. # bins/s of the nano clock

#cyclescale = 16e6 # wrong!
#cyclescale = 2.**24 # also wrong
cyclescale = 1 / 60e-9 # cycles/s and bins/s of the cycle clock
upperscale = 2.**32

oneTick = 50e-9
tickRate = 20e6

nominal_ratio = 50.0 # nominal value of nanoscale/cyclescale

clockerror = 0 # Do we calculate uncertainties in the clock ratio?

histbins = 204
histextra = 0.01

shorttime = 0.0005 # Make short separation histogram below here

psd_lc_bins = 2 ** 24 # big FFT
psd_display_bins = 2 ** 10 # rebin PSD to display this many bins

lcbins = 2 ** 9 # display light curve with this many bins

psd_peak = (0.0, 100.0) # should be a peak in the PSD in this range
psd_cut = 2.0 # split between lo and hi frequency PSD
## end config


## get input and output names
inFile = sys.argv[1]

if len(sys.argv) > 2:
    outroot = sys.argv[2]
else:
    outroot = os.path.basename(inFile)
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
    short = num.nonzero(mask)[0] + 1
    short = num.take(events, short)
    long = num.nonzero(num.logical_not(mask))[0] + 1
    long = num.take(events, long)
    return long, short


## read some data
aside.write("Reading data from %s ... " % inFile)
nTuple = readColumns.readTuple(inFile)

seconds = nTuple['EvtSecond']
nanoseconds = nTuple['EvtNanoSecond']
upper = nTuple['EvtUpperTime']
lower = nTuple['EvtLowerTime']
evtTicks = nTuple['EvtTicks']
 
nanos = (seconds - seconds[0]) * nanoscale + nanoseconds
cycles = (upper - upper[0]) * upperscale + lower

#nanos -= nanos[0]
#cycles -= cycles[0]

aside.write("ok\n")

## calibrate
aside.write("Comparing timebases ... ")

nanErr = 1.0e9 / (nanoGran * num.sqrt(12)) # This should be solid.
cycErr = 1.0 / num.sqrt(12) # We'll make a better guess later.

aside.write("calibrating seconds ... ")
(junk, nanoRate), (trash, nrSigma), nanStat, nanResid = \
       linFit.linFit(evtTicks, nanos, sigma=nanErr, recenter=True)

mine = num.minimum.reduce(nanResid)
maxe = num.maximum.reduce(nanResid)
binner = histogram.Histogram(edges(mine, maxe), normwidth=0, normtot=0)
binner.add(nanResid)
nanCen = binner.centers
nanHist, nhErr = binner.getvalue()

aside.write("calibrating cycles ... ")
(junk, cycleRate), (trash, crSigma), cycStat, cycResid = \
       linFit.linFit(evtTicks, cycles, sigma=cycErr, recenter=True)
# We don't have proper errors on cycles, so pick a value
# that should give the same chisqr as we got for the SBC RTC
# (for which we do have decent errors).)
cycErr *= num.sqrt(cycStat / nanStat)
(junk, cycleRate), (trash, crSigma), cycStat, cycResid = \
       linFit.linFit(evtTicks, cycles, sigma=cycErr, recenter=True)

binner = histogram.Histogram(edges(mine, maxe), normwidth=0, normtot=0)
binner.add(cycResid)
cycHist, chErr = binner.getvalue()

cycPerNano = cycleRate / nanoRate
cycHist /= cycPerNano
chErr /= cycPerNano

# put them in a file
ofp = open(errfile, 'w')
ofp.write("read serr 2 3\nerr off\nline step\nlog y\n")
ofp.write("! LAT Clock rate = %.17g +/- %.7g ns/tick (%.2f MHz)\n" %
          (nanoRate, nrSigma, 1e3/nanoRate))
ofp.write("! SBC Clock rate = %.17g +/- %.7g cycles/tick (%.2f MHz)\n" %
          (cycleRate, crSigma, 1e3*cycleRate/nanoRate))
ofp.write("! LAT chisqr/dof = %.17g\n" % (nanStat / (len(nanos) - 2)))
ofp.write("! Cycle sigma = %.17g cycles\n" % cycErr)
ofp.write("! Minimum LAT error = %.17g, maximum = %.17g\n" % (mine, maxe))
ofp.write("! Minimum SBC error = %.17g, maximum = %.17g\n" % \
          (num.minimum.reduce(cycResid), num.maximum.reduce(cycResid)))
ofp.write("label top Time Error Distribution for %s\n" % inFile)
ofp.write("label x Event Separation (ns)\n")
ofp.write("label y Events / bin\n")
tableio.writetable((nanCen, nanHist, nhErr, cycHist, chErr), ofp)
ofp.close()

# use measured values for LAT clock rate from now on
oneTick = nanoRate / 1e9
tickRate = 1.0 / oneTick

aside.write("ok\n")



## histogram waiting times, from the more accurate timebase
aside.write("Checking waiting times ... ")

wtimes = (evtTicks[1:] - evtTicks[:-1]) / tickRate

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
ofp.write("! Data taken from %s\n" % inFile)
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
ofp.write("! Data taken from %s\n" % inFile)
ofp.write("! Minimum waiting time = %.17g, maximum = %.17g\n" % (mint, maxt))
#ofp.write("! %.3g %% in 1.7ms peaks.\n" % pctpeak)
ofp.write("label top Short Waiting Time Distribution\n")
ofp.write("label x Event Separation (s)\n")
ofp.write("label y Events / bin\n")
tableio.writetable((cen, hist, err), ofp)
ofp.close()

aside.write("ok\n")


## Make a power spectrum
aside.write("Making light curve and PSD ... ")

bintime = evtTicks - evtTicks[0]

rate = bintime[-1] / tickRate / (len(bintime) - 1)

maxbins = bintime[-1]
binfactor = int(maxbins / psd_lc_bins)
last_bin = psd_lc_bins * float(binfactor)
bintime = num.compress(bintime<last_bin, bintime)

nevent = len(bintime)
freqres = tickRate / last_bin

aside.write("binning ... ")
hedges = num.arange(psd_lc_bins) * float(binfactor)
lcurve = lightcurve(bintime, hedges)
del hedges # It's so big!

aside.write("light curve ... ")
lc_lo, lcerr = rebin(lcurve, lcbins, 0)
lcfactor = float(psd_lc_bins / lcbins) 
binsize = lcfactor * binfactor / tickRate
lc_lo /= binsize
lcerr /= binsize
lctaxis = num.arange(lcbins) * binsize + binsize / 2

ofp = open(lcfile, 'w')
ofp.write("read serr 2\nline step\nerr off\n")
ofp.write("! Data taken from %s\n" % inFile)
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

# display around expected peak freq
aside.write("peak ... ")
mask = (orig_freq > psd_peak[0]) & (orig_freq < psd_peak[1])
ppsd = num.compress(mask, psd)
ppsd, perr = rebin(ppsd, psd_display_bins)
pfreq = num.compress(mask, orig_freq)
pfreq, junk = rebin(pfreq, psd_display_bins)
ofp = open(peakfile, 'w')
ofp.write("read serr 2\n")
ofp.write("label x Frequency (Hz)\n")
ofp.write("label y Power (Leahy)\n")
ofp.write("label top Power Spectrum\n")
tableio.writetable((pfreq, ppsd, perr), ofp)
ofp.close()

aside.write("ok\n")

