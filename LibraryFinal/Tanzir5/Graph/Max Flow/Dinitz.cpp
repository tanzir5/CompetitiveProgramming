/// Zobayer vai's code

/// 1 based indexing
/// MAXE = twice the number of edges
/// for directed edge, cap[nEdge] = 0

const int MAXN = ?, MAXE = ?; // MAXE = twice the number of edges
int src, snk, nNode, nEdge;
int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
int flow[MAXE*2], cap[MAXE*2], nxt[MAXE*2], to[MAXE*2];
const int inf = ?;
inline void init(int _src, int _snk, int _n)
{
    src = _src, snk = _snk, nNode = _n, nEdge = 0;
    mem(fin, -1);
}

inline void add(int u, int v, int _cap)
{
    to[nEdge] = v, cap[nEdge] = _cap, flow[nEdge] = 0, nxt[nEdge] = fin[u], fin[u] = nEdge++;
    to[nEdge] = u, cap[nEdge] = _cap, flow[nEdge] = 0, nxt[nEdge] = fin[v], fin[v] = nEdge++; // for directed cap[nEdge]=0 here
}

bool bfs()
{
    int st, en, i, u, v;
    mem(dist, -1);
    dist[src] = st = en = 0;
    Q[en++] = src;
    while(st < en)
    {
        u = Q[st++];
        for(i=fin[u]; i>=0; i=nxt[i])
        {
            v = to[i];
            if(flow[i] < cap[i] && dist[v]==-1)
            {
                dist[v] = dist[u]+1;
                if(v == snk)
                    return true;
                Q[en++] = v;
            }
        }
    }
    return dist[snk]!=-1;
}

int dfs(int u, int fl)
{
    if(u==snk) return fl;
    for(int &e=pro[u], v, df; e>=0; e=nxt[e])
    {
        v = to[e];
        if(flow[e] < cap[e] && dist[v]==dist[u]+1)
        {
            df = dfs(v, min(cap[e]-flow[e], fl));
            if(df>0)
            {
                flow[e] += df;
                flow[e^1] -= df;
                return df;
            }
        }
    }
    return 0;
}

int dinitz()   // 1-based indexing
{
    int ret = 0;
    int df;
    while(bfs())
    {
        for(int i=1; i<=nNode; i++) pro[i] = fin[i];
        while(true)
        {
            df = dfs(src, inf);
            if(df) ret += df;
            else break;
        }
    }
    return ret;
}
