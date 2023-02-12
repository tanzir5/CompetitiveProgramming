/// Decomposes the graph into Bridge Tree and finds the bridges too
/// n is the number of nodes
/// bridge will contain the bridge edges
/// tree is the new graph with trees
/// 1 based indexing

vector<int> E[MAX+10], stck, tree[MAX+10];
vector <pii> bridge;
bool vis[MAX+10];
int parent[MAX+10], disc[MAX+10], low[MAX+10], block_num[MAX+10], block_cnt, n;
void dfs(int node)
{
    stck.push_back(node);
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
            {
                bridge.pb( {min(u,v), max(u,v)} );
                block_cnt++;
                while(true)
                {
                    int nw = stck.back();
                    stck.pop_back();
                    block_num[nw] = block_cnt;
                    if(nw == v)
                        break;
                }
            }
        }
        else if(v!=parent[u])
            low[u] = min( low[u], disc[v] );
    }
}

void form_bridge_tree()
{
    for(int i = 0; i<=MAX; i++)
        tree[i].clear();
    block_cnt = 0;
    mem(parent, -1);
    mem(vis, 0);
    bridge.clear();
    for(int i = 1; i<=n; i++)
    {
        if(!vis[i])
        {
            dfs(i);
            block_cnt++;
            while(!stck.empty())
            {
                block_num[stck.back()] = block_cnt;
                stck.pop_back();
            }
        }
    }
    /// add edges in the bridge tree here.
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<E[i].size(); j++)
        {
            int v = E[i][j];
            if(block_num[i] != block_num[v])
                tree[block_num[i]].pb(block_num[v]);
        }
    }
}

