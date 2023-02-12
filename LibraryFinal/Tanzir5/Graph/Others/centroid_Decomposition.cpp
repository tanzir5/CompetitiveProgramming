/*
    1 based indexing
    Centroid Decomposition tree.
    Complexity - O(Vlog(V)) , V is the number of nodes in the graph
    MAX is the maximum number of nodes.
    Just put the edges in E and call centroid_decomposition().
    Root is the root of the new tree.
    Tree will hold the new tree.
*/
#define MAX         ?

vector<int> E[MAX+10], tree[MAX+10];
int Root, taken[MAX+10];
pii mx[MAX+10];

int dfs1(int node, int par)
{
    int ret = 1;
    mx[node] = {0, node};
    for(int i = 0; i<E[node].size(); i++)
    {
        int v = E[node][i];
        if(par == v || taken[v])
            continue;
        int nw = dfs1(v, node);
        mx[node] = max(mx[node], (pii){nw, v});
        ret += nw;
    }
    return ret;
}
int dfs2(int node, int nNode)
{
    if(mx[node].xx <= nNode/2)
        return node;
    return dfs2(mx[node].yy, n);
}
int getCentroid(int node)
{
    /// n = number of nodes in current tree
    int nNode = dfs1(node, 0);
    return dfs2(node, nNode);
}
void build(int root)
{
    for(int i = 0; i<E[root].size(); i++)
    {
        int v= E[root][i];
        if(taken[v])
            continue;
        int nw = getCentroid(v);
        tree[root].pb(nw);
        taken[nw] = 1;
        build(nw);
    }
}
void centroid_decomposition()
{
    /// Find Root
    Root = getCentroid(1);
    taken[Root] = 1;
    build(Root);
}
