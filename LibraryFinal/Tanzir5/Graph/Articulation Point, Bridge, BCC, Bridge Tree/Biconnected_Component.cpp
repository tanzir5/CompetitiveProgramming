/// Decomposes the graph into  Biconnected Components and also finds the articulation points
/// n is the number of nodes
/// BCC[i] will contain the nodes of i'th BCC
/// AP will contain the articulation points
/// 1 based indexing

vector<int> E[MAX+10], stck, BCC[MAX+10], AP;
int n, m, low[MAX+10], disc[MAX+10], BCC_cnt, parent[MAX+10];
bool vis[MAX+10], pushed[MAX+10];

bool is_AP(int u, int v, int children)
{
    if(parent[u] == -1)
    {
        /// u is root and has two children who have no connection except the root. so it's an articulation point.
        if(children > 1)
            return true;
        return false;
    }
    else
    {
        /// There is no backedge towards u's ancestor from any node of the subtree from u going through v and u is not a root.
        /// so u must be an articulation point
        if(low[v] >= disc[u])
            return true;
        return false;
    }
}

void dfs(int node)
{
    vis[node] = 1;
    stck.push_back(node);
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
            if(is_AP(u, v, children))
            {
                if(!pushed[u])
                    AP.pb(u);
                pushed[u] = 1;
                BCC_cnt++;
                BCC[BCC_cnt].push_back(u);
                while(true)
                {
                    int nw = stck.back();
                    BCC[BCC_cnt].pb(nw);
                    stck.pop_back();
                    if(nw == v)
                        break;
                }
            }
        }
        else if( v !=parent[u])
            low[u] = min(low[u],disc[v]);
    }
    return;
}


void find_BCC()
{
    for(int i = 0; i<=MAX; i++)
        BCC[i].clear();
    mem(parent, -1);
    BCC_cnt = 0;
    mem(vis, 0);
    AP.clear();
    mem(pushed, 0);
    for(int i = 1; i<=n; i++)
    {
        if(!vis[i])
        {
            dfs(i);
            if(!stck.empty())
                BCC_cnt++;
            while(!stck.empty())
            {
                BCC[BCC_cnt].pb(stck.back());
                stck.pop_back();
            }
        }

    }
}
