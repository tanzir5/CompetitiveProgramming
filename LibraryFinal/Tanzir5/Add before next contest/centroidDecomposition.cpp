/*
    1 based indexing
    Centroid Decomposition tree. (CDT)
    Complexity - O(Vlog(V)) , V is the number of nodes in the graph
    MAX is the maximum number of nodes.
    Just put the edges in E and call centroid_decomposition().
    Root is the root of the new tree.
    Tree will hold the new tree.
    dist[i][v] = distance of v from its i'th level ancestor in CDT.
    myLevel[i] = level of i'th node in CDT.
    par[i] = parent of i'th node in CDT.
*/
#define MAX         ?
#define MAXLG       ?

vector<int> E[MAX+10], tree[MAX+10];
int taken[MAX+10], dist[MAXLG+5][MAX+10], myLevel[MAX+10], par[MAX+10];
pii mx[MAX+10];

int dfs1(int node, int par)
{
    int ret = 1;
    mx[node] = {0, node};
    for(auto v: E[node])
    {
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
    return dfs2(mx[node].yy, nNode);
}
int getCentroid(int node)
{
    /// nNode = number of nodes in current tree
    int nNode = dfs1(node, 0);
    return dfs2(node, nNode);
}

void setDist(int node, int level, int d, int par)
{
    dist[level][node] = d;
    for(auto v: E[node])
    {
        if(taken[v] || v == par)
            continue;
        setDist(v, level, d+1, node);
    }
}

void build(int root, int L)
{
    setDist(root, L, 0, -1);
    myLevel[root] = L;
    for(auto v: E[root])
    {
        if(taken[v])
            continue;
        int nw = getCentroid(v);

        tree[root].pb(nw);
        par[nw] = root;
        taken[nw] = 1;
        build(nw, L+1);
    }
}
void centroidDecomposition(int &Root)
{
    mem(taken, 0);
    Root = getCentroid(1);
    taken[Root] = 1;
    build(Root, 1);
}

int getLCA(int u, int v)
{
    if(myLevel[u] < myLevel[v])
        swap(u,v);
    while(myLevel[u] != myLevel[v])
        u = par[u];
    while(u != v)
        u = par[u], v = par[v];
    return u;
}

int queryDist(int u, int v)
{
    int lca = getLCA(u,v);
    return dist[myLevel[lca]][u] + dist[myLevel[lca]][v];
}
