/// Each node in the tree has a value
/// Update a node's value
/// query for the summation of values of the nodes on the path from u to v
/// chainNo is the total number of chains
/// chainHead[u] is the head of node u's chain
/// chainSize[i] is the size of the chain i
/// chainId[u] is the id/number of u's chain
/// idxInBaseArray[u] is the index of the base array where data about u is stored
/// baseArray is the array upon which BIT/Segment tree is created
/// It's expected that subtreeSize array is filled up while doing dfs for initSparseTable
#define MAXN ?
int chainNo = 0, chainHead[MAXN+10], chainSize[MAXN+10], chainId[MAXN+10], idxInBaseArray[MAXN+10],
    baseArray[MAXN+10], cnt = 0, subtreeSize[MAXN+10];

/// HLD start
void HLD(int node, int par)
{
    cnt++;
    idxInBaseArray[node] = cnt;
    baseArray[cnt] = val[node];
    if(chainHead[chainNo] == -1)
        chainHead[chainNo] = node;
    chainId[node] = chainNo;
    chainSize[chainNo]++;
    int specialChild = -1, maxSubtreeSize = 0;
    for(int i = 0; i<E[node].size(); i++)
    {
        int v = E[node][i];
        if(v != par && subtreeSize[v] > maxSubtreeSize)
        {
            maxSubtreeSize = subtreeSize[v];
            specialChild = v;
        }
    }
    if(specialChild != -1)
        HLD(specialChild, node);
    for(int i = 0; i<E[node].size(); i++)
    {
        int v = E[node][i];
        if(v != par && v != specialChild)
        {
            chainNo++;
            HLD(v,node);
        }
    }
}

inline void HLDConstruct()
{
    cnt = 0;
    chainNo = 0;
    mem(chainHead,-1);
    mem(chainSize,0);
    HLD(1,-1);
    initBIT(n);
    for(int i = 1; i<=n; i++)
        updateBIT(i, baseArray[i]);
}
/// HLD End

inline int solve(int u, int v)
{
    /// v is below u, level[v] > level[u];
    int ret = 0;
    while(true)
    {
        if(chainId[u] == chainId[v])
        {
            int L = idxInBaseArray[u];
            int R = idxInBaseArray[v];
            ret += range_query(L,R);
            return ret;
        }
        int head = chainHead[chainId[v]];
        int L = idxInBaseArray[head];
        int R = idxInBaseArray[v];
        ret += range_query(L,R);
        v = parent[head];
    }
}
inline int query(int u, int v)
{
    int lca = findLCA(u,v);
    int ret = 0;
    return solve(lca,u) + solve(lca, v) - baseArray[idxInBaseArray[lca]];
}

inline void update(int a, int v)
{
    int idx = idxInBaseArray[a];
    int diff = v - baseArray[idx];
    baseArray[idx] = v;
    updateBIT(idx,diff);
}
