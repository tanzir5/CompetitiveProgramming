/// Bridge
/// n is the number of nodes
/// bridge will contain the bridge edges
/// 1 based indexing

vector<int> E[MAX+10];
vector <pii> bridge;
bool vis[MAX+10];
int parent[MAX+10], disc[MAX+10], low[MAX+10], n;
void dfs(int node)
{
    vis[node] = 1;
    if(parent[node] == -1)
        disc[node] = low[node] = 1;
    else
        disc[node] = low[node] = disc[parent[node]]+1;
    int i, u, v;
    u = node;
    for(i = 0; i<E[u].size(); i++)
    {
        v = E[u][i];
        if(!vis[v])
        {
            parent[v] = u;
            dfs(v);
            low[u] = min( low[u], low[v] );
            if(low[v] > disc[u] )
                bridge.pb( {min(u,v), max(u,v)} );
        }
        else if(v!=parent[u])
            low[u] = min( low[u], disc[v] );
    }
}

void find_bridge()
{
    mem(parent, -1);
    mem(vis, 0);
    bridge.clear();
    for(int i = 1; i<=n; i++)
    {
        if(!vis[i])
            dfs(i);
    }
}
