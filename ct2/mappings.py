## @file mappings.py
## @brief Functions to translate register settings into a useful form.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Functions to translate register settings into a useful form.

"""



#
def mapTkrDac(dac):
    """@brief Display range and threshhold for a GTFE dac.
    Uses getThrDac and getThrDacRange."""
    return '%s,%s' % (getThrDACRange(dac), getThrDAC(dac))

#
def getThrDAC(dac):
    """@brief Get threshhold from GTFE dac."""
    b0 = dac & 0x40
    b1 = dac & 0x20
    b2 = dac & 0x10
    b3 = dac & 0x8
    b4 = dac & 0x4
    b5 = dac & 0x2
    return (b0>>6) + (b1>>4) + (b2>>2) + b3 + (b4<<2) + (b5<<4)

#
def getThrDACRange(dac):
    """@brief Get range from GTFE dac."""
    return dac & 0x1



#
def displayTime(ticks):
    """Display registers that measure time.
    Uses ticksToTime.
    """
    time = '%s (%s)' % (ticks, ticksToTime(ticks))
    return time

#
def ticksToTime(ticks):
    """Convert instrument ticks to time."""
    import jobOptions
    seconds = ticks * jobOptions.tick
    scaled = seconds * jobOptions.timeScale
    scaled = int(scaled + 0.5)
    time = '%s%s' % (scaled, jobOptions.timeUnits)
    return time


#
def logical(bit):
	"""Display a logical value."""
	return ['Off', 'On'][bit]
