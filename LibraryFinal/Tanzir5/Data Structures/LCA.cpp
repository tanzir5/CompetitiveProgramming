/// Run a dfs and fill up level and parent arrays first.
/// 1 based indexing
#define MAXLG ?
#define MAXN ?
int parent[MAXN+10], sparseTable[MAXLG+2][MAXN+10], level[MAXN+10], n;

void dfs(int node, int par, int currentLevel);
void initSparseTable(int Root)
{
    dfs(Root,0,1);
    for(int i = 1; i<=n; i++)
        sparseTable[0][i] = parent[i];
    for(int p = 1; p <= MAXLG; p++)
    {
        for(int u = 1; u <= n; u++)
            sparseTable[p][u] = sparseTable[p-1][sparseTable[p-1][u]];
    }
}

int findLCA(int u, int v)
{
    /// keep u as the deeper node
    if(level[v] > level[u])
        swap(u,v);
    for(int i = MAXLG; i>=0; i--)
    {
        if((1<<i) <= level[u] - level[v])
            u = sparseTable[i][u];
    }
    if(u == v)
        return v;
    for(int i = MAXLG; i>=0; i--)
    {
        if(sparseTable[i][u] != sparseTable[i][v])
            u = sparseTable[i][u], v = sparseTable[i][v];
    }
    return parent[v];
}
