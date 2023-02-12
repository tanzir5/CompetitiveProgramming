
/*
    Euler path = path that visits all the edges in a graph.
    An undirected graph has a Euler cycle iff it is connected and each vertex has an even degree.

    An undirected graph has an Euler tour iff it is connected, and each vertex, except for exactly two vertices, has an even degree.
    The two vertices of odd degree have to be the endpoints of the tour.

    A directed graph has a Euler cycle iff it is strongly connected and the in-degree of each vertex is equal to its out-degree.

    A directed graph has an Euler tour if and only if at most one vertex has (out-degree) − (in-degree) = 1, at most one vertex has
    (in-degree) − (out-degree) = 1, every other vertex has equal in-degree and out-degree, and all of its vertices with nonzero degree belong
    to a single connected component of the underlying undirected graph.

    This code finds euler circuit.
    To find an Eulerian tour, simply find one of the nodes which has odd degree and call find_circuit with it.
    Multiple edges between nodes can be handled by the exact same algorithm.
    Self-loops can be handled by the exact same algorithm as well, if self-loops are considered to add 2 (one in and one out) to the degree of a node.
    A directed graph has a Eulerian circuit if it is strongly connected (except for nodes with both in-degree and out-degree of 0) and the indegree of each node equals its outdegree. The algorithm is exactly the same, except that because of the way this code finds the cycle, you must traverse arcs in reverse order.
*/

///The following code finds euler path for directed graph
/// For others, just change the existence of euler path check accordingly.
/// To find an Eulerian tour in an undirected graph, simply find one of the nodes which has odd degree and make it the source.
/// For others, anyone with non-zero indegree can be source.

#define MAX     ?
vector<int>E[MAX+10], sltn;
int indeg[MAX+10], outdeg[MAX+10];
int n ;
bool vis[MAX+10];
void dfs(int nd)
{
    /// this vis[nd] only makes sure in the end that nodes with nonzero degree are all under
    /// the same weakly connected component. It has nothing to do with finding the actual euler path.
    vis[nd] = true;
    while(E[nd].size())
    {
        int v = E[nd].back();
        E[nd].pop_back();
        dfs(v);
    }
    sltn.pb(nd);
}

/// Returns false if there is no euler path, returns true and prints the path if there is an euler path
bool Find_Euler_Path()
{
    int src , sink;
    bool found_src = false, found_sink = false;
    mem(indeg,0);
    mem(outdeg,0);
    sltn.clear();
    /// calculate indegree and outdegree of every node
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<E[i].size(); j++)
        {
            int v = E[i][j];
            outdeg[i]++;
            indeg[v]++;
        }
    }
    /// check if euler path exists
    for(int i = 1; i<=n; i++)
    {
        int diff = outdeg[i] - indeg[i];
        if(diff == 1)
        {
            if(found_src)
                return false;
            found_src = true;
            src = i;
        }
        else if (diff == -1)
        {
            if(found_sink)
                return false;
            found_sink = true;
            sink = i;
        }
        else if(diff != 0)
            return false;
    }
    if(!found_src)
    {
        /// there actually exists a euler cycle. So you need to pick a random node with non-zero degrees.
        for(int i = 1; i<=n;i++)
        {
            if(outdeg[i])
            {
                found_src = true;
                src = i;
                break;
            }
        }
    }
    if(!found_src)
        return true;
    mem(vis,0);
    dfs(src);
    for(int i = 1; i<=n; i++)
    {
        /// the underlying graph is not even weakly connected.
        if(outdeg[i] && !vis[i])
            return false;
    }
    for(int i = (int)sltn.size()-1; i>=0; i--)
        printf("%d ",sltn[i]);
    puts("");
    return true;
}
