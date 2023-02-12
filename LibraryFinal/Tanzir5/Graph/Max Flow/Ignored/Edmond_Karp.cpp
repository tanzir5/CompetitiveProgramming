/// Edmond Karp Max Flow
/// O(V*E^2);
int E[MAX+10][MAX+10], src, dest;
queue<int> q;
bool vis[MAX*2+10];
int parent[MAX+10], n, m, B, S, D;

bool bfs()
{
    while(!q.empty())
        q.pop();
    mem(vis,0);
    vis[src] = 1;
    q.push(src);
    int i, nw, tmp;
    while(!q.empty())
    {
        nw = q.front();
        q.pop();
        for(i = 1; i<=n; i++)
        {
            if(!E[nw][i])
                continue;
            tmp = i;
            if(!vis[tmp])
            {
                vis[tmp] = 1;
                q.push(tmp);
                parent[tmp] = nw;
            }
            if(tmp == dest)
                return 1;
        }
    }
    return 0;
}
int go(int nd)
{
    if(nd == src)
        return inf;

    return min(E[parent[nd]][nd], go(parent[nd]));
}
void update(int nd, int mn)
{
    if(nd == src)
        return;

    E[parent[nd]][nd] -= mn;
    E[nd][parent[nd]] += mn;

    update(parent[nd],mn);
}
int Edmond_Karp()
{
    int ans = 0, mn;
    while(bfs())
    {
        mn = go(dest);
        ans += mn;
        update(dest,mn);
    }
    return ans;
}
