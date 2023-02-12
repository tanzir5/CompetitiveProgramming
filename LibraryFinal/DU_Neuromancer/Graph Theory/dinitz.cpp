
/*
max flow (dinitz algorithm)
works on undirected/directed graph
in order to make it work for directed graph, change the add function
can have loops, multiple edges, cycles
DO NOT USE 0 as source, use 1 :)
*/

#define MAXN        200
#define MAXE        5000
const int INF = 0x7f7f7f7f;

int src, snk, nNode, nEdge;
int Q[MAXN+5], fin[MAXN+5], pro[MAXN+5], dist[MAXN+5];
int flow[2*MAXE+5], cap[2*MAXE+5], next[2*MAXE+5], to[2*MAXE+5];

inline void init(int _src, int _snk, int _n) {
    src = _src, snk = _snk, nNode = _n, nEdge = 0;
    memset(fin,-1,sizeof(fin));
}

inline void add_edge(int u, int v, int c) {
    to[nEdge] = v, cap[nEdge] = c, flow[nEdge] = 0, next[nEdge] = fin[u], fin[u] = nEdge++;
    to[nEdge] = u, cap[nEdge] = c, flow[nEdge] = 0, next[nEdge] = fin[v], fin[v] = nEdge++;
    assert(nEdge <= 2*MAXE);
}

bool bfs() {
    int st, en, i, u, v;
    memset(dist, -1, sizeof(dist));
    dist[src] = st = en = 0;
    Q[en++] = src;
    while(st < en) {
        u = Q[st++];
        for(i=fin[u]; i>=0; i=next[i]) {
            v = to[i];
            if(flow[i] < cap[i] && dist[v]==-1) {
                dist[v] = dist[u]+1;
                Q[en++] = v;
            }
        }
    }
    return dist[snk]!=-1;
}

int dfs(int u, int fl) {
    if(u==snk) return fl;
    for(int &e=pro[u], v, df; e>=0; e=next[e]) {
        v = to[e];
        if(flow[e] < cap[e] && dist[v]==dist[u]+1) {
            df = dfs(v, min(cap[e]-flow[e], fl));
            if(df>0) {
                flow[e] += df;
                flow[e^1] -= df;
                return df;
            }
        }
    }
    return 0;
}

LL dinitz() {
    LL ret = 0;
    int df;
    while(bfs()) {
        for(int i=1; i<=nNode; i++) pro[i] = fin[i];
        while(true) {
            df = dfs(src, INF);
            if(df) ret += (LL)df;
            else break;
        }
    }
    return ret;
}
