/// Original Tree in G
/// Binary version created in E
/// call goBinarize with the number of nodes in the original tree. It returns number of nodes in the binary tree.
#define MAX         ?
vector<int> E[MAX+10], G[MAX+10];
int nxt;
void binarize(int node, int par)
{
    if( (G[node].size() <= 3 && par != -1) || (G[node].size() <= 2 && par == -1))
    {
        for(auto v: G[node])
        {
            if(v != par)
            {
                E[node].pb(v);
                E[v].pb(node);
                binarize(v, node);
            }
        }
    }
    else
    {
        int st;
        for(int i = 0; i<G[node].size(); i++)
        {
            int v = G[node][i];
            if(v != par)
            {
                st = i;
                E[node].pb(v);
                E[v].pb(node);
                break;
            }
        }
        int u = node, v = ++nxt;
        E[u].pb(v);
        E[v].pb(u);
        for(int i = st+1; i<G[node].size(); i++)
        {
            int v = G[node][i];
            if(v != par)
            {
                E[nxt].pb(v);
                E[v].pb(nxt);

                u = nxt+1;
                E[nxt].pb(u);
                E[u].pb(nxt);
                nxt++;
            }
        }
        for(auto v: G[node])
        {
            if(v != par)
                binarize(v, node);
        }
    }
}

int goBinarize(int nNode)
{
    nxt = nNode;
    binarize(1, -1);
    return nxt;
}
