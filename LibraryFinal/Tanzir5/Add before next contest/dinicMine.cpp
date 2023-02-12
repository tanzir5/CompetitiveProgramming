/// works for both 0 based and 1 based indexing
/// O(min(F,V^2)E)
/// O(sqrt(E)*E) for unit capacity graphs
/// O(sqrt(V)*E) for BPM
const int MAXN = ?;
int src, snk, nxt[MAXN+5], inf = ?, dist[MAXN+5];
struct edge
{
    int v, cap, opposite, flow;
};

vector<edge>E[MAXN+5];

void init(int _src, int _snk, int _n)
{
    src = _src, snk = _snk;
    for(int i = 0; i<=n; i++)
        E[i].clear();
}

void add(int u, int v, int cap)
{
    E[u].push_back({v,cap,E[v].size(),0});
    E[v].push_back({u,cap,E[u].size()-1,0});
}

bool bfs()
{
    memset(dist,-1,sizeof(dist));
    queue<int>q;
    dist[src] = 0;
    q.push(src);
    while(!q.empty())
    {
        int u = q.front();
        if(u == snk)
            return true;
        q.pop();
        for(int i = 0; i<E[u].size(); i++)
        {
            if(E[u][i].cap > E[u][i].flow)
            {
                int v = E[u][i].v;
                if(dist[v] == -1)
                {
                    dist[v] = dist[u] +1;
                    q.push(v);
                }
            }
        }
    }
    return dist[snk] != -1;
}

int dfs(int u, int sentFlow)
{
    if(u == snk)
        return sentFlow;
    for(; nxt[u]<E[u].size(); nxt[u]++)
    {
        int v = E[u][nxt[u]].v;
        int c = E[u][nxt[u]].cap;
        int f = E[u][nxt[u]].flow;
        int opposite = E[u][nxt[u]].opposite;
        if(dist[v] == dist[u]+1 && c > f)
        {
            int tmp = dfs(v,min(sentFlow,c-f));
            if(tmp)
            {
                E[u][nxt[u]].flow += tmp;
                E[v][opposite].flow -= tmp;
                return tmp;
            }
        }
    }
    return 0;
}

int dinitz()
{
    int totalFlow = 0;
    while(bfs())
    {
        memset(nxt,0,sizeof(nxt));
        int sentFlow;
        while(true)
        {
            sentFlow = dfs(src,inf);
            if(sentFlow == 0)
                break;
            totalFlow += sentFlow;
        }
    }
    return totalFlow;
}

