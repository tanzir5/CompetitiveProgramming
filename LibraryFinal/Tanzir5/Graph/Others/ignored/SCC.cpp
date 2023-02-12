/*
    MAX is the maximum number of nodes.
    n is the number of nodes.
    vector comp[i] holds the nodes of i'th scc.
    G is the new DAG formed by taking SCC as super nodes.
    comp_num[i] holds the component number that the i'th node belongs to
*/
int n, m, comp_num[MAX+10], total_comp;
vector<int> E[MAX+10], Rev[MAX+10], V, comp[MAX+10], G[MAX+10];
bool vis[MAX+10];
void dfs(int nd)
{
    vis[nd] = 1;
    for(int i = 0; i<E[nd].size(); i++)
    {
        int v = E[nd][i];
        if(!vis[v])
            dfs(v);
    }
    V.pb(nd);
}

void dfs2(int nd, int cur)
{
    vis[nd] = 1;
    comp_num[nd] = cur;
    comp[cur].pb(nd);
    for(int i = 0; i<Rev[nd].size(); i++)
    {
        int v = Rev[nd][i];
        if(!vis[v])
            dfs2(v, cur);
    }
}

/// forms a directed graph with the SCCs as nodes
void build_new_graph()
{
    for(int i = 1; i<=n; i++)
    {
        int u = comp_num[i];
        for(int j = 0; j<E[i].size(); j++)
        {
            int k = E[i][j];
            int v = comp_num[k];
            if(u != v)
                G[u].pb(v);//, G[v].pb(u);
        }
    }
    /// deleting duplicate edges
    for(int i = 1; i<=total_comp; i++)
    {
        sort(all(G[i]));
        un(G[i]);
    }
}

void build_SCC()
{
    /// topologically sort
    mem(vis,0);
    for(int i = 1; i<=n; i++)
    {
        if(!vis[i])
            dfs(i);
    }
    mem(vis,0);
    int cur_comp = 0;
    for(int i = (int)V.size()-1; i>=0; i--)
    {
        int u = V[i];
        if(!vis[u])
        {
            cur_comp++;
            dfs2(u,cur_comp);
        }
    }
    total_comp = cur_comp;
    build_new_graph();
}
