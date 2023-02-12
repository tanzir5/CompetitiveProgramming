
//Bridges
VI edge[MAX+10];
int low[MAX+10], d[MAX+10], tm;
bool vis[MAX+10];
vector<pair <int, int> > bridges;

void dfs(int idx, int par)
{
    vis[idx] = true;
    int i, cur;
    low[idx] = d[idx] = ++tm;

    for(i = 0; i < (int) edge[idx].sz ; i++)
    {
        cur = edge[idx][i];
        if(cur == par) continue;

        if(vis[cur]) low[idx] = min(low[idx], d[cur]);
        else
        {
            dfs(cur, idx);
            low[idx] = min(low[idx], low[cur]);
            if(low[cur] > d[idx]) bridges.push_back(make_pair(min(cur,idx), max(cur,idx)));
        }
    }
}
