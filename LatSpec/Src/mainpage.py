# -*- mode: auto-fill-mode; fill-prefix: ## ; -*-

## @file mainpage.py
## @brief Top-level documentation for spectral analysis package.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Top-level documentation for spectral analysis package.

"""

##@mainpage LatSpec
## 
## @section intro Introduction
## 
## These programs and modules create files for analysis of GLAST LAT data with
## the XSPEC spectral analysis program (generally used for x- and low-energy
## gamma-ray spectroscopy).
## 
## The spectra analysed with XSPEC were traditionally histograms of detected
## events in ADC channels from a pulse height analyzer.  With the LAT, they
## are histograms over essentially arbitrarily defined bins of reconstructed
## energy (we'll refer to them as channels in either case).  In either case,
## the histogram is stored in a Pulse Height Analyzer (PHA) file, which is a
## FITS file, and also may contain statistical and systematic errors,
## information about data quality, and exposure time.  The format of PHA files
## is described in <A
## HREF="http://heasarc.gsfc.nasa.gov/docs/heasarc/ofwg/docs/summary/ogip_92_007_summary.html">
## The OGIP Spectral File Format </A>.
## 
## 
## No attempt is made to correct the histograms for detector energy
## resolution, gain, or energy-dependent detection efficiency.  Rather, one's
## best knowledge of these effects is part of the model.  A theoretical source
## spectrum is generated, then modified by the detection efficiency and
## smeared with the detector resolution.  This "folded" model is compared to
## the data, and the model's parameters adjusted to fit the data by minimizing
## a fit statistic such as @f$\chi^2@f$.
## 
## The knowledge of the detector is stored in two files (also FITS):
## @li an Ancillary Response File (ARF), which specifies the probability that
## an incident photon in a given true energy bin will be detected (accepted,
## for the LAT), and
## @li a Redistribution Matrix File (RMF), which specifies, for each channel,
## the probability that a detected (accepted) event in a given true energy bin
## will be assigned to that channel.
## 
## The formats of both file types are described in <A
## HREF="http://legacy.gsfc.nasa.gov/docs/heasarc/caldb/docs/summary/cal_gen_92_002_summary.html">
## The Calibration Requirements for Spectral Analysis </A>
## 
## Note that the true energy bins used by the ARF and RMF must match, and the
## observed or reconstructed energy channels used by the PHA and the RMF must
## match.  The bins and channels do not need to match each other, however.
## Indeed, the bins generally cover a wider energy range with a finer grid
## than do the channels.
## 
## The formula used to predict the observed reconstructed energy spectrum is
## @f$m=MAs@f$, where @f$m@f$ is the prediction (a vector, length nchan),
## @f$M@f$ is the redistribution matrix (a matrix with nchan rows and nbin
## columns), @f$A@f$ is the ancillary response (a diagonal matrix with nbin
## rows and columns), and @f$s@f$ is the model source spectrum (a vector of
## length nbin).  The source spectrum is integrated into the true energy bins;
## in practice the bins are usually narrow enough that trapezoid-rule
## integration is sufficient for continuum spectra.

