
## @file histogram.py
## @brief Code to calculate histograms.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## This file can be run as a script to perform a simple test:
## "python histogram.py" should print the message "Passed unit test."

#

"""@brief Code to calculate histograms.

"""

import Numeric as num

# 
class Histogram:
    """@brief Create histograms, in one or more dimensions.

    More description goes here.
    
    """

    # Total number of items that have been submitted to histogram.
    total = 0L
    # Number of items that have been in range of bins.
    accepted = 0L
    # Edges of histogram bins for each dimension
    edges = ()
    # The shape of the histogram
    shape = ()
    # The binned data.
    histogram = ()

    #
    def __init__(self, edges):
        """@brief Initialize Histogram objects.

        @param edges A nested sequence of bin edges.  For each dimension of
        the histogram, @a edges should contain a 1-dimensional sequence of bin
        edges.  The bins should be contiguous and disjoint, and the sequence
        of edges should be sorted.  @a edges=([1,2,3]) defines a 1-dimensional
        histogram with two bins, one collecting values between 1 and 2, and
        the other collecting values between 2 and 3.  @a edges=([1,2,3],[4,5])
        defines a two-dimensional histogram with 2 bins along the first axis
        and one along the second.

        @return An empty Histogram.

        """

        # generalize 1-d as a special case of n-d
        if isinstance(edges[1], (type(1), type(1L), type(1.0))):
            edges = (edges,)

        shape = []
        for edge in edges:
            edge = num.array(edge)
            if len(edge.shape) != 1:
                raise ValueError, "Each edge must be a 1-dimensional sequence."
            shape.append(len(edge) - 1)
            self.edges += (edge,)
        self.histogram = num.zeros(shape)
        self.shape = num.array(shape)

        pass

    #
    def add(self, values):
        """@brief Bin values into the histogram.

        hist.add(values) can also be spelled hist+=values.

        @param values An n-tuple of data points to be binned into the
        histogram.

        @return 

        """

        values = num.asarray(values)

        # # make sure inputs are sane
        if len(values.shape) == 1:
            # generalize 1-d as a special case of n-d
            values = num.reshape(values, (-1, 1))
        if len(values.shape) > 2:
            raise ValueError, "Value array must be 2-dimensional, this is %d."\
                  % len(values.shape)
        if values.shape[1] != len(self.edges):
            raise ValueError, \
                  "Data dimensionality (%d) doesn't match histogram (%d)." % \
                  (values.shape[1], len(self.edges))

        # # get rid of the points that are out of range
        # set up limits
        loLim = []
        hiLim = []
        for edge in self.edges:
            loLim.append(edge[0])
            hiLim.append(edge[-1])
        loLim = num.array(loLim)
        hiLim = num.array(hiLim)
        # compare to limits on element-by-element basis
        mask = (values >= loLim) & (values < hiLim)
        # combine n-dim element mask into 1-dim point mask
        mask = num.alltrue(mask, 1)
        # and pull out the good points
        good = num.compress(mask, values, 0)

        # # find which bins to put values in
        indices = []
        for dim, edge in enumerate(self.edges):
            index = num.searchsorted(edge, good[:, dim]) - 1
            indices.append(index)
        indices = num.transpose(indices)

        # # increment appropriate bins
        for point in indices:
            self.histogram[tuple(point)] += 1
            
        self.accepted += len(good)
        self.total += len(values)
        return self
    
    __iadd__ = add

#     #
#     def __getattr__(self, name):
#         """@brief Magic.

#         This does inscrutable fun stuff.

#         """

#         return
    

#
def _test():
    """@brief Test Histogram class.

    If everything works, this should return True and raise no exceptions.
    
    @return True if it works, False if it doesn't.
    """

    # test 1-d
    d1e = [1, 2, 3]
    d1v = [1.1, 2.2, 0.1, 1.1, 3.3, 1.1, 1.1]
    h1 = Histogram(d1e)
    h1 += d1v
    if h1.total != 7 or h1.accepted != 5 or \
       not num.alltrue(h1.histogram == [4, 1]):
        return False

    # test 2-d
    d2e = [[1, 2, 3], [4,5]]
    d2v = [[ 1.1,  4.4],
           [ 2.2,  4.1],
           [ 0.1,  4.4],
           [ 1.1,  5.5],
           [ 3.3,  4.4],
           [ 1.1,  3.3],
           [ 1.1,  4.4]]
    h2 = Histogram(d2e)
    h2 += d2v
    if h2.total != 7 or h2.accepted != 3 or \
       not num.alltrue(num.alltrue(h2.histogram == [[2], [1]])):
        return False

    return True


if __name__ == '__main__':
    result = _test()
    
    if result:
        print "Passed unit test."
    else:
        print "Failed unit test."
