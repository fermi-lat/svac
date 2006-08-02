
import numarray as num

def invQ((cons, lin, quad), yy):

    cons = cons - yy

    determ = lin ** 2 - 4 * quad * cons
    if num.any(determ < 0):
        print determ
        raise ValueError, "No real solution"

    denom = 2 * quad
    bterm = -lin / denom
    dterm = num.sqrt(determ) / denom

    big = bterm + dterm
    #small = bterm - dterm

    #return big, small
    # Always use +, since ticks vs time (thus time vs ticks)
    # is always monotonically increasing.
    return big


if __name__ == "__main__":

    import models
    import tableio

    outFile = 'junk.tnt'
    title = 'qudratic'
    title = 'Neg'
    outFile = title + '.tnt'
    
    #parm = (2e7+100, -3.3e-3, 2.0e-7) # deltaish
    parm = (0.0, 2e7+100, -6.6e-3) # tickish
    fun = models.poly

    times = num.arange(-900., 900.)
    ticks = fun(parm, times)

    big, small = invQ(parm, ticks)

    colNames = ["Time", "Ticks", "Big", "Small"]
    data = [times, ticks, times-big, times-small]

    
    tableio.writehippo(data, outFile, title, colNames)
    
