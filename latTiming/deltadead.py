
import Numeric as num

def deltadead((rate, tdead, ttot), edges):
    edges = discontinue_edges(edges)
    lower = edges[:, 0]
    upper = edges[:, 1]

    result = num.zeros(len(edges), num.Float64)
    
    below = upper < tdead
    inside = (lower < tdead) & (upper > tdead)
    above = lower > tdead

    # bins which are entirely below the deadtime get nuthin'
    # and like it
    num.putmask(result, below, 0)

    # bins which are entirely above the deadtime don't make no trouble
    # if they know what's good for 'em
    aedges = num.compress(above, edges, 1)
    aresult = intexp((rate, ttot), aedges)
    num.putmask(result, above, aresult)

    # bins which contain the deadtime get smacked around a bit
    # then they don't make no more trouble
    iedges = num.compress(inside, edges, 1)
    iedges[:, 0] = tdead
    iresult = intexp((rate, ttot), iedges)
    num.putmask(result, inside, iresult)

    return result




def discontinue_edges(edges):
    edges = num.array(edges)
    edims = edges.shape
    if len(edims) == 1:
        lower = edges[:-1]
        upper = edges[1:]
        edges = num.transpose((lower, upper))
    elif len(edims) == 2 and edims[-1] == 2:
        pass
    else:
        raise ValueError, \
              "edges should have shape (n,) or (n, 2) but has %s." % edims
    return edges
