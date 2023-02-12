/*
    Finding Maximum independent set from BPM ( Kuhn and Karp )
    Run BPM. After that do a dfs from every node in the left side that are unmatched. Then take an edge from u to v only
    and only if
    i) u is on the left side and match[u] != v
    ii) u is on the right side and match[v] == u

    After this, all visited nodes on the left and all unvisited nodes on the right will form the
    maximum independent set.

*/

/*
    Finding the edges in the minimum cut
    After running max flow, do a DFS from source on the residual graph. Then an edge from u to v will be in the
    minimum cut if and only if,
    i) u is visited and v is unvisited
    ii) u is unvisited and v is visited

*/

/*
    Fixing lower bound on edges
    Create a super source, a super sink. If u->v has a lower bound of LB, give an edge from super source to v with capacity LB.
    Give an edge from u to super sink with capacity LB.
    Give an edge from normal sink to normal source with capacity infinity.
    If maxflow is equal to LB, then the lower bound can be satisfied.
*/

/*
    Finding minimum flow that will make sure lower bound for every edge.
    Usually for lower bound an edge with infinite capacity is given from destination to source.
    But now we will binary search on the value of the capacity of the edge from the destination
    to the source.
*/

/*
    Finding Maximum flow that will make sure lower bound for every edge.
    Just add a super source and binary search on the upper bound of the edge from super source to
    normal source to find a solution satisfying upper bounds of all other edges.
*/

/*
    To solve a maximization problem with max flow, convert it to a minimization problem somehow and
    then try to find the solution from min cut.
*/

/*
    Project Selection Problem
    Maximize total profit.
    Doing i'th project profits you by P[i]
    Doing i'th project requires you to buy a list of instruments each of which has different cost.
    Different projects may require the same instrument in which case, buying one instrument is ok.
    Make a flow graph with projects on the left and instruments on the right.
    cap[source][i'th project] = P[i]
    cap[j'th instrument][sink] = Cost[j]
    cap[i'th project][j'th instrument] = inf ( if i'th project requires j'th instrument )
    here mincut will minimize this function ( sacrifice profits of projects + cost of instruments to be bought )
    So ans is = Total profit of all projects - mincut.
*/

/*
    Image Segmentation Problem
    There are n pixels. Each pixel i can be assigned a foreground value  fi or a background value bi.
    There is a penalty of pij if pixels i, j are adjacent and have different assignments. The problem is to assign pixels to foreground or background
    such that the sum of their values minus the penalties is maximum.
    Let P be the set of pixels assigned to foreground and Q be the set of points assigned to background, then the problem can be formulated as
    maximize  ( totalF + totalB - sacrificeFore for Q - sacrificeBack for P - penalty pij)
    or, minimize( sacrificeFore for Q + sacrificeBack for P + penalty pij)
    The above minimization problem can be formulated as a minimum-cut problem by constructing a network
    where the source is connected to all the pixels with capacity  fi, and the sink is connected by all the pixels with capacity bi.
    Two edges (i, j) and (j, i) with pij capacity are added between two adjacent pixels.
    The s-t cut-set then represents the pixels assigned to the foreground in P and pixels assigned to background in Q.
*/
