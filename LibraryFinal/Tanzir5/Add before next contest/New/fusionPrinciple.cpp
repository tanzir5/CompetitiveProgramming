/// MAX should be equal to (V+E) for safety
#define MAX     ?
struct edgeData{
    vector<int> E[MAX+10];
}A[2];
int root;
vector<int>stck, tmp;
bool forbidden[MAX+10], vis[MAX+10];
int n;
void getCycle(int u)
{
    tmp.clear();
    for(int i = (int)stck.size()-1; i>=0; i--)
    {
        tmp.pb(stck[i]);
        if(stck[i] == u)
        {
            stck = tmp;
            return;
        }
    }
    assert(false);
}

bool dfs(int node, int par, vector<int>E[])
{
    vis[node] = true;
    stck.pb(node);
    int cnt = 0;
    for(auto v: E[node])
    {
        if(v == par)
            cnt++;
    }
    if(cnt > 1)
    {
        getCycle(par);
        return true;
    }
    for(auto v: E[node])
    {
        if(par != v)
        {
            if(vis[v])
            {
                getCycle(v);
                return true;
            }
            if(dfs(v, node, E))
                return true;
        }
    }
    stck.pop_back();
    return false;
}

int green(int node, int par, vector<int>E[])
{
    int x = 0;
    for(auto v: E[node])
    {
        if(v != par)
            x ^= (green(v, node, E) + 1);
    }
    return x;
}
string solve()
{
    bool kechal = true;
    root = 1;
    int nw = 0, nxt = 1;
    while(kechal)
    {
        mem(vis, 0);
        stck.clear();
        kechal = dfs(root, -1, A[nw].E);
        if(kechal)
        {
            n++;
            assert(n <= MAX);
            int current = n, cnt = 0;
            for(auto u: stck)
            {
                forbidden[u] = true;
                if(u == root)
                    root = n;
            }
            for(int i= 1; i<current; i++)
            {
                for(auto v: A[nw].E[i])
                {
                    if(forbidden[i] && forbidden[v])
                        cnt++;
                    else if(forbidden[i])
                        A[nxt].E[current].pb(v);
                    else if(forbidden[v])
                        A[nxt].E[i].pb(current);
                    else
                        A[nxt].E[i].pb(v);
                }
            }
            cnt /= 2;
            if(cnt & 1)
                A[nxt].E[current].pb(++n), A[nxt].E[n].pb(current);
            stck.clear();
//            int totalNew = 0, totalOld = 0;
            for(int i = 1; i<=n; i++)
            {
//                totalNew += A[nxt].E[i].size();
//                totalOld += A[nw].E[i].size();
                A[nw].E[i].clear();
            }
            swap(nw, nxt);
        }
    }
    return green(root, -1, A[nw].E) ? "Alice" : "Bob";
}

int cnt[MAX+10];
int main()
{
    int t, u, v, m;
    sf(t);
    for(int cs = 1; cs<=t; cs++)
    {
        sff(n,m);
        mem(cnt, 0);
        for(int i = 1; i<=m; i++)
        {
            sff(u,v);
            if(u == v)
                cnt[u]++;
            else
            {
                A[0].E[u].pb(v);
                A[0].E[v].pb(u);
            }
        }
        int cur = n;
        for(int i = 1; i<=cur; i++)
        {
            if(cnt[i] > 1)
            {
                if(cnt[i] & 1)
                    A[0].E[i].pb(++n), A[0].E[n].pb(i);
            }
        }
        cout << solve() << '\n';
        for(int i = 1; i<=n; i++)
            A[0].E[i].clear(), A[1].E[i].clear();
        mem(forbidden, 0);
    }
    return 0;
}


