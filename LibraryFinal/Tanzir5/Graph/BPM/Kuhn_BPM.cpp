/// Kuhn's BPM
/// O(V*E)
/// n is the number of nodes on the left side
/// 1 based indexing
int Left[MAX+10], Right[MAX+10];
vector<int> E[MAX+10];
bool vis[MAX+10];

bool dfs(int node)
{
    if(vis[node])
        return false;
    vis[node] = 1;
    for(int i = 0; i<E[node].size(); i++)
    {
        int v = E[node][i];
        if(Right[v] == -1)
        {
            Left[node] = v;
            Right[v] = node;
            return true;
        }
    }
    for(int i = 0; i<E[node].size(); i++)
    {
        int v = E[node][i];
        if(dfs(Right[v]))
        {
            Left[node] = v;
            Right[v] = node;
            return true;
        }
    }
    return false;
}
int BPM(int n)
{
    mem(Left,-1);
    mem(Right,-1);
    bool done = false;
    while(!done)
    {
        done = true;
        mem(vis,0);
        for(int i = 1; i<=n; i++)
        {
            if(Left[i] == -1 && dfs(i))
                done = false;
        }
    }
    int ret = 0;
    for(int i = 1; i<=n; i++)
        ret += (Left[i] != -1);
    return ret;
}
