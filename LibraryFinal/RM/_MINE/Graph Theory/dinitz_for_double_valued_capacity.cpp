
/*
max flow (dinitz algorithm)
works on undirected/directed graph
in order to make it work for directed graph, change the add function
can have loops, multiple edges, cycles
DO NOT USE 0 as source, use 1 :)
INF has to be greater than or equal to the max capacity in the network.
*/

#define MAXN        10110
#define MAXE        30110
const long double INF = 1e12;

int src, snk, nNode, nEdge;
int Q[MAXN+5], fin[MAXN+5], pro[MAXN+5], dist[MAXN+5];
long double flow[2*MAXE+5], cap[2*MAXE+5];
int nxt[2*MAXE+5], to[2*MAXE+5];

 void init(int _src, int _snk, int _n) {
    src = _src, snk = _snk, nNode = _n, nEdge = 0;
    memset(fin,-1,sizeof(fin));
}

 void add_edge(int u, int v, long double c) {
    to[nEdge] = v, cap[nEdge] = c, flow[nEdge] = 0, nxt[nEdge] = fin[u], fin[u] = nEdge++;
    to[nEdge] = u, cap[nEdge] = 0.00, flow[nEdge] = 0, nxt[nEdge] = fin[v], fin[v] = nEdge++;
    assert(nEdge <= 2*MAXE);
}

bool bfs() {
    int st, en, i, u, v;
    memset(dist, -1, sizeof(dist));
    dist[src] = st = en = 0;
    Q[en++] = src;
    while(st < en) {
        u = Q[st++];
        for(i=fin[u]; i>=0; i=nxt[i]) {
            v = to[i];
            if(flow[i]  + eps < cap[i] && dist[v]==-1) {
                dist[v] = dist[u]+1;
                Q[en++] = v;
            }
        }
    }
    return dist[snk]!=-1;
}

long double dfs(int u, long double fl) {
    if(u==snk) return fl;
    long double df;

    for(int &e=pro[u], v; e>=0; e=nxt[e]) {
        v = to[e];
        if(flow[e]  + eps < cap[e] && dist[v]==dist[u]+1) {
            df = dfs(v, min(cap[e]-flow[e], fl));

            if(df> eps) {
                flow[e] += df;
                flow[e^1] -= df;
                return df;
            }
        }
    }
    return 0;
}

long double dinitz() {
    long double ret = 0, df;

    while(bfs()) {
        for(int i=1; i<=nNode; i++) pro[i] = fin[i];
        while(true) {
            df = dfs(src, INF);
            if(fabs(df) > eps) ret += df;
            else break;
        }
    }
    return ret;
}
