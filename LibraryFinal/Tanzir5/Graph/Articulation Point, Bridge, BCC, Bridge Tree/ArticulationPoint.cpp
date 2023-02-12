/// Articulation Point
/// n is the number of nodes
/// AP will contain the articulation points
/// 1 based indexing

vector<int> E[MAX+10];
bool vis[MAX+10], pushed[MAX+10];
int disc[MAX+10], low[MAX+10], parent[MAX+10], n;
vector <int> AP;

///ARTICULATION POINT
bool is_AP(int u, int v, int children)
{
    if(parent[u] == -1)
    {
        /// u is root and has two children who have no connection except the root. so it's an articulation point.
        if(children > 1 )
            return true;
        return false;
    }
    else
    {
        /// There is no backedge towards u's ancestor from any node of the subtree from u going through v and u is not a root.
        /// so u must be an articulation point
        if(low[v] >= disc[u] )
            return true;
        return false;
    }
}

void dfs(int node)
{
    vis[node]=1;
    if(parent[node] == -1)
        disc[node] = low[node] = 1;
    else
        disc[node] = low[node] = disc[parent[node]]+1;

    int children = 0, v, u = node;
    for(int i = 0; i<E[u].size();i++)
    {
        v = E[u][i];
        if( !vis[v] )
        {
            children++;
            parent[v]=u;
            dfs(v);
            low[u]=min(low[u],low[v]);
            if(is_AP(u, v, children) && pushed[u] == 0)
            {
                pushed[u] = 1;
                AP.pb(u);
            }
        }
        else if(v!=parent[u])
            low[u]=min(low[u],disc[v]);
    }
    return;
}

void find_articulation_point()
{
    mem(vis, 0);
    mem(pushed, 0);
    mem(parent, -1);
    AP.clear();
    for(int i = 1; i<=n; i++)
    {
        if(!vis[i])
            dfs(i);
    }
}
